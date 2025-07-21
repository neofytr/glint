#include "color.h"
#include <fstream>

// constructors
Color::Color() : colors{0, 0, 0} {}
Color::Color(double red, double green, double blue) : colors{red, green, blue} {}

// helper functions
void writePixelToFile(std::ofstream &file, const Color &pixelColor) {
    double r = pixelColor.red();
    double g = pixelColor.green();
    double b = pixelColor.blue();

    // translate [0, 1] component values to the byte rate [0, 255]
    int rbyte = int(256.0 * r);
    int gbyte = int(256.0 * g);
    int bbyte = int(256.0 * b);

    file << rbyte << " " << gbyte << " " << bbyte << "\n";
    return;
}

// access operator
double Color::operator[](int index) const {
    return colors[index];
}

// compound operators
Color &Color::operator+=(const Color &other) {
    colors[0] += other.colors[0];
    colors[1] += other.colors[1];
    colors[2] += other.colors[2];
    return *this;
}

Color &Color::operator*=(double scaleFactor) {
    colors[0] *= scaleFactor;
    colors[1] *= scaleFactor;
    colors[2] *= scaleFactor;
    return *this;
}

Color &Color::operator/=(double scaleFactor) {
    return *this *= (1 / scaleFactor);
}

Color &Color::operator*=(const Color &other) {
    colors[0] *= other.colors[0];
    colors[1] *= other.colors[1];
    colors[2] *= other.colors[2];
    return *this;
}

// utility operator overloads
std::ostream &operator<<(std::ostream &out, const Color &color) {
    return out << color.red() << " " << color.green() << " " << color.blue() << "\n";
}

Color operator+(const Color &a, const Color &b) {
    return Color(a.red() + b.red(), a.green() + b.green(), a.blue() + b.blue());
}

Color operator*(const Color &a, const Color &b) {
    return Color(a.red() * b.red(), a.green() * b.green(), a.blue() * b.blue());
}

Color operator*(const Color &color, double scale) {
    return Color(color.red() * scale, color.green() * scale, color.blue() * scale);
}

Color operator*(double scale, const Color &color) {
    return color * scale;
}

Color operator/(const Color &color, double scale) {
    return color * (1 / scale);
}
