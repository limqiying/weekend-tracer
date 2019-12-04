#ifndef HITABLEH
#define HITABLEH

#include "ray.h"
#include <Eigen/Dense>

struct hit_record 
{
    float t;
    Eigen::Vector3f p;
    Eigen::Vector3f normal;  
};

class hitable 
{
    public: 
        virtual bool hit(const ray& r, float t_min, float t_max, hit_record&rec) const = 0;
};

#endif /* HITABLEH */