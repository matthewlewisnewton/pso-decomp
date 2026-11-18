// Host behavior test for the portable Ginja vector fallbacks.
//
// The same source builds on x86_64 and aarch64, including the Allwinner H700
// (Cortex-A53) in the Anbernic RG34XXSP: it uses only the standard C++
// library and the shared fallback header, with no architecture intrinsics.

#include <cmath>
#include <cstdio>

#include "pso/port/VectorMathFallbacks.h"

struct Vec3f { float x, y, z; };

static int failures = 0;

static bool close_rel(double got, double want, double tol) {
    double scale = 1.0 + std::fabs(want);
    return std::fabs(got - want) <= tol * scale;
}

static void check(const char *what, double got, double want, double tol) {
    if (!close_rel(got, want, tol)) {
        std::printf("FAIL %s: got %.9g want %.9g\n", what, got, want);
        ++failures;
    }
}

static void ref_cross(const Vec3f *a, const Vec3f *b, double out[3]) {
    double ax = a->x, ay = a->y, az = a->z;
    double bx = b->x, by = b->y, bz = b->z;
    out[0] = ay * bz - az * by;
    out[1] = az * bx - ax * bz;
    out[2] = ax * by - ay * bx;
}

static void test_dot() {
    Vec3f a = {1.0f, 2.0f, 3.0f}, b = {4.0f, 5.0f, 6.0f};
    check("dot basic", pso::port::vec3_dot(&a, &b), 32.0, 1e-6);

    Vec3f c = {-1.5f, 0.25f, 8.0f}, d = {2.0f, -4.0f, 0.5f};
    check("dot mixed", pso::port::vec3_dot(&c, &d),
          (double)c.x * d.x + (double)c.y * d.y + (double)c.z * d.z, 1e-5);

    Vec3f z = {0.0f, 0.0f, 0.0f};
    check("dot zero", pso::port::vec3_dot(&z, &c), 0.0, 1e-6);
}

static void test_cross_one(const Vec3f &a, const Vec3f &b, const char *tag) {
    Vec3f out;
    float r = pso::port::vec3_cross(&a, &b, &out);
    double ref[3];
    ref_cross(&a, &b, ref);
    char name[64];
    std::sprintf(name, "%s x", tag); check(name, out.x, ref[0], 1e-5);
    std::sprintf(name, "%s y", tag); check(name, out.y, ref[1], 1e-5);
    std::sprintf(name, "%s z", tag); check(name, out.z, ref[2], 1e-5);
    double len = std::sqrt(ref[0] * ref[0] + ref[1] * ref[1] + ref[2] * ref[2]);
    std::sprintf(name, "%s len", tag); check(name, r, len, 1e-5);
}

static void test_cross() {
    Vec3f x = {1, 0, 0}, y = {0, 1, 0}, z = {0, 0, 1};
    test_cross_one(x, y, "x*y");
    test_cross_one(y, z, "y*z");
    test_cross_one(z, x, "z*x");
    test_cross_one(y, x, "y*x");

    Vec3f a = {2, 0, 0}, b = {0, 2, 0};
    test_cross_one(a, b, "2x*2y");

    Vec3f c = {1.25f, -3.5f, 0.75f}, d = {-2.0f, 0.5f, 4.25f};
    test_cross_one(c, d, "mixed");

    // Aliasing: out == a and out == b must load all inputs before storing.
    Vec3f p = {1, 2, 3}, q = {4, 5, 6}, save_p = p, save_q = q;
    pso::port::vec3_cross(&p, &q, &p);
    double ref[3];
    ref_cross(&save_p, &save_q, ref);
    check("alias a x", p.x, ref[0], 1e-5);
    check("alias a y", p.y, ref[1], 1e-5);
    check("alias a z", p.z, ref[2], 1e-5);

    Vec3f ou = {1, 2, 3}, ov = {4, 5, 6}, v = ov;
    pso::port::vec3_cross(&ou, &v, &v);
    ref_cross(&ou, &ov, ref);
    check("alias b x", v.x, ref[0], 1e-5);
    check("alias b y", v.y, ref[1], 1e-5);
    check("alias b z", v.z, ref[2], 1e-5);

    Vec3f zero = {0, 0, 0}, out;
    check("cross zero len", pso::port::vec3_cross(&zero, &c, &out), 0.0, 1e-6);

    // Large magnitude: the f64 length square exceeds f32, but the length is
    // representable. The fallback takes the root in double before narrowing.
    Vec3f big = {1e20f, 0.0f, 0.0f}, unit = {0.0f, 1.0f, 0.0f};
    check("large cross len", pso::port::vec3_cross(&big, &unit, &out), 1e20, 1e-5);
}

static void test_normalize_one(const Vec3f &in, const char *tag) {
    Vec3f v = in;
    float r = pso::port::normalize_vector(&v);
    double len = std::sqrt((double)in.x * in.x + (double)in.y * in.y +
                           (double)in.z * in.z);
    char name[64];
    std::sprintf(name, "%s len", tag); check(name, r, len, 1e-5);
    if (len > 0.0) {
        std::sprintf(name, "%s x", tag); check(name, v.x, (double)in.x / len, 1e-5);
        std::sprintf(name, "%s y", tag); check(name, v.y, (double)in.y / len, 1e-5);
        std::sprintf(name, "%s z", tag); check(name, v.z, (double)in.z / len, 1e-5);
    }
}

static void test_normalize() {
    Vec3f a = {3, 4, 0}; test_normalize_one(a, "3-4-0");
    Vec3f b = {1, 0, 0}; test_normalize_one(b, "unit x");
    Vec3f c = {1.25f, -3.5f, 0.75f}; test_normalize_one(c, "mixed");
    Vec3f d = {1000, 2000, 2000}; test_normalize_one(d, "large");

    // The original has no zero guard: fres(frsqrte(0)) returns 0 and the
    // component scales are NaN. The fallback keeps that behavior.
    Vec3f z = {0, 0, 0};
    check("normalize zero len", pso::port::normalize_vector(&z), 0.0, 1e-6);
    if (!(z.x != z.x) || !(z.y != z.y) || !(z.z != z.z)) {
        std::printf("FAIL normalize zero: expected NaN components, got %g %g %g\n",
                    z.x, z.y, z.z);
        ++failures;
    }
}

int main() {
    test_dot();
    test_cross();
    test_normalize();
    if (failures) {
        std::printf("%d failure(s)\n", failures);
        return 1;
    }
    std::printf("all host fallback behavior checks passed\n");
    return 0;
}
