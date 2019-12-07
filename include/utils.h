#ifndef UTILSH
#define UTILSH

#include <random>
#include <Eigen/Dense>

Eigen::Vector3f random_in_unit_sphere()
{
    /*
    * returns a random point that falls in a unit sphere centered at (0, 0, 0)
    */
   Eigen::Vector3f p;
   // create random number generator between [0, 1)
   std::random_device rd;
   std::mt19937 gen(rd());
   std::uniform_real_distribution<> dis(0, 1); //uniform distribution between 0 and 1
   do {
       // p falls in the square of length [-1, 1] ^ 3
       p = 2.0 * Eigen::Vector3f(dis(gen), dis(gen), dis(gen)) - Eigen::Vector3f::Ones();
   } while (p.dot(p) >= 1.0);
   return p;
}

Eigen::Vector3f reflect(const Eigen::Vector3f& v, const Eigen::Vector3f& n) {
    return v - 2 * v.dot(n) * n;
}

#endif /* UTILSH */