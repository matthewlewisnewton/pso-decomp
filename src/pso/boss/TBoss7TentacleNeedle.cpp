#include "pso/math/MatrixCopy.h"
#include "pso/system/vector.h"
#include "types.h"
#include "pso/object/TObject_80019A50.h"
#include "pso/object/TObject_8001A448.h"
#include "pso/player/TObjPlayer_803E4954.h"
#include "pso/unk/text_803D853C.h"
#include "pso/unk/text_803E2D70.h"
#include "pso/TBoss7Tentacle.h"
#include "pso/boss/TBoss7PhotonBullet.h"
#include "pso/boss/TBoss7TentacleNeedle.h"
#include "pso/boss/TBoss7Joint.h"
#include "pso/boss/TObjBoss2Tunnel.h"
#include "pso/player/TObjPlayer.h"

struct Ten_802F08A8;
struct V_802EFF24 { f32 x, y, z; };
struct Node_802EFF24 {
    u32 flags;
    u8 pad4[4];
    V_802EFF24 pos;
    u8 pad14[8];
    s32 ang;
    u8 pad20[0xC];
    Node_802EFF24 *next;
    Node_802EFF24 *child;
    u8 pad34[4];
};
extern "C" {
TParticleCtrl *create_particle_emitter(void *pos, s32 id);
void TBoss7Tentacle__sub_802EF954(void *p);
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
void TObjPlayer__sub_802EFEC4(void);
void TObjPlayer__sub_802F0D2C(void);
s32 TObjPlayer__sub_802E80A0(void);
void fn_802EFEA8(void);
void *__dt__20TBoss7TentacleNeedleFv(TBoss7TentacleNeedle *arg0, s16 arg1);
f64 atan2_float(f32, f32);
s32 approach_angle_limited(s32, s32, s32);
s32 play_sound_effect(int, void *, int, int);
void TBoss7Tentacle__sub_802F0608(TBoss7Tentacle *tentacle, f32 len);
f32 sin_table_lookup(s32);
s32 set_matrix_identity(int);
s32 subtract_vector(void *, void *);
s32 transform_point_by_current_matrix(void *, void *);
void push_matrix(void);
void pop_matrix(void);
struct Cnt_802EF898 { u8 pad[4]; u32 n; };

typedef struct Anim_802F0BE8 { u8 pad0[4]; u32 n; } Anim_802F0BE8;

s32 attach_particle_model(int, int, int, int, int, f32);
void *spawn_particle_effect(void *pos, s32 id);
f32 horizontal_distance_squared(void *, void *);
TObjPlayer *get_player_by_client_id(s32 i);
void __dl__7TObjectFPv(void *);
void __dt__7TObjectFv(void *, int);
s32 rand(void);
s32 rotate_matrix_y(int, int);
void rotate_matrix_by_node_angles(void *, int);
s32 scale_current_matrix(void *);
void post_translate_matrix(void *);

extern s32 __vt__20TBoss7TentacleNeedle[];
extern Node_802EFF24 lbl_80541528[];
extern Vec TBoss7Tentacle__segment_offsets[];
extern u32 TBoss7Tentacle__needle_offsets[];

struct Boss7TentacleNeedleTargetState {
    s32 f0;
    s32 f4;
    s32 f8;
    u8 remaining[4];
};
extern Boss7TentacleNeedleTargetState boss7_tentacle_needle_target_state;
extern s32 lbl_805D6948;

// .rodata 0x80474070-0x804740C8 and the .sdata names are not this TU's: defined here, run_task would
// address the tables and its 10430.38 literal off one hoisted .rodata base, and defined after their
// first use CW would place them in .data.
extern const f32 lbl_80474070[3];
extern const s32 TBoss7Tentacle__target_angle_table[4];
extern const s32 boss7_tentacle_angle_table[4];
extern const char *lbl_805D3FD8;
extern const char *boss7_tentacle_needle_name_ptr;
}

