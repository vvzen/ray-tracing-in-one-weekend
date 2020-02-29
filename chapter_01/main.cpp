#include <iostream>
#include <fstream>
#include <random>

struct RGBColor {
    int r;
    int g;
    int b;
};

void write_ppm_header(int ncols, int nrows, int maxvalue, std::ofstream &f){

    f << "P3" << std::endl;
    f << ncols << " " << nrows << std::endl;
    f << maxvalue << std::endl;
}

void write_ppm_num(RGBColor c, std::ofstream &f){
    f << std::to_string(c.r) << " " << std::to_string(c.g) << " " << std::to_string(c.b);
}


int main(){

    std::ofstream image_file;
    image_file.open("chapter_01.ppm");

    int width = 256;
    int height = 128;
    write_ppm_header(width, height, 255, image_file);

    for (int j = height - 1; j >= 0; j--){
        for (int i = 0; i < width; i++){

            RGBColor c;
            c.r = (float(i) / float(width)) * 255.99;
            c.g = (float(j) / float(height)) * 255.99;
            c.b = 0.2 * 255.99;
            write_ppm_num(c, image_file);

            if (i < width - 1){
                image_file << " ";
            }
        }
        image_file << std::endl;
    }

    image_file.close();

    return 0;
}