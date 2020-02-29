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

    int num_cols = 256;
    int num_rows = 256;
    write_ppm_header(num_rows, num_cols, 255, image_file);

    // Random num generator
    std::random_device rd; // Used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<int> rand_dist(0, 255);

    for (int j = 0; j < num_rows; j++){
        RGBColor c;
        c.r = 255 - j;
        c.g = rand_dist(gen);

        for (int i = 0; i < num_cols; i++){
            c.b = 255 - i;
            write_ppm_num(c, image_file);
            if (i < num_cols - 1){
                image_file << " ";
            }

        }
        image_file << std::endl;
    }

    image_file.close();

    return 0;
}