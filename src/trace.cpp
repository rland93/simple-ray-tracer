#include "trace.h"

const float MAX_DIST = 1e8;
const unsigned int DEPTH_MAX = 4;
const Color background = Color(55,55, 55);
// explicit light placement (for now)
Vecf light = Vecf(1.0f,1.0f,4.0f);

Color trace(const Ray &ray, const std::vector<Sphere> &spheres, unsigned int &depth) {
    
    Sphere *object = nullptr;
    Vecf *traceHit = nullptr;
    Vecf *surfNormal = nullptr;
    bool insideSphere = false;
    bool collided = false;
    Color color;
    findCollisions(spheres, object, ray, *surfNormal, *traceHit, insideSphere, MAX_DIST);
    // collision
    if (object != nullptr) {
        Ray shadowRay;
        shadowRay.direction = light - *traceHit;
        shadowRay.origin = light;
        shadowRay.length = MAX_DIST;
        color = object->color;
        for (unsigned i = 0; i < spheres.size(); ++i) {
            if (spheres[i].simpleCollision(shadowRay) == true) {
                color = Color(0,0,0);
                break;
            }
        }
    }
    else {
        color = background;
    }
    return color;
}

// store object, surface normal, point of hit of closest collision with the ray.
void findCollisions(const std::vector<Sphere> &objects, Sphere *object, const Ray &incidentRay, Vecf &surfNormal, Vecf &hit, bool &insideSphere, const float &MAX_DIST) {
    float dist = MAX_DIST;
    float object_dist = MAX_DIST;
    for (unsigned i = 0; i < objects.size(); ++i) {
        // dist to collision updated
        insideSphere = false;
        if (objects[i].collision(incidentRay, dist, insideSphere)) {
            // if closer object
            if (dist < object_dist) {
                // store object and distance, set flag
                * object = objects[i];
                object_dist = dist;
            }
        }
    }
    // store surface normal
    hit = incidentRay.origin + incidentRay.direction * dist;
    surfNormal = object->find_normal(hit);
}

std::vector<Color> * drawImg(unsigned int imgW, unsigned int imgH, float fov, Vecf &viewPoint, Vecf baseDir, const std::vector<Sphere> &objects) {
    // fov degrees -> radians
    float fov_radians = (180/M_PI) * fov;
    // create empty frame vector
    std::vector<Color> *frame = new std::vector<Color>[imgW * imgH];
    // rotate direction to top left corner
    baseDir = baseDir.rotateX(-fov_radians/2.0).rotateY(-fov_radians/2.0);

    for (unsigned i = 0; i < imgH; i++) {
        // rotate the view (y direction)
        baseDir = baseDir.rotateY((i * 1/float(imgH)) * fov_radians);
        for (unsigned j = 0; j < imgW; j++) {
            // rotate the view (x direction)
            baseDir = baseDir.rotateX((j * 1/float(imgW)) * fov_radians);
            // create a ray from new view direction, trace that ray, and pack the color into frame
            unsigned depth = 0;
            (*frame)[i + j*imgW] = trace(Ray(baseDir, viewPoint, 1e8), objects, depth);
        }
    }
    return frame;
}

void drop_ppm_image(const std::string filename, Color *image, const unsigned imgW, const unsigned imgH) {
    // open file stream
    std::ofstream ofs(filename);
    ofs << "P6\n" << imgW << " " << imgH << "\n255\n";
    // populate each pixel
    for (unsigned i = 0; i < imgW * imgH; ++i) {
        uint8_t r, g, b, a = 255;
        r = image[i].r;
        g = image[i].g;
        b = image[i].b;
        ofs << static_cast<char>(r) << static_cast<char>(g) << static_cast<char>(b);
    }
    ofs.close();
}