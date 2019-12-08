#ifndef CAMERA_H
#define CAMERA_H

#include <Eigen/Dense>

#include "ray.h"

class Camera 
{
    public:
        Camera(Eigen::Vector3f, Eigen::Vector3f, Eigen::Vector3f, float, float);
        Ray get_ray(float, float);
        Eigen::Vector3f origin;
        Eigen::Vector3f lower_left_corner;
        Eigen::Vector3f horizontal;
        Eigen::Vector3f vertical;

        ~Camera();
};

#endif /* CAMERA_H */