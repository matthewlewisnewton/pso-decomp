#pragma defer_codegen on
#define TOBJECT_OUT_OF_LINE_HELPERS
#include "pso/boss/derolle/TObjBoss2Dust.h"
#include "pso/system/vector.h"
#include "pso/system/TrailStrip.h"
#include "pso/system/MatrixStack.h"
#include "pso/boss/derolle/TObjBoss2DustCtrl.h"
#include "pso/math/MatrixTransforms.h"
#include "pso/math/MatrixVector.h"
#include "pso/unk/text_803D96A8.h"
#include "types.h"
#include "pso/effect/particle/TParticleCtrl.h"
#include "pso/player/TObjPlayer.h"
#include "pso/system/MatrixOps.h"
#include "pso/system/task/TObject.h"

extern "C" {

f32 sin_table_lookup(int);
f32 cos_table_lookup(int, f32);
void matrix_mult_vec(s32, Vec *, TrailStripVertex *);
Vec boss2_dust_points[6];
s32 boss2_dust_rotation_table[20];
TrailStripVertex boss2_dust_output_table[60];
s32 boss2_dust_random_angles[10];
extern const f32 boss2_dust_origin;
extern const f32 boss2_dust_vertical_travel;
extern const f32 boss2_dust_angle_step;
extern const f32 boss2_dust_helix_radius;
extern const f32 boss2_dust_helix_rise;
s32 TObjBoss2DustCtrl_dust_counter;

extern const f32 boss2_raft_step;
extern s32 __vt__17TObjBoss2DustCtrl[];
extern s32 tl_05;


}

struct RecoveredGlobal_8003AA9C___vt__13TObjBoss2Dust {
    s32 value;
    u8 remaining[0x14];
};
typedef char RecoveredGlobal_8003AA9C___vt__13TObjBoss2Dust_size[sizeof(RecoveredGlobal_8003AA9C___vt__13TObjBoss2Dust) == 0x18 ? 1 : -1];

extern "C" {
s32 __ct__7TObjectFP7TObject(void *, void *);
extern RecoveredGlobal_8003AA9C___vt__13TObjBoss2Dust __vt__13TObjBoss2Dust;
}

#pragma push
#pragma readonly_strings on
const char *TObjBoss2DustCtrl__name = "TObjBoss2DustCtrl";
const char *TObjBoss2Dust__name = "TObjBoss2Dust";
#pragma pop

extern "C" {
void fn_8003AD54(void) {
    s32 i;
    s32 j;

    for (i = 0; i < 6; i++) {
        s32 a = (s32)(boss2_dust_angle_step * (f32)i);
        f32 s = boss2_dust_helix_radius * sin_table_lookup(a);
        boss2_dust_points[i].x = s;
        boss2_dust_points[i].y = boss2_dust_helix_rise * (f32)i;
        boss2_dust_points[i].z = boss2_dust_helix_radius * cos_table_lookup(a, s);
    }
    {
        s32 *p = boss2_dust_rotation_table;
        for (i = 0; i < 20; i++) {
            *p++ = TObjPlayer::calc_random_scaled();
        }
    }
    {
        TrailStripVertex *o = boss2_dust_output_table;
        for (i = 0; i < 60; i++) {
            o->x = boss2_dust_origin;
            o->y = boss2_dust_origin;
            o->z = boss2_dust_origin;
            o->color = 0xFF709070;
            o++;
        }
    }
    for (j = 0; j < 10; j++) {
        boss2_dust_random_angles[j] = TObjPlayer::calc_random_scaled();
    }
    TObjBoss2DustCtrl_dust_counter = 0;
}

void TObjBoss2DustCtrl__sub_8003AD50(void) {  }
}

void TObjBoss2DustCtrl::create() {
    void* obj = TObject::operator new(0x1C);
    if (obj != 0) {
        ((s32 (*)(void *, s32))TObjBoss2DustCtrl__ct)(obj, tl_05);
    }
}

