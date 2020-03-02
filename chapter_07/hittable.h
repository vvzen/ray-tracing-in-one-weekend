#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

struct hit_record {
    float t;
    vec3 pos;
    vec3 N;
};


class hittable {

    public:

        virtual bool hit(
            const ray &r, float t_min, float t_max, hit_record &rec
        ) const = 0; // the const = 0 specifies that this is a pure virtual function

};


#endif