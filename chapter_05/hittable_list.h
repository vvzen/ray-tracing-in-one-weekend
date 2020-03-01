#ifndef HITTABLELISTH
#define HITTABLELISTH

#include "hittable.h"

class hittable_list: public hittable {

    public:

        hittable **list; // pointer to a pointer
        int list_size;

        hittable_list(){}
        hittable_list(hittable **l, int n){
            list = l;
            list_size = n;
        }

        virtual bool hit(
            const ray &r, float t_min, float t_max, hit_record &rec
        ) const;
};

bool hittable_list::hit(const ray &r, float t_min, float t_max, hit_record &rec) const {

    hit_record temp_record;
    bool hit_anything = false;
    double closest_so_far = t_max;

    // Loop through all the elements
    // and put in the hit record the closest element
    for (int i = 0; i < list_size; i++){
        if (list[i]->hit(r, t_min, closest_so_far, temp_record)){
            hit_anything = true;
            closest_so_far = temp_record.t;
            rec = temp_record;
        }
    }

    return hit_anything;
}

#endif