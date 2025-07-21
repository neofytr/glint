#ifndef COLOR_H
#define COLOR_H

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

#endif // COLOR_H