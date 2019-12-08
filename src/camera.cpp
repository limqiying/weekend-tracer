#include "camera.h"
#include "utils.h"

using namespace Eigen;

Camera::Camera(Vector3f lookFrom, Vector3f lookAt, Vector3f up, 
        float verticalFOV, float aspect, 
        float aperture, float focusDistance): lens_radius(aperture / 2.0f) {

    float theta = verticalFOV / 180 * M_PI;
    float halfHeight = tan(theta / 2);
    float halfWidth = aspect * halfHeight;

    w = (lookFrom - lookAt).normalized();   // vector from target to eye
    u = (up.cross(w)).normalized(); // vector perpendicular to up vector and lookAt vector
    v = w.cross(u); // up vector

    origin = lookFrom;
    lower_left_corner = origin - halfWidth * focusDistance * u - halfHeight * focusDistance * v - w * focusDistance;
    horizontal = 2 * halfWidth * focusDistance * u;
    vertical = 2 * halfHeight * focusDistance * v;
}   

Ray Camera::get_ray(float s, float t) {
    // for each pixel, shoot a bunch of rays out of the lens that hits the particular
    // focal point determined by the focal distance, where the rays are offset
    // randomly
    Vector3f randomPointInLens = lens_radius * random_in_unit_sphere();
    Vector3f offset = randomPointInLens.x() * u + randomPointInLens.y() * v;
    return Ray(origin + offset, lower_left_corner + s * horizontal + t * vertical - origin - offset);
}

Camera::~Camera() {}