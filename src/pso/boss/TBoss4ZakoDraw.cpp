#include "pso/boss/TBoss4ZakoDrawBuffer.h"
#define TOBJECT_OUT_OF_LINE_HELPERS
#include "pso/TBoss4ZakoDraw.h"
#include "pso/misc/TCameraCtrl.h"
#include "pso/system/BmlResource.h"
#include "pso/system/CurrentTextureList.h"
#include "pso/system/NinjaTypes.h"
#include "pso/system/ChunkMaterialState.h"
#include "pso/system/MatrixStack.h"
#include "pso/player/TObjPlayer_803DF7A8.h"
#include "pso/unk/text_803E2D70.h"
#include "pso/TParticleCtrl.h"
#include "types.h"
#include "pso/system/vector.h"
#include "pso/boss/TBoss4DarkFalz.h"
#include "pso/boss/TBoss4Zako.h"
#include "pso/player/TObjPlayer.h"
#include "pso/boss/TBoss4Uro.h"
#include "pso/boss/TBoss4ZakoTexture.h"

extern "C" {
s32 is_split_screen();
void TObjPlayer__sub_8030A9B0();
extern u32 TCameraCtrl__data_804FF634[18];
extern s32 TBoss4ZakoDraw__draw_buffer_index;
extern s32 TBoss4ZakoDraw__rotation_phase;
void TCameraCtrl__sub_8030ABF4(void);
void TObjPlayer__sub_80052390(f32);
void rotate_matrix_y(int, int);
void rotate_matrix_x(int, int);
extern const f32 lbl_805DF148;
}
extern u8 *camera_ctrl_instance;
extern u32 saved_model_render_flags;
extern s32 saved_chunk_polygon_flags_and_mask;
extern s32 saved_chunk_polygon_flags_or_mask;
extern void *falz_zako_chunk_model;
extern s32 chunk_polygon_flags_or_mask;
extern s32 chunk_polygon_flags_and_mask;
extern u32 model_render_flags;
extern u32 lbl_805DF138;
extern const f32 lbl_805DF13C;
extern const f32 lbl_805DF140;
extern const f32 lbl_805DF144;
extern const f32 lbl_805DF14C;

extern const char *TBoss4ZakoDraw__class_name;
extern u32 dark_falz_controller_instance;

void TBoss4ZakoDraw::render() {
    TObjPlayer::toggle_particle_effect();
    TCameraCtrl__sub_8030ABF4();
    TParticleCtrl::end_effect_render();
}
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
#pragma push
#pragma fp_contract on
void TObjPlayer__sub_8030A9B0() {
    Vec pos;
    Boss4ZakoDrawBuffer *tbl;
    Boss4ZakoDrawEntry *e;
    s32 rot;
    s32 i;
    f32 d;
    f32 t;
    f32 k;
    saved_model_render_flags = model_render_flags;
    saved_chunk_polygon_flags_and_mask = chunk_polygon_flags_and_mask;
    saved_chunk_polygon_flags_or_mask = chunk_polygon_flags_or_mask;
    model_render_flags &= ~0x10U;
    model_render_flags |= lbl_805DF138;
    set_chunk_material_override_pair(0xFF00, 0x900);
    tbl = &boss4_zako_draw_buffers[TBoss4ZakoDraw__draw_buffer_index];
    e = tbl->entries;
    rot = (TBoss4ZakoDraw__rotation_phase << 16) / 16;
    // The shared camera slot retains its legacy byte-pointer declaration.
    VecCopy(&pos, &((TCameraCtrl *)camera_ctrl_instance)->position);
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
        // Copy initialization retains the native word copy without an assignment helper.
        Vec v = e->position;
        v.y = lbl_805DF13C;
        post_translate_matrix(&v.x);
        rotate_matrix_y(0, e->f10 + rot);
        NJS_ARGB col;
        col.b = lbl_805DF14C;
        col.g = lbl_805DF14C;
        col.a = lbl_805DF13C * k + lbl_805DF14C;
        col.r = lbl_805DF14C;
        set_constant_material(&col);
        draw_chunk_model(falz_zako_chunk_model);
        pop_matrix();
    }
    chunk_polygon_flags_and_mask = saved_chunk_polygon_flags_and_mask;
    chunk_polygon_flags_or_mask = saved_chunk_polygon_flags_or_mask;
    model_render_flags = saved_model_render_flags;
}
#pragma pop

void TObjPlayer::draw_area_chunk_objects() {
    NJS_OBJECT *model;
    Boss4ZakoDrawBuffer *t = &boss4_zako_draw_buffers[TBoss4ZakoDraw__draw_buffer_index];
    Boss4ZakoDrawEntry *p = t->entries;
    s32 i;
    model = get_bml_model(TBoss4Uro::get_instance_count(), 8);
    TObjPlayer__sub_80052390(lbl_805DF148);
    set_current_texture_list(falz_zako_texture_list);
    for (i = 0; i < t->count; i++, p++) {
        push_matrix();
        post_translate_matrix(&p->position.x);
        rotate_matrix_y(0, p->f10);
        rotate_matrix_x(0, p->f0c);
        draw_chunk_object(model);
        pop_matrix();
    }
    TObjPlayer::sync_player_globals();
}

void TCameraCtrl__sub_8030ABF4(void) {
    if (boss4_zako_draw_buffers[TBoss4ZakoDraw__draw_buffer_index].count != 0) {
        // The camera owner stores the viewport rectangle at byte offset 0x30.
        void *rect = &TCameraCtrl__data_804FF634[12];
        if (is_split_screen() == 0) {
            TCameraCtrl::set_viewport_scissor(2, rect);
        }
        NJS_OBJECT *model = get_bml_model(TBoss4Uro::get_instance_count(), 8);
        model->child->ang[1] = TBoss4ZakoDraw__rotation_phase << 12;
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
