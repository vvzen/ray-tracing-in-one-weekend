#ifndef VEC3H
#define VEC3H


#include <math.h>
#include <iostream>
#include <stdlib.h>


class vec3 {
   public:
    float e[3];

    vec3() {}

    vec3(float x, float y, float z) {
        e[0] = x;
        e[1] = y;
        e[2] = z;
    }

    // See https://stackoverflow.com/questions/3141087/what-is-meant-with-const-at-end-of-function-declaration
    // to understand what the const after the function declaration means
    inline float x() const { return e[0]; }
    inline float y() const { return e[1]; }
    inline float z() const { return e[2]; }

    inline float r() const { return e[0]; }
    inline float g() const { return e[1]; }
    inline float b() const { return e[2]; }

    // Operators overloading
    inline const vec3 &operator+() const {
        return *this;
    }

    inline vec3 operator-() const {
        return vec3(-e[0], -e[1], -e[2]);
    }

    inline float operator[](int i) const {
        return e[i];
    }

    inline float& operator[](int i) {
        return e[i];
    }

    // Vector operations
    inline vec3 operator+=(const vec3 &v2);
    inline vec3 operator-=(const vec3 &v2);
    inline vec3 operator*=(const vec3 &v2);
    inline vec3 operator/=(const vec3 &v2);

    // Scalar operations
    inline vec3 operator*=(const float t);
    inline vec3 operator/=(const float t);

    inline float length() {
        return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
    }

    inline float squared_length() {
        return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
    }

    inline void make_unit_vector();

};

inline std::istream& operator>>(std::istream &is, vec3 &v){
    is >> v.e[0] >> v.e[1] >> v.e[2];
    return is;
}

inline std::ostream& operator>>(std::ostream &os, vec3 &v){
    os << v.e[0] << " " << v.e[1] << " " << v.e[2];
    return os;
}

inline void vec3::make_unit_vector(){
    float k = 1.0 / sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
    e[0] *= k;
    e[1] *= k;
    e[2] *= k;
}

inline vec3 operator+(const vec3 &v1, const vec3 &v2) {
    return vec3(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
}

inline vec3 operator-(const vec3 &v1, const vec3 &v2) {
    return vec3(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
}

inline vec3 operator*(const vec3 &v1, const vec3 &v2) {
    return vec3(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
}

inline vec3 operator*(const vec3 &v1, const float t) {
    return vec3(t * v1.e[0], t * v1.e[1], t * v1.e[2]);
}

inline vec3 operator*(const float t, const vec3 &v1) {
    return vec3(t * v1.e[0], t * v1.e[1], t * v1.e[2]);
}

inline vec3 operator/(const vec3 &v1, const vec3 &v2) {
    return vec3(v1.e[0] / v2.e[0], v1.e[1] / v2.e[1], v1.e[2] / v2.e[2]);
}

inline vec3 operator/(const vec3 &v1, const float t) {
    return vec3(t / v1.e[0], t / v1.e[1], t / v1.e[2]);
}

inline vec3 operator/(const float t, const vec3 &v1) {
    return vec3(t / v1.e[0], t / v1.e[1], t / v1.e[2]);
}

// Vector operations
inline float dot(const vec3 &v1, const vec3 &v2){
    return v1.e[0] * v2.e[0]
         + v1.e[1] * v2.e[1]
         + v1.e[2] * v2.e[2];
}

inline vec3 cross(const vec3 &v1, const vec3 &v2){
    return vec3(v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1],
                v1.e[2] * v2.e[0] - v1.e[0] * v2.e[2],
                v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]);
}

// Element wise operations
inline vec3 vec3::operator+=(const vec3 &v2){
    return vec3(this->e[0] += v2.e[0],
                this->e[1] += v2.e[1],
                this->e[2] += v2.e[2]);
}

inline vec3 vec3::operator-=(const vec3 &v2){
    return vec3(this->e[0] -= v2.e[0],
                this->e[1] -= v2.e[1],
                this->e[2] -= v2.e[2]);
}

inline vec3 vec3::operator*=(const vec3 &v2){
    return vec3(this->e[0] *= v2.e[0],
                this->e[1] *= v2.e[1],
                this->e[2] *= v2.e[2]);
}

inline vec3 vec3::operator/=(const vec3 &v2){
    return vec3(this->e[0] /= v2.e[0],
                this->e[1] /= v2.e[1],
                this->e[2] /= v2.e[2]);
}

inline vec3 vec3::operator*=(const float t){
    this->e[0] *= t;
    this->e[1] *= t;
    this->e[2] *= t;
    return *this;
}

inline vec3 vec3::operator/=(const float t){
    // Multiplication is faster than division
    float k = 1.0f / t;
    this->e[0] *= k;
    this->e[1] *= k;
    this->e[2] *= k;
    return *this;
}

inline vec3 unit_vector(vec3 v) {
    return v / v.length();
}

#endif