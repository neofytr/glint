#ifndef SPHERE_H
#define SPHERE_H

#include "../hittable/hittable.h"
#include "../vector/vector.h"

class Sphere : public Hittable {
  private:
    Point  center;
    double radius;

  public:
    Sphere(const Point &center, double radius);
    bool hit(const Ray &ray, double rayTMin, double rayTMax, HitRecord &rec) const override;
};

#endif