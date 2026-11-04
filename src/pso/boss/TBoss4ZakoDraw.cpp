#define TOBJECT_OUT_OF_LINE_HELPERS
#include "pso/system/NinjaTypes.h"
#include "types.h"
#include "pso/misc/MaterialColorFade.h"
#include "pso/system/vector.h"
#include "pso/boss/TBoss4DarkFalz.h"
#include "pso/boss/TBoss4Zako.h"
#include "pso/player/TObjPlayer.h"
#include "pso/boss/TBoss4Uro.h"
#include "pso/system/CurrentTextureList.h"
#include "pso/TBoss4ZakoDraw.h"
#include "pso/object/TObject_80019A50.h"
#include "pso/TParticleCtrl.h"
#include "pso/misc/TCameraCtrl.h"
#include "pso/system/BmlResource.h"

void set_constant_material(const NJS_ARGB *color);
void draw_chunk_model(void *arg0);

struct Boss4ZakoEntry {
    f32 x;
    f32 y;
    f32 z;
    s32 f0c;
    s32 f10;
};

struct Boss4ZakoBuffer {
    s32 count;
    Boss4ZakoEntry ents[96];
};

typedef char Boss4ZakoBuffer_size[sizeof(Boss4ZakoBuffer) == 0x784 ? 1 : -1];

struct FalzViewport {
    u8 prefix[0x30];
    f32 x0;
    f32 y0;
    f32 x1;
    f32 y1;
    u8 tail[8];
};

typedef char FalzViewport_size[sizeof(FalzViewport) == 0x48 ? 1 : -1];
typedef char FalzViewport_rect[offsetof(FalzViewport, x0) == 0x30 ? 1 : -1];

extern "C" {
s32 is_split_screen();
void TObjPlayer__sub_8030A9B0();
void TCameraCtrl__sub_8030ABF4(void);
void TObjPlayer__sub_80052390(f32);
void rotate_matrix_y(int, int);
void rotate_matrix_x(int, int);
void push_matrix(void);
void pop_matrix(void);
void post_translate_matrix(void *);
void draw_chunk_object(int);
void set_chunk_material_override_pair(int, int, u32, s32, s32, u32);
f32 xyz_distance(void *, void *);
}

extern const char *TBoss4ZakoDraw__class_name;
extern FalzViewport TCameraCtrl__data_804FF634;
extern TCameraCtrl *camera_ctrl_instance;
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
extern u32 dark_falz_controller_instance;
extern s32 falz_zako_texture_list;

Boss4ZakoBuffer boss4_zako_draw_buffers[2];

void TBoss4ZakoDraw::render() { TObjPlayer::toggle_particle_effect(); TCameraCtrl__sub_8030ABF4(); TParticleCtrl::end_effect_render(); }

void TBoss4ZakoDraw::run_task() {
    s32 old;
    if (dark_falz_controller_instance == 0U) {
        queue_destruction();
        return;
    }
    old = TBoss4ZakoDraw__draw_buffer_index;
    boss4_zako_draw_buffers[old].count = 0;
    TBoss4ZakoDraw__draw_buffer_index = old ^ 1;
    if (++TBoss4ZakoDraw__rotation_phase >= 4) {
        TBoss4ZakoDraw__rotation_phase = 0;
    }
}

TBoss4ZakoDraw::~TBoss4ZakoDraw() {}

TBoss4ZakoDraw::TBoss4ZakoDraw(TObject *parent) : TObject(parent) {
    m_name = TBoss4ZakoDraw__class_name;
}

extern "C" {

struct Raw_8030A9B0 { u8 b[12]; };
struct Col_8030A9B0 { f32 r, g, b, a; };

void TObjPlayer__sub_8030A9B0() {
    Raw_8030A9B0 pos;
    Raw_8030A9B0 v;
    Col_8030A9B0 col;
    Boss4ZakoBuffer *tbl;
    Boss4ZakoEntry *e;
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
    set_chunk_material_override_pair(0xFF00, 0x900, old & ~0x10, chunk_polygon_flags_or_mask, chunk_polygon_flags_and_mask, old);
    tbl = &boss4_zako_draw_buffers[TBoss4ZakoDraw__draw_buffer_index];
    e = tbl->ents;
    rot = (TBoss4ZakoDraw__rotation_phase << 16) / 16;
    VecCopy((Vec *)&pos, &camera_ctrl_instance->position);
    i = 0;
    *(f32 *)((s8 *)&pos + 4) = lbl_805DF13C;
    for (; i < tbl->count; i++, e++) {
        if (e->f0c != 0 || e->y < lbl_805DF140) {
            continue;
        }
        d = xyz_distance(e, &pos);
        if (d >= lbl_805DF144) {
            continue;
        }
        t = d / lbl_805DF144;
        k = lbl_805DF148 - t * (t * t);
        push_matrix();
        ((u32 *)&v)[0] = ((u32 *)e)[0];
        ((u32 *)&v)[1] = ((u32 *)e)[1];
        ((u32 *)&v)[2] = ((u32 *)e)[2];
        *(f32 *)((s8 *)&v + 4) = lbl_805DF13C;
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

void TObjPlayer::draw_area_chunk_objects() {
    Boss4ZakoBuffer *t = &boss4_zako_draw_buffers[TBoss4ZakoDraw__draw_buffer_index];
    Boss4ZakoEntry *p = t->ents;
    s32 r31;
    s32 i;
    r31 = get_bml_model((BmlResource *)TBoss4Uro::get_instance_count(), 8);
    TObjPlayer__sub_80052390(lbl_805DF148);
    set_current_texture_list((GinjaTextureList *)(falz_zako_texture_list));
    for (i = 0; i < t->count; i++, p++) {
        push_matrix();
        post_translate_matrix(p);
        rotate_matrix_y(0, p->f10);
        rotate_matrix_x(0, p->f0c);
        draw_chunk_object(r31);
        pop_matrix();
    }
    TObjPlayer::sync_player_globals();
}

void TCameraCtrl__sub_8030ABF4(void) {
    NJS_OBJECT *model;
    void *rect;
    if (boss4_zako_draw_buffers[TBoss4ZakoDraw__draw_buffer_index].count != 0) {
        rect = &TCameraCtrl__data_804FF634.x0;
        if (is_split_screen() == 0) {
            TCameraCtrl::set_viewport_scissor(2, rect);
        }
        model = (NJS_OBJECT *)get_bml_model((BmlResource *)TBoss4Uro::get_instance_count(), 8);
        model->child->ang[1] = TBoss4ZakoDraw__rotation_phase << 12;
        TObjPlayer::draw_area_chunk_objects();
        TObjPlayer__sub_8030A9B0();
    }
}

s32 TBoss4Zako::queue_entry(void *v, s32 a, s32 b) {
    Boss4ZakoBuffer *t = &boss4_zako_draw_buffers[TBoss4ZakoDraw__draw_buffer_index ^ 1];
    s32 n = t->count;
    Boss4ZakoEntry *e = &t->ents[n];
    if (n >= 0x60) {
        return 0;
    }
    VecCopy((Vec *)e, (const Vec *)v);
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
