#ifndef HITTABLE_H
#define HITTABLE_H

#include "../ray/ray.h"

class HitRecord {
  public:
    Point  p;
    Vector normal;
    double t;
};

// represents all objects that can be hit
// the hits only count if they are between t_min and t_max
class Hittable {
  public:
    virtual ~Hittable()                                                                  = default;
    virtual bool hit(const Ray &r, double rayTMin, double rayTMax, HitRecord &rec) const = 0;
};

#endif