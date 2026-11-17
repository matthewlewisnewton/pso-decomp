#!/usr/bin/env python3
"""Host smoke test of the collision sphere source with 32-bit game types.

The math stub uses an accurate reciprocal square root, not the Gekko estimate.
The bound helpers are host stubs; native object comparison checks their calls.
"""
from pathlib import Path
import argparse
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[2]
SOURCE = ROOT / "src/pso/player/TObjPlayer_803E112C.cpp"
HEADER = r'''
#include <cstdint>
#include <cmath>
#include <cstdio>
typedef std::int32_t s32;
typedef unsigned char u8;
typedef float f32;
typedef double f64;
struct CollisionSphere_80155C54 { struct { f32 x, y, z; } center; f32 radius; };
#define __fabs std::fabs
static inline double __frsqrte(double x) { return 1.0 / std::sqrt(x); }
'''
HARNESS = r'''
extern "C" void calc_bounds_min_max__10TObjPlayerFPvPvPv(CollisionPoint *p, CollisionPoint *mn, CollisionPoint *mx) {
    *mn = *mx = p[0];
    for (int i = 1; i < 8; ++i) {
        mn->x = std::fmin(mn->x, p[i].x); mn->y = std::fmin(mn->y, p[i].y); mn->z = std::fmin(mn->z, p[i].z);
        mx->x = std::fmax(mx->x, p[i].x); mx->y = std::fmax(mx->y, p[i].y); mx->z = std::fmax(mx->z, p[i].z);
    }
}
extern "C" void calc_bounds__10TObjPlayerFPUcPUc(CollisionSphere *s, CollisionPoint *mn, CollisionPoint *mx) {
    *mn = {s->center.x-s->radius, s->center.y-s->radius, s->center.z-s->radius};
    *mx = {s->center.x+s->radius, s->center.y+s->radius, s->center.z+s->radius};
}
extern "C" s32 test_aabb_overlap__10TObjPlayerFPUcPUcPUc(CollisionPoint *a, CollisionPoint *b, CollisionPoint *c, CollisionPoint *d) {
    return b->x>=c->x && a->x<=d->x && b->y>=c->y && a->y<=d->y && b->z>=c->z && a->z<=d->z;
}
int main() {
    CollisionPoint box[8] = {{0,0,0},{1,0,0},{1,1,0},{0,1,0},{0,0,1},{1,0,1},{1,1,1},{0,1,1}};
    CollisionSphere cases[] = {{{.5f,.5f,.5f},.1f}, {{2.f,.5f,.5f},.25f},
                               {{1.1f,.5f,.5f},.2f}, {{1.5f,1.5f,1.5f},.1f}};
    const int expected[] = {1, 0, 1, 0};
    for (int i = 0; i < 4; ++i) {
        int got = test_box_sphere_contact(box, &cases[i]);
        if (got != expected[i]) {
            std::fprintf(stderr, "case %d: got %d, expected %d\n", i, got, expected[i]);
            return 1;
        }
    }
    std::puts("sphere contact: 4 cases passed");
}
'''


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--sanitize", action="store_true", help="enable ASan and UBSan")
    args = parser.parse_args()
    # The real headers target 32-bit PowerPC long; this harness uses exact-width
    # host types while compiling the production function body unchanged.
    body = "\n".join(line for line in SOURCE.read_text().splitlines() if not line.startswith("#include "))
    with tempfile.TemporaryDirectory(prefix="pso-sphere-contact-") as temp:
        temp = Path(temp)
        source, binary = temp / "test.cpp", temp / "test"
        source.write_text(HEADER + body + HARNESS)
        command = ["c++", "-std=c++17", "-Wno-unknown-pragmas"]
        if args.sanitize:
            command.extend(["-fsanitize=address,undefined", "-fno-omit-frame-pointer"])
        subprocess.run(command + [str(source), "-o", str(binary)], check=True)
        subprocess.run([str(binary)], check=True)


if __name__ == "__main__":
    main()
