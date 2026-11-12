#include "pso/boss/TBoss4ZakoDrawBuffer.h"
#define TOBJECT_OUT_OF_LINE_HELPERS
#include "pso/TBoss4ZakoDraw.h"
#include "pso/misc/TCameraCtrl.h"
#include "pso/system/BmlResource.h"
#include "pso/system/CurrentTextureList.h"
#include "pso/system/NinjaTypes.h"
void set_constant_material(const NJS_ARGB *color);
#include "types.h"
#include "pso/misc/MaterialColorFade.h"
#include "pso/system/vector.h"
#include "pso/boss/TBoss4DarkFalz.h"
#include "pso/boss/TBoss4Zako.h"
#include "pso/player/TObjPlayer.h"
#include "pso/boss/TBoss4Uro.h"
#include "pso/boss/TBoss4ZakoTexture.h"
#include "pso/object/TObjFish.h"

struct RecoveredGlobal_8030ABF4_TCameraCtrl__data_804FF634 {
    s32 value;
    u8 remaining[0x44];
};

extern "C" {
s32 is_split_screen();
void TObjPlayer__sub_8030A9B0();
extern RecoveredGlobal_8030ABF4_TCameraCtrl__data_804FF634 TCameraCtrl__data_804FF634;
extern s32 TBoss4ZakoDraw__draw_buffer_index;
extern s32 TBoss4ZakoDraw__rotation_phase;
void TCameraCtrl__sub_8030ABF4(void);
extern s32 TBoss4ZakoDraw__draw_buffer_index;
void TObjPlayer__sub_80052390(f32);
void rotate_matrix_y(int, int);
void rotate_matrix_x(int, int);
void push_matrix(void);
void pop_matrix(void);
void post_translate_matrix(void *);
void draw_chunk_object(int);
extern s32 TBoss4ZakoDraw__draw_buffer_index;
extern const f32 lbl_805DF148;
extern s32 TBoss4ZakoDraw__draw_buffer_index;
struct Col_8030A9B0 { f32 r, g, b, a; };

void set_chunk_material_override_pair(int, int);
f32 xyz_distance(void *, void *);
}
void draw_chunk_model(void *arg0);
extern u8 *camera_ctrl_instance;
extern u32 saved_model_render_flags;
extern s32 saved_chunk_polygon_flags_and_mask;
extern s32 saved_chunk_polygon_flags_or_mask;
extern s32 falz_zako_chunk_model;
extern s32 TBoss4ZakoDraw__draw_buffer_index;
extern s32 TBoss4ZakoDraw__rotation_phase;
extern s32 chunk_polygon_flags_or_mask;
extern s32 chunk_polygon_flags_and_mask;
extern u32 model_render_flags;
extern u32 lbl_805DF138;
extern const f32 lbl_805DF13C;
extern const f32 lbl_805DF140;
extern const f32 lbl_805DF144;
extern const f32 lbl_805DF148;
extern const f32 lbl_805DF14C;

extern const char *TBoss4ZakoDraw__class_name;

TBoss4ZakoDraw::TBoss4ZakoDraw(TObject *parent) : TObject(parent) {
    m_name = TBoss4ZakoDraw__class_name;
}

