#ifndef CAMERA_H
#define CAMERA_H

#include <Eigen/Dense>

#include "ray.h"

class Camera 
{
    public:
        Camera();
        Ray get_ray(float u, float v);
        Eigen::Vector3f origin;
        Eigen::Vector3f lower_left_corner;
        Eigen::Vector3f horizontal;
        Eigen::Vector3f vertical;

        ~Camera();
};

#endif /* CAMERA_H */