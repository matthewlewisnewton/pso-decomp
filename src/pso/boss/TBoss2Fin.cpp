#include "pso/system/CurrentTextureList.h"
#include "pso/boss/TBoss2Fin.h"
#include "pso/system/vector.h"
#include "pso/TObjEZRopeBase.h"
#include "pso/object/TObjFish.h"
#include "types.h"
#include <stddef.h>

struct G_800367C4;
struct Stack_800365C8 {
    s32 sp8;
    s32 spC;
    s32 sp10;
};
struct RecoveredGlobal_800365C8_lbl_80435A44 {
    s32 value;
    u8 remaining[0x8];
};
struct Vec_800363B4 { f32 x, y, z; };
struct Seg_800363B4 { s8 n; u8 pad1[0xF]; void *model1; void *model2; };
struct Ang_800363B4 { s32 yaw; u8 pad4[0xC]; };
extern "C" {
extern const f32 lbl_805D8458;
extern RecoveredGlobal_800365C8_lbl_80435A44 lbl_80435A44;
f32 fabs_float(f32);
f32 atan2_float(f32, f32);
f32 get_scale_factor__10TObjPlayerFv(f32);
s32 TObjLight__sub_801337F8(s32);
s32 scale_matrix(int, f32, f32, f32);
f32 vector_length(void *);
void translate_matrix_vec3(u8 *arg0, u8 *arg1);
s32 rotate_matrix_y(int, int);
s32 subtract_vector(void *, void *);
s32 rotate_matrix_x(int, int);
s32 normalize_vector(void *);
s32 push_matrix();
s32 pop_matrix();
void draw_chunk_object(void *child);
extern const f64 lbl_80435A50[];
extern G_800367C4 *lbl_805D4BA4;
extern s32 current_scene_light;
extern const f32 lbl_805D8260;
extern const f32 TBoss2Fin__data_805D8450;
extern const f32 lbl_805D8454;

}

void TBoss2Fin::render() {
    u8 *arg0 = (u8*)this;
    Seg_800363B4 *seg;
    Ang_800363B4 *ang;
    Vec_800363B4 *pt;
    s32 j;
    s32 yaw;
    Vec_800363B4 v;
    set_current_texture_list((GinjaTextureList *)(*(s32 *)((s8 *)(*(u8 **)((s8 *)lbl_805D4BA4 + 0x42C)) + 0x2C)));
    seg = *(Seg_800363B4 * *)&this->m_20;
    ang = *(Ang_800363B4 **)((s8 *)arg0 + 0x24);
    pt = *(Vec_800363B4 * *)&this->m_2c;
    for (; seg->n >= 2; pt++, seg++, ang++) {
        for (j = seg->n - 1; j > 0; j--, pt++) {
            push_matrix();
            translate_matrix_vec3((u8 *)(0), (u8 *)pt);
            VecCopy((Vec *)&v, (const Vec *)(pt + 1));
            subtract_vector(&v, pt);
            if (TBoss2Fin__data_805D8450 == vector_length(&v)) {
                v.x = TBoss2Fin__data_805D8450;
                v.y = lbl_805D8454;
                v.z = TBoss2Fin__data_805D8450;
            } else {
                normalize_vector(&v);
            }
            yaw = 0;
            if (TBoss2Fin__data_805D8450 != fabs_float(v.x) + fabs_float(v.z)) {
                yaw = lbl_80435A50[0] * atan2_float(-v.x, -v.z);
                rotate_matrix_y(0, yaw);
            }
            rotate_matrix_x(0, lbl_80435A50[0] * get_scale_factor__10TObjPlayerFv(-v.y));
            rotate_matrix_y(0, ang->yaw - yaw);
            push_matrix();
            scale_matrix(0, lbl_805D8260, lbl_805D8260, lbl_805D8260);
            rotate_matrix_x(0, -0x4000);
            if (j == 1) {
                if (seg->model2 != NULL) {
                    draw_chunk_object(seg->model2);
                }
            } else if (seg->model1 != NULL) {
                draw_chunk_object(seg->model1);
            }
            pop_matrix();
            pop_matrix();
        }
    }
    TObjLight__sub_801337F8(current_scene_light);
}

