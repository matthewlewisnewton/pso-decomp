#include "pso/system/CurrentTextureList.h"
#include "pso/boss/TBoss2Fin.h"
#include "pso/system/vector.h"
#include "pso/TObjEZRopeBase.h"
#include "pso/object/TObjFish.h"
#include "types.h"

struct G_800367C4;
extern "C" {
extern const f32 lbl_805D8458;
extern const Vec lbl_80435A44;
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
    RopeSegment *seg;
    RopeAnchor *ang;
    Vec *pt;
    s32 j;
    s32 yaw;
    Vec v;
    set_current_texture_list((GinjaTextureList *)(*(s32 *)((s8 *)(*(u8 **)((s8 *)lbl_805D4BA4 + 0x42C)) + 0x2C)));
    seg = segments;
    ang = anchors;
    pt = points;
    for (; seg->point_count >= 2; pt++, seg++, ang++) {
        for (j = seg->point_count - 1; j > 0; j--, pt++) {
            push_matrix();
            translate_matrix_vec3((u8 *)(0), (u8 *)pt);
            VecCopy(&v, pt + 1);
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
                if (seg->end_model != NULL) {
                    draw_chunk_object(seg->end_model);
                }
            } else if (seg->segment_model != NULL) {
                draw_chunk_object(seg->segment_model);
            }
            pop_matrix();
            pop_matrix();
        }
    }
    TObjLight__sub_801337F8(current_scene_light);
}

void TBoss2Fin::run_task() {
    init_link_points();
    Vec offset = lbl_80435A44;
    sub_800FF788(&offset);
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

struct In_800367C4 { u8 pad[0x8]; void *end_model; u8 pad2[0xC]; void *segment_model; };

struct G_800367C4 { u8 pad[0x42c]; In_800367C4 *in; };

extern "C" {
extern RopeSegment lbl_804FE590[];
extern const f32 lbl_805D8460;
extern const char *TBoss2Fin__name;
extern const f32 lbl_805D845C;
void TBoss2Fin__sub_800367C0(void);

TBoss2Fin::TBoss2Fin(TObject *parent, const Vec *left, const Vec *right)
    : TObjEZRopeBase(parent) {
    s32 i;
    RopeCollisionSphere *p;
    m_name = TBoss2Fin__name;
    left_position = left;
    right_position = right;
    p = sphere_storage;
    for (i = 0; i < 2; i++, p++) {
        p->radius = lbl_805D845C;
        p->center.x = TBoss2Fin__data_805D8450;
        p->center.y = TBoss2Fin__data_805D8450;
        p->center.z = TBoss2Fin__data_805D8450;
    }
    p->radius = lbl_805D8454;
    init_link_points();
    sub_800FF8CC(lbl_804FE590, anchor_storage, sphere_storage);
}

void TBoss2Fin__sub_800367C0(void) {  }
void TBoss2Fin::init_effect_table() {
    RopeSegment *p = lbl_804FE590;
    s32 i;
    for (i = 0; i < 2; i++) {
        p->point_count = 6;
        p->step.x = TBoss2Fin__data_805D8450;
        p->step.y = TBoss2Fin__data_805D8450;
        p->step.z = lbl_805D8460;
        p->segment_model = lbl_805D4BA4->in->segment_model;
        p->end_model = lbl_805D4BA4->in->end_model;
        p++;
    }
    p->point_count = -1;
}

}
