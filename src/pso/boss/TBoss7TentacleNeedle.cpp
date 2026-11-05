#include "pso/math/MatrixCopy.h"
#include "pso/system/vector.h"
#include "types.h"
#include "pso/object/TObject_80019A50.h"
#include "pso/object/TObject_8001A448.h"
#include "pso/player/TObjPlayer_803E4954.h"
#include "pso/unk/text_803D853C.h"
#include "pso/unk/text_803E2D70.h"
#include "pso/TBoss7Tentacle.h"
#include "pso/boss/Boss7TentacleBanks.h"
#include "pso/boss/TBoss4Type2_800874F4.h"
#include "pso/boss/TBoss7DeRolLeC.h"
#include "pso/boss/TBoss7TentacleNeedle.h"
#include "pso/boss/TBoss7Joint.h"
#include "pso/boss/TObjBoss2Tunnel.h"
#include "pso/math/AngleLookup.h"
#include "pso/math/MatrixTransforms.h"
#include "pso/math/MatrixVector.h"
#include "pso/misc/ParticleFactory.h"
#include "pso/player/TObjPlayer.h"
#include "pso/player/TObjPlayer_80011014.h"
#include "pso/player/TObjPlayer_801AF2F0.h"
#include "pso/render/render_util.h"
#include "pso/system/MatrixStack.h"
#include "pso/system/SoundEffect.h"
#include "pso/unk/text_803D8F74.h"
#include "pso/TParticleCtrl.h"
#include <stdlib.h>

struct GinjaTextureList;

extern "C" {
u8 TBoss7Tentacle__sub_802F0904(TBoss7Tentacle *arg0);
void TBoss7Tentacle__sub_802F0918(TBoss7Tentacle *p);
void TBoss7Tentacle__sub_802F09B4(TBoss7Tentacle *p);
void TBoss7Tentacle__sub_802F09C8(TBoss7Tentacle *a0);
void TBoss7Tentacle__sub_802F0A14(TBoss7Tentacle *arg0);
void TBoss7Tentacle__sub_802F0A2C(TBoss7Tentacle *arg0);
void TBoss7Tentacle__sub_802F0A44(TBoss7Tentacle *arg0);
void TBoss7Tentacle__sub_802F0AD0(TBoss7Tentacle *a0);
void TBoss7Tentacle__sub_802F0AF0(TBoss7Tentacle *arg0);
void TBoss7Tentacle__sub_802F0B58(TBoss7Tentacle *arg0);
void TBoss7Tentacle__sub_802F0B70(TBoss7Tentacle *p);
void TBoss7Tentacle__sub_802F0B80(TBoss7Tentacle *p);
void TBoss7Tentacle__sub_802F0608(TBoss7Tentacle *tentacle, f32 len);
void TObjPlayer__sub_802EFEC4(void);
void TObjPlayer__sub_802F0D2C(void);
void fn_802EFEA8(void);

// The headers that carry these (TBoss1Dragon.h, TBoss8Dragon_80065C90.h,
// Boss7DeRolLeCBehavior.h) declare them with u8 * / s32 / void stand-ins that
// other units still rely on.
void copy_model_node(NJS_OBJECT *dst, NJS_OBJECT *src);
void attach_particle_model(TParticleCtrl *emitter, NJS_OBJECT *model, GinjaTextureList *texlist, s32 arg3, s32 arg4, f32 scale);
GinjaTextureList *TObjPlayer__sub_802E80A0(void);

struct Boss7TentacleNeedleTargetState {
    NJS_MOTION *f0;
    NJS_MOTION *f4;
    NJS_MOTION *f8;
    u8 remaining[4];
};
extern Boss7TentacleNeedleTargetState boss7_tentacle_needle_target_state;
extern NJS_OBJECT *lbl_805D6948;

// .rodata 0x80474070-0x804740C8 and the .sdata names are not this TU's: defined here, run_task would
// address the tables and its 10430.38 literal off one hoisted .rodata base, and defined after their
// first use CW would place them in .data.
extern const f32 lbl_80474070[3];
extern const s32 TBoss7Tentacle__target_angle_table[4];
extern const s32 boss7_tentacle_angle_table[4];
extern const char *lbl_805D3FD8;
extern const char *boss7_tentacle_needle_name_ptr;
}

