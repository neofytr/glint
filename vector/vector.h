#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>
#include <iostream>

class Vector {
    public:
        double coords[3]; // (x, y, z)

        // constructors
        Vector() : coords{0, 0, 0} {}
        Vector(double x, double y, double z) : coords{x, y, z} {}
        Vector(double x, double y) : coords{x, y, 0.0} {}
        
        // getter functions
        inline double x() const {return coords[0];}
        inline double y() const {return coords[1];}
        inline double z() const {return coords[2];}

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

using Point = Vector; // point is just an alias for vector internally

// vector utility functions
inline std::ostream &operator<<(std::ostream &out, const Vector &vec) {
    return out << vec.x() << " " << vec.y() << " " << vec.z() << "\n";
}

inline Vector operator+(const Vector &v, const Vector &u) {
    return Vector(v.x() + u.x(), v.y() + u.y(), v.z() + u.z());
}

inline Vector operator-(const Vector &v, const Vector &u) {
    return Vector(v.x() - u.x(), v.y() - u.y(), v.z() - u.z());
}

inline Vector operator*(const Vector &v, const Vector &u) {
    return Vector(v.x() * u.x(), v.y() * u.y(), v.z() * u.z());
}

// two separate so that * works both ways (t * v and v * t)
inline Vector operator*(const double scaleFactor, const Vector &vec) {
    return Vector(vec.x() * scaleFactor, vec.y() * scaleFactor, vec.z() * scaleFactor);
}

inline Vector operator*(const Vector &vec, const double scaleFactor) {
    return Vector(vec.x() * scaleFactor, vec.y() * scaleFactor, vec.z() * scaleFactor);
}

inline Vector operator/(const Vector &vec, const double scaleFactor) {
    return vec * (1 / scaleFactor);
}

inline double dot(const Vector &v, const Vector &u) {
    return v.x() * u.x() + v.y() * u.y() + v.z() * u.z();
}

inline Vector cross(const Vector &v, const Vector &u) {
    return Vector(
        v.y() * u.z() - v.z() * u.y(),
        v.z() * u.x() - v.x() * u.z(),
        v.x() * u.y() - v.y() * u.x()
    );
}

inline Vector unitVector(const Vector &vec) {
    return vec / vec.length();
}

#endif // VECTOR_H