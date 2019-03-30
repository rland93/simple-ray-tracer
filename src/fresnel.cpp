#include "fresnel.h"

// returns the direction of a reflected ray from an incident and a surface.
Vecf reflect(const Vecf &incidentDirection, const Vecf &surfaceNormal) {
    float cosI = incidentDirection.dot(surfaceNormal) * -1;
    return incidentDirection - surfaceNormal * (2 * cosI);
}
// calculate reflectance of a light ray hitting a non-opaque surface
float fresnel_reflectance(const Vecf &incidentDirection, const Vecf &surfaceNormal, const float n1, const float n2) {
    const float n = n1/n2;
    // cos of incident angle
    const float cosi = incidentDirection.dot(surfaceNormal) * -1;
    // sin^2 of transmission angle 
    const float sint2 = n * n * (1.0f - cosi * cosi);
    // cos of transmisssion angle
    const float cost = sqrt(1.0f - sint2);
    // rs - reflectance of s-polarized light
    float rs = (n1 * cosi - n2 * cost)/(n1 * cosi + n2 * cost);
    rs *= rs;
    // rp - reflectance of p-polarized light
    float rp = (n1 * cost - n2 * cosi)/(n1 * cost + n2 * cosi);
    rp *= rp;
    // average reflectivity
    const float reff = (rs + rp)/2.0f;
    // total internal reflection case
    if (sint2 > 1.0f) return 1.0f;
    else return reff;
}
// return direction of a refracted vector.
Vecf refract(const Vecf &incidentDirection, const Vecf &surfaceNormal, const float n1, const float n2, bool &TIR) {
    const float n = n1/n2;
    const float cosi = incidentDirection.dot(surfaceNormal) * -1;
    const float sint2 = n * n * (1.0f - cosi * cosi);
    const float cost = sqrt(1.0f - sint2);
    Vecf refracted = incidentDirection * n + surfaceNormal * (n * cosi - cost);
    // only get a refracted ray if total internal reflection doesn't occur.
    if (sint2 > 1.0f) {
        TIR = true;
        return Vecf(0);
    }
    else {
        TIR = false;
        return refracted;
    }
}