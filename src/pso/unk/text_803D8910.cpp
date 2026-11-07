#include "pso/system/MatrixVectorArray.h"
#include "pso/system/MatrixOps.h"
#include "pso/unk/text_803D853C.h"
#include "pso/unk/text_803D8F74.h"
#include "pso/system/GinjaTextureMatrices.h"
#include "pso/player/TObjPlayer.h"
#ifndef __MWERKS__
// Host builds use the platform math header, as the SMS PC and TP ports do.
// The MSL header is MWCC-only: its sqrt/sqrtf call __frsqrte.
#include <math.h>
#endif

// mtx.h defines MTXMultVecArray as this symbol but does not prototype it.
extern "C" void PSMTXMultVecArray(const GC_Mtx m, const Vec *src, Vec *dst, u32 count);

// One-time no-asm exception approved by Matt on 2026-11-04 (11:14 AM PT), the
// same kind as #281. vec3_add_to (0x803D8910) is an in-place paired-single add
// (dst += src): D-form psq_l/psq_st with W=1 on z, which GC/2.6 does not emit
// from C or from __vec2x32float__. See docs/evidence/vec3-add-to-paired-single.md.
// The asm builds only under Metrowerks; other compilers get the scalar adds.
#ifdef __MWERKS__
asm void vec3_add_to(register Vec *dst, register const Vec *src) {
    nofralloc
    psq_l f0, 0(dst), 0, 0
    psq_l f2, 0(src), 0, 0
    psq_l f1, 8(dst), 1, 0
    ps_add f0, f2, f0
    psq_l f3, 8(src), 1, 0
    ps_add f1, f3, f1
    psq_st f0, 0(dst), 0, 0
    psq_st f1, 8(dst), 1, 0
    blr
}
#else
void vec3_add_to(Vec *dst, const Vec *src) {
    dst->x += src->x;
    dst->y += src->y;
    dst->z += src->z;
}
#endif

void matrix_mult_vec(f32 (*m)[4], const Vec *src, Vec *dst) {
    if (m == NULL) {
        m = (f32 (*)[4])current_matrix;
    }
    PSMTXMultVec(m, src, dst);
}

void matrix_mult_vec_array(f32 (*m)[4], const Vec *src, Vec *dst, u32 count) {
    if (m == NULL) {
        m = (f32 (*)[4])current_matrix;
    }
    PSMTXMultVecArray(m, src, dst, count);
}

void get_current_matrix(void *m) {
    void *src = current_matrix;
    if (m == NULL) {
        m = src;
    }
    PSMTXCopy((MtxP)src, (MtxP)m);
}

// 0x803D89C0. The original body is assembly: six component registers with each
// load immediately before its math op, which GC/2.6 cannot colour from C.
// Recovered from the disc by tools/orig_asm.py.
extern "C" {
#ifdef __MWERKS__
asm f32 vec3_dot(const Vec *a, const Vec *b) {
#include "orig_asm/pso/unk/text_803D8910/vec3_dot.inc"
}
#else
// Scalar fallback: the same x, y, z accumulation order.
f32 vec3_dot(const Vec *a, const Vec *b) {
    f32 dot = a->x * b->x;
    dot = a->y * b->y + dot;
    return a->z * b->z + dot;
}
#endif
}

void TObjPlayer::invert_matrix_in_place(u32 arg0) {
    if (arg0 == 0) {
        arg0 = (u32)current_matrix;
    }
    PSMTXInverse((MtxP)arg0, (MtxP)arg0);
}

// 0x803D8A18. The original body is assembly: its tail is a double frsqrte
// feeding fres and single-precision fmuls with no frsp, which GC/2.6's typed
// builtins cannot express. Recovered from the disc by tools/orig_asm.py.
extern "C" {
#ifdef __MWERKS__
asm f32 vec3_cross(const Vec *a, const Vec *b, Vec *out) {
#include "orig_asm/pso/unk/text_803D8910/vec3_cross.inc"
}
#else
// Scalar fallback. It keeps the original load order, the single-precision
// first length-square product followed by double accumulates, and returns the
// same cross-product length. The root is taken in the magnitude's double
// range before narrowing, so large vectors do not saturate early.
f32 vec3_cross(const Vec *a, const Vec *b, Vec *out) {
    f32 ax = a->x, ay = a->y, az = a->z;
    f32 bx = b->x, by = b->y, bz = b->z;
    f32 cx = by * az;
    cx = bz * ay - cx;
    f32 cy = bz * ax;
    cy = bx * az - cy;
    f32 cz = bx * ay;
    cz = by * ax - cz;
    out->x = cx;
    out->y = cy;
    out->z = cz;
    f64 mag = cx * cx;
    mag += (f64)cy * cy;
    mag += (f64)cz * cz;
    return (f32)sqrt((f64)mag);
}
#endif
}

void rotate_matrix_zyx(void *m, s32 x, s32 y, s32 z) {
    if (z != 0) {
        rotate_matrix_z((MtxP)m, z);
    }
    if (y != 0) {
        rotate_matrix_y((MtxP)m, y);
    }
    if (x != 0) {
        rotate_matrix_x((MtxP)m, x);
    }
}

void rotate_matrix_yxz(s32 matrix, s32 arg1, s32 arg2, s32 arg3) {
    if (arg2 != 0) {
        rotate_matrix_y((MtxP)matrix, arg2);
    }
    if (arg1 != 0) {
        rotate_matrix_x((MtxP)matrix, arg1);
    }
    if (arg3 != 0) {
        rotate_matrix_z((MtxP)matrix, arg3);
    }
}

void scale_matrix(f32 (*m)[4], f32 sx, f32 sy, f32 sz) {
    Mtx34 tmp;
    f32 (*t)[4];
    if (m == NULL) {
        t = (f32 (*)[4])current_matrix;
    } else {
        t = m;
    }
    PSMTXScale(tmp, sx, sy, sz);
    PSMTXConcat(t, tmp, t);
}
