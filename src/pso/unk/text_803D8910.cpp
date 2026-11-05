#include "pso/system/MatrixVectorArray.h"
#include "pso/system/MatrixOps.h"
#include "pso/unk/text_803D853C.h"
#include "pso/unk/text_803D8F74.h"
#include "pso/system/GinjaTextureMatrices.h"
#include "pso/player/TObjPlayer.h"

// mtx.h defines MTXMultVecArray as this symbol but does not prototype it.
extern "C" void PSMTXMultVecArray(const GC_Mtx m, const Vec *src, Vec *dst, u32 count);

extern "C" asm void vec3_add_to(Vec *dst, const Vec *src) {
#include "orig_asm/pso/unk/text_803D8910/vec3_add_to.inc"
}

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


extern "C" asm f32 vec3_dot(const Vec *a, const Vec *b) {
#include "orig_asm/pso/unk/text_803D8910/vec3_dot.inc"
}

void TObjPlayer::invert_matrix_in_place(u32 arg0) {
    if (arg0 == 0) {
        arg0 = (u32)current_matrix;
    }
    PSMTXInverse((MtxP)arg0, (MtxP)arg0);
}


extern "C" asm f32 vec3_cross(const Vec *a, const Vec *b, Vec *out) {
#include "orig_asm/pso/unk/text_803D8910/vec3_cross.inc"
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