extern "C" {
void *TObjBoss2DustCtrl__ct(void *boss2_dust_ctrl) {
    void __ct__7TObjectFP7TObject(void *);
    __ct__7TObjectFP7TObject(boss2_dust_ctrl);
    *(s32 **)((s8 *)boss2_dust_ctrl + 0x18) = __vt__17TObjBoss2DustCtrl;
    ((TObjBoss2DustCtrl *)boss2_dust_ctrl)->m_name = TObjBoss2DustCtrl__name;
    return boss2_dust_ctrl;
}
}

TObjBoss2DustCtrl::~TObjBoss2DustCtrl() {}

extern "C" {
#pragma push
#pragma opt_propagation off
void TObjBoss2DustCtrl::run_task() {
    f32 scale;
    s32 *ang;
    TrailStripVertex *out;
    s32 *rot;
    s32 i;
    s32 j;

    rot = boss2_dust_rotation_table;
    out = boss2_dust_output_table;
    push_matrix();
    scale = boss2_dust_vertical_travel;
    ang = boss2_dust_random_angles;
    for (i = 0; i < 10; i++) {
        set_matrix_identity(0);
        translate_matrix(0, boss2_dust_origin, scale * sin_table_lookup(ang[i]), boss2_dust_origin);
        {
            s32 a = ang[i];
            s32 r;
            *rot += 0x1333;
            r = *rot++;
            ang[i] = a + 0x800;
            rotate_matrix_x(0, r);
        }
        *rot += 0x555;
        rotate_matrix_x(0, *rot++);
        for (j = 0; j < 6; j++) {
            matrix_mult_vec(0, &boss2_dust_points[j], out++);
        }
    }
    pop_matrix();
}
#pragma pop

s32 TObjBoss2DustCtrl__sub_8003AB5C(void) {
    s32 slot = TObjBoss2DustCtrl_dust_counter;
    TObjBoss2DustCtrl_dust_counter = slot + 1;
    if (slot + 1 >= 10) {
        TObjBoss2DustCtrl_dust_counter = 0;
    }
    return slot;
}

void boss2_dust_draw_at(const Vec *position, s32 slot) {
    TParticleCtrl::end_effect_render();
    push_matrix();
    post_translate_matrix(&position->x);
    draw_trail_strip(&boss2_dust_output_table[slot * 6], 6, 0);
    pop_matrix();
}

u8 *__ct__13TObjBoss2DustFv(u8 *object, s32 arg1, s32 arg2) {
    __ct__7TObjectFP7TObject((void *)object, (void *)arg1);
    *(s32 **)((s8 *)object + 0x18) = &__vt__13TObjBoss2Dust.value;
    *(const char **)((s8 *)object + 0) = TObjBoss2Dust__name;
    TObjBoss2Dust *dust = (TObjBoss2Dust *)object;
    VecCopy(&dust->position, (const Vec *)arg2);
    dust->ticks = 0;
    dust->strip_slot = TObjBoss2DustCtrl__sub_8003AB5C();
    return object;
}
}

TObjBoss2Dust::~TObjBoss2Dust() {}

void TObjBoss2Dust::run_task() {
    position.z -= boss2_raft_step;
    ticks++;
    if (ticks >= 90) {
        queue_destruction();
    }
}

__declspec(section ".sdata2") const f32 boss2_raft_step = 9.259259f;
__declspec(section ".sdata2") const f32 boss2_dust_origin ATTRIBUTE_ALIGN(8) = 0.0f;
__declspec(section ".sdata2") const f32 boss2_dust_vertical_travel = 6.0f;
__declspec(section ".sdata2") const f32 boss2_dust_angle_step = 65536.0f / 6.0f;
__declspec(section ".sdata2") const f32 boss2_dust_helix_radius = 0.7f;
__declspec(section ".sdata2") const f32 boss2_dust_helix_rise = 1.0f / 12.0f;
