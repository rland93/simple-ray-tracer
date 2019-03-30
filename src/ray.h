#ifndef RAY
#define RAY
#include "vec.h"
struct Ray
{
    Vecf direction, origin;
    float length;
    Ray() : direction(Vecf(0)), origin(Vecf(0)), length(1e8) {}
    Ray(
        const Vecf direction, 
        const Vecf origin,
        const float length) : 
        direction(direction), origin(origin), length(length) 
    {
        direction.normalize();
    }
};
#endif