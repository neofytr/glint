#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>
#include <iostream>

// inlining functions and including them in multiple translating units does not cause 
// linking errors

class Vector {
    public:
        double coords[3]; // (x, y, z)

        // constructors
        Vector();
        Vector(double x, double y, double z);
        Vector(double x, double y);
        
        // getter functions
        inline double x() const { return coords[0]; }
        inline double y() const { return coords[1]; }
        inline double z() const { return coords[2]; }

        // overloading operators for Vector class
        Vector operator-() const;
        double operator[](int index) const;

        Vector& operator+=(const Vector &vec);
        Vector& operator*=(double scaleFactor);
        Vector& operator/=(double scaleFactor);

        double lengthSquared() const;
        double length() const;
};

using Point = Vector; // point is just an alias for vector internally

// vector utility functions
inline std::ostream &operator<<(std::ostream &out, const Vector &vec);
inline Vector operator+(const Vector &v, const Vector &u);
inline Vector operator-(const Vector &v, const Vector &u);
inline Vector operator*(const Vector &v, const Vector &u);
inline Vector operator*(const double scaleFactor, const Vector &vec);
inline Vector operator*(const Vector &vec, const double scaleFactor);
inline Vector operator/(const Vector &vec, const double scaleFactor);
inline double dot(const Vector &v, const Vector &u);
inline Vector cross(const Vector &v, const Vector &u);
inline Vector unitVector(const Vector &vec);

#endif // VECTOR_H