extern "C" {
void TObjPlayer__sub_802F0D30(void) {
    NJS_OBJECT *src;
    NJS_OBJECT *dst;
    s32 i;

    src = TObjPlayer::queue_boss_effect(1);
    TObjPlayer::notify_fish_obj(0x11);
    dst = lbl_80541528;
    for (i = 0; i < 12; i++) {
        copy_model_node(dst, src);
        dst->child = dst + 1;
        dst++;
        src = src->child;
    }
    copy_model_node(dst, src);
    dst->sibling = dst + 1;
    copy_model_node(&dst[1], src->sibling);
    for (i = 0; i < 14; i++) {
        lbl_80541528[i].evalflags &= ~(NJD_EVAL_UNIT_POS | NJD_EVAL_UNIT_ANG);
        TBoss7Tentacle__segment_offsets[i].x = (f64)lbl_80541528[i].pos[0];
        TBoss7Tentacle__segment_offsets[i].y = lbl_80541528[i].pos[1];
        TBoss7Tentacle__segment_offsets[i].z = lbl_80541528[i].pos[2];
        TBoss7Tentacle__needle_offsets[i] = lbl_80541528[i].ang[2];
    }
}
}

void TObjPlayer__sub_802F0D2C(void) {  }

TBoss7Tentacle::TBoss7Tentacle(TObject *object, const f32 (*matrix)[4], s32 kind) : TObject(object) {
    m_name = lbl_805D3FD8;
    model = TObjPlayer::queue_boss_effect(1);
    motion = TObjPlayer::notify_fish_obj(0x11);
    m_130 = matrix;
    this->kind = kind;
    m_30 = 0;
    m_34 = 0;
    m_38 = 0;
    this->init_segments();
    m_134 = (f32)(motion->nbFrame - 1) * (3.0517578e-05f * (f32)rand());
    m_138 = 0.8f;
    m_13c = 0;
    m_140 = 0;
    m_144 = 0x5EF;
    m_148 = TObjPlayer::calc_random_scaled();
    m_158 = 0.0f;
    m_15c = 0.0f;
    m_164 = 0;
    m_168 = 0x78;
    m_14c.x = 0.0f;
    m_14c.y = 0.0f;
    m_14c.z = 0.0f;
    m_3c = 0;
    scale.x = 1.0f;
    scale.y = 1.0f;
    scale.z = 1.0f;
}

TBoss7Tentacle::~TBoss7Tentacle() {}

void TBoss7Tentacle__sub_802F0B80(TBoss7Tentacle *p) { p->m_3c &= 0xfffffffd; }

void TBoss7Tentacle__sub_802F0B70(TBoss7Tentacle *p) { p->m_3c |= 0x2; }

void TBoss7Tentacle__sub_802F0B58(TBoss7Tentacle *arg0) {
    arg0->m_34 = 1;
    arg0->m_3c = (s32)(arg0->m_3c & 0xFFFFFFFD);
}

void TBoss7Tentacle::start_attack_at_position(const Vec *target, s32 arg2) {
    s32 var_r5;
    var_r5 = arg2;
    if ((var_r5 <= 0) || (var_r5 >= 0x258)) {
        var_r5 = 0x78;
    }
    m_168 = var_r5;
    VecCopy(&m_14c, target);
    TBoss7Tentacle__sub_802F0A14(this);
}

void TBoss7Tentacle__sub_802F0AF0(TBoss7Tentacle *arg0) {
    arg0->m_34 = 5;
    arg0->m_3c = (s32)(arg0->m_3c & 0xFFFFFFFD);
}

void TBoss7Tentacle__sub_802F0AD0(TBoss7Tentacle *a0) { a0->m_138 = 1.6f; a0->m_144 = 3038; a0->m_140 = 0; a0->m_34 = 0; }

void TBoss7Tentacle::init_segments() {
    s32 i;
    for (i = 0; i < 14; i++) {
        VecCopy(&segments[i], &TBoss7Tentacle__segment_offsets[i]);
        m_f8[i] = TBoss7Tentacle__needle_offsets[i];
    }
}

