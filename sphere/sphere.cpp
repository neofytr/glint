#include "sphere.h"

Sphere::Sphere(const Point &center, double radius) {
    this->center = center;
    this->radius = fmax(0, radius);
    return;
}

bool Sphere::hit(const Ray &ray, double rayTMin, double rayTMax, HitRecord &rec) const {
    Vector oc           = ray.origin() - center;
    double a            = dot(ray.direction(), ray.direction());
    double b            = 2.0 * dot(oc, ray.direction());
    double c            = dot(oc, oc) - radius * radius;
    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0.0) {
        return false; // no intersection
    }

    double sqrtD = sqrt(discriminant);
    double t1    = (-b - sqrtD) / (2.0 * a); // closer intersection (since t1 <= t2 always)
    double t2    = (-b + sqrtD) / (2.0 * a); // farther intersection
    double t;

    if (t1 >= 0) {
        t = t1;
    } else if (t2 >= 0) {
        t = t2;
    } else {
        return false; // no possible intersection
    }

    rec.p      = ray.at(t);
    rec.t      = t;
    rec.normal = (rec.p - center) / radius;

    return true;
}