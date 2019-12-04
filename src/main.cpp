#include <iostream>
#include <fstream>
#include "ray.h"
#include <Eigen/Dense>


using namespace std; using namespace Eigen;

Vector3f color(const ray& r) {
    /*
    * Linearly interpolates blue and white, depending on the
    * y-direction value of the ray
    */
    Vector3f unit_direction = r.direction().normalized();
    float t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * Vector3f::Ones() + t * Vector3f(0.5, 0.7, 1.0);
}

int main() {
    ofstream imageFile;
    imageFile.open("output.ppm");

	int nx = 200;
    int ny = 100;
    
    imageFile << "P3\n" << nx << " "<< ny << "\n255\n";

    Vector3f lower_left_corner(-2.0, -1.0, -1.0);   // the lower left hand cordiner of the 200 x 100 image
    Vector3f horizontal(4.0, 0.0, 0.0); // the horizontal extents of the image
    Vector3f vertical(0.0, 2.0, 0.0);   // the vertical extents of the image
    Vector3f origin(0.0, 0.0, 0.0); // the origin of the camera location
    
    for (int j = ny-1; j >= 0; j--) {
        for (int i=0; i < nx; i++) {

            float u = float(i) / float(nx);
            float v = float(j) / float(ny);

            // the ray direction here is not normalized for simpler and faster code
            ray r(origin, lower_left_corner + u * horizontal + v * vertical);
            Vector3f col = color(r);

            int ir = int (255.99 * col[0]);
            int ig = int (255.99 * col[1]);
            int ib = int (255.99 * col[2]);

            imageFile << ir << " " << ig << " " << ib << "\n";
        }
    }
    imageFile.close();
 }