void TBoss7Tentacle::restart_particle_effect() {
    s32 particle_effect;
    s32 temp_r3;
    if (fld.m_40_effect != NULL) {
        fld.m_40_effect->queue_destruction();
        fld.m_40_effect = NULL;
    }
    particle_effect = (s32)spawn_particle_effect(&position, 0x215);
    temp_r3 = particle_effect;
    if (temp_r3 != 0) {
        particle_effect = TObjPlayer__sub_802E80A0();
        attach_particle_model((int)temp_r3, (int)TObjPlayer::queue_boss_effect((void *)4), (int)particle_effect, 0, 0, 1.0f);
    }
    play_sound_effect(0x3A809, &position, 0, 0);
}

s32 TBoss7Tentacle::advance_anim_time_wrapped(f32 d) {
    f32 lim = (f32)((Cnt_802EF898 *)anim.anim_c)->n - 1.0f;
    anim.anim_t += d;
    if (lim <= anim.anim_t) {
        anim.anim_t -= lim;
    }
}

s32 TBoss7Tentacle::advance_toward_limit(f32 farg0) {
    f32 temp_f4;

    temp_f4 = anim.anim_t;
    if (temp_f4 < ((f32)((Cnt_802EF898 *)anim.anim_c)->n - 1.0f)) {
        anim.anim_t = (f32)(temp_f4 + farg0);
        return 0;
    }
    anim.anim_t = 0.0f;
    return 1;
}

void TBoss7Tentacle__sub_802EF954(void *p) {
    TBoss7Tentacle *self = (TBoss7Tentacle *)p;
    if (self->advance_toward_limit(1.0f) != 0) {
        self->queue_destruction();
        self->disallow_rendering();
    }
}

void TBoss7Tentacle::damage_nearby_players(void *p) {
    TBoss7Tentacle *self = (TBoss7Tentacle *)p;
    s32 i;
    self->advance_anim_time_wrapped(0.6f);
    for (i = 0; (u16)i != 12; i++) {
        TObjPlayer *player = get_player_by_client_id((u16)i);
        if (player != NULL && horizontal_distance_squared(&player->position, &self->position) < 100.0f) {
            if (self->m_3c == 0 && player->roll_physical_accuracy(self->m_up, 0, 10.0f) != 0) {
                player->receive_physical_attack(self->m_up, 1.0f);
            }
            if (player->obj_testFlags30(0x801) == 0) {
                DirectAttackPayload attack;
                attack.kind = 15;
                attack.power = 100.0f;
                player->receive_direct_attack(self->m_up, attack, NULL, -1, -1);
                if (self->hit.target_flags[(u16)i] == 0) {
                    spawn_particle_effect(&player->body_center_position, 0x214);
                    self->hit.target_flags[(u16)i] = 1;
                }
            }
        }
    }
    if (self->m_3c == 0x3C) {
        self->m_38 = 3;
        self->m_3c = 0;
        self->anim.anim_c = (void *)boss7_tentacle_needle_target_state.f8;
        self->anim.anim_t = 0.0f;
    } else {
        self->m_3c += 1;
    }
}

