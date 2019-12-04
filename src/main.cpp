#include <iostream>
#include <fstream>
#include <random>

#include <Eigen/Dense>

#include "sphere.h"
#include "hitable_list.h"
#include "float.h"
#include "camera.h"


using namespace std; using namespace Eigen;

Vector3f color(const ray& r, hitable *world) 
{
    hit_record rec;
    if (world->hit(r, 0.0, MAXFLOAT, rec)) {
        return 0.5 * (rec.normal + Vector3f::Ones());
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

            int ir = int (255.99 * col[0]);
            int ig = int (255.99 * col[1]);
            int ib = int (255.99 * col[2]);

            imageFile << ir << " " << ig << " " << ib << "\n";
        }
    }
    imageFile.close();
 }