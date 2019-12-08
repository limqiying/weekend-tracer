#include <iostream>
#include <fstream>

#include <Eigen/Dense>
#include "float.h"

#include "hitable.h"
#include "camera.h"
#include "utils.h"
#include "material.h"

using namespace std; using namespace Eigen;

inline Vector3f lowAttenuation() {
    // each component of the vector is > 0.5
    return Vector3f(0.5 * (1 + getRandom()), 0.5 * (1 + getRandom()), 0.5 * (1 + getRandom()));
}

inline Vector3f highAttenuation() {
    return Vector3f(getRandom() * getRandom(), getRandom() * getRandom(), getRandom() * getRandom());
}

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

Hitable* randomScene() {
    std::cout << "Generating random scene" << std::endl;

    int n = 500;
    Hitable **list = new Hitable *[n+1];
    list[0] = new Sphere(Vector3f(0, -1000, 0), 1000, new Lambertian(Vector3f(0.5, 0.5, 0.5)));
    int i = 1;
    for (int x=-11; x<11; x++) {
        for (int z=-11; z<11; z++) {
            float chooseMaterial = getRandom();
            Vector3f center(x + 0.9 * getRandom(), 0.2, z + 0.9 + getRandom());
            if (chooseMaterial < 0.8) { // use diffuse material
                list[i++] = new Sphere(center, 0.2, new Lambertian(highAttenuation()));
            } else if (chooseMaterial < 0.95) { // use metal
                list[i++] = new Sphere(center, 0.2, new Metal(lowAttenuation(), 0.5 * getRandom()));
            } else { // glass
                list[i++] = new Sphere(center, 0.2, new Dielectric(1.5));
            }
        }
    }
    list[i++] = new Sphere(Vector3f(0, 1, 0), 1.0, new Dielectric(1.5));
    list[i++] = new Sphere(Vector3f(-4, 1, 0), 1.0, new Lambertian(Vector3f(0.4, 0.2, 0.1)));
    list[i++] = new Sphere(Vector3f(4.0, 1.0, 0), 1.0, new Metal(Vector3f(0.7, 0.6, 0.5), 0.0f));
     
    std::cout << "Done generating random scene" << std::endl;
    
    return new HitableList(list, i);
}

int main() 
{
    ofstream imageFile;
    imageFile.open("output.ppm");

	int nx = 500;
    int ny = 250;
    int ns = 100; // number of samples per pixel
    
    imageFile << "P3\n" << nx << " "<< ny << "\n255\n";

    // create the world of hitables
    // Hitable *list[5];
    // list[0] = new Sphere(Vector3f(0, 0, -1), 0.5, new Lambertian(Vector3f(0.8, 0.3, 0.3)));
    // list[1] = new Sphere(Vector3f(0, -100.5, -1.0), 100, new Lambertian(Vector3f(0.8, 0.8, 0.0)));
    // list[2] = new Sphere(Vector3f(1, 0, -1), 0.5, new Metal(Vector3f(0.8, 0.6, 0.2), 0.0f));
    // list[3] = new Sphere(Vector3f(-1, 0, -1), 0.5, new Dielectric(1.5));
    // list[4] = new Sphere(Vector3f(-1, 0, -1), -0.45, new Dielectric(1.5));
    // Hitable *world = new HitableList(list, 5);
    Hitable *world = randomScene();

    Vector3f lookFrom(3.0f, 3.0f, 2.0f);
    Vector3f lookAt(0.0f, 0.0f, -1.0f);
    float distToFocus = (lookFrom - lookAt).norm();
    Camera cam(lookFrom, 
            lookAt, 
            Vector3f(0.0f, 1.0f, 0.0f), // up vector
            80.0f, // vertical field of view
            float(nx)/float(ny),   // aspect ratio
            2.0f, // aperture
            distToFocus);

    for (int z = ny-1; z >= 0; z--) {
        for (int x=0; x < nx; x++) {

            Vector3f col(0, 0, 0);
            // #pragma omp for
            for (int s=0; s < ns; s++) {
                float u = float(x + getRandom()) / float(nx);
                float v = float(z+ getRandom()) / float(ny);
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