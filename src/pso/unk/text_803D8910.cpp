#include "pso/system/MatrixVectorArray.h"
#include "pso/system/MatrixOps.h"
#include "pso/unk/text_803D853C.h"
#include "pso/unk/text_803D8F74.h"
#include "pso/system/GinjaTextureMatrices.h"
#include "pso/player/TObjPlayer.h"

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

// 0x803D89C0. a->x * b->x, then y and z, contracted by the unit's -fp_contract on.
extern "C" f32 vec3_dot(const Vec *a, const Vec *b) {
    f32 dot = a->x * b->x;
    dot = a->y * b->y + dot;
    return a->z * b->z + dot;
}

void TObjPlayer::invert_matrix_in_place(u32 arg0) {
    if (arg0 == 0) {
        arg0 = (u32)current_matrix;
    }
    PSMTXInverse((MtxP)arg0, (MtxP)arg0);
}

// 0x803D8A18. a × b into out, written so each fmsubs multiplies b then a.
// The length square starts before out->z is stored. The return is
// fres(frsqrte(len^2)); the y/z squares are double fmadds.
extern "C" f32 vec3_cross(const Vec *a, const Vec *b, Vec *out) {
    f32 cx = b->z * a->y - b->y * a->z;
    out->x = cx;
    f32 cy = b->x * a->z - b->z * a->x;
    out->y = cy;
    f32 cz = b->y * a->x - b->x * a->y;
    f64 mag = cx * cx;
    out->z = cz;
    mag += (f64)cy * cy;
    mag += (f64)cz * cz;
    return __fres(__frsqrte(mag));
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