void TBoss2Fin::run_task() {
    s32 arg0 = (s32)this;
    typedef char sp8_offset[(offsetof(Stack_800365C8, sp8) == 0x0) ? 1 : -1];
    typedef char spC_offset[(offsetof(Stack_800365C8, spC) == 0x4) ? 1 : -1];
    typedef char sp10_offset[(offsetof(Stack_800365C8, sp10) == 0x8) ? 1 : -1];
    Stack_800365C8 stack;
    ((TBoss2Fin *)arg0)->init_link_points();
    stack.sp8 = *(s32 *)((s8 *)&lbl_80435A44.value + 0);
    stack.spC = *(s32 *)((s8 *)&lbl_80435A44.value + 4);
    stack.sp10 = *(s32 *)((s8 *)&lbl_80435A44.value + 8);
    ((TObjEZRopeBase *)arg0)->sub_800FF788((void *)&stack.sp8);
}

void TBoss2Fin::init_link_points() {
    u8 *arg0 = (u8 *)this;
    *(s32 *)((s8 *)arg0 + 0x30) = 0;
    VecCopy((Vec *)(arg0 + 0x34), (const Vec *)(*(u8 **)((s8 *)arg0 + 0x80)));
    VecCopy((Vec *)(arg0 + 0x54), (const Vec *)(*(u8 **)((s8 *)arg0 + 0x80)));
    *(f32 *)((s8 *)arg0 + 0x58) = (f32) (*(f32 *)((s8 *)arg0 + 0x58) - lbl_805D8458);
    *(f32 *)((s8 *)arg0 + 0x5C) = (f32) (*(f32 *)((s8 *)arg0 + 0x5C) + lbl_805D8458);
    *(s32 *)((s8 *)arg0 + 0x40) = 0;
    VecCopy((Vec *)(arg0 + 0x44), (const Vec *)(*(u8 **)((s8 *)arg0 + 0x84)));
    VecCopy((Vec *)(arg0 + 0x64), (const Vec *)(*(u8 **)((s8 *)arg0 + 0x84)));
    *(f32 *)((s8 *)arg0 + 0x68) = (f32) (*(f32 *)((s8 *)arg0 + 0x68) - lbl_805D8458);
    *(f32 *)((s8 *)arg0 + 0x6C) = (f32) (*(f32 *)((s8 *)arg0 + 0x6C) + lbl_805D8458);
}

TBoss2Fin::~TBoss2Fin() {}

struct E_800367C4 { s8 type; f32 a; f32 b; f32 c; s32 d; s32 e; };

struct In_800367C4 { u8 pad[0x8]; s32 f8; u8 pad2[0xC]; s32 f18; };

struct G_800367C4 { u8 pad[0x42c]; In_800367C4 *in; };

struct Rec_80036718 { f32 a, b, c, d; };

struct Obj_80036718 {
    s32 f0;
    u8 pad4[0x14];
    void *vt;
    u8 pad1c[0x30 - 0x1C];
    u8 f30[0x20];
    Rec_80036718 recs[3];
    s32 f80;
    s32 f84;
};

extern "C" {
extern E_800367C4 lbl_804FE590[];
extern const f32 lbl_805D8460;
void *TObjEZRopeBase__ct(void *);
extern u8 __vt__9TBoss2Fin[];
extern s32 TBoss2Fin__name;
extern const f32 lbl_805D845C;
Obj_80036718 *__ct__9TBoss2FinFv(Obj_80036718 *self, s32 arg1, s32 arg2, s32 arg3);
void TBoss2Fin__sub_800367C0(void);

Obj_80036718 *__ct__9TBoss2FinFv(Obj_80036718 *self, s32 arg1, s32 arg2, s32 arg3) {
    s32 i;
    Rec_80036718 *p;
    TObjEZRopeBase__ct(self);
    self->vt = __vt__9TBoss2Fin;
    self->f0 = TBoss2Fin__name;
    self->f80 = arg2;
    self->f84 = arg3;
    p = self->recs;
    for (i = 0; i < 2; i++, p++) {
        p->a = lbl_805D845C;
        p->b = TBoss2Fin__data_805D8450;
        p->c = TBoss2Fin__data_805D8450;
        p->d = TBoss2Fin__data_805D8450;
    }
    p->a = lbl_805D8454;
    ((TBoss2Fin *)self)->init_link_points();
    ((TObjEZRopeBase *)self)->sub_800FF8CC((void *)((u8 *)&lbl_804FE590), (void *)self->f30, (s32)self->recs);
    return self;
}

void TBoss2Fin__sub_800367C0(void) {  }
void TBoss2Fin::init_effect_table() {
    E_800367C4 *p = lbl_804FE590;
    s32 i;
    for (i = 0; i < 2; i++) {
        p->type = 6;
        p->a = TBoss2Fin__data_805D8450;
        p->b = TBoss2Fin__data_805D8450;
        p->c = lbl_805D8460;
        p->d = lbl_805D4BA4->in->f18;
        p->e = lbl_805D4BA4->in->f8;
        p++;
    }
    p->type = -1;
}

}
