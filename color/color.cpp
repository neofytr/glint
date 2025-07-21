#include "color.h"
#include <fstream>

// constructors
Color::Color() : colors{0,0,0} {}
Color::Color(double red, double green, double blue) : colors{red, green, blue} {}

// helper functions
void writePixelToFile(std::ofstream &file, const Color &pixelColor) {
    double r = pixelColor.red();
    double g = pixelColor.green();
    double b = pixelColor.blue();

    // translate [0, 1] component values to the byte rate [0, 255]
    int rbyte = int (256.0 * r);
    int gbyte = int (256.0 * g);
    int bbyte = int (256.0 * b);

    file << rbyte << " " << gbyte << " " << bbyte << "\n";
    return;
}

std::ostream &operator<<(std::ostream &out, const Color &pixelValue) {
    return out << pixelValue.red() << " " << pixelValue.green() << " " << pixelValue.blue() << "\n";
}