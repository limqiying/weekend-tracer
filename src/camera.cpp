#include "camera.h"

Camera::Camera():   lower_left_corner(Eigen::Vector3f(-2.0, -1.0, -1.0)), 
                    horizontal(Eigen::Vector3f(4.0, 0.0, 0.0)), 
                    vertical(Eigen::Vector3f(0.0, 2.0, 0.0)), 
                    origin(Eigen::Vector3f(0.0, 0.0, 0.0)) {}

Ray Camera::get_ray(float u, float v) {
    return Ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
}

Camera::~Camera() {}