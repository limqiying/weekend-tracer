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

/*
* Methods for Dielectric class
*/

Dielectric::Dielectric(float ri): refractionIndex(ri) {}

bool Dielectric::scatter(const Ray& r_in, const HitRecord &rec, Eigen::Vector3f& attenuation, Ray& scattered) const {
    Vector3f outwardNormal;
    float ni_over_nt, cosine, reflectProbability;
    Vector3f refracted;
    Vector3f reflected = reflect(r_in.direction(), rec.normal);
    attenuation = Vector3f(1.0f, 1.0f, 1.0f);

    if (r_in.direction().dot(rec.normal) > 0) {
        // when the ray is exiting from the material
        outwardNormal = -rec.normal;
        ni_over_nt = refractionIndex;
        cosine = refractionIndex * r_in.direction().dot(rec.normal) / r_in.direction().norm();
    } else {
        // when the ray is entering the material
        outwardNormal = rec.normal;
        ni_over_nt = 1.0f / refractionIndex;
        cosine = -r_in.direction().dot(rec.normal) / r_in.direction().norm();
    }

    // if there is no total internal reflection, return the refracted ray
    // otherwise, return the reflected ray
    if (refract(r_in.direction(), outwardNormal, ni_over_nt, refracted)) {
        reflectProbability = schlick(cosine, refractionIndex);
    } else {
        reflectProbability = 1.0f;
    }

    // randomly decides if ray gets scattered or refracted
    if (getRandom() < reflectProbability) {
        scattered = Ray(rec.p, reflected);
    } else {
        scattered = Ray(rec.p, refracted);

    }
    return true;

}

Dielectric::~Dielectric() {}