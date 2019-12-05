#include <iostream>
#include <fstream>
#include <random>

#include <Eigen/Dense>

#include "sphere.h"
#include "hitable_list.h"
#include "float.h"
#include "camera.h"
#include "utils.h"


using namespace std; using namespace Eigen;

Vector3f color(const ray& r, hitable *world) 
{
    hit_record rec;
    // do an offset from tmin = 0 to avoid reflection detected off reflected surfaces
    if (world->hit(r, 0.001, MAXFLOAT, rec)) {
        Vector3f target = rec.p + rec.normal + random_in_unit_sphere();
        // reflect the ray off the hit point in direction from hitpoint to the randomly picked target
        // multiply by 0.5 as spheres only absort half the energy on each bounce
        return 0.5 * color(ray(rec.p, target - rec.p), world);
    } else {
        Vector3f unit_direction = r.direction().normalized();
        float t = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - t) * Vector3f::Ones() + t * Vector3f(0.5, 0.7, 1.0);
    }
}

int main() 
{
    ofstream imageFile;
    imageFile.open("output.ppm");

	int nx = 200;
    int ny = 100;
    int ns = 100; // number of samples per pixel
    
    imageFile << "P3\n" << nx << " "<< ny << "\n255\n";

    Vector3f lower_left_corner(-2.0, -1.0, -1.0);   // the lower left hand cordiner of the 200 x 100 image
    Vector3f horizontal(4.0, 0.0, 0.0); // the horizontal extents of the image
    Vector3f vertical(0.0, 2.0, 0.0);   // the vertical extents of the image
    Vector3f origin(0.0, 0.0, 0.0); // the origin of the camera location

    // create the world of hitables
    hitable *list[2];
    list[0] = new sphere(Vector3f(0, 0, -1), 0.5);
    list[1] = new sphere(Vector3f(0, -100.5, -1.0), 100);
    hitable *world = new hitable_list(list, 2);

    // create the camera
    camera cam;

    // create random number generator between [0, 1)
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 1); //uniform distribution between 0 and 1
    
    for (int j = ny-1; j >= 0; j--) {
        for (int i=0; i < nx; i++) {

            Vector3f col(0, 0, 0);
            for (int s=0; s < ns; s++) {
                float u = float(i + dis(gen)) / float(nx);
                float v = float(j+ dis(gen)) / float(ny);
                
                ray r = cam.get_ray(u, v);
                col += color(r, world);
            }
            col /= float(ns);
            // gamma2 (raise color to power 1/2)
            col = Vector3f(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
            int ir = int (255.99 * col[0]);
            int ig = int (255.99 * col[1]);
            int ib = int (255.99 * col[2]);

            imageFile << ir << " " << ig << " " << ib << "\n";
        }
    }
    imageFile.close();
 }