#ifndef FRESNEL
#define FRESNEL
#include <cmath>
#include "vec.h"
#include "ray.h"
#endif

Vecf reflect(const Vecf &incidentDirection, const Vecf &surfaceNormal);
float fresnel_reflectance(const Vecf &incidentDirection, const Vecf &surfaceNormal, const float n1, const float n2);
Vecf refract(const Vecf &incidentDirection, const Vecf &surfaceNormal, const float n1, const float n2, bool &TIR);