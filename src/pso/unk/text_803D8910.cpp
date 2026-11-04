#include "pso/system/MatrixVectorArray.h"
#include "pso/render/DebugFont.h"
#include "pso/unk/text_803D853C.h"
#define PSO_SDK_COMPACT_MATH
#include <dolphin/gx/GXStruct.h>
#undef PSO_SDK_COMPACT_MATH

#include "types.h"

#include "stdarg.h"
// The game links the SDK's GXInitTexObj and GXSetVtxDesc under these names.
#define GXInitTexObj Dolphin_GXInitTexObj
#define GXSetVtxDesc Dolphin_GXSetVtxDesc
#include <dolphin/gx.h>
#undef GXInitTexObj
#undef GXSetVtxDesc
#include <dolphin/mtx.h>
#include <string.h>
#include "pso/player/TObjPlayer.h"
#include "pso/enemy/TObjEneMe1Gee.h"
extern "C" {
void PSMTXMultVecArray(const f32 (*m)[4], const Vec *src, Vec *dst, u32 count);
extern s32 current_matrix;
void PSMTXMultVec(const f32 (*m)[4], const Vec *src, Vec *dst);
void rotate_matrix_z(void *, s32);
void rotate_matrix_x(void *, s32);
void rotate_matrix_y(void *, s32);
void PSMTXScale(f32 (*m)[4], f32 sx, f32 sy, f32 sz);
void scale_matrix(f32 (*m)[4], f32 sx, f32 sy, f32 sz);

#pragma push
#pragma scheduling off
void matrix_mult_vec(f32 (*m)[4], const Vec *src, Vec *dst) {
    if (m == NULL) {
        m = (f32 (*)[4])current_matrix;
    }
    PSMTXMultVec(m, src, dst);
}
#pragma pop

#pragma push
#pragma scheduling off
void matrix_mult_vec_array(f32 (*m)[4], const Vec *src, Vec *dst, u32 count) {
    if (m == NULL) {
        m = (f32 (*)[4])current_matrix;
    }
    PSMTXMultVecArray(m, src, dst, count);
}
}
#pragma pop

#pragma push
#pragma scheduling off
#pragma peephole off
void get_current_matrix(void *m) {
    void *src = (*(void * *)&current_matrix);
    if (m == 0) {
        m = src;
    }
    PSMTXCopy((MtxP)src, (MtxP)m);
}
#pragma pop

#pragma push
#pragma scheduling off

void TObjPlayer::invert_matrix_in_place(u32 arg0) {
    u32 var_r3;
    var_r3 = arg0;
    if (var_r3 == 0U) {
        var_r3 = (*(u32 *)&current_matrix);
    }
    PSMTXInverse((MtxP)var_r3, (MtxP)var_r3);
}
#pragma pop

#pragma push
#pragma scheduling off
#pragma optimize_for_size off
void rotate_matrix_zyx(void *m, s32 x, s32 y, s32 z) {
    if (z != 0) {
        rotate_matrix_z(m, z);
    }
    if (y != 0) {
        rotate_matrix_y(m, y);
    }
    if (x != 0) {
        rotate_matrix_x(m, x);
    }
}
#pragma pop

void rotate_matrix_yxz(s32 matrix, s32 arg1, s32 arg2, s32 arg3) {
    if (arg2 != 0) {
        rotate_matrix_y((void *)matrix, (s32)arg2);
    }
    if (arg1 != 0) {
        rotate_matrix_x((void *)matrix, (s32)arg1);
    }
    if (arg3 != 0) {
        rotate_matrix_z((void *)matrix, (s32)arg3);
    }
}
typedef f32 Mtx_803D8B5C[3][4];
extern "C" {
void scale_matrix(f32 (*m)[4], f32 sx, f32 sy, f32 sz) {
    Mtx_803D8B5C tmp;
    f32 (*t)[4];
    if (m == NULL) t = (f32 (*)[4])current_matrix;
    else t = m;
    PSMTXScale(tmp, sx, sy, sz);
    PSMTXConcat(t, tmp, t);
}
}
