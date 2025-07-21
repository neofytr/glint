#ifndef COLOR_H
#define COLOR_H

#include <fstream>
#include <ostream>

class Color {
  public:
    double colors[3];

    // constructors
    Color();
    Color(double red, double green, double blue);

    // getter functions
    inline double red() const { return colors[0]; }
    inline double green() const { return colors[1]; }
    inline double blue() const { return colors[2]; }

    // operator overloads
    double operator[](int index) const;
    Color &operator+=(const Color &other);
    Color &operator*=(double scaleFactor);
    Color &operator/=(double scaleFactor);
    Color &operator*=(const Color &other); // component-wise multiplication
};

// utility functions
std::ostream &operator<<(std::ostream &out, const Color &color);
Color         operator+(const Color &a, const Color &b);
Color         operator*(const Color &a, const Color &b); // component-wise
Color         operator*(const Color &color, double scale);
Color         operator*(double scale, const Color &color);
Color         operator/(const Color &color, double scale);

void writePixelToFile(std::ofstream &file, const Color &pixelColor);

#endif // COLOR_H
