#ifndef SPHEREH
#define SPHEREH

#include "hitable.h"
#include "material.h"

class sphere: public hitable 
{
    public:
        sphere() {}
        sphere(Eigen::Vector3f c, float r, material* m): center(c), radius(r), mat(m){};
        virtual bool hit(const ray &r, float tmin, float tmax, hit_record &rec) const;
        Eigen::Vector3f center;
        float radius;
        material* mat;
};

#endif /* SPHEREH */