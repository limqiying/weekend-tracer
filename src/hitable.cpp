#include "hitable.h"

using namespace Eigen;

/*
* Methods for Sphere class
*/

Sphere::Sphere() {}

Sphere::Sphere(Vector3f c, float r, Material* m): center(c), radius(r), mat(m) {}

bool Sphere::hit (const Ray& r, float t_min, float t_max, HitRecord &rec) const 
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
        rec.mat_ptr = mat;
        return true;
    }
    return false;
}

Sphere::~Sphere() {}

/*
* Methods for HitableList class
*/

HitableList::HitableList() {}

HitableList::HitableList(Hitable **l, int n): list(l), list_size(n) {}

bool HitableList::hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const 
{
    HitRecord temp_rec;
    bool hit_anything = false;
    double closest_so_far = t_max;
    for (int i=0; i<list_size; i++) {
        if (list[i]->hit(r, t_min, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }
    return hit_anything;
}

HitableList::~HitableList() {}