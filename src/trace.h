#ifndef TRACE
#define TRACE
#include <vector>
#include <fstream>
#include <string>
#include "sphere.h"
#include "color.h"
#include "ray.h"
#include "fresnel.h"
#include "vec.h"
#endif

std::vector<Color> * drawImg(unsigned int imgW, unsigned int imgH, float fov, Vecf &viewPoint, Vecf baseDir, const std::vector<Sphere> &objects);
void drop_ppm_image(const std::string filename, Color *image, const unsigned imgW, const unsigned imgH);
Color trace(const Ray &ray, const std::vector<Sphere> &spheres, unsigned int &depth);
void findCollisions(const std::vector<Sphere> &objects, Sphere *object, const Ray &incidentRay, Vecf &surfNormal, Vecf &hit, bool &insideSphere, const float &MAX_DIST);