#ifndef UTILS_H
#define UTILS_H

#include <random>

#include <Eigen/Dense>

// create random number generator between [0, 1)
static std::random_device rd;
static std::mt19937 gen(rd());
static std::uniform_real_distribution<> dis(0, 1); //uniform distribution between 0 and 1

static float getRandom() {
    return dis(gen);
}

static Eigen::Vector3f random_in_unit_sphere()
{
    /*
    * returns a random point that falls in a unit sphere centered at (0, 0, 0)
    */
   Eigen::Vector3f p;
   do {
       // p falls in the square of length [-1, 1] ^ 3
       p = 2.0 * Eigen::Vector3f(getRandom(), getRandom(), getRandom()) - Eigen::Vector3f::Ones();
   } while (p.dot(p) >= 1.0);
   return p;
}

/*
* When the ray is in the material with the higher refractive index, there is no solution to Snell's law, and no
* refraction is possible. (Total internal reflection)This ffunction checks if refraction is possible, 
* and outputs the refracted ray if this is so. Otherwise, it returns false
*/
static bool refract(const Eigen::Vector3f& v, const Eigen::Vector3f& n, float ni_over_nt, Eigen::Vector3f& refracted) {
    // Snell's law states that n * sin(theta) = n' * sin(theta')
    Eigen::Vector3f unitV = v.normalized();
    float dt = unitV.dot(n);    
    float discriminant = 1.0f - ni_over_nt * ni_over_nt * (1.0f - dt * dt);
    if (discriminant > 0.0f) {
        refracted = ni_over_nt * (unitV - n * dt)  - n * sqrt(discriminant);
        return true;
    } else {
        return false;
    }
}

/*
* Polynomial apprxoimation that gives glass reflectivity that varies with angle -- by Christophe Schlick
*/
inline static float schlick(float cosine, float refractiveIndex) {
    float r0 = (1 - refractiveIndex) / (1 + refractiveIndex);
    r0 = r0 * r0;
    return r0 + (1 - r0) * pow((1 - cosine), 5);
}

inline static Eigen::Vector3f reflect(const Eigen::Vector3f& v, const Eigen::Vector3f& n) {
    return v - 2 * v.dot(n) * n;
}

#endif /* UTILS_H */