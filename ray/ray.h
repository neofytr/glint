#ifndef RAY_H
#define RAY_H

#include "../vector/vector.h"

// line equation ->
// R = A + tB
// A is the ray origin; B is the ray direction
// t >= 0 makes P move in front of A on the line (ray)
// t < 0 makes P move in back of A on the line

// const here just means that these functions can be safely called for a constant Ray object

class Ray {
    private:
        Point orig;
        Vector direc;

    public:
        Ray() {}
        Ray(const Point &origin, const Vector &direction) : orig(origin), direc(direction) {}

        // an immutable reference to the private members is returned
        const Point &origin() const {return orig;} 
        const Vector &direction() const {return direc;}

        Point at(double param) const {
            return orig + param * direc;
        }
};

#endif // RAY_H