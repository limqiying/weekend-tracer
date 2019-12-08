#ifndef HITABLE_H
#define HITABLE_H

#include <Eigen/Dense>

#include "ray.h"

class Material;

struct HitRecord 
{
    float t;
    Eigen::Vector3f p;
    Eigen::Vector3f normal;  
    Material *mat_ptr;
};

class Hitable 
{
    public: 
        virtual bool hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const = 0;
};

class Sphere: public Hitable 
{
    public:
        Sphere();
        Sphere(Eigen::Vector3f c, float r, Material* m);
        bool hit(const Ray &r, float tmin, float tmax, HitRecord &rec) const;
        Eigen::Vector3f center;
        float radius;
        Material* mat;
        ~Sphere();
};

class HitableList: public Hitable 
{
    public:
         HitableList();
         HitableList(Hitable **l, int n);
         bool hit(const Ray& r, float tmin, float tmax, HitRecord &rec) const;
         Hitable **list;
         int list_size;
         ~HitableList();
};

#endif /* HITABLE_H */