#include "types.h"
#include "pso/math/MatrixVector.h"
#ifndef __MWERKS__
#include "libc/math.h"
#endif

struct Vec_803D8D1C { f32 x, y, z; };

extern "C" {
void matrix_identity(u8 *arg0);
extern u8 *current_matrix;
// Shared {1.0f, 0.0f} float pair in an .sdata block no unit owns yet; the
// original math kernels read their 1.0f from it instead of a pooled literal.
// The complete array type keeps the small-data (SDA21) reference of the
// original object.
extern f32 lbl_805D46AC[2];
void GXGetProjectionv(f32 *p);
void GXGetViewportv(f32 *vp);
void GXProject(f32 x, f32 y, f32 z, u8 *mtx, f32 *pm, f32 *vp, f32 *sx, f32 *sy, f32 *sz);
void project_world_to_screen(u8 *mtx, Vec_803D8D1C *pos, f32 *out);
extern f64 lbl_805E0ED8;
s32 scale_matrix(f32, f32, f32);
s32 translate_matrix(f32, f32, f32);

void scale_matrix_vec3(u8 *arg0, u8 *arg1) {
    scale_matrix((f32) (*(f32 *)((s8 *)arg1 + 0)), (f32) (*(f32 *)((s8 *)arg1 + 4)), (f32) (*(f32 *)((s8 *)arg1 + 8)));
}

// Approximate length: the original sums the squares in single precision and
// applies bare `frsqrte`+`fres` estimates to the sum. CW cannot chain those
// two without an intervening frsp (its __frsqrte is f64-typed and __fres
// f32-typed in every shipped version), so this kernel keeps the original's
// hand-written body, built from the disc like the SDK's assembly.
#ifdef __MWERKS__
asm f32 vector_length(const Vec *v) {
#include "orig_asm/pso/math/MatrixVector/vector_length.inc"
}
#else
// Scalar fallback: the exact length (the original's estimates are only
// accurate to a few bits).
f32 vector_length(const Vec *v) {
    f32 x = v->x;
    f32 y = v->y;
    f32 z = v->z;
    return sqrtf((x * x) + (y * y) + (z * z));
}
#endif

#pragma push
#pragma scheduling off
void rotate_matrix_about_axis(u8 *arg0, s32 arg1, s32 arg2) {
    u8 sp8[0x30];
    u8 *m;
    if (arg0 == 0) {
        m = current_matrix;
    } else {
        m = arg0;
    }
    if (arg2 != 0) {
        PSMTXRotAxisRad((MtxP)sp8, (Vec *)arg1, lbl_805E0ED8 * arg2);
        PSMTXConcat((MtxP)m, (MtxP)sp8, (MtxP)m);
    }
}
#pragma pop

void translate_matrix_vec3(u8 *arg0, u8 *arg1) {
    translate_matrix((f32) (*(f32 *)((s8 *)arg1 + 0)), (f32) (*(f32 *)((s8 *)arg1 + 4)), (f32) (*(f32 *)((s8 *)arg1 + 8)));
}

// Writes the 3x4 identity to arg0. The original loads the shared {1.0f, 0.0f}
// pair's first float, makes the zero pair with `ps_sub` and the {1,0} pairs
// with `ps_merge01`, and stores them with `psq_st`. CW 2.6 has no paired-
// single intrinsics and never auto-emits them, so this kernel keeps the
// original's hand-written body, built from the disc like the SDK's assembly.
#ifdef __MWERKS__
asm void matrix_identity(u8 *arg0) {
#include "orig_asm/pso/math/MatrixVector/matrix_identity.inc"
}
#else
// Scalar fallback: writes the 3x4 row-major identity matrix.
void matrix_identity(u8 *arg0) {
    f32 *m = (f32 *)arg0;
    for (int i = 0; i < 12; i++) {
        m[i] = (i % 5 == 0) ? 1.0f : 0.0f;
    }
}
#endif

#pragma push
#pragma scheduling off
void set_matrix_identity(u8 *arg0) {
    u8 *var_r3;
    var_r3 = arg0;
    if (var_r3 == NULL) {
        var_r3 = current_matrix;
    }
    matrix_identity(var_r3);
}
#pragma pop

#pragma push
#pragma fp_contract on
f32 vec_squared_length(const Vec *v) {
    f32 x = v->x;
    f32 y = v->y;
    f32 sum = x * x;
    f32 z = v->z;
    sum = (y * y) + sum;
    return (z * z) + sum;
}
#pragma pop

#pragma push
#pragma scheduling off
void project_world_to_screen(u8 *mtx, Vec_803D8D1C *pos, f32 *out) {
    f32 proj[7];
    f32 vp[6];
    f32 sz;
    f32 sy;
    f32 sx;
    u8 *m;
    GXGetProjectionv(proj);
    GXGetViewportv(vp);
    if (mtx == 0) {
        m = current_matrix;
    } else {
        m = mtx;
    }
    GXProject(pos->x, pos->y, pos->z, m, proj, vp, &sx, &sy, &sz);
    out[0] = sx;
    out[1] = sy;
}
#pragma pop

#pragma push
#pragma scheduling off
void rotate_vector_by_matrix(u32 arg0, const Vec *src, Vec *dst) {
    u32 var_r3;
    var_r3 = arg0;
    if (var_r3 == 0U) {
        var_r3 = (*(u32 *)&current_matrix);
    }
    PSMTXMultVecSR((MtxP)var_r3, src, dst);
}
#pragma pop

}
