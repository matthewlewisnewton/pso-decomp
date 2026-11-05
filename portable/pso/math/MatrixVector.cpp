// Portable implementations of the two hand-written Gekko kernels of
// src/pso/math/MatrixVector.cpp, for builds that do not need byte-exact
// output, such as non-GameCube targets. The originals are hand-written
// assembly — `frsqrte`+`fres` estimates in vector_length at 0x803D8BD8 and
// paired-single stores in matrix_identity at 0x803D8CA8 — that CodeWarrior
// cannot emit from C or C++, so the matching build takes those bodies from
// the disc at build time through orig_asm. This file is a drop-in
// alternative; it is not part of the PsoV3 build and is not byte-matching.
// See docs/evidence/matrixvector-asm-kernels-evidence.md.

#include "types.h"
#include <dolphin/mtx.h>
#include "libc/math.h"

extern "C" {

// The original computes the length with two hardware estimates and is only
// accurate to a few bits; the portable branch returns the exact value.
f32 vector_length(const Vec *v) {
    f32 x = v->x;
    f32 y = v->y;
    f32 sum = x * x;
    f32 z = v->z;
    sum = (y * y) + sum;
    sum = (z * z) + sum;
#ifdef __PPCGEKKO__
    // Closest CodeWarrior C to the original; the frsp between the f64
    // reciprocal square root and the f32 reciprocal is unavoidable.
    return __fres((f32)__frsqrte(sum));
#else
    return sqrtf(sum);
#endif
}

// Writes the 3x4 row-major identity matrix to arg0, as the original's
// paired-single stores do.
void matrix_identity(u8 *arg0) {
    f32 *m = (f32 *)arg0;
#ifdef __PPCGEKKO__
    // The original reads its 1.0f from the shared .sdata pair lbl_805D46AC
    // and derives the zeros from it; keep that data flow on this target.
    extern f32 lbl_805D46AC[2];
    f32 one = lbl_805D46AC[0];
    f32 zero = one - one;
#else
    f32 one = 1.0f;
    f32 zero = 0.0f;
#endif
    m[0] = one;
    m[1] = zero;
    m[2] = zero;
    m[3] = zero;
    m[4] = zero;
    m[5] = one;
    m[6] = zero;
    m[7] = zero;
    m[8] = zero;
    m[9] = zero;
    m[10] = one;
    m[11] = zero;
}

}
