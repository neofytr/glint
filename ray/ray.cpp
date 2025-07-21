#include "ray.h"

Point Ray::at(double param) const {
    return orig  + param * direc;
}