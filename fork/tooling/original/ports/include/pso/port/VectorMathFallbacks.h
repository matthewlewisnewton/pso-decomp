#ifndef PSO_PORT_VECTOR_MATH_FALLBACKS_H
#define PSO_PORT_VECTOR_MATH_FALLBACKS_H

// Portable scalar implementations of the Ginja vector kernels.
//
// The GameCube build uses the original assembly bodies in
// src/pso/unk/text_803D8910.cpp and src/pso/unk/text_803D96A8.cpp. Their
// non-MWERKS branches call these templates, so the x86 harness in ports/tests
// exercises exactly the code a port builds. Each function accepts any type
// with floating x, y and z members (the game's Vec, or the harness's Vec3f).
//
// This follows the SMS PC and TP port pattern: use the host math library
// instead of the MWCC-only MSL header.

#include "pso/port/PortCompat.h"

namespace pso {
namespace port {

template <class V>
inline float vec3_dot(const V *a, const V *b) {
    float dot = a->x * b->x;
    dot = a->y * b->y + dot;
    return a->z * b->z + dot;
}

template <class V>
inline float vec3_cross(const V *a, const V *b, V *out) {
    float ax = a->x, ay = a->y, az = a->z;
    float bx = b->x, by = b->y, bz = b->z;
    float cx = by * az;
    cx = bz * ay - cx;
    float cy = bz * ax;
    cy = bx * az - cy;
    float cz = bx * ay;
    cz = by * ax - cz;
    out->x = cx;
    out->y = cy;
    out->z = cz;
    double mag = cx * cx;
    mag += (double)cy * cy;
    mag += (double)cz * cz;
    return (float)std::sqrt((double)mag);
}

template <class V>
inline float normalize_vector(V *v) {
    float x = v->x, y = v->y, z = v->z;
    float acc = x * x;
    acc = y * y + acc;
    float sum = z * z + acc;
    float inv = 1.0f / std::sqrt(sum);
    v->x = inv * x;
    v->y = inv * y;
    v->z = inv * z;
    return std::sqrt(sum);
}

} // namespace port
} // namespace pso

#endif
