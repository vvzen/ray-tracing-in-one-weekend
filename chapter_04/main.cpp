#include <fstream>
#include <iostream>
#include <random>

#include "ray.h"
#include "vec3.h"

bool hit_sphere(const vec3 &center, float radius, const ray &r){
    vec3 offset_center = r.origin() - center;

    float a = dot(r.direction(), r.direction());
    float b = 2.0 * dot(offset_center, r.direction());
    float c = dot(offset_center, offset_center) - radius * radius;

    float discriminant = b * b - 4 * a * c;

    // std::cout << "discriminant: " << discriminant << std::endl;

    return (discriminant > 0);
}

vec3 color(const ray &r) {

    // If the ray touches the sphere, use sphere_color
    vec3 sphere_origin = vec3(0.0, 0.25, -1.0);
    if (hit_sphere(sphere_origin, 0.25, r)){
        vec3 sphere_color = vec3(1, 0.996, 0.841);
        return sphere_color;
    }

    vec3 unit_direction = unit_vector(r.direction());
    float t = 0.5 * (unit_direction.y() + 1.0);

    vec3 start_col = vec3(0.725, 0.094, 0.698);
    vec3 end_col = vec3(0.952, 0.662, 0.349);

    // Linear interpolation, when t=0 I want start_col, when t=1 I want end_col
    vec3 blended_value = (1.0 - t) * start_col + t * end_col;
    return blended_value;
}

void write_ppm_header(int ncols, int nrows, int maxvalue, std::ofstream &f) {
    f << "P3" << std::endl;
    f << ncols << " " << nrows << std::endl;
    f << maxvalue << std::endl;
}

void write_ppm_num(vec3 c, std::ofstream &f) {
    int i_r = int(255.99 * c.r());
    int i_g = int(255.99 * c.g());
    int i_b = int(255.99 * c.b());

    f << std::to_string(i_r) << " ";
    f << std::to_string(i_g) << " ";
    f << std::to_string(i_b);
}

int main() {
    std::ofstream image_file;
    image_file.open("chapter_04.ppm");

    int width = 512;
    int height = 256;
    write_ppm_header(width, height, 255, image_file);

    vec3 lower_left_corner(-2.0, -1.0, -1.0);
    vec3 horizontal(4.0, 0.0, 0.0);
    vec3 vertical(0.0, 2.0, 0.0);
    vec3 origin(0.0, 0.0, 0.0);

    for (int j = height - 1; j >= 0; j--) {
        for (int i = 0; i < width; i++) {

            // Normalized width and height
            float u = float(i) / float(width);
            float v = float(j) / float(height);

            ray r(origin, lower_left_corner + u * horizontal + v * vertical);
            vec3 col = color(r);

            // vec3 col(u, v, 0.0);

            write_ppm_num(col, image_file);

            if (i < width - 1) {
                image_file << " ";
            }
        }
        image_file << std::endl;
    }

    image_file.close();

    return 0;
}