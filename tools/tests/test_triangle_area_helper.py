"""Characterize the scalar 2D collision-area helper on finite inputs.

The oracle uses a determinant and the native 0.025 near-vertical rule. The host
reciprocal square root emulates the estimate mathematically, not bit for bit;
original instructions and relocations remain the native build's responsibility.
"""
from pathlib import Path
import os
import re
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]
SOURCE = ROOT / "src/pso/player/TObjPlayer_803DF7A8.cpp"

CPP_PREFIX = r'''
#include <cmath>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
typedef float f32; typedef double f64;
struct ProjectedPoint { f32 u,v; };
static f64 __frsqrte(f64 x) { return 1.0/std::sqrt(x); }
'''

CPP_CASES = r'''

static void check(ProjectedPoint p,ProjectedPoint a,ProjectedPoint b, double tolerance=0.00001) {
    ProjectedPoint oldp=p,olda=a,oldb=b;
    double dx=(double)a.u-p.u,dy=(double)a.v-p.v;
    double expected=std::fabs(dx*((double)b.v-p.v)-dy*((double)b.u-p.u))*0.5;
    if (std::fabs(dx)<(double)0.025f) expected=std::fabs((double)b.u-p.u)*std::hypot(dx,dy)*0.5;
    float got=triangle_area(&p,&a,&b);
    assert(std::isfinite(got) && std::isfinite(expected));
    if (std::fabs(got-expected)>tolerance+0.00001*expected) {
        std::fprintf(stderr,"area %.9g expected %.9g\n",got,expected);std::abort();
    }
    assert(std::memcmp(&p,&oldp,sizeof(p))==0 && std::memcmp(&a,&olda,sizeof(a))==0 && std::memcmp(&b,&oldb,sizeof(b))==0);
}
int main() {
    check({0,0},{3,0},{0,4}); check({0,0},{0,4},{3,0}); check({3,0},{0,0},{0,4});
    check({1,1},{1,1},{9,4}); check({0,0},{4,4},{2,2});
    check({2,1},{2.01f,5},{7,3}); check({2,1},{2.025f,5},{7,3});
    unsigned state=0xDECAFBAD;
    for (unsigned i=0;i<4096;i++) {
        ProjectedPoint points[3];
        for (auto &p:points) {
            state=state*1664525u+1013904223u;p.u=((int)(state>>16)-32768)/100.0f;
            state=state*1664525u+1013904223u;p.v=((int)(state>>16)-32768)/100.0f;
        }
        check(points[0],points[1],points[2],0.05);
    }
}
'''


class TriangleAreaHelperTests(unittest.TestCase):
    def test_finite_triangles_and_near_vertical_edges(self):
        compiler = shutil.which("g++")
        if compiler is None:
            self.skipTest("g++ is required")
        source = SOURCE.read_text()
        definition = re.search(r"^f32 triangle_area\([^;{}]*\) \{", source, re.MULTILINE)
        self.assertIsNotNone(definition)
        opening = definition.end() - 1
        end, depth = opening + 1, 1
        while depth:
            depth += (source[end] == "{") - (source[end] == "}")
            end += 1
        body = source[definition.start():end]
        with tempfile.TemporaryDirectory() as tmp:
            path = Path(tmp)
            fixture, binary = path / "triangle.cpp", path / "triangle"
            fixture.write_text(CPP_PREFIX + body + CPP_CASES)
            flags = ["-std=c++17", "-O2", "-ffp-contract=off", "-Wall", "-Wextra", "-Werror"]
            if os.environ.get("PSO_TEST_SANITIZERS") == "1":
                flags += ["-fsanitize=address,undefined", "-fno-sanitize-recover=all", "-fno-pie", "-no-pie"]
            result = subprocess.run([compiler, *flags, str(fixture), "-o", str(binary)],
                                    capture_output=True, text=True, timeout=30)
            self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
            result = subprocess.run([str(binary)], capture_output=True, text=True, timeout=5)
            self.assertEqual(result.returncode, 0, result.stdout + result.stderr)


if __name__ == "__main__":
    unittest.main()
