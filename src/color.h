#ifndef COLOR
#define COLOR
#include <cstdint>
#include <ostream>

struct Color 
{
    uint8_t r, g, b, a;
    // default constructor
    Color() : r(uint8_t(0)), g(uint8_t(0)), b(uint8_t(0)), a(uint8_t(255)) {}
    // <r, g, b>
    Color(uint8_t r, uint8_t g, uint8_t b): r(uint8_t(r)), g(uint8_t(g)), b(uint8_t(b)), a(uint8_t(255)) {}
    // <r, g, b, a>
    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a): r(uint8_t(r)), g(uint8_t(g)), b(uint8_t(b)), a(uint8_t(a)) {}
    uint32_t pack(const uint8_t rr, 
                    const uint8_t gg, 
                    const uint8_t bb, 
                    const uint8_t aa) {
        return (aa>>24) + (bb>>16) + (gg>>8) + (rr);
    }
    uint32_t pack() {
        return (a>>24) + (b>>16) + (g>>8) + (r);
    }
    void unpack(const uint32_t &color32) {
        r = (color32 >>   0) & 255;
        g = (color32 >>   8) & 255;
        b = (color32 >>  16) & 255;
        a = (color32 >>  24) & 255;
    }
    // addition
    Color operator + (const Color u) const {
        uint8_t newr, newg, newb;
        // result cannot be greater than 255
        if (int(r) + int(u.r) > 255) newr = 255;
        else newr = r + u.r;
        if (int(g) + int(u.g) > 255) newg = 255;
        else newg = g + u.g;
        if (int(b) + int(u.b) > 255) newb = 255;
        else newb = b + u.b;
        return Color(newr, newg, newb);
    }
    // subtraction
    Color operator - (const Color u) const {
        uint8_t newr, newg, newb;
        int testr, testg, testb;
        // result cannot be less than 0
        testr = int(r) + int(u.r * -1);
        if (testr < 0) newr = static_cast<uint8_t>(testr);
        else newr = 0;
        testg = int(g) + int(u.g * -1);
        if (testg < 0) newg = static_cast<uint8_t>(testg);
        else newg = 0;
        testb = int(b) + int(u.b * -1);
        if (testb < 0) newb = static_cast<uint8_t>(testb);
        else newb = 0;
        return Color(newr, newg, newb);
    }
    // scalar multiplication. Argument must be in [0,1].
    Color operator * (const float u) const {
        // cap scalar operand between 0,1
        float x;
        if (u > 1.0) x = 1.0;
        else if (u < 0.0) x = 0.0;
        else x = u;
        return Color(uint8_t(r * x), uint8_t(g * x), uint8_t(b * x));
    }
    // Print
    friend std::ostream& operator<< (std::ostream &os, const Color& u) {
        os << "[" << u.r << "," << u.g << "," << u.b << "]";
        return os;
    }
};
#endif