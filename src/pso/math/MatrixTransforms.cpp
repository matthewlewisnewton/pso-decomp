#include "pso/math/MatrixCopy.h"
#include "types.h"
#include "pso/math/MatrixTransforms.h"
#include "dolphin/mtx.h"
#include "pso/player/TObjPlayer.h"

struct Matrix34 { f32 elements[3][4]; };

extern "C" {
s32 matrix_apply_translation(int, f32, f32, f32);
extern u32 current_matrix;
f32 sin_table_lookup(int);
f32 cos_table_lookup(int);

__declspec(section ".sdata2") extern const f64 lbl_805E0F08;
__declspec(section ".sdata2") extern const f64 lbl_805E0F10;
__declspec(section ".sdata2") extern const f64 lbl_805E0F18;

__declspec(section ".sdata2") extern const f64 lbl_805E0F38;
void rotate_matrix_z(Matrix34* matrix, s32 angle) {
    Matrix34 rotation;
    Matrix34* selected;
    if (angle != 0) {
        if (matrix == NULL) selected = (Matrix34*)current_matrix;
        else selected = matrix;
        PSMTXRotRad(rotation.elements, 'z', (f32)(lbl_805E0F38 * (f64)angle));
        PSMTXConcat(selected->elements, rotation.elements, selected->elements);
    }
}

}

#pragma push
#pragma peephole off
extern "C" void copy_matrix(MtxP dest, const f32 (*source)[4]) {
    u32 var_r0;
    u32 var_r3;
    if (dest == NULL) {
        var_r0 = current_matrix;
    } else {
        var_r0 = (u32)dest;
    }
    if (source == NULL) {
        var_r3 = current_matrix;
    } else {
        var_r3 = (u32)source;
    }
    PSMTXCopy((MtxP)var_r3, (MtxP)var_r0);
}

#pragma pop

extern "C" void subtract_vector(Vec *v, const Vec *sub) {
    v->x -= sub->x;
    v->y -= sub->y;
    v->z -= sub->z;
}

void euler_zyx_to_quaternion(u8 *arg0, u8 *arg1) {
    f32 temp_f1;
    f32 temp_f27;
    f32 temp_f28;
    f32 temp_f29;
    f32 temp_f30;
    f32 temp_f31;
    temp_f27 = sin_table_lookup((int) ((s32) *(s32 *)((s8 *)arg0 + 0) >> 1));
    temp_f28 = cos_table_lookup((int) ((s32) *(s32 *)((s8 *)arg0 + 0) >> 1));
    temp_f29 = sin_table_lookup((int) ((s32) *(s32 *)((s8 *)arg0 + 4) >> 1));
    temp_f30 = cos_table_lookup((int) ((s32) *(s32 *)((s8 *)arg0 + 4) >> 1));
    temp_f31 = sin_table_lookup((int) ((s32) *(s32 *)((s8 *)arg0 + 8) >> 1));
    temp_f1 = cos_table_lookup((int) ((s32) *(s32 *)((s8 *)arg0 + 8) >> 1));
    *(f32 *)((s8 *)arg1 + 0) = (f32) ((temp_f1 * (temp_f28 * temp_f30)) + (temp_f31 * (temp_f27 * temp_f29)));
    *(f32 *)((s8 *)arg1 + 4) = (f32) ((temp_f31 * (-temp_f28 * temp_f29)) + (temp_f1 * (temp_f27 * temp_f30)));
    *(f32 *)((s8 *)arg1 + 8) = (f32) ((temp_f27 * (temp_f30 * temp_f31)) + (temp_f28 * (temp_f29 * temp_f1)));
    *(f32 *)((s8 *)arg1 + 0xC) = (f32) ((temp_f29 * (-temp_f1 * temp_f27)) + (temp_f30 * (temp_f31 * temp_f28)));
}

void euler_yxz_to_quaternion(u8 *arg0, u8 *arg1) {
    f32 temp_f1;
    f32 temp_f27;
    f32 temp_f28;
    f32 temp_f29;
    f32 temp_f30;
    f32 temp_f31;
    temp_f27 = sin_table_lookup((int) ((s32) *(s32 *)((s8 *)arg0 + 0) >> 1));
    temp_f28 = cos_table_lookup((int) ((s32) *(s32 *)((s8 *)arg0 + 0) >> 1));
    temp_f29 = sin_table_lookup((int) ((s32) *(s32 *)((s8 *)arg0 + 4) >> 1));
    temp_f30 = cos_table_lookup((int) ((s32) *(s32 *)((s8 *)arg0 + 4) >> 1));
    temp_f31 = sin_table_lookup((int) ((s32) *(s32 *)((s8 *)arg0 + 8) >> 1));
    temp_f1 = cos_table_lookup((int) ((s32) *(s32 *)((s8 *)arg0 + 8) >> 1));
    *(f32 *)((s8 *)arg1 + 0) = (f32) ((temp_f1 * (temp_f28 * temp_f30)) + (temp_f31 * (temp_f27 * temp_f29)));
    *(f32 *)((s8 *)arg1 + 4) = (f32) ((temp_f31 * (temp_f28 * temp_f29)) + (temp_f1 * (temp_f27 * temp_f30)));
    *(f32 *)((s8 *)arg1 + 8) = (f32) ((temp_f27 * (-temp_f30 * temp_f31)) + (temp_f28 * (temp_f29 * temp_f1)));
    *(f32 *)((s8 *)arg1 + 0xC) = (f32) ((temp_f29 * (-temp_f1 * temp_f27)) + (temp_f30 * (temp_f31 * temp_f28)));
}

#pragma push
#pragma scheduling off

void translate_matrix(u32 arg0, f32 x, f32 y, f32 z) {
    u32 var_r3;
    u32 phi_r3;
    var_r3 = arg0;
    phi_r3 = var_r3;
    if (var_r3 == 0U) {
        phi_r3 = current_matrix;
    }
    matrix_apply_translation(phi_r3, x, y, z);
}
#pragma pop
