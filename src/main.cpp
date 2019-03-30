#include "trace.h"
#include "fresnel.h"
#include "ray.h"
#include "sphere.h"
#include "vec.h"
#include <iostream>

int main(int, char**) {
    unsigned int w = 128, h = 128;

    std::vector<Sphere> spheres;
    // center, radius, refr index, reflectivity, transparent color
    Vecf center = Vecf(4.0f, 0.0f, 0.0f);
    float radius = 1.0f;
    float refractive_index = 0.0f;
    float reflectivity = 0.5;
    bool transparent = false;
    Color spcolor = Color(240, 100, 24);


    spheres.push_back(Sphere(center, radius, refractive_index, reflectivity, transparent, spcolor));

    // view
    Vecf viewPoint = Vecf(0.0f, 0.0f, 0.0f);
    Vecf baseDir = Vecf(1.0f, 0.0f, 0.0f);
    Ray singleRay = Ray(viewPoint, baseDir,1e8);

    unsigned depth = 2;
    Color tracedColor = trace(singleRay, spheres, depth);

    std::cout << tracedColor << std::endl;
    

    Color * img = drawImg(w, h, 40.0f, viewPoint, baseDir, spheres);
    drop_ppm_image("img", img, w, h);
}