void TBoss7Tentacle::update_retract_state(void *p) {
    TBoss7Tentacle *self = (TBoss7Tentacle *)p;
    f32 temp_f1;
    temp_f1 = self->anim.anim_t;
    if ((24.5f < temp_f1) && (temp_f1 <= 25.5f)) {
        self->restart_particle_effect();
    }
    if (self->advance_toward_limit(1.0f) != 0) {
        self->m_38 = 2;
        self->m_3c = 0;
        self->anim.anim_c = (void *)boss7_tentacle_needle_target_state.f4;
        self->anim.anim_t = 0.0f;
    }
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

void TBoss7TentacleNeedle::render() {
    TObjPlayer::draw_effect();
    set_motion_packed_rotation();
    push_matrix();
    post_translate_matrix(&this->position);
    rotate_matrix_by_node_angles(&this->m_28, 1);
    draw_model_motion((void *)lbl_805D6948, (void *)this->m_78, this->m_74);
    pop_matrix();
    clear_motion_packed_rotation();
}

void TBoss7TentacleNeedle::run_task() {

    switch (this->m_38) {
    case 0:
        this->advance_needle_timer();
        return;
    case 1:
        TBoss7Tentacle::update_retract_state(this);
        return;
    case 2:
        TBoss7Tentacle::damage_nearby_players(this);
        return;
    case 3:
        TBoss7Tentacle__sub_802EF954(this);
        return;
    }
}

void *__dt__20TBoss7TentacleNeedleFv(TBoss7TentacleNeedle *arg0, s16 arg1) {
    if (arg0 != NULL) {
        *(s32 **)((s8 *)arg0 + 0x18) = __vt__20TBoss7TentacleNeedle;
        if (arg0->m_40 != NULL) { queue_destruction__7TObjectFv(arg0->m_40); arg0->m_40 = NULL; }
        __dt__7TObjectFv(arg0, 0);
        if (arg1 > 0) {
            __dl__7TObjectFPv(arg0);
        }
    }
    return arg0;
}


TBoss7TentacleNeedle::TBoss7TentacleNeedle(TObject *parent, Vec *pos)
    : TObject(parent) {
    m_name = boss7_tentacle_needle_name_ptr;
    m_34 = 1e-05f;
    m_28 = 0;
    m_2c = (s32)(65536.0f * (3.0517578e-05f * (f32)rand()));
    m_30 = 0;
    position.x = 5.0f * (3.0517578e-05f * (f32)rand()) + pos->x - 2.5f;
    position.y = pos->y;
    position.z = 5.0f * (3.0517578e-05f * (f32)rand()) + pos->z - 2.5f;
    m_38 = 0;
    m_3c = 0;
    s32 w0;
    s32 w1;
    s32 w2;
    s32 emitter_words[3];
    w2 = ((s32 *)pos)[0];
    w0 = w2;
    w1 = ((s32 *)pos)[1];
    w2 = ((s32 *)pos)[2];
    emitter_words[0] = w0;
    emitter_words[1] = w1;
    emitter_words[2] = w2;
    m_40 = create_particle_emitter(emitter_words, 0x212);
    for (s32 i = 0; i < 12; i++) {
        target_flags[i] = 0;
    }
    m_78 = (u32)boss7_tentacle_needle_target_state.f0;
    m_74 = 0.0f;
}

extern "C" {

void fn_802EFEA8(void) {
    boss7_tentacle_needle_target_state.f0 = 0;
    lbl_805D6948 = 0;
    boss7_tentacle_needle_target_state.f4 = 0;
    boss7_tentacle_needle_target_state.f8 = 0;
}

void TObjPlayer__sub_802EFEC4(void) {
    lbl_805D6948 = (s32)TObjPlayer::queue_boss_effect((void *)5);
    boss7_tentacle_needle_target_state.f0 = (s32)TObjPlayer::notify_fish_obj((void *)0x13);
    boss7_tentacle_needle_target_state.f4 = (s32)TObjPlayer::notify_fish_obj((void *)0x14);
    boss7_tentacle_needle_target_state.f8 = (s32)TObjPlayer::notify_fish_obj((void *)0x12);
}

}

void TBoss7Tentacle::render() {
    s32 var_ctr;
    TObjPlayer::draw_effect();
    push_matrix();
    switch (m_30) {
    case 0:
        set_motion_packed_rotation();
        concat_matrix((MtxP)(0), (const f32 (*)[4])m_130);
        rotate_matrix_y(0, m_13c);
        scale_current_matrix(&ent.m_24);
        draw_model_motion(ent.m_1c, ent.m_20, m_134);
        clear_motion_packed_rotation();
        break;
    case 1:
    case 4:
    case 5:
        set_motion_packed_rotation();
        concat_matrix((MtxP)(0), (const f32 (*)[4])m_130);
        rotate_matrix_zyx(0, m_140, m_13c, 0);
        scale_current_matrix(&ent.m_24);
        draw_model_motion(ent.m_1c, ent.m_20, m_134);
        clear_motion_packed_rotation();
        break;
    case 2:
        concat_matrix((MtxP)(0), (const f32 (*)[4])m_130);
        rotate_matrix_zyx(0, m_140, m_13c, 0);
        scale_current_matrix(&ent.m_24);
        draw_chunk_object(ent.m_1c);
        break;
    case 3:
        post_translate_matrix(&geo.m_40);
        scale_current_matrix((void *)(lbl_80474070));
        rotate_matrix_zyx(0, 0, m_13c, m_140);
        for (var_ctr = 0; var_ctr < 14; var_ctr++) {
            lbl_80541528[var_ctr].pos.x = geo.m_50[var_ctr].x;
            lbl_80541528[var_ctr].pos.y = geo.m_50[var_ctr].y;
            lbl_80541528[var_ctr].pos.z = geo.m_50[var_ctr].z;
            lbl_80541528[var_ctr].ang = m_f8[var_ctr];
        }
        scale_current_matrix(&ent.m_24);
        draw_chunk_object((lbl_80541528));
        break;
    }
    pop_matrix();
}

#pragma push
#pragma opt_common_subs off
void TBoss7Tentacle::update_extend_amount() {
    if (m_3c & 2) {
        m_2c = (f32)(m_2c - 0.1f);
        if (m_2c < 0.0f) {
            m_2c = 0.0f;
        }
    } else {
        m_2c += 0.2f;
        if (m_2c > 1.0f) {
            m_2c = 1.0f;
        }
    }
}
#pragma pop

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

void TBoss7Tentacle::run_task() {
    switch_state();
    switch (m_30) {
    case 0:
        advance_path_position();
        m_148 = m_148 + m_144;
        m_13c = (s32)(1365.0f * (1.0f + sin_table_lookup(m_148)));
        if (!(fld.m_4c & 1)) {
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
        concat_matrix((MtxP)(0), (const f32 (*)[4])m_130);
        transform_point_by_current_matrix(&v, &geo.m_40);
        pop_matrix();
        VecCopy(&v, &m_14c);
        subtract_vector(&v, &geo.m_40);
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
                geo.m_50[i].x = m_160 * TBoss7Tentacle__segment_offsets[i].x;
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
                    u32 st = TBoss7Joint::get_state();
                    if (st != 0U) {
                        ((TBoss7PhotonBullet *)st)->emit_hit_effect(&p);
                    }
                }
                play_sound_effect(0x3A809, &p, 0, 0);
            }
            if (m_158 >= 0.4f * len) {
                m_15c = 1.0f;
            } else {
                m_15c = m_158 / (0.4f * len);
            }
            m_140 = approach_angle_limited(m_140, boss7_tentacle_angle_table[fld.m_4c], 0x100);
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
        m_13c = approach_angle_limited(m_13c, TBoss7Tentacle__target_angle_table[fld.m_4c], 0x80);
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

extern "C" {
f32 newton_sqrtf(f32);
}

void TBoss7Tentacle__sub_802F0608(TBoss7Tentacle *tentacle, f32 len) {
    s32 i;
    s32 prev, ang;
    s32 j;
    f32 scale = 0.5f;
    f32 half = scale * len;
    f32 h = 60.0f - tentacle->fld.m_44;
    f32 a;
    f32 step = tentacle->m_158;
    a = -(h / (half * half));
    step /= 9.0f;
    f32 dx, dy, px, py, w, k;
    for (i = 0; i < 10; i++) {
        f32 t = step * (f32)i;
        f32 d = t - half;
        s32 k = i + 2;
        tentacle->geo.m_50[k].x = scale * t;
        tentacle->geo.m_50[k].y = scale * (d * (a * d) + h);
    }
    tentacle->geo.m_50[2].x = 0.0f;
    tentacle->geo.m_50[2].y = 0.0f;
    tentacle->geo.m_50[2].z = 0.0f;
    px = 0.0f;
    py = 0.0f;
    prev = 0;
    for (j = 3; j <= 11; j++) {
        f32 x = tentacle->geo.m_50[j].x;
        f32 y = tentacle->geo.m_50[j].y;
        dx = x - px;
        dy = y - py;
        px = x;
        py = y;
        ang = (s32)(10430.38043493439 * atan2_float(dy, dx));
        tentacle->m_f8[j - 1] = ang - prev;
        prev = ang;
        tentacle->geo.m_50[j].x = newton_sqrtf(dy * dy + dx * dx);
        tentacle->geo.m_50[j].y = 0.0f;
        tentacle->geo.m_50[j].z = 0.0f;
    }
    tentacle->m_f8[11] = tentacle->m_f8[10];
    w = tentacle->m_15c;
    if (w < 1.0f) {
        k = 1.0f - w;
        k *= tentacle->m_160;
        for (i = 2; i < 12; i++) {
            tentacle->geo.m_50[i].x = tentacle->geo.m_50[i].x * w + k * TBoss7Tentacle__segment_offsets[i].x;
        }
        tentacle->m_f8[2] = (s32)(16384.0f * (1.0f - tentacle->m_15c) + (f32)tentacle->m_f8[2] * w);
        for (i = 3; i < 12; i++) {
            tentacle->m_f8[i] = (s32)((f32)tentacle->m_f8[i] * w);
        }
    }
}

void TBoss7Tentacle::advance_path_position() {
    f32 lim = (f32)(((Anim_802F0BE8 *)ent.m_20)->n - 1);
    m_134 = m_134 + m_138;
    if (m_134 >= lim) {
        m_134 = m_134 - lim;
    }
}

u8 TBoss7Tentacle__sub_802F0904(TBoss7Tentacle *arg0) {
    return (u8)(arg0->m_30 == 4);
}

void TBoss7Tentacle__sub_802F0918(TBoss7Tentacle *p) { p->m_13c = 0; p->m_140 = 16384; }

void TBoss7Tentacle::reset_state() { m_13c = 0; m_140 = 0; m_38 = 0; init_segments(); m_158 = 20.0f; m_164 = 0; m_15c = 0.0f; m_160 = 1.0f; }

void TBoss7Tentacle::setup_state() { m_13c = TBoss7Tentacle__target_angle_table[fld.m_4c]; m_140 = 16384; m_38 = 0; }

void TBoss7Tentacle__sub_802F09B4(TBoss7Tentacle *p) { p->m_13c = 0; p->m_140 = 16384; }

void TBoss7Tentacle__sub_802F09C8(TBoss7Tentacle *a0) { a0->m_13c = TBoss7Tentacle__target_angle_table[a0->fld.m_4c]; a0->m_140 = 0; }

void TBoss7Tentacle::sub_802F09EC() { m_140 = 0; m_13c = 0; }

void TBoss7Tentacle::sub_802F09FC() {
    m_34 = 3;
    m_3c = (s32)(m_3c & 0xFFFFFFFD);
}

void TBoss7Tentacle__sub_802F0A14(TBoss7Tentacle *arg0) {
    arg0->m_34 = 2;
    arg0->m_3c = (s32)(arg0->m_3c & 0xFFFFFFFD);
}

void TBoss7Tentacle__sub_802F0A2C(TBoss7Tentacle *arg0) {
    arg0->m_34 = 4;
    arg0->m_3c = (s32)(arg0->m_3c & 0xFFFFFFFD);
}

void TBoss7Tentacle__sub_802F0A44(TBoss7Tentacle *arg0) {
    arg0->m_34 = 0;
    arg0->m_3c = (s32)(arg0->m_3c & 0xFFFFFFFD);
}

void TBoss7Tentacle::init_segments() {
    s32 i;
    for (i = 0; i < 14; i++) {
        VecCopy(&geo.m_50[i], &TBoss7Tentacle__segment_offsets[i]);
        m_f8[i] = TBoss7Tentacle__needle_offsets[i];
    }
}

void TBoss7Tentacle__sub_802F0AD0(TBoss7Tentacle *a0) { a0->m_138 = 1.6f; a0->m_144 = 3038; a0->m_140 = 0; a0->m_34 = 0; }

void TBoss7Tentacle__sub_802F0AF0(TBoss7Tentacle *arg0) {
    arg0->m_34 = 5;
    arg0->m_3c = (s32)(arg0->m_3c & 0xFFFFFFFD);
}

void TBoss7Tentacle::start_attack_at_position(u8 *arg1, s32 arg2) {
    s32 var_r5;
    var_r5 = arg2;
    if ((var_r5 <= 0) || (var_r5 >= 0x258)) {
        var_r5 = 0x78;
    }
    m_168 = var_r5;
    VecCopy(&m_14c, (const Vec *)arg1);
    TBoss7Tentacle__sub_802F0A14(this);
}

void TBoss7Tentacle__sub_802F0B58(TBoss7Tentacle *arg0) {
    arg0->m_34 = 1;
    arg0->m_3c = (s32)(arg0->m_3c & 0xFFFFFFFD);
}

void TBoss7Tentacle__sub_802F0B70(TBoss7Tentacle *p) { p->m_3c |= 0x2; }

void TBoss7Tentacle__sub_802F0B80(TBoss7Tentacle *p) { p->m_3c &= 0xfffffffd; }

TBoss7Tentacle::~TBoss7Tentacle() {}

TBoss7Tentacle::TBoss7Tentacle(TObject *object, s32 arg2, s32 arg3) : TObject(object) {
    m_name = lbl_805D3FD8;
    ent.m_1c = TObjPlayer::queue_boss_effect((void *)1);
    ent.m_20 = TObjPlayer::notify_fish_obj((void *)0x11);
    m_130 = arg2;
    fld.m_4c = arg3;
    m_30 = 0;
    m_34 = 0;
    m_38 = 0;
    this->init_segments();
    m_134 = (f32)(((Anim_802F0BE8 *)ent.m_20)->n - 1) * (3.0517578e-05f * (f32)rand());
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
    ent.m_24 = 1.0f;
    m_28 = 1.0f;
    m_2c = 1.0f;
}

void TObjPlayer__sub_802F0D2C(void) {  }


extern "C" {
void copy_model_node(u8 *dst, u8 *src);

// Unit-owned .bss banks (claim 1eadd7fe: pso/boss/TBoss7TentacleNeedle .bss
// 0x80541528-0x80541928). Definition order == address order: nodes 0x310,
// segment_offsets +0x310 (0xA8), needle_offsets +0x3B8 (0x38).
// In-TU defined (twin TBoss2Tentacle precedent, 100.0): enables MWCC
// base-hoist into r31 + copy-propagation sink; externs remat instead.
Node_802EFF24 lbl_80541528[14];
Vec TBoss7Tentacle__segment_offsets[14];
u32 TBoss7Tentacle__needle_offsets[14];
Boss7TentacleNeedleTargetState boss7_tentacle_needle_target_state;
s32 lbl_805D6948;

void TObjPlayer__sub_802F0D30(void) {
    Node_802EFF24 *src;
    Node_802EFF24 *dst;
    s32 i;

    src = (Node_802EFF24 *)TObjPlayer::queue_boss_effect((void *)1);
    TObjPlayer::notify_fish_obj((void *)0x11);
    dst = lbl_80541528;
    for (i = 0; i < 12; i++) {
        copy_model_node((u8 *)dst, (u8 *)src);
        dst->next = dst + 1;
        dst++;
        src = src->next;
    }
    copy_model_node((u8 *)dst, (u8 *)src);
    dst->child = dst + 1;
    copy_model_node((u8 *)&dst[1], (u8 *)src->child);
    for (i = 0; i < 14; i++) {
        lbl_80541528[i].flags &= ~3;
        TBoss7Tentacle__segment_offsets[i].x = (f64)lbl_80541528[i].pos.x;
        TBoss7Tentacle__segment_offsets[i].y = lbl_80541528[i].pos.y;
        TBoss7Tentacle__segment_offsets[i].z = lbl_80541528[i].pos.z;
        TBoss7Tentacle__needle_offsets[i] = (u32)lbl_80541528[i].ang;
    }
}
}
