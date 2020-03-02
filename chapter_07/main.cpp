#include <fstream>
#include <iostream>
#include <random>

#include "vec3.h"
#include "ray.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
#include "random.h"

#define GAMMA 2.2

// Sample a random point in a unit sphere
vec3 random_in_unit_sphere(){
    vec3 p;

    do {
        // Sample between [0.0, 2.0]
        p = 2.0 * vec3(random_double(), random_double(), random_double());
        // Then remap to [-1.0, 1.0]
        p -= vec3(1.0, 1.0, 1.0);
    } while (p.squared_length() >= 1.0); // If the point is outside the sphere, try again

    return p;
}

vec3 color(const ray &r, hittable *world) {

    hit_record rec;

    if (world->hit(r, 0.001, MAXFLOAT, rec)){

        vec3 target = rec.pos + rec.N + random_in_unit_sphere();
        // std::cout << "target: " << target << std::endl;

        return 0.5 * color(ray(rec.pos, target - rec.pos), world);
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
    image_file.open("chapter_07_extra.ppm");

    int width = 512;
    int height = 256;
    int num_samples = 8;
    int total_samples = width * height * num_samples;
    int current_sample = 0;

    write_ppm_header(width, height, 255, image_file);

    int num_elements = 64;
    hittable *list[num_elements];
    for (int i = 0; i < num_elements; i++){
        list[i] = new sphere(vec3(random_double() * 4.0 - 1.5, random_double() * 2.0 - 1.0, -1), random_double() * 0.2);
    }
    // list[0] = new sphere(vec3(0.0, 0.0, -1), 0.5);

    hittable *world = new hittable_list(list, num_elements);

    camera cam;

    std::cout << "sampling rays" << std::endl;

    for (int j = height - 1; j >= 0; j--) {
        for (int i = 0; i < width; i++) {

            vec3 col(0.0, 0.0, 0.0);

            for (int s = 0; s < num_samples; s++){
                // Normalized width and height
                float u = float(i + random_double()) / float(width);
                float v = float(j + random_double()) / float(height);
                // std::cout << "u: " << u << "v: " << v << "\r";

                ray r = cam.get_ray(u, v);
                col += color(r, world);

                current_sample++;
                if (current_sample % 100 == 0 || current_sample == total_samples) {
                    std::cout << current_sample << " / " << total_samples << "\r";
                }
            }

            // Do the average of the sampled color
            // This is a simple way to do antialiasing
            col /= float(num_samples);

            // Take into account the gamma correction that will be applied by the image reader
            col = vec3(pow(col[0], 1.0 / GAMMA), pow(col[1], 1.0 / GAMMA), pow(col[2], 1.0 / GAMMA));

            write_ppm_num(col, image_file);

            if (i < width - 1) {
                image_file << " ";
            }
        }
        image_file << std::endl;
    }
    std::cout << std::endl;
    std::cout << "finished" << std::endl;

    image_file.close();

    return 0;
}