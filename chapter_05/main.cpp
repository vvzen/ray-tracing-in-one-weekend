#include <fstream>
#include <iostream>
#include <random>

#include "vec3.h"
#include "ray.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"

vec3 color(const ray &r, hittable *world) {

    hit_record rec;

    // Return the normal of the hit object
    if (world->hit(r, 0.0, MAXFLOAT, rec)){
        return 0.5 * vec3(rec.N.x() + 1, rec.N.y() + 1, rec.N.z() + 1);
    }
    else {

        vec3 unit_direction = unit_vector(r.direction());
        float t = 0.5 * (unit_direction.y() + 1.0);

        vec3 start_col = vec3(0.725, 0.094, 0.698);
        vec3 end_col = vec3(0.952, 0.662, 0.349);

        // Linear interpolation, when t=0 I want start_col, when t=1 I want end_col
        vec3 blended_value = (1.0 - t) * start_col + t * end_col;
        return blended_value;
    }
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
    image_file.open("chapter_05.ppm");

    int width = 512;
    int height = 256;
    write_ppm_header(width, height, 255, image_file);

    vec3 lower_left_corner(-2.0, -1.0, -1.0);
    vec3 horizontal(4.0, 0.0, 0.0);
    vec3 vertical(0.0, 2.0, 0.0);
    vec3 origin(0.0, 0.0, 0.0);

    int num_elements = 2;
    hittable *list[num_elements];
    list[0] = new sphere(vec3(0.0, 0.0, -1), 0.5);
    list[1] = new sphere(vec3(0,-100.5,-1), 100);

    hittable *world = new hittable_list(list, num_elements);

    for (int j = height - 1; j >= 0; j--) {
        for (int i = 0; i < width; i++) {

            // Normalized width and height
            float u = float(i) / float(width);
            float v = float(j) / float(height);

            ray r(origin, lower_left_corner + u * horizontal + v * vertical);
            vec3 p = r.point_at_parameter(1.0);

            vec3 col = color(r, world);

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