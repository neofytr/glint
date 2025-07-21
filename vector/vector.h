#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>
class Vector {
    public:
        double coords[3]; // (x, y, z)

        // constructors
        Vector() : coords{0, 0, 0} {}
        Vector(double x, double y, double z) : coords{x, y, z} {}
        Vector(double x, double y) : coords{x, y, 0.0} {}
        
        // getter functions
        double x() const {return coords[0];}
        double y() const {return coords[1];}
        double z() const {return coords[2];}

        // overloading operators for Vector class
        Vector operator-() const {return Vector{-coords[0], -coords[1], -coords[2]};}
        double operator[](int index) const {return coords[index];}

        Vector& operator+=(const Vector &vec) {
            coords[0] += vec.coords[0];
            coords[1] += vec.coords[1];
            coords[2] += vec.coords[2];
            return *this; // returning a reference to the modified object enables chaining of the operation
        }

        Vector& operator*=(double scaleFactor) {
            coords[0] *= scaleFactor;
            coords[1] *= scaleFactor;
            coords[2] *= scaleFactor;
            return *this;
        }
        
        Vector& operator/=(double scaleFactor) {
            return *this *= (1 / scaleFactor);
        }

        double lengthSquared() const {
            return coords[0] * coords[0] + coords[1]* coords[1] + coords[2] * coords[2];
        }

        double length() const {
            return std::sqrt(lengthSquared());
        }
};

#endif // VECTOR_H