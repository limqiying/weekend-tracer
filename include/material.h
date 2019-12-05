#ifndef MATERIALH
#define MATERIALH

#include <Eigen/Dense>
#include "hitable.h"
#include "utils.h"

class material 
{
    public:
        virtual bool scatter(const ray& r_in, const hit_record& rec, Eigen::Vector3f attentuation, ray& scattered) const = 0;
};

class lambertian : public material 
{
    public:
        lambertian(const Eigen::Vector3f& a): albedo(a) {}

        virtual bool scatter(const ray& r_in, const hit_record &rec, Eigen::Vector3f attenuation, ray& scattered) const {
            Eigen::Vector3f target = rec.p + rec.normal + random_in_unit_sphere();
            scattered = ray(rec.p, target - rec.p);
            attenuation = albedo;
            return true;
        }

        Eigen::Vector3f albedo;

}

class metal: public material
{
    public:
        metal(const Eigen::Vector3f &a): albedo(a) {}

        virtual bool scatter(const ray& r_in, const hit_record &rec, Eigen::Vector3f attenuation, ray& scattered) const {
            Eigen::Vector3f reflected = reflect(r_in.direction().normalized(), rec.normal);
            scattered = ray(rec.p, reflected);
            attenuation = albedo;
            return scattered.direction().dot(rec.normal) > 0;
        }

        Eigen::Vector3f albedo;

    private:
        Eigen::Vector3f reflect(const Eigen::Vector3f& v, const Eigen::Vector3f& n) {
            return v - 2 * v.dot(n) * n;
        }
}

#endif /* MATERIALH */