extern "C" {
typedef char RecoveredGlobal_8030ABF4_TCameraCtrl__data_804FF634_size[sizeof(RecoveredGlobal_8030ABF4_TCameraCtrl__data_804FF634) == 0x48 ? 1 : -1];

#pragma push
#pragma fp_contract on
#pragma inline_depth(1)
#pragma dont_inline off
void TObjPlayer__sub_8030A9B0() {
    Vec pos;
    Vec v;
    Col_8030A9B0 col;
    Boss4ZakoDrawBuffer *tbl;
    Boss4ZakoDrawEntry *e;
    s32 rot;
    s32 i;
    f32 d;
    f32 t;
    f32 k;
    u32 old;

    old = model_render_flags;
    model_render_flags = old & ~0x10;
    saved_model_render_flags = old;
    saved_chunk_polygon_flags_and_mask = chunk_polygon_flags_and_mask;
    saved_chunk_polygon_flags_or_mask = chunk_polygon_flags_or_mask;
    model_render_flags |= lbl_805DF138;
    ((void (*)(int, int, u32, s32, s32, u32))set_chunk_material_override_pair)(0xFF00, 0x900, old & ~0x10, chunk_polygon_flags_or_mask, chunk_polygon_flags_and_mask, old);
    tbl = &boss4_zako_draw_buffers[TBoss4ZakoDraw__draw_buffer_index];
    e = tbl->entries;
    rot = (TBoss4ZakoDraw__rotation_phase << 16) / 16;
    VecCopy(&pos, (const Vec *)(camera_ctrl_instance + 0x178));
    i = 0;
    pos.y = lbl_805DF13C;
    for (; i < tbl->count; i++, e++) {
        if (e->f0c != 0 || e->position.y < lbl_805DF140) {
            continue;
        }
        d = xyz_distance(&e->position, &pos);
        if (d >= lbl_805DF144) {
            continue;
        }
        t = d / lbl_805DF144;
        k = lbl_805DF148 - t * (t * t);
        push_matrix();
        __memcpy(&v, &e->position, sizeof(Vec));
        v.y = lbl_805DF13C;
        post_translate_matrix(&v);
        rotate_matrix_y(0, e->f10 + rot);
        col.a = lbl_805DF14C;
        col.b = lbl_805DF14C;
        col.r = lbl_805DF13C * k + lbl_805DF14C;
        col.g = lbl_805DF14C;
        set_constant_material((const NJS_ARGB *)(((f32 *)&col)));
        draw_chunk_model((void *)falz_zako_chunk_model);
        pop_matrix();
    }
    chunk_polygon_flags_and_mask = saved_chunk_polygon_flags_and_mask;
    chunk_polygon_flags_or_mask = saved_chunk_polygon_flags_or_mask;
    model_render_flags = saved_model_render_flags;
}
void TObjPlayer__sub_8030A9B0();
#pragma pop

void TObjPlayer::draw_area_chunk_objects() {
    Boss4ZakoDrawBuffer *t = &boss4_zako_draw_buffers[TBoss4ZakoDraw__draw_buffer_index];
    Boss4ZakoDrawEntry *p = t->entries;
    s32 r31;
    s32 i;
    r31 = ((s32)get_bml_model(TBoss4Uro::get_instance_count(), 8));
    TObjPlayer__sub_80052390(lbl_805DF148);
    set_current_texture_list(falz_zako_texture_list);
    for (i = 0; i < t->count; i++, p++) {
        push_matrix();
        post_translate_matrix(&p->position);
        rotate_matrix_y(0, p->f10);
        rotate_matrix_x(0, p->f0c);
        draw_chunk_object(r31);
        pop_matrix();
    }
    TObjPlayer::sync_player_globals();
}

void TCameraCtrl__sub_8030ABF4(void) {
    s32 *var_r3;
    u8 *var_r31;
    u8 *var_r4;
    if (boss4_zako_draw_buffers[TBoss4ZakoDraw__draw_buffer_index].count != 0) {
        var_r3 = (s32 *)&TCameraCtrl__data_804FF634.value;
        var_r3 = (s32 *)&TCameraCtrl__data_804FF634.value;
        var_r31 = (u8 *)&TCameraCtrl__data_804FF634.value + 0x30;
        if (is_split_screen() == 0) {
            var_r4 = var_r31;
            var_r3 = (s32 *)((u8 *)((s32 *)2));
            TCameraCtrl::set_viewport_scissor(2, var_r4);
        }
        var_r4 = (u8 *)((void *)8);
        var_r3 = (s32 *)(*(s32 **)((s8 *)(get_bml_model(TBoss4Uro::get_instance_count(), 8)) + 0x2C));
        *(s32 *)((s8 *)var_r3 + 0x18) = (s32) (TBoss4ZakoDraw__rotation_phase << 0xC);
        TObjPlayer::draw_area_chunk_objects();
        TObjPlayer__sub_8030A9B0();
    }
}

s32 TBoss4Zako::queue_entry(void *v, s32 a, s32 b) {
    Boss4ZakoDrawBuffer *t = &boss4_zako_draw_buffers[TBoss4ZakoDraw__draw_buffer_index ^ 1];
    s32 n = t->count;
    Boss4ZakoDrawEntry *e = &t->entries[n];
    if (n >= 0x60) {
        return 0;
    }
    VecCopy(&e->position, (const Vec *)v);
    e->f0c = a;
    e->f10 = b;
    t->count += 1;
    return 1;
}

void TBoss4DarkFalz::clear_uro_link_state() {
    s32 i;
    for (i = 0; i < 2; i++) {
        boss4_zako_draw_buffers[i].count = 0;
    }
    TBoss4ZakoDraw__draw_buffer_index = 0;
}

}

Boss4ZakoDrawBuffer boss4_zako_draw_buffers[2];
