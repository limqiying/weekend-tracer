#ifndef HITABLEH
#define HITABLEH

#include "ray.h"
#include <Eigen/Dense>

class material;

struct hit_record 
{
    float t;
    Eigen::Vector3f p;
    Eigen::Vector3f normal;  
    material *mat_ptr;
};

class hitable 
{
    public: 
        virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
};

#endif /* HITABLEH */