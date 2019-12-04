#ifndef SPHEREH
#define SPHEREH

#include "hitable.h"

class sphere: public hitable 
{
    public:
        sphere() {}
        sphere(Eigen::Vector3f c, float r): center(c), radius(r) {};
        virtual bool hit(const ray &r, float tmin, float tmax, hit_record &rec) const;
        Eigen::Vector3f center;
        float radius;
};

#endif /* SPHEREH */