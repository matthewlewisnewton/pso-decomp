#include "types.h"
#include "pso/math/MatrixVector.h"
#ifndef __MWERKS__
#include "libc/math.h"
#endif

extern "C" {
extern u8 *current_matrix;
void GXGetProjectionv(f32 *p);
void GXGetViewportv(f32 *vp);
void GXProject(f32 x, f32 y, f32 z, u8 *mtx, f32 *pm, f32 *vp, f32 *sx, f32 *sy, f32 *sz);
void project_world_to_screen(u8 *mtx, Vec *pos, f32 *out);
s32 scale_matrix(f32, f32, f32);
s32 translate_matrix(f32, f32, f32);

void scale_matrix_vec3(u8 *arg0, u8 *arg1) {
    scale_matrix((f32) (*(f32 *)((s8 *)arg1 + 0)), (f32) (*(f32 *)((s8 *)arg1 + 4)), (f32) (*(f32 *)((s8 *)arg1 + 8)));
}

#ifdef __MWERKS__
asm f32 vector_length(const Vec *v) {
#include "orig_asm/pso/math/MatrixVector/vector_length.inc"
}
#else
f32 vector_length(const Vec *v) {
    return sqrtf(v->x * v->x + v->y * v->y + v->z * v->z);
}
#endif

#pragma push
#pragma scheduling off
void rotate_matrix_about_axis(u8 *arg0, s32 arg1, s32 angle) {
    u8 sp8[0x30];
    u8 *m;
    if (arg0 == 0) {
        m = current_matrix;
    } else {
        m = arg0;
    }
    if (angle != 0) {
        const f64 radiansPerAngleUnit = 3.141592f / 32768.0;
        PSMTXRotAxisRad((MtxP)sp8, (Vec *)arg1, radiansPerAngleUnit * angle);
        PSMTXConcat((MtxP)m, (MtxP)sp8, (MtxP)m);
    }
}
#pragma pop

void translate_matrix_vec3(u8 *arg0, u8 *arg1) {
    translate_matrix((f32) (*(f32 *)((s8 *)arg1 + 0)), (f32) (*(f32 *)((s8 *)arg1 + 4)), (f32) (*(f32 *)((s8 *)arg1 + 8)));
}

// The paired-single identity kernel reads 1.0f from this shared {1.0f, 0.0f} pair.
extern f32 lbl_805D46AC[2];

#ifdef __MWERKS__
asm void matrix_identity(MtxP m) {
#include "orig_asm/pso/math/MatrixVector/matrix_identity.inc"
}
#else
void matrix_identity(MtxP m) {
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 4; ++col) {
            m[row][col] = row == col ? 1.0f : 0.0f;
        }
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
    matrix_identity((MtxP)var_r3);
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
void project_world_to_screen(u8 *mtx, Vec *pos, f32 *out) {
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
