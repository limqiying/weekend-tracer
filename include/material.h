#ifndef MATERIAL_H
#define MATERIAL_H

#include <Eigen/Dense>

#include "hitable.h"
#include "utils.h"

class Material {
    public:
        virtual bool scatter(const Ray& r_in, const HitRecord& rec, Eigen::Vector3f& attentuation, Ray& scattered) const = 0;
};

class Lambertian : public Material {
    public:
        Lambertian(const Eigen::Vector3f& a);
        bool scatter(const Ray& r_in, const HitRecord &rec, Eigen::Vector3f& attenuation, Ray& scattered) const;
        Eigen::Vector3f albedo;
        ~Lambertian();
};

class Metal: public Material {
    public:
        Metal(const Eigen::Vector3f &a);
        Metal(const Eigen::Vector3f &a, float f);
        bool scatter(const Ray& r_in, const HitRecord &rec, Eigen::Vector3f& attenuation, Ray& scattered) const;
        Eigen::Vector3f albedo;
        float fuzz;
        ~Metal();
};

#endif /* MATERIAL_H */