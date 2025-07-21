#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>

using namespace std;

int main() {
    int imageWidth = 256;
    int imageHeight = 256;
    const char *imageName = "image.ppm";

    ofstream image(imageName); // will create the file if it doesn't exist
    if (!image) {
        cerr << "ERROR -> couldn't open/create the file " << imageName << "\n";
        return EXIT_FAILURE;
    }

    // PPM format headers
    image << "P3\n";
    image << imageWidth << " " << imageHeight << "\n";
    image << "255\n";

    // image pixel data
    for (int row = 0; row < imageHeight; row++) {
        for (int col = 0; col < imageWidth; col++) {
            double r = double(row) / (imageHeight - 1);
            double g = double(col) / (imageWidth - 1);
            double b = 0.0;

            int ir = int(256.0 * r);
            int ig = int(256.0 * g);
            int ib = int(256.0 * b);

            image << ir << " " << ig << " " << ib << "\n";
        }
    }
    return EXIT_SUCCESS;
}