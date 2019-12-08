#include "camera.h"

using namespace Eigen;

Camera::Camera(Vector3f lookFrom, Vector3f lookAt, Vector3f up, float verticalFOV, float aspect) {
    Vector3f u, w, v; // specify the coordinate system for the camera

    float theta = verticalFOV / 180 * M_PI;
    float halfHeight = tan(theta / 2);
    float halfWidth = aspect * halfHeight;

    w = (lookFrom - lookAt).normalized();   // vector from target to eye
    u = (up.cross(w)).normalized(); // vector perpendicular to up vector and lookAt vector
    v = w.cross(u); // up vector

    origin = lookFrom;
    lower_left_corner = origin - halfWidth * u - halfHeight * v - w;
    horizontal = 2 * halfWidth * u;
    vertical = 2 * halfHeight * v;
}   

Ray Camera::get_ray(float u, float v) {
    return Ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
}

Camera::~Camera() {}