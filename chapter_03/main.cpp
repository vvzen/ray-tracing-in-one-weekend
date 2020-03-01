#include <fstream>
#include <iostream>
#include <random>

#include "ray.h"
#include "vec3.h"

vec3 color(const ray &r) {
    vec3 unit_direction = unit_vector(r.direction());

    float t = 0.5 * (unit_direction.y() + 1.0);

    vec3 start_col = vec3(1.0, 1.0, 1.0);
    vec3 end_col = vec3(0.5, 0.7, 1.0);

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
    image_file.open("chapter_03.ppm");

    int width = 256;
    int height = 128;
    write_ppm_header(width, height, 255, image_file);

    vec3 lower_left_corner(-1.0, -1.0, -1.0);
    vec3 horizontal(20.0, 0.0, 0.0);
    vec3 vertical(0.0, 10.0, 0.0);
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