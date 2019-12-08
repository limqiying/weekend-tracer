#ifndef CAMERA_H
#define CAMERA_H

#include <Eigen/Dense>

#include "ray.h"

class Camera 
{
    Eigen::Vector3f origin, lower_left_corner, horizontal, vertical;
    Eigen::Vector3f u, w, v;
    float lens_radius;
    
    public:
        Camera(Eigen::Vector3f, Eigen::Vector3f, Eigen::Vector3f, float, float, float, float);
        Ray get_ray(float, float);

        ~Camera();
};

#endif /* CAMERA_H */