void TBoss7Tentacle__sub_802F0A44(TBoss7Tentacle *arg0) {
    arg0->m_34 = 0;
    arg0->m_3c = (s32)(arg0->m_3c & 0xFFFFFFFD);
}

void TBoss7Tentacle__sub_802F0A2C(TBoss7Tentacle *arg0) {
    arg0->m_34 = 4;
    arg0->m_3c = (s32)(arg0->m_3c & 0xFFFFFFFD);
}

void TBoss7Tentacle__sub_802F0A14(TBoss7Tentacle *arg0) {
    arg0->m_34 = 2;
    arg0->m_3c = (s32)(arg0->m_3c & 0xFFFFFFFD);
}

void TBoss7Tentacle::sub_802F09FC() {
    m_34 = 3;
    m_3c = (s32)(m_3c & 0xFFFFFFFD);
}

void TBoss7Tentacle::sub_802F09EC() { m_140 = 0; m_13c = 0; }

void TBoss7Tentacle__sub_802F09C8(TBoss7Tentacle *a0) { a0->m_13c = TBoss7Tentacle__target_angle_table[a0->kind]; a0->m_140 = 0; }

void TBoss7Tentacle__sub_802F09B4(TBoss7Tentacle *p) { p->m_13c = 0; p->m_140 = 16384; }

void TBoss7Tentacle::setup_state() { m_13c = TBoss7Tentacle__target_angle_table[kind]; m_140 = 16384; m_38 = 0; }

void TBoss7Tentacle::reset_state() { m_13c = 0; m_140 = 0; m_38 = 0; init_segments(); m_158 = 20.0f; m_164 = 0; m_15c = 0.0f; m_160 = 1.0f; }

void TBoss7Tentacle__sub_802F0918(TBoss7Tentacle *p) { p->m_13c = 0; p->m_140 = 16384; }

u8 TBoss7Tentacle__sub_802F0904(TBoss7Tentacle *arg0) {
    return (u8)(arg0->m_30 == 4);
}

void TBoss7Tentacle::advance_path_position() {
    f32 lim = (f32)(motion->nbFrame - 1);
    m_134 = m_134 + m_138;
    if (m_134 >= lim) {
        m_134 = m_134 - lim;
    }
}

void TBoss7Tentacle__sub_802F0608(TBoss7Tentacle *tentacle, f32 len) {
    s32 i;
    s32 prev, ang;
    s32 j;
    f32 scale = 0.5f;
    f32 half = scale * len;
    f32 h = 60.0f - tentacle->base.y;
    f32 a;
    f32 step = tentacle->m_158;
    a = -(h / (half * half));
    step /= 9.0f;
    f32 dx, dy, px, py, w, k;
    for (i = 0; i < 10; i++) {
        f32 t = step * (f32)i;
        f32 d = t - half;
        s32 k = i + 2;
        tentacle->segments[k].x = scale * t;
        tentacle->segments[k].y = scale * (d * (a * d) + h);
    }
    tentacle->segments[2].x = 0.0f;
    tentacle->segments[2].y = 0.0f;
    tentacle->segments[2].z = 0.0f;
    px = 0.0f;
    py = 0.0f;
    prev = 0;
    for (j = 3; j <= 11; j++) {
        f32 x = tentacle->segments[j].x;
        f32 y = tentacle->segments[j].y;
        dx = x - px;
        dy = y - py;
        px = x;
        py = y;
        ang = (s32)(10430.38043493439 * atan2_float(dy, dx));
        tentacle->m_f8[j - 1] = ang - prev;
        prev = ang;
        tentacle->segments[j].x = newton_sqrtf(dy * dy + dx * dx);
        tentacle->segments[j].y = 0.0f;
        tentacle->segments[j].z = 0.0f;
    }
    tentacle->m_f8[11] = tentacle->m_f8[10];
    w = tentacle->m_15c;
    if (w < 1.0f) {
        k = 1.0f - w;
        k *= tentacle->m_160;
        for (i = 2; i < 12; i++) {
            tentacle->segments[i].x = tentacle->segments[i].x * w + k * TBoss7Tentacle__segment_offsets[i].x;
        }
        tentacle->m_f8[2] = (s32)(16384.0f * (1.0f - tentacle->m_15c) + (f32)tentacle->m_f8[2] * w);
        for (i = 3; i < 12; i++) {
            tentacle->m_f8[i] = (s32)((f32)tentacle->m_f8[i] * w);
        }
    }
}

