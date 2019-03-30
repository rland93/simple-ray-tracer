#ifndef SPHERE
#define SPHERE
#include "vec.h"
#include <cmath>
#include "color.h"
#include "ray.h"
struct Sphere 
{
    Vecf center;
    float radius;
    float refractiveIndex;
    float reflectivity;
    bool transparent;
    Color color;
    Sphere(const Vecf center, const float radius, const float refractiveIndex, const float reflectivity, const bool transparent, const Color color) : center(center), radius(radius), refractiveIndex(refractiveIndex), reflectivity(reflectivity), transparent(transparent), color(color) {}

    bool collision(const Ray &incidentRay, float &hitDist, bool &insideSphere) const {
        hitDist = 1e8;
        bool collides = false;
        // vector pointing from incident ray origin to center of sphere
        Vecf l = (center - incidentRay.origin);
        // distance from center of sphere to closest point on ray.
        float b = incidentRay.direction.dot(l);
        // l and b are two sides of a right triangle; b is hypotenuse, l is one side, d is the other. we keep d squared (d2) because we only need it for comparisons.
        float d2 = l.dot(l) - b * b;
        // inside sphere case
        if (l.mag2() <= radius * radius) {
            insideSphere = true;
            collides = true;
            hitDist = b + sqrt(radius * radius - d2);
        }
        // outside sphere case
        else {
            insideSphere = false;
            if (d2 <= radius * radius) {
                collides = true;
                hitDist = b - sqrt(radius * radius - d2);
            }
            else collides = false;
        }
        return collides;
    }

    bool simpleCollision(const Ray &incidentRay) const {
        Vecf l = (center - incidentRay.origin);
        float b = incidentRay.direction.dot(l);
        float d2 = l.dot(l) - b * b;
        if (d2 <= radius * radius) return true;
        else return false;
     }

    // return normal to surface
    Vecf find_normal(const Vecf &pSurf) {
        Vecf r = pSurf - center;
        // check that point is on surface
        assert(r.mag2() == radius);
        return r.normalize();
    }
};
#endif