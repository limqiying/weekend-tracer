#include "sphere.h"


using namespace Eigen;

bool sphere::hit (const ray& r, float t_min, float t_max, hit_record &rec) const 
{
    Vector3f oc = r.origin() - center;
    float a = r.direction().dot(r.direction());
    float b = oc.dot(r.direction());
    float c = oc.dot(oc) - radius * radius;
    float discriminant = b * b - a * c;
    if (discriminant > 0) {
        float temp =  (- b - sqrt(discriminant)) / a;
        if (!(temp < t_max && temp > t_min)) {
            temp =  (- b + sqrt(discriminant)) / a;
            if (!(temp < t_max && temp > t_min)) {
                return false;    
            }
        }
        rec.t = temp;
        rec.p = r.point_at_parameter(rec.t);
        rec.normal = (rec.p - center) / radius;
        return true;
    }
    return false;
}