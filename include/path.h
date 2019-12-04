#ifndef RAYH
#def RAYH
#include <Eigen/Dense>

class ray
{
    public:
    ray() {}
    ray(const Eigen::Vector3f&a, const Eigen::Vector3f b): A(a), B(b) {};
    Eigen::Vector3f origin() const { return A; }
    Eigen::Vector3f direction() const { return B; }
    Eigen::Vector3f point_at_parameter(float t) const {return A + t * B};

    Eigen::Vector3f A;
    Eigen::Vector3f B;
}

#endif