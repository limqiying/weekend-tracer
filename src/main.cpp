#include <iostream>
#include <fstream>

#include <Eigen/Dense>
#include "float.h"

#include "hitable.h"
#include "camera.h"
#include "utils.h"
#include "material.h"

using namespace std; using namespace Eigen;

Vector3f color(const Ray& r, Hitable *world, int depth) 
{
    HitRecord rec;
    // do an offset from tmin = 0 to avoid reflection detected off reflected surfaces
    if (world->hit(r, 0.001, MAXFLOAT, rec)) {
        Ray scattered;
        Vector3f attenuation;
        if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
            return attenuation.cwiseProduct(color(scattered, world, depth+1));
        } else {
            return Vector3f::Zero();
        }
        Vector3f target = rec.p + rec.normal + random_in_unit_sphere();
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

    // create the world of hitables
    Hitable *list[5];
    list[0] = new Sphere(Vector3f(0, 0, -1), 0.5, new Lambertian(Vector3f(0.8, 0.3, 0.3)));
    list[1] = new Sphere(Vector3f(0, -100.5, -1.0), 100, new Lambertian(Vector3f(0.8, 0.8, 0.0)));
    list[2] = new Sphere(Vector3f(1, 0, -1), 0.5, new Metal(Vector3f(0.8, 0.6, 0.2), 0.3));
    list[3] = new Sphere(Vector3f(-1, 0, -1), 0.5, new Dielectric(1.5));
    list[4] = new Sphere(Vector3f(-1, 0, -1), -0.45, new Dielectric(1.5));
    Hitable *world = new HitableList(list, 5);

    // Hitable *list[2];
    // float R = cos(M_PI / 4);
    // list[0] = new Sphere(Vector3f(-R, 0, -1), R, new Lambertian(Vector3f(0.8, 0.3, 0.3)));
    // list[1] = new Sphere(Vector3f(R, 0, -1), R, new Lambertian(Vector3f(0.8, 0.8, 0.0)));
    // Hitable *world = new HitableList(list, 2);

    Camera cam(Vector3f(-2, 2, 1), Vector3f(0, 0, -1), Vector3f(0, 1, 0), 45, float(nx)/float(ny));

    for (int j = ny-1; j >= 0; j--) {
        for (int i=0; i < nx; i++) {

            Vector3f col(0, 0, 0);
            for (int s=0; s < ns; s++) {
                float u = float(i + getRandom()) / float(nx);
                float v = float(j+ getRandom()) / float(ny);
                Ray r = cam.get_ray(u, v);
                col += color(r, world, 0);
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