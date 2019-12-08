#include "material.h"

#include <iostream>

#include "utils.h"

using namespace Eigen;

/*
* Methods for Lambertian class
*/

Lambertian::Lambertian(const Vector3f& a): albedo(a) {}

bool Lambertian::scatter(const Ray& r_in, const HitRecord &rec, Vector3f& attenuation, Ray& scattered) const {
    Vector3f target = rec.p + rec.normal + random_in_unit_sphere();
    scattered = Ray(rec.p, target - rec.p);
    attenuation = albedo;
    return true;
}

Lambertian::~Lambertian() {}

/*
* Methods for Metal class
*/

Metal::Metal(const Vector3f &a): albedo(a), fuzz(0.0f) {}

Metal::Metal(const Vector3f&a, float f): albedo(a) {
    if (f < 1 && f > 0) 
        fuzz = f; 
    else 
        fuzz = 0.0f;
}

bool Metal::scatter(const Ray& r_in, const HitRecord &rec, Vector3f& attenuation, Ray& scattered) const {
    Vector3f reflected = reflect(r_in.direction().normalized(), rec.normal);
    scattered = Ray(rec.p, reflected + fuzz * random_in_unit_sphere());
    attenuation = albedo;
    return scattered.direction().dot(rec.normal) > 0;
}

Metal::~Metal() {}