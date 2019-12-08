#ifndef RAY_H
#define RAY_H
#include <Eigen/Dense>

class Ray
{
    public:
        Ray() {}
        Ray(const Eigen::Vector3f&a, const Eigen::Vector3f b): o(a), d(b) {}
        Eigen::Vector3f origin() const { return o; }
        Eigen::Vector3f direction() const { return d; }
        Eigen::Vector3f point_at_parameter(float t) const { return o + t * d; }

        Eigen::Vector3f o;
        Eigen::Vector3f d;
};

#endif /*RAY_H*/