void TBoss7Tentacle::run_task() {
    switch_state();
    switch (m_30) {
    case 0:
        advance_path_position();
        m_148 = m_148 + m_144;
        m_13c = (s32)(1365.0f * (1.0f + sin_table_lookup(m_148)));
        if (!(kind & 1)) {
            m_13c = -m_13c;
        }
        break;
    case 1:
        advance_path_position();
        m_140 = approach_angle_limited(m_140, 0x4000, 0x280);
        break;
    case 2:
        m_13c = approach_angle_limited(m_13c, 0, 0x80);
        if (m_13c == 0) {
            sub_802F09FC();
        }
        break;
    case 3: {
        Vec p;
        Vec v;
        f32 len;
        s32 i;
        v.x = 0.0f;
        v.y = 0.0f;
        v.z = 0.0f;
        push_matrix();
        set_matrix_identity(0);
        concat_matrix(0, m_130);
        transform_point_by_current_matrix(&v.x, &base);
        pop_matrix();
        VecCopy(&v, &m_14c);
        subtract_vector(&v, &base);
        len = normalize_vector_xz(&v);
        m_13c = (s32)(10430.38043493439 * atan2_float(v.x, v.z)) + 0x8000;
        VecCopy(&p, &m_14c);
        switch (m_38) {
        case 0:
            m_160 -= 0.1f;
            if (m_160 <= 0.1f) {
                m_160 = 0.1f;
                m_164 = 0;
                m_38 = 1;
            }
            for (i = 2; i < 12; i++) {
                segments[i].x = m_160 * TBoss7Tentacle__segment_offsets[i].x;
            }
            m_f8[2] = 0x4000;
            break;
        case 1:
            m_158 += 8.0f;
            if (m_158 > len) {
                m_158 = len;
                m_164 = 0;
                m_38 = 2;
                {
                    TBoss7DeRolLeC *st = TBoss7Joint::get_state();
                    if (st != NULL) {
                        st->emit_hit_effect(&p);
                    }
                }
                play_sound_effect(0x3A809, &p, 0, 0);
            }
            if (m_158 >= 0.4f * len) {
                m_15c = 1.0f;
            } else {
                m_15c = m_158 / (0.4f * len);
            }
            m_140 = approach_angle_limited(m_140, boss7_tentacle_angle_table[kind], 0x100);
            TBoss7Tentacle__sub_802F0608(this, len);
            break;
        case 2:
            m_164 = m_164 + 1;
            if (m_164 > m_168) {
                m_164 = 0;
                m_160 = 1.0f;
                m_38 = 3;
            }
            break;
        case 3:
            m_158 -= 8.0f;
            if (m_158 < 20.0f) {
                m_158 = 20.0f;
                m_38 = 2;
                TBoss7Tentacle__sub_802F0A2C(this);
            }
            if (m_158 >= 0.4f * len) {
                m_15c = 1.0f;
            } else {
                m_15c = m_158 / (0.4f * len);
            }
            m_140 = approach_angle_limited(m_140, 0, 0x100);
            TBoss7Tentacle__sub_802F0608(this, len);
            break;
        }
        break;
    }
    case 4:
        advance_path_position();
        m_13c = approach_angle_limited(m_13c, TBoss7Tentacle__target_angle_table[kind], 0x80);
        break;
    case 5:
        advance_path_position();
        m_140 = approach_angle_limited(m_140, 0, 0x280);
        if (m_140 == 0) {
            TBoss7Tentacle__sub_802F0A44(this);
        }
        break;
    }
    update_extend_amount();
}

void TBoss7Tentacle::switch_state() {
    s32 state = m_34;
    if (state != m_30) {
        switch (state) {
        case 0:
            sub_802F09EC();
            break;
        case 1:
            TBoss7Tentacle__sub_802F09C8(this);
            break;
        case 4:
            TBoss7Tentacle__sub_802F09B4(this);
            break;
        case 2:
            setup_state();
            break;
        case 3:
            reset_state();
            break;
        case 5:
            TBoss7Tentacle__sub_802F0918(this);
            break;
        }
        m_30 = m_34;
    }
}

