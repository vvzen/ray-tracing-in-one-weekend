#ifndef RAY_H
#define RAY_H

#include <math.h>
#include <iostream>
#include <stdlib.h>

#include "vec3.h"

class ray {

    public:

        ray(){}

        vec3 A, B;

        ray(const vec3 &a, const vec3 &b){
            A = a;
            B = b;
        }

        vec3 origin() const{
            return A;
        }

        vec3 direction() const{
            return B;
        }

        vec3 point_at_parameter(float t) const {
            return A + t * B;
        }

};


#endif