#ifndef VEC
#define VEC
#include <ostream>
template<typename T>
/* A vector with 3 components.*/
class Vec {
public:
    T x, y, z;
    // <0,0,0>
    Vec(): x(T(0)), y(T(0)), z(T(0)) {}
    // <n,n,n>
    Vec(T(n)) : x(T(n)), y(T(n)), z(T(n)) {}
    // <u,v,w>
    Vec(T(u), T(v), T(w)) : x(T(u)), y(T(v)), z(T(w)) {}
    // Dot Product
    T dot(const Vec<T> &u) const {
        return x * u.x + y * u.y + z * u.z;
    }
    // Cross Product
    Vec<T> cross(const Vec<T> &u) const {
        return Vec((y * u.z - z * u.y), 
                   (z * u.x - x * u.z), 
                   (x * u.y - y * u.x)
                  );
    }
    // Add
    Vec<T> operator + (const Vec<T> &u) const {
        return Vec<T>(x + u.x, y + u.y, z + u.z);
    }

    // Subtract
    Vec<T> operator - (const Vec<T> &u) const {
        return Vec<T>(x - u.x, y - u.y, z - u.z);
    }
    // Multiply by constant
    Vec<T> operator * (const T &u) const {
        return Vec<T>(x * u, y * u, z * u);
    }
    // Find magnitude
    T mag() const {
        return sqrt(x * x + y * y + z * z);
    }
    // Find u.u (magnitude squared)
    T mag2() const {
        return x * x + y * y + z * z;
    }
    // Rotate x axis
    Vec<T> rotateX(const float t) const {
        return Vec<T>(dot(Vec<T>(1, 0, 0)), 
                      dot(Vec<T>(0, cos(t), -sin(t))), 
                      dot(Vec<T>(0, sin(t), cos(t))));
    }
    // Rotate y axis
    Vec<T> rotateY(const float t) const {
        return Vec<T>(dot(Vec<T>(cos(t), 0, sin(t))),
                      dot(Vec<T>(0, 1, 0)),
                      dot(Vec<T>(-sin(t), 0, cos(t))));
    }
    // Rotate z axis
    Vec<T> rotateZ(const float t) const {
        return Vec<T>(dot(Vec<T>(cos(t), -sin(t), 0)),
                      dot(Vec<T>(sin(t), cos(t), 0)),
                      dot(Vec<T>(0, 0, 1)));
    }
    // Arbitrary multiplication
    Vec<T> multiply(const T v[2][2]) const {
        return Vec<T>(dot(Vec<T>(v[0][0], v[1][0], v[2][0])),
                      dot(Vec<T>(v[0][1], v[1][1], v[2][1])),
                      dot(Vec<T>(v[0][2], v[1][2], v[2][2])));
    }
    // Normalize
    Vec<T> normalize() const {
        T l = mag();
        return Vec<T>(x / l, y / l, z / l);
    }
    // Print
    friend std::ostream& operator<< (std::ostream &os, const Vec& u) {
        os << "[" << u.x << "," << u.y << "," << u.z << "]";
        return os;
    }
};
typedef Vec<float> Vecf;
typedef Vec<double> Vecd;
#endif