void TBoss7Tentacle::update_extend_amount() {
    if (m_3c & 2) {
        scale.z = (f32)(scale.z - 0.1f);
        if (scale.z < 0.0f) {
            scale.z = 0.0f;
        }
    } else {
        scale.z += 0.2f;
        if (scale.z > 1.0f) {
            scale.z = 1.0f;
        }
    }
}

void TBoss7Tentacle::render() {
    s32 var_ctr;
    TObjPlayer::draw_effect();
    push_matrix();
    switch (m_30) {
    case 0:
        set_motion_packed_rotation();
        concat_matrix(0, m_130);
        rotate_matrix_y(0, m_13c);
        scale_current_matrix(&scale.x);
        draw_model_motion(model, motion, m_134);
        clear_motion_packed_rotation();
        break;
    case 1:
    case 4:
    case 5:
        set_motion_packed_rotation();
        concat_matrix(0, m_130);
        rotate_matrix_zyx(0, m_140, m_13c, 0);
        scale_current_matrix(&scale.x);
        draw_model_motion(model, motion, m_134);
        clear_motion_packed_rotation();
        break;
    case 2:
        concat_matrix(0, m_130);
        rotate_matrix_zyx(0, m_140, m_13c, 0);
        scale_current_matrix(&scale.x);
        draw_chunk_object(model);
        break;
    case 3:
        post_translate_matrix(&base.x);
        scale_current_matrix(lbl_80474070);
        rotate_matrix_zyx(0, 0, m_13c, m_140);
        for (var_ctr = 0; var_ctr < 14; var_ctr++) {
            lbl_80541528[var_ctr].pos[0] = segments[var_ctr].x;
            lbl_80541528[var_ctr].pos[1] = segments[var_ctr].y;
            lbl_80541528[var_ctr].pos[2] = segments[var_ctr].z;
            lbl_80541528[var_ctr].ang[2] = m_f8[var_ctr];
        }
        scale_current_matrix(&scale.x);
        draw_chunk_object((lbl_80541528));
        break;
    }
    pop_matrix();
}

extern "C" {
void TObjPlayer__sub_802EFEC4(void) {
    lbl_805D6948 = TObjPlayer::queue_boss_effect(5);
    boss7_tentacle_needle_target_state.f0 = TObjPlayer::notify_fish_obj(0x13);
    boss7_tentacle_needle_target_state.f4 = TObjPlayer::notify_fish_obj(0x14);
    boss7_tentacle_needle_target_state.f8 = TObjPlayer::notify_fish_obj(0x12);
}
}

extern "C" {
void fn_802EFEA8(void) {
    boss7_tentacle_needle_target_state.f0 = NULL;
    lbl_805D6948 = NULL;
    boss7_tentacle_needle_target_state.f4 = NULL;
    boss7_tentacle_needle_target_state.f8 = NULL;
}
}

TBoss7TentacleNeedle::TBoss7TentacleNeedle(TObject *parent, Vec *pos)
    : TObject(parent) {
    m_name = boss7_tentacle_needle_name_ptr;
    m_34 = 1e-05f;
    angle[0] = 0;
    angle[1] = (s32)(65536.0f * (3.0517578e-05f * (f32)rand()));
    angle[2] = 0;
    position.x = 5.0f * (3.0517578e-05f * (f32)rand()) + pos->x - 2.5f;
    position.y = pos->y;
    position.z = 5.0f * (3.0517578e-05f * (f32)rand()) + pos->z - 2.5f;
    m_38 = 0;
    m_3c = 0;
    const Vec emitter_position = *pos;
    m_40 = create_particle_emitter(&emitter_position, 0x212);
    for (s32 i = 0; i < 12; i++) {
        target_flags[i] = 0;
    }
    m_78 = boss7_tentacle_needle_target_state.f0;
    m_74 = 0.0f;
}

TBoss7TentacleNeedle::~TBoss7TentacleNeedle() {
    if (m_40 != NULL) {
        m_40->queue_destruction();
        m_40 = NULL;
    }
}

void TBoss7TentacleNeedle::run_task() {

    switch (this->m_38) {
    case 0:
        this->advance_needle_timer();
        return;
    case 1:
        update_retract_state();
        return;
    case 2:
        damage_nearby_players();
        return;
    case 3:
        finish_retract();
        return;
    }
}

