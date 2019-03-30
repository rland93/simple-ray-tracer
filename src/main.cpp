#include "trace.h"
#include "fresnel.h"
#include "ray.h"
#include "sphere.h"
#include "vec.h"
#include <iostream>

int main(int, char**) {
    unsigned int w = 128, h = 128;

    std::vector<Sphere> spheres;
    // scene contains 2 spheres
    spheres.push_back(Sphere(Vecf(1.0f, 1.0f, 0.0f), 2.0f, 1.0f, 0.5f, false, Color(213, 124, 25)));
    spheres.push_back(Sphere(Vecf(3.0f, 0.5f, 1.0f), 1.0f, 1.0f, 0.5f, false, Color(155, 215, 0)));

    // view
    Vecf viewPoint = Vecf(1.0f, 1.0f, 1.0f);
    Vecf baseDir = Vecf(1.0f, 1.0f, 0.0f).normalize();
    Ray singleRay = Ray(Vecf(1.0f, 1.0f, 0.0f),Vecf(0.0f,0.0f,1.0f),1e8);

    unsigned depth = 2;
    Color tracedColor = trace(singleRay,spheres, depth);
    std::cout << tracedColor << std::endl;

    /*std::vector<Color> *img = nullptr;
    img = drawImg(w, h, 40.0f, viewPoint, baseDir, spheres);
    drop_ppm_image("img", img, w, h);*/
}
