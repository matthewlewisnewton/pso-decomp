#include "pso/boss/TObjBoss7DustCtrl.h"
#include "pso/math/AngleLookup.h"
#include "pso/math/MatrixTransforms.h"
#include "pso/math/MatrixVector.h"
#include "pso/system/MatrixOps.h"
#include "pso/system/MatrixStack.h"
#include "pso/system/TrailStrip.h"
#include "pso/unk/text_803D853C.h"
#include "pso/TParticleCtrl.h"
#include "pso/player/TObjPlayer.h"
#include <stddef.h>

struct Boss7DustVertex {
    Vec position;
    u32 color;
};

typedef char Boss7DustVertexSize[sizeof(Boss7DustVertex) == 0x10 ? 1 : -1];
typedef char Boss7DustVertexColor[offsetof(Boss7DustVertex, color) == 0xC ? 1 : -1];

extern "C" {
Vec TObjBoss7DustCtrl__helix_points[6];
// Two X rotations per strip, walked as twenty consecutive angle words.
s32 TObjBoss7DustCtrl__rotation_pairs[20];
Boss7DustVertex TObjBoss7DustCtrl__transformed_vertices[60];
s32 TObjBoss7DustCtrl__vertical_phase_angles[10];
extern s32 lbl_805D6958;
extern const char *lbl_805D3FE0;
extern TObject *tl_05;

void boss7_dust_draw_at(const Vec *position, s32 slot) {
    TParticleCtrl::end_effect_render();
    push_matrix();
    post_translate_matrix(&position->x);
    draw_trail_strip(&TObjBoss7DustCtrl__transformed_vertices[slot * 6], 6, 0);
    pop_matrix();
}

s32 TObjBoss7DustCtrl__sub_802F125C(void) {
    s32 slot = lbl_805D6958;
    s32 next = slot + 1;
    lbl_805D6958 = next;
    if (next >= 10) {
        lbl_805D6958 = 0;
    }
    return slot;
}
}

void TObjBoss7DustCtrl::run_task() {
    f32 scale;
    s32 *ang;
    Boss7DustVertex *out;
    s32 *rot;
    s32 i;
    s32 j;

    rot = TObjBoss7DustCtrl__rotation_pairs;
    out = TObjBoss7DustCtrl__transformed_vertices;
    push_matrix();
    scale = 6.0f;
    ang = TObjBoss7DustCtrl__vertical_phase_angles;
    for (i = 0; i < 10; i++) {
        set_matrix_identity(NULL);
        translate_matrix(0, 0.0f, scale * sin_table_lookup(ang[i]), 0.0f);
        {
            s32 a = ang[i];
            s32 r;
            *rot += 0x1333;
            r = *rot++;
            ang[i] = a + 0x800;
            rotate_matrix_x(NULL, r);
        }
        *rot += 0x555;
        rotate_matrix_x(NULL, *rot++);
        for (j = 0; j < 6; j++) {
            matrix_mult_vec(NULL, &TObjBoss7DustCtrl__helix_points[j], &out++->position);
        }
    }
    pop_matrix();
}

TObjBoss7DustCtrl::~TObjBoss7DustCtrl() {}

TObjBoss7DustCtrl::TObjBoss7DustCtrl(TObject *parent) : TObject(parent) {
    m_name = lbl_805D3FE0;
}

void TObjBoss7DustCtrl::create() {
    new TObjBoss7DustCtrl(tl_05);
}

extern "C" {
void TObjBoss7DustCtrl__sub_802F1450(void) {}

void fn_802F1454(void) {
    // Separate loop indices preserve native allocation with the one-argument cosine API.
    s32 a;
    for (s32 i = 0; i < 6; i++) {
        a = (s32)((65536.0f / 6.0f) * (f32)i);
        f32 s = 0.7f * sin_table_lookup(a);
        TObjBoss7DustCtrl__helix_points[i].x = s;
        TObjBoss7DustCtrl__helix_points[i].y = (1.0f / 12.0f) * (f32)i;
        TObjBoss7DustCtrl__helix_points[i].z = 0.7f * cos_table_lookup(a);
    }
    {
        s32 *p = TObjBoss7DustCtrl__rotation_pairs;
        for (s32 i = 0; i < 20; i++) {
            *p++ = TObjPlayer::calc_random_scaled();
        }
    }
    {
        Boss7DustVertex *o = TObjBoss7DustCtrl__transformed_vertices;
        for (s32 i = 0; i < 60; i++) {
            o->position.x = 0.0f;
            o->position.y = 0.0f;
            o->position.z = 0.0f;
            o->color = 0xFF709070;
            o++;
        }
    }
    for (s32 j = 0; j < 10; j++) {
        TObjBoss7DustCtrl__vertical_phase_angles[j] = TObjPlayer::calc_random_scaled();
    }
    lbl_805D6958 = 0;
}
}
