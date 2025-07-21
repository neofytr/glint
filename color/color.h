#ifndef COLOR_H
#define COLOR_H

#include <ostream>
class Color {
    public:
        double colors[3];

        Color();
        Color(double red, double green, double blue);
        
        // getter functions
        inline double red() const { return colors[0]; }
        inline double green() const { return colors[1]; }
        inline double blue() const { return colors[2]; }
};

std::ostream &operator<<(std::ostream &out, const Color &pixelValue);
void writePixelToFile(std::ofstream &file, const Color &pixelColor);

#endif // COLOR_H