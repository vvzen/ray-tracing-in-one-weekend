#include <iostream>
#include <fstream>
#include <random>

#include "vec3.h"


void write_ppm_header(int ncols, int nrows, int maxvalue, std::ofstream &f){

    f << "P3" << std::endl;
    f << ncols << " " << nrows << std::endl;
    f << maxvalue << std::endl;
}

void write_ppm_num(vec3 c, std::ofstream &f){
    int i_r = int(255.99 * c.r());
    int i_g = int(255.99 * c.g());
    int i_b = int(255.99 * c.b());

    f << std::to_string(i_r) << " ";
    f << std::to_string(i_g) << " ";
    f << std::to_string(i_b);
}


int main(){

    std::ofstream image_file;
    image_file.open("chapter_01.ppm"s);

    int width = 256;
    int height = 128;
    write_ppm_header(width, height, 255, image_file);

    for (int j = height - 1; j >= 0; j--){
        for (int i = 0; i < width; i++){

            vec3 col(float(i) / float(width), float(j) / float(height), 0.2);
            write_ppm_num(col, image_file);

            if (i < width - 1){
                image_file << " ";
            }
        }
        image_file << std::endl;
    }

    image_file.close();

    return 0;
}