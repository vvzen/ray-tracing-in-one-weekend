#ifndef SPHEREH
#define SPHEREH

#include "hittable.h"

class sphere: public hittable {

    public:

        vec3 center;
        float radius;

        sphere(){}
        sphere(vec3 c, float r) : center(c), radius(r) {};

        virtual bool hit(
            const ray &r, float t_min, float t_max, hit_record &rec
        ) const;
};


bool sphere::hit(const ray &r, float t_min, float t_max, hit_record &rec) const {

    vec3 offset_center = r.origin() - center;

    float a = dot(r.direction(), r.direction());
    float b = dot(offset_center, r.direction());
    float c = dot(offset_center, offset_center) - radius * radius;

    float discriminant = b * b - a * c;

    if (discriminant > 0){
        float temp = (-b - sqrt(discriminant)) / a;
        if (temp > t_min && temp < t_max){
            rec.t = temp;
            rec.pos = r.point_at_parameter(rec.t);
            rec.N = (rec.pos - center) / radius;
            return true;
        }

        temp = (-b + sqrt(discriminant)) / a;
        if (temp > t_min && temp < t_max) {
            rec.t = temp;
            rec.pos = r.point_at_parameter(rec.t);
            rec.N = (rec.pos - center) / radius;
            return true;
        }
    }
    return false;
}

#endif