void TBoss7TentacleNeedle::render() {
    TObjPlayer::draw_effect();
    set_motion_packed_rotation();
    push_matrix();
    post_translate_matrix(&position.x);
    rotate_matrix_by_node_angles(angle, 1);
    draw_model_motion(lbl_805D6948, this->m_78, this->m_74);
    pop_matrix();
    clear_motion_packed_rotation();
}

void TBoss7TentacleNeedle::advance_needle_timer() {
    s32 temp_r4;

    temp_r4 = this->m_3c;
    if (temp_r4 == 0x1E) {
        this->m_38 = 1;
        this->m_74 = 14.0f;
        return;
    }
    this->m_3c = (s32)(temp_r4 + 1);
}

void TBoss7TentacleNeedle::update_retract_state() {
    f32 temp_f1;
    temp_f1 = m_74;
    if ((24.5f < temp_f1) && (temp_f1 <= 25.5f)) {
        restart_particle_effect();
    }
    if (advance_toward_limit(1.0f) != 0) {
        m_38 = 2;
        m_3c = 0;
        m_78 = boss7_tentacle_needle_target_state.f4;
        m_74 = 0.0f;
    }
}

void TBoss7TentacleNeedle::damage_nearby_players() {
    s32 i;
    advance_anim_time_wrapped(0.6f);
    for (i = 0; (u16)i != 12; i++) {
        TObjPlayer *player = get_player_by_client_id((u16)i);
        if (player != NULL && horizontal_distance_squared(&player->position, &position) < 100.0f) {
            if (m_3c == 0 && player->roll_physical_accuracy(m_up, 0, 10.0f) != 0) {
                player->receive_physical_attack(m_up, 1.0f);
            }
            if (player->obj_testFlags30(0x801) == 0) {
                DirectAttackPayload attack;
                attack.kind = 15;
                attack.power = 100.0f;
                player->receive_direct_attack(m_up, attack, NULL, -1, -1);
                if (target_flags[(u16)i] == 0) {
                    spawn_particle_effect(&player->body_center_position, 0x214);
                    target_flags[(u16)i] = 1;
                }
            }
        }
    }
    if (m_3c == 0x3C) {
        m_38 = 3;
        m_3c = 0;
        m_78 = boss7_tentacle_needle_target_state.f8;
        m_74 = 0.0f;
    } else {
        m_3c += 1;
    }
}

void TBoss7TentacleNeedle::finish_retract() {
    if (advance_toward_limit(1.0f) != 0) {
        queue_destruction();
        disallow_rendering();
    }
}

s32 TBoss7TentacleNeedle::advance_toward_limit(f32 farg0) {
    f32 temp_f4;

    temp_f4 = m_74;
    if (temp_f4 < ((f32)m_78->nbFrame - 1.0f)) {
        m_74 = (f32)(temp_f4 + farg0);
        return 0;
    }
    m_74 = 0.0f;
    return 1;
}

void TBoss7TentacleNeedle::advance_anim_time_wrapped(f32 d) {
    f32 lim = (f32)m_78->nbFrame - 1.0f;
    m_74 += d;
    if (lim <= m_74) {
        m_74 -= lim;
    }
}

void TBoss7TentacleNeedle::restart_particle_effect() {
    TParticleCtrl *emitter;
    if (m_40 != NULL) {
        m_40->queue_destruction();
        m_40 = NULL;
    }
    emitter = spawn_particle_effect(&position, 0x215);
    if (emitter != NULL) {
        attach_particle_model(emitter, TObjPlayer::queue_boss_effect(4), TObjPlayer__sub_802E80A0(), 0, 0, 1.0f);
    }
    play_sound_effect(0x3A809, &position, 0, 0);
}

extern "C" {
// Defined here, in address order, so run_task and render address the banks
// off one hoisted base; as externs each access rematerialises the address.
NJS_OBJECT lbl_80541528[14];
Vec TBoss7Tentacle__segment_offsets[14];
u32 TBoss7Tentacle__needle_offsets[14];
Boss7TentacleNeedleTargetState boss7_tentacle_needle_target_state;
NJS_OBJECT *lbl_805D6948;
}
