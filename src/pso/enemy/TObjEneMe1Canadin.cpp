#pragma auto_inline off
#pragma dont_inline off
#pragma inline_depth(1)
#pragma defer_codegen on
#define TOBJECT_OUT_OF_LINE_HELPERS
#include "pso/enemy/TObjEnemy.h"
#include "pso/enemy/TObjEneRe7Berura_803E4CE0.h"
#include "pso/system/vector.h"
#include "pso/system/NinjaTypes.h"
#include "types.h"
#include "pso/enemy/TObjEneEpsilon.h"
#include "pso/enemy/TObjEneDD.h"
#include "pso/enemy/TObjEneDD_ST.h"
#include "pso/enemy/TObjEneMe1Canadin.h"
#include "pso/enemy/TObjEneMe1Canadin_EffLight.h"
#include "pso/player/TObjPlayer.h"
#include "pso/player/TObjChara.h"
#include "pso/object/TObjMotion.h"

#include "pso/enemy/TUnk_80494938.h"
#include <stddef.h>
#include "pso/system/BmlResource.h"
#include "pso/system/BmlResourceDescriptor.h"

#include "pso/enemy/TObjEneMe1CanadinLeader.h"
#include "pso/TObject.h"
#include "pso/TParticleCtrl.h"
#include "pso/boss/TBoss3Volopt.h"

#include "pso/enemy/TObjEneMe1Gee.h"
#include "pso/enemy/TObjEneRe7Berura.h"
#include "pso/object/TObjFish.h"

extern "C" {
s32 is_main_phase_15__9TObjEneDDFv();
s32 defer_render__7TObjectFv(void *);
s32 rotate_matrix_y(int, int);
s32 rotate_matrix_z(int, int);
void translate_matrix(u32 arg0, f32 x, f32 y, f32 z);
s32 push_matrix();
s32 pop_matrix();
s32 post_translate_matrix(void *);
void fn_8009BD00(void);
extern s32 lbl_8043A268[];
extern s32 lbl_8043A274[];
extern u32 lbl_805D4FD4;
extern s32 TObjEneMe1Canadin__render_point_cursor;
extern s32 saved_model_render_flags;
extern s32 model_render_flags;
extern const f32 lbl_805D9898;
extern const f32 lbl_805D98A0;
extern const f32 lbl_805D98A4;
extern const f32 lbl_805D9E84;
extern const f32 lbl_805D9E88;
f64 atan2_float(f32, f32);
void rotate_xz_pair_by_angle(f32 *arg0, f32 *arg1, s32 arg2);
void push_history_entry__17TObjEneMe1CanadinFPvfPvi(void *, f32, void *, s32);
f32 calc_elapsed_scaled__9TObjEneDDFv(void *);
s32 advance_animation__10TObjMotionFv(void *);
f32 subtract_vector(void *, void *);
extern const f64 lbl_8043A3C8;
extern const f32 TObjEneMe1Canadin__data_805D988C;
extern const f32 TObjEneMe1Canadin__data_805D98B4;
extern const f32 lbl_805D98D8;
extern const f32 lbl_805D98DC;
extern const f32 lbl_805D98E0;
extern const f32 lbl_805D98E4;
void *create_particle_emitter(void *, s32);
void TObjEneMe1Canadin_EffDischarge__ct(void *, void *, void *, void *);
u8 *TObjEneMe1Canadin_EffLine__ct(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);
void TObjEneEpsilon__sub_800B92F8(u8 *arg0, s32 arg1, f32 farg0);
s32 transition_enemy_state__9TObjEneDDFl(void *, s32);
s32 play_sound_effect(s32, void *, s32, s32);
void * __nw__7TObjectFUl(int);
extern const s32 canadin_formation_reset_vec4[];
extern u8 TObjEneMe1Canadin__map_core_default_vec4[];
extern const f32 TObjEneMe1Canadin__data_805D98BC;
extern const f32 lbl_805D9910;
u32 __cvt_fp2unsigned(f32);
extern const f32 lbl_805D9914;
s32 pack_debug_text_position(s32 arg0, s32 arg1);
void draw_chunk_object(void *child);
extern s32 lbl_8043A398[];
extern s32 lbl_8043A3A8[];
extern s32 lbl_8043A3BC[];

struct Entry_8009E860 { u16 id; u8 pad2[2]; f32 dist; };

f32 random_ratio__9TObjCharaFv(s32);
u16 get_entity_id(void *);
f32 newton_sqrtf(f32);
f32 floor_to_float(f32);
f32 get_status_value_f32__23TObjEneMe1CanadinLeaderFv(f32);
void *create_timed_particle_emitter(void *owner, s32 id, s32 b, s32 c);
void * __dt__26TObjEneDf2Bringer_Eff_RushFv(void *arg0, s16 arg1);

void TObjEneEpsilon__sub_800B92AC(u8 *arg0, s32 arg1, f32 farg0);
s32 set_target_player__12TObjEneDD_STFPv(void *);
void reset_hp__9TObjEneDDFP15BattleBaseStatsP12AttackParamsP15ActorParamBlock(void *, s32, s32, s32);
s32 transform_point_to_view(void *, int);
s32 update_camera_sequence__9TObjEneDDFv();
void initialize_enemy_state__9TObjEneDDFl(void *, s32);
void TObjEneDD__sub_800BA5A4(void *, void *, void *);
u32 is_player_entity_id(u16 arg0);
int vfunc_89__9TObjEneDDFv(void*);
void set_part_position__9TObjEneDDFPvPvi(void *, s32, s32);
void init_model__9TObjEneDDFP13CollisionBodyl(void *, void *, s32);
s32 collect_enemy_target_candidates(void *, Entry_8009E860 *);
void clear_attack_receipts__9TObjEneDDFv();
void invoke_initialization_hook__9TObjEneDDFPv(void *, void *);
s32 start_fade_in__13TUnk_80494938Fv(void *);
void TBoss3Volopt__sub_800D8D88(s32 arg0);
s32 trigger_dell_biter_events__10TObjPlayerFv(void *, f32);
s32 approach_angle_limited(s32, s32, s32);
void *find_entity_by_id(u16 id);
void free_collision_body_parts(void *);
void *get_player_by_client_id(s32 i);
s32 play_persistent_sound(s32 id, s32 a1, u32 src, s32 a3, s32 flags);
s32 rand();
f32 sin_table_lookup(int);
f32 cos_table_lookup(int);
void vec3_add_to(void *, void *);
s32 matrix_mult_vec(int, void *, int);
s32 rotate_vector_by_matrix(int, int, int);

extern const f32 TObjEneMe1Canadin__data_805D98AC;
extern NJS_ARGB canadin_formation_fade_start_color;
extern CanadinActionParameters canadin_behavior_params;
extern CanadinActionParameters canadin_projectile_param_block;
extern f32 lbl_80500960[4];
extern void *TObjEneMe1Canadin__class_name;
extern BmlResource *lbl_805D4FD0;
extern void *lbl_805D4FDC;
extern s32 lbl_805D4FE0;
extern s32 *lbl_805D4FE4;
extern s32 *lbl_805D4FE8;
extern s32 *lbl_805D4FEC;
extern s32 *lbl_805D4FF0;
extern const f32 lbl_805D9890;
extern const f32 lbl_805D9894;
extern const f32 lbl_805D989C;
extern const f32 lbl_805D98A8;
extern const f32 lbl_805D98B0;
extern const f32 lbl_805D98B8;
extern const f32 lbl_805D98D0;
extern const f32 lbl_805D98D4;
extern const f32 lbl_805D98F4;
extern const f32 lbl_805D98E8;
extern const f32 lbl_805D98EC;
extern const f32 lbl_805D98F0;
extern const f32 lbl_805D98F8;
extern const f32 lbl_805D98FC;
extern const f32 lbl_805D9900;
extern const f32 lbl_805D9904;
extern const f32 lbl_805D9908;
extern const f32 lbl_805D990C;
int is_target_android(void *p);
extern const f32 lbl_805D991C;
extern const f32 lbl_805D9918;
extern const f32 lbl_805D9920;
extern const f32 lbl_805D9924;
extern const f32 lbl_805D9928;
extern const f32 lbl_805D992C;
extern void *tl_04;

extern "C" {
extern u8 lbl_8043A1B0[];
}
extern "C" {
extern u8 lbl_8043A1C0[];
}
extern "C" {
extern u8 lbl_8043A1CC[];
}
extern "C" {
extern u8 lbl_8043A1E4[];
}
extern "C" {
extern u8 lbl_8043A1FC[];
}
extern "C" {
extern u8 lbl_8043A214[];
}
extern "C" {
extern u8 lbl_8043A22C[];
}
extern "C" {
extern u8 lbl_8043A240[];
}
extern "C" {
extern u8 lbl_8043A254[];
}
extern "C" {
extern u8 lbl_8043A2B0[];
}
extern "C" {
extern u8 lbl_8043A2CC[];
}
extern "C" {
extern u8 lbl_8043A2D8[];
}
extern "C" {
extern u8 lbl_8043A2F8[];
}
extern "C" {
extern u8 lbl_8043A308[];
}

CanadinMovementParameters canadin_setup_param_block = {
    225.0f, 0.0f, 0x600, {0, 0, 0, 0}
};
CollisionBody lbl_8048FECC = {
    {0.0f, 0.0f, 0.0f}, 8.0f, 0.0f, 0, 0x8003,
    {0.0f, 0.0f, 0.0f}, 0.0f
};
const char *bm_ene_me1_mb_model_names[3] = {
    (const char *)lbl_8043A1B0, (const char *)lbl_8043A1C0, NULL
};
const char *bm_ene_me1_mb_motion_names[7] = {
    (const char *)lbl_8043A1CC, (const char *)lbl_8043A1E4,
    (const char *)lbl_8043A1FC, (const char *)lbl_8043A214,
    (const char *)lbl_8043A22C, (const char *)lbl_8043A240, NULL
};
BmlResourceDescriptor bm_ene_me1_mb_resource_descriptor = {
    (const char *)lbl_8043A254, bm_ene_me1_mb_model_names,
    bm_ene_me1_mb_motion_names, 2, 6
};
TObjMotionAction lbl_8048FF30[7] = {
    {1, 0, 4, 0.2f, 0},
    {1, 0, 5, 0.2f, 0},
    {2, 1, 1, 0.5f, 0},
    {2, 0, 0, 0.5f, 0},
    {2, 0, 2, 0.7f, 0},
    {2, 1, 3, 0.6f, 0},
    {3, 0, 1, 0.5f, 0}
};
s8 *canadin_leader_fade_sequence_table[5] = {
    (s8 *)lbl_8043A2B0, (s8 *)lbl_8043A2CC, (s8 *)lbl_8043A2D8,
    (s8 *)lbl_8043A2F8, (s8 *)lbl_8043A308
};

u32 lbl_80500930[3];
u32 lbl_8050093C[3];
u32 lbl_80500948[3];
u32 lbl_80500954[3];
#define lbl_80500930 ((s32 *)lbl_80500930)
#define lbl_8050093C ((s32 *)lbl_8050093C)
#define lbl_80500948 ((s32 *)lbl_80500948)
#define lbl_80500954 ((s32 *)lbl_80500954)

void *__dt__26TObjEneDf2Bringer_Eff_RushFv(void *arg0, s16 arg1);

extern s32 TObjEneMe1CanadinLeader__class_name;

}
u8 * construct_bringer_rush_effect(u8 *arg0, s32 arg1, u8 *arg2, s32 arg3, f32 farg0);
u8 *construct_bringer_rush_effect(u8 *arg0, s32 arg1, u8 *arg2, s32 arg3, f32 farg0);

extern "C" {
TObjEneMe1Canadin::TObjEneMe1Canadin(TObject *parent, void *set_data, s32 kind)
    : TObjEneDD_ST(parent) {
    m_name = (const char *)TObjEneMe1Canadin__class_name;
    invoke_initialization_hook__9TObjEneDDFPv(this, set_data);
    m_3c8 = 0;
    update_by_field_0x354();
    m_3c0 = this;
    m_3c4 = kind;
    setup_enemy();
}

TObjEneMe1Canadin::TObjEneMe1Canadin(TObject *parent, TObjEneMe1Canadin *leader, Vec *spawn_position, s32 id, s32 index)
    : TObjEneDD_ST(parent) {
    m_name = (const char *)TObjEneMe1Canadin__class_name;
    m_3c0 = leader;
    init_common_from((u8 *)m_3c0);
    entity_id = id;
    set_index = index;
    m_3c0->calc_move_vector(&position);
    VecCopy(&position, spawn_position);
    rotation_y = m_3c0->rotation_y;
    m_3c8 = 0;
    m_3c4 = 1;
    setup_enemy();
}

#pragma push
#pragma fp_contract on
void TObjEneMe1Canadin::setup_enemy() {
    u8 *arg0 = (u8 *)this;
    s32 i;

    this->init_position_vectors();
    this->vfunc_106();
    init_model__9TObjEneDDFP13CollisionBodyl(arg0, &lbl_8048FECC, 1);
    ((TObjMotion *)arg0)->set_field_d8((s32)lbl_8048FF30);
    ((TObjMotion *)arg0)->set_field_dc((s32)lbl_805D4FD0->motions);
    m_b8 = 0;
    ((TObjMotion *)arg0)->set_animation(m_b8);
    ((TObjMotion *)arg0)->set_field_b8(m_b8);
    reset_hp__9TObjEneDDFP15BattleBaseStatsP12AttackParamsP15ActorParamBlock(arg0, lbl_80500930[m_3c4], lbl_8050093C[m_3c4], lbl_80500948[m_3c4]);
    this->check_state_flag_4();
    movementParameters = &canadin_setup_param_block;
    initialize_enemy_state__9TObjEneDDFl(arg0, 0x1C);
    m_37c = lbl_805D989C;
    this->enemy_init_acquire_period(0x2D);
    this->enemy_init_validate_period(0x2D);
    this->set_active();
    actorFlags |= 0x01000000;
    m_468 = (CanadinParameters *)lbl_80500954[m_3c4];
    m_3cc.reset_color();
    m_3e8 = lbl_805D9928;
    m_3ec = lbl_805D98A4;
    m_3f0 = TObjEneMe1Canadin__data_805D98AC * (lbl_805D992C * (f32)rand()) + lbl_805D98A4;
    m_3f4 = m_3ec;
    hover_y = position.y + m_3f4;
    m_3fc = 4;
    m_400 = 0;
    m_404 = 0;
    m_408 = new TObjEneMe1Canadin_EffLight(this, 5);
    m_40c = 0;
    m_410 = 0;
    for (i = 0; i < 7; i++) {
        VecCopy((Vec *)(&m_414[i]), (const Vec *)(&position));
    }
    m_46c = 0;
    m_470 = 0;
    m_474 = 0;
    m_478 = 0;
    m_47c = 0;
    m_480 = 0;
    m_484 = lbl_805D9898;
    m_488 = lbl_805D9898;
    m_48c = lbl_805D9898;
    m_490.x = lbl_805D9898;
    m_490.y = lbl_805D9898;
    m_490.z = lbl_805D9898;
    m_49c = NULL;
    m_4a0 = NULL;
    copy_argb(&m_4a4, (NJS_ARGB *)TObjEneMe1Canadin__map_core_default_vec4);
    m_4a4.a = lbl_805D9898;
    m_4b8 = 0;
    m_4b4 = 0;
    m_4bc = 0;
    m_4c0 = 0;
    m_4c4 = 0;
    copy_pos();
    set_part_position__9TObjEneDDFPvPvi(arg0, (s32)bodies, 0);
    mode = 0;
    this->dispatch_action(mode, 4);
    if (m_3c0 != NULL) {
        m_4c8 = get_entity_id(m_3c0);
    } else {
        m_4c8 = 0xFFFF;
    }
}
#pragma pop

TObjEneMe1Canadin::~TObjEneMe1Canadin() {
    if (m_4a0 != NULL) {
        m_4a0->queue_destruction();
        m_4a0 = NULL;
    }
    m_408->queue_destruction();
    m_408 = NULL;
    free_collision_body_parts(this);
}

void TObjEneMe1Canadin::run_task() {
    u8 *arg0 = (u8 *)this;
    TObjEneMe1Canadin *temp_r3;
    if (TObjPlayer::check_demo_mode() != 0) {
        this->update_if_ready();
        return;
    }
    if (((s32) m_3c4 == 1) && ((m_3c0 = (TObjEneMe1Canadin *)find_entity_by_id(m_4c8), temp_r3 = m_3c0, temp_r3 == NULL) || (temp_r3->all_parents_unqueued_for_destruction() == 0))) {
        queue_destruction();
        return;
    }
    if (this->vfunc_83() != 4) {
        this->vfunc_85();
        update_fade_sequence();
    }
    copy_pos();
    this->submit_default_cursor_candidate();
    this->vfunc_100();
}

void TObjEneMe1Canadin::vfunc_28() {  }

void TObjEneMe1Canadin::vfunc_63() {
    s16 temp_r0;

    temp_r0 = mode;
    if ((temp_r0 != 0xD) && (temp_r0 != 0xB)) {
        transition_enemy_state(0xD);
    }
}

void TObjEneMe1Canadin::vfunc_62() { if (mode != 12) { transition_enemy_state(12); } }

void TObjEneMe1Canadin::vfunc_61() {  }

void TObjEneMe1Canadin::copy_pos() {
    m_2fc = (f32) position.x;
    m_300 = (f32) hover_y;
    m_304 = (f32) position.z;
    VecCopy(&center, body_center());
}

void TObjEneMe1Canadin::vfunc_88() {
    TObjEneMe1Canadin *o = this;
    m_3f4 = (f32) (hover_y - position.y);
    if (m_3f4 < lbl_805D98D0) {
        o->vfunc_98();
    } else {
        o->vfunc_97();
    }
    bodies[0].offset.y = (f32) m_3f4;
}

void TObjEneMe1Canadin::update_by_field_0x354() {
    if ((s32) floor_to_float(parameters[0]) == 0) {
        this->fn_8009E350();
        return;
    }
    this->fn_8009E334();
}

void TObjEneMe1Canadin::vfunc_106() {
    model = (void *)lbl_805D4FD0->models[0].model;
    texlist = lbl_805D4FD0->models[1].m_c;
}

#pragma push
#pragma fp_contract on
void TObjEneMe1Canadin::calc_move_vector(Vec *arg1) {
    f32 temp_f1;
    f32 temp_f31;
    s32 random_scaled;

    random_scaled = TObjEneDD::get_random_scaled();
    f32 fv = random_ratio();
    temp_f31 = (lbl_805D98D0 * fv) + lbl_805D989C;
    temp_f1 = temp_f31 * sin_table_lookup(random_scaled);
    arg1->x = temp_f1;
    arg1->y = (f32) lbl_805D9898;
    arg1->z = (f32) (temp_f31 * cos_table_lookup(random_scaled));
    vec3_add_to(arg1, &position);
}
#pragma pop

u8 *TObjEneMe1Canadin::vfunc_101(u8 *pos) {
    u8 *result = TObjEneDD::vfunc_101(pos);
    if (result == 0) {
        m_3c8 &= 0xFEFFFFFF;
    } else {
        m_3c8 |= 0x01000000;
    }
    return result;
}

void TObjEneMe1Canadin::approach_hover_y(f32 target_y) {
    f32 temp_f3;
    temp_f3 = target_y - hover_y;
    m_3c8 = (s32) (m_3c8 & 0xFFF7FFFF);
    if (temp_f3 >= TObjEneMe1Canadin__data_805D98BC) {
        hover_y = (f32) (hover_y + TObjEneMe1Canadin__data_805D98BC);
        return;
    }
    if (temp_f3 <= lbl_805D9924) {
        hover_y = (f32) (hover_y - TObjEneMe1Canadin__data_805D98BC);
        return;
    }
    hover_y = target_y;
    m_3c8 = (s32) (m_3c8 | 0x80000);
}

void TObjEneMe1Canadin::update_position_with_offset() {
    this->approach_hover_y(position.y + m_3e8);
}

void TObjEneMe1Canadin::update_hover_position(f32 height) {
    Vec stack;
    this->approach_hover_y(height);
    VecCopy((Vec *)(&stack), (const Vec *)(&position));
    stack.y = hover_y;
    this->vfunc_101((u8 *)&stack);
}

void TObjEneMe1Canadin::set_target_speed_z() {
    this->update_hover_position((m_3ec + position.y));
}

void TObjEneMe1Canadin::update_hover_height() {
    this->update_hover_position((m_3e8 + position.y));
}

void TObjEneMe1Canadin::update_angle() {
    rotation_y = approach_angle_limited(rotation_y, (s32) (lbl_8043A3C8 * atan2_float(m_3a0.x, m_3a0.z)), 0x400);
    rotation_y = (s32) (s16) rotation_y;
}

void TObjEneMe1Canadin::update_move() {
    if (enemy_has_live_target() != 0) {
        enemy_copy_target_destination();
        update_velocity();
        update_angle();
    }
}

void TObjEneMe1Canadin::vfunc_105() {
    u8 *arg0 = (u8 *)this;
    if (m_3c8 & 0x100) {
        transition_enemy_state__9TObjEneDDFl(arg0, 7);
        return;
    }
    if ((s32) m_3c4 == 0) {
        if ((s32) m_46c < 2) {
            transition_enemy_state__9TObjEneDDFl(arg0, 6);
            m_46c = (s32) (m_46c + 1);
            return;
        }
        transition_enemy_state__9TObjEneDDFl(arg0, 7);
        m_46c = 0;
        return;
    }
    transition_enemy_state__9TObjEneDDFl(arg0, 6);
}

void TObjEneMe1Canadin::vfunc_89() { vfunc_89__9TObjEneDDFv(this); }

void TObjEneMe1Canadin::fn_8009E948() {
    bodies[0].flags |= 0x28;
}

void TObjEneMe1Canadin::fn_8009E930() {
    bodies[0].flags &= ~0x28;
}

s32 TObjEneMe1Canadin::fn_8009E860(f32 *out, f32 _w2) {
    TObjEneMe1Canadin *self = this;
    Entry_8009E860 list[5];
    s32 found;
    s32 count;
    u32 id;
    s32 i;
    found = 0;
    *out = lbl_805D98F4;
    count = collect_enemy_target_candidates(self, list);
    for (i = 0; i < count; i++) {
        id = (u32)get_player_by_client_id(list[i].id);
        if (id != (u32)self->m_390) {
            self->m_3c0 = (TObjEneMe1Canadin *)find_entity_by_id(self->m_4c8);
            if (self->m_3c0->vfunc_116((TObjChara *)id) != 0) {
                *out = newton_sqrtf(list[i].dist);
                found = 1;
                self->set_target_player((void *)id);
                break;
            }
        }
    }
    return found;
}

s32 TObjEneMe1Canadin::check_target() {
    f32 sp8;
    s32 var_r31;

    var_r31 = 0;
    if (m_3ac < lbl_805D98E4) {
        var_r31 = 1;
        m_3c0 = (TObjEneMe1Canadin *)find_entity_by_id(m_4c8);
        if ((m_3c0->vfunc_116(m_390) == 0) && (this->fn_8009E860(&sp8, lbl_805D9920) != 0) && (sp8 > lbl_805D98E4)) {
            var_r31 = 0;
        }
    }
    return var_r31;
}

void TObjEneMe1Canadin::advance_state_4_to_5() {
    if ((s32) m_3fc == 4) {
        m_b8 = 2;
        m_3fc = 5;
    }
}

void TObjEneMe1Canadin::advance_state_5_to_4() {
    if ((s32) m_3fc == 5) {
        m_b8 = 3;
        m_3fc = 4;
    }
}

s32 TObjEneMe1Canadin::fn_8009E76C() {
    return m_3f4 < lbl_805D991C;
}

void TObjEneMe1Canadin::vfunc_107() {  }

s32 TObjEneMe1Canadin::vfunc_108() {
    u8 *arg0 = (u8 *)this;
    s32 temp_r4;
    temp_r4 = m_3c8;
    if (temp_r4 & 0x20) {
        m_3c8 = (s32) (temp_r4 & 0xFFFFFFDF);
        transition_enemy_state__9TObjEneDDFl(arg0, 0xA);
        m_40c = 0;
        return 1;
    }
    if (temp_r4 & 0x40) {
        m_3c8 = (s32) (temp_r4 & 0xFFFFFFBF);
        transition_enemy_state__9TObjEneDDFl(arg0, 0xB);
        return 1;
    }
    return 0;
}

s32 TObjEneMe1Canadin::try_trigger_action() {
    if (m_390 == NULL) {
        transition_enemy_state__9TObjEneDDFl(this, 0xE);
        return 1;
    }
    return 0;
}

void TObjEneMe1Canadin::fn_8009E6B0() {
      }

void TObjEneMe1Canadin::vfunc_104(f32 distance) {
    TObjEneDD_ST::select_and_apply_target(distance);
}

void TObjEneMe1Canadin::update_fade_sequence() {
    TObjEneMe1Canadin *p = this;
    switch (p->m_4b8) {
    case 0:
        break;
    case 1:
        if (p->m_4a4.a > lbl_805D9898) {
            p->m_4a4.a = p->m_4a4.a - lbl_805D9918;
        } else {
            p->m_4a4.a = lbl_805D9898;
            p->m_4b8 = 0;
        }
        p->pack_color_rgba();
        break;
    case 2:
        if (p->m_4a4.a < lbl_805D98D4) {
            p->m_4a4.a = p->m_4a4.a + lbl_805D9918;
        } else {
            p->m_4a4.a = lbl_805D98D4;
            p->m_4b8 = 0;
        }
        p->pack_color_rgba();
        break;
    case 3:
        p->m_4c0++;
        if ((f32)p->m_4c0 >= lbl_805D98B0) {
            p->m_4c0 = 0;
            switch (canadin_leader_fade_sequence_table[p->m_4bc][p->m_4c4++]) {
            case 0x62:
                p->m_4a4.a = lbl_805D9898;
                break;
            case 0x63:
                p->m_4b8 = 0;
                copy_argb((NJS_ARGB *)&p->m_4a4.a, (NJS_ARGB *)canadin_formation_reset_vec4);
                break;
            case 0x61:
                p->m_4a4.a = lbl_805D98D4;
                break;
            }
            p->pack_color_rgba();
        }
        break;
    }
}

void TObjEneMe1Canadin::fn_8009E4AC(s32 arg1) {
    this->reset_map_core(&canadin_formation_fade_start_color);
    m_4b8 = 3;
    m_4bc = arg1;
    m_4c0 = 2;
    m_4c4 = 0;
}

void TObjEneMe1Canadin::reset_map_core(NJS_ARGB *color) { copy_argb(&m_4a4, color); pack_color_rgba(); }

void TObjEneMe1Canadin::pack_color_rgba() {
    m_4b4 = ((u8) __cvt_fp2unsigned(lbl_805D9914 * m_4a4.g) << 24)
        | ((u8) __cvt_fp2unsigned(lbl_805D9914 * m_4a4.b) << 16)
        | ((u8) __cvt_fp2unsigned(TObjEneMe1Canadin__data_805D98B4 * (lbl_805D9914 * m_4a4.a)) << 8)
        | (u8) __cvt_fp2unsigned(lbl_805D9914 * m_4a4.r);
}

void TObjEneMe1Canadin::vfunc_113() {
    *lbl_805D4FEC = m_4b4;
    *lbl_805D4FF0 = m_4b4;
}

int TObjEneMe1Canadin::vfunc_109() { return 1; }

void TObjEneMe1Canadin::fn_8009E378() {
    if ((s16) mode == 2) {
        m_3c0 = (TObjEneMe1Canadin *)find_entity_by_id(m_4c8);
        m_3c0->fn_8009E2DC();
    }
}

int TObjEneMe1Canadin::fn_8009E36C() {
    return (m_3c8 >> 15) & 0x1; }

void TObjEneMe1Canadin::fn_8009E350() {
    m_3c8 = (s32) (m_3c8 | 0x100);
    m_3c8 = (s32) (m_3c8 & 0xFFFFFDFF);
}

void TObjEneMe1Canadin::fn_8009E334() {
    m_3c8 = (s32) (m_3c8 | 0x200);
    m_3c8 = (s32) (m_3c8 & 0xFFFFFEFF);
}

s32 TObjEneMe1Canadin::fn_8009E31C(s32 arg1) {
    return (u8) ((m_3c8 & arg1) != 0);
}

TObjChara *TObjEneMe1Canadin::fn_8009E300() {
    if (m_3c8 & 0x40000) {
        return m_390;
    }
    return 0;
}

void TObjEneMe1Canadin::vfunc_117(TObjEneMe1Canadin *) {  }

int TObjEneMe1Canadin::vfunc_116(TObjChara *) { return 1; }

void TObjEneMe1Canadin::fn_8009E2DC() {
    m_400 = 0;
    m_3c8 = (s32) (m_3c8 | 1);
}

void TObjEneMe1Canadin::set_leader_index(TObjChara *target, s32 arg2) {
    set_target_player(target);
    m_400 = arg2;
    m_3c8 = (s32) (m_3c8 | 1);
}

void TObjEneMe1Canadin::set_attack_flag() { m_3c8 |= 0x2; }

void TObjEneMe1Canadin::fn_8009E27C() {
    m_3c8 |= 0x4; }

void TObjEneMe1Canadin::set_flag3c8_bit8() { m_3c8 |= 0x8; }

void TObjEneMe1Canadin::fn_8009E258() {
    m_3c8 = (s32) (m_3c8 | 0x100000 | 4);
}

void TObjEneMe1Canadin::set_flag3c8_bit20() { m_3c8 |= 0x20; }

void TObjEneMe1Canadin::set_flag3c8_bit40() { m_3c8 |= 0x40; }

#pragma push
#pragma inline_depth(1)
#pragma auto_inline off
#pragma dont_inline off
void TObjEneMe1Canadin::fn_8009E1D4(Vec *position) {
    CanadinActionParameters params = canadin_behavior_params;
    params.field_4 = m_468->field_4;
    TObjEneDD::setup(this, (s32)position, (s32)&params);
}
#pragma pop

void TObjEneMe1Canadin::dispatch_action(u32 which, s32 arg) {
    TObjEneMe1Canadin *self = this;
    switch (which) {
    case 0:
        self->handle_state(arg);
        break;
    case 1:
        self->fn_8009DE90(arg);
        break;
    case 2:
        self->action(arg);
        break;
    case 3:
        self->vfunc_110(arg);
        break;
    case 4:
        self->vfunc_111(arg);
        break;
    case 5:
        self->move(arg);
        break;
    case 6:
        self->fn_8009D320(arg);
        break;
    case 7:
        self->fn_8009CC74(arg);
        break;
    case 8:
        self->fn_8009C91C(arg);
        break;
    case 9:
        self->run_task(arg);
        break;
    case 10:
        self->fn_8009C2EC(arg);
        break;
    case 11:
        self->fn_8009C178(arg);
        break;
    case 12:
        self->fn_8009C510(arg);
        break;
    case 13:
        self->vfunc_112(arg);
        break;
    case 14:
        self->fn_8009BFF8(arg);
        break;
    case 16:
        self->update_walk_animation(arg);
        break;
    case 17:
        self->update_by_state(arg);
        break;
    }
}

void TObjEneMe1Canadin::handle_state(s32 arg1) {
    switch (arg1) {
    case 4:
        m_b8 = 0;
        set_field_378(2);
        this->vfunc_95();
        m_3c8 = (s32) (m_3c8 | 0x400000);
        m_3fc = 4;
        m_4b8 = 1;
        m_470 = 0;
        return;
    case 3:
        if ((s32) m_470 >= 4) {
            if ((s32) m_3c4 == 0) {
                m_3c8 = (s32) (m_3c8 | 0x100000);
            }
            transition_enemy_state__9TObjEneDDFl(this, 1);
        }
    case 5:
        return;
    case 0:
        m_470 = (s32) (m_470 + 1);
        if ((s32) m_470 == 2) {
            this->vfunc_107();
        }
        m_3c8 = (s32) (m_3c8 & 0xFEFFFFFF);
        break;
    }
}

void TObjEneMe1Canadin::fn_8009DE90(s32 arg1) {
    void * argv0 = (void *)this;
    u8 *arg0 = (u8 *)argv0;
    switch (arg1) {
    case 4:
        m_b8 = 0;
        this->set_field_378(2);
        m_3c8 = (s32) (m_3c8 & 0xFFBFFFFF);
        this->vfunc_95();
        actorFlags = (s32) (actorFlags | 0x01000000);
        m_3fc = 4;
        m_4b8 = 1;
        start_fade_in__13TUnk_80494938Fv(&m_3cc);
        TBoss3Volopt__sub_800D8D88((s32)(&position));
        return;
    case 3:
        if (this->m_3cc.advance_toward_max() != 0) {
            transition_enemy_state__9TObjEneDDFl(arg0, 2);
        }
    case 5:
        return;
    case 0:
        advance_animation__10TObjMotionFv(this);
        if ((s32) m_3c4 == 2) {
            this->update_hover_position(lbl_805D9890 + position.y);
        } else {
            this->set_target_speed_z();
        }
        this->vfunc_88();
        break;
    }
}

void TObjEneMe1Canadin::action(s32 arg1) {
    s32 temp_r3;

    switch (arg1) {
    case 4:
        m_b8 = 0;
        set_field_378(2);
        m_3c8 = (s32) (m_3c8 & 0xFFBFFFFF);
        this->vfunc_95();
        actorFlags = (s32) (actorFlags & 0xFEFFFFFF);
        m_3fc = 4;
        m_4b8 = 1;
        break;
    case 3:
        if (this->vfunc_108() == 0) {
            temp_r3 = m_3c8;
            if (temp_r3 & 1) {
                m_3c8 = (s32) (temp_r3 & 0xFFFFFFFE);
                transition_enemy_state__9TObjEneDDFl(this, 3);
            } else if (enemy_has_live_target() != 0) {
                transition_enemy_state__9TObjEneDDFl(this, 3);
            }
        }
        break;
    case 0:
        advance_animation__10TObjMotionFv(this);
        if ((s32) m_3c4 != 1) {
            update_linked_position(TObjEneMe1Canadin__data_805D988C);
        }
        if ((s32) m_3c4 == 2) {
            this->update_hover_position(lbl_805D9890 + position.y);
        } else {
            set_target_speed_z();
        }
        this->vfunc_89();
        break;
    case 5:
    case 1:
        break;
    }
}

void TObjEneMe1Canadin::vfunc_110(s32 arg1) {
    u8 *arg0 = (u8 *)this;
    s32 temp_r3;
    f32 temp_f1;

    switch (arg1) {
    case 4:
        this->advance_state_5_to_4();
        this->set_field_378(3);
        m_3c8 = (s32) (m_3c8 & 0xFFBFFFFF);
        this->vfunc_96();
        actorFlags = (s32) (actorFlags & 0xFEFFFFFF);
        {
            const f32 *p = (const f32 *) canadin_formation_reset_vec4;
            m_4a4.r = p[1];
            m_4a4.g = p[2];
            m_4a4.b = p[3];
            this->pack_color_rgba();
        }
        m_470 = 0;
        return;
    case 3:
        if (this->vfunc_108() == 0) {
            temp_r3 = m_3c8;
            if (temp_r3 & 2) {
                m_3c8 = (s32) (temp_r3 & 0xFFFFFFFD);
                if ((s32) m_3c4 == 1) {
                    transition_enemy_state__9TObjEneDDFl(arg0, 5);
                } else {
                    transition_enemy_state__9TObjEneDDFl(arg0, 4);
                }
            }
        }
    case 1:
        return;
    case 0:
        advance_animation__10TObjMotionFv(this);
        this->update_linked_position(TObjEneMe1Canadin__data_805D988C);
        switch (m_470) {
        case 2:
            break;
        case 0:
            m_400 = (s32) (m_400 - 1);
            if ((s32) m_400 <= 0) {
                m_4b8 = 2;
                m_470 = 1;
                play_sound_effect(0x4003B21A, body_center(), 0, 0);
            }
            break;
        case 1:
            if ((s32) m_4b8 == 0) {
                m_3c8 = (s32) (m_3c8 | 0x8000);
                switch (m_3c4) {
                case 0:
                    this->set_attack_flag();
                case 1:
                    m_470 = 3;
                    break;
                }
            }
            update_move();
            break;
        case 3:
            update_move();
            break;
        }
        this->set_target_speed_z();
        this->vfunc_89();
        return;
    case 5:
        this->vfunc_92();
        break;
    }
}

void TObjEneMe1Canadin::vfunc_111(s32 arg1) {
    switch (arg1) {
    case 4:
        this->advance_state_5_to_4();
        set_field_378(4);
        m_3c8 = (s32) (m_3c8 & 0xFFBFFFFF);
        this->vfunc_96();
        actorFlags = (s32) (actorFlags | 0x01000000);
        return;
    case 3:
        if (m_3c8 & 0x80000) {
            m_404 = 0;
            this->vfunc_105();
        }
        return;
    case 5:
        break;
    case 0:
        advance_animation__10TObjMotionFv(this);
        update_linked_position(TObjEneMe1Canadin__data_805D988C);
        update_move();
        this->update_hover_height();
        this->vfunc_89();
        this->fn_8009E6B0();
        break;
    }
}

void TObjEneMe1Canadin::move(s32 arg1) {
    s32 temp_r3;

    switch (arg1) {
    case 4:
        this->advance_state_5_to_4();
        set_field_378(5);
        m_3c8 = (s32) (m_3c8 & 0xFFBFFFFF);
        this->vfunc_96();
        actorFlags = (s32) (actorFlags | 0x01000000);
        m_470 = 0;
        return;
    case 3:
        if ((this->vfunc_108() == 0) && ((s32) m_470 == 3)) {
            m_404 = 0;
            this->vfunc_105();
        }
    case 5:
    case 1:
        return;
    case 0:
        advance_animation__10TObjMotionFv(this);
        update_linked_position(TObjEneMe1Canadin__data_805D988C);
        switch (m_470) {
        case 0:
            temp_r3 = m_3c8;
            if (temp_r3 & 4) {
                m_3c8 = (s32) (temp_r3 & 0xFFFFFFFB);
                if (this->fn_8009E31C(0x200) != 0) {
                    m_470 = 1;
                    this->fn_8009E4AC(1);
                } else {
                    m_470 = 2;
                    advance_state_4_to_5();
                    this->fn_8009E4AC(3);
                }
            }
            update_move();
            update_hover_height();
            break;
        case 1:
            if ((s32) m_4b8 == 0) {
                m_470 = 3;
            }
            update_move();
            update_hover_height();
            break;
        case 2:
            update_move();
            if ((s32) m_4b8 != 0) {
                update_hover_height();
            } else {
                this->update_hover_position(position.y + m_3f0);
                if (m_3c8 & 0x80000) {
                    m_470 = 3;
                }
            }
            break;
        }
        this->vfunc_89();
        this->fn_8009E6B0();
        break;
    }
}

#pragma push
#pragma fp_contract on
void TObjEneMe1Canadin::fn_8009D320(s32 arg1) {
    Vec *pos;
    void *p;
    TObjEneMe1Canadin *o = this;
    pos = &o->m_490;
    switch (arg1) {
    case 4:
        o->set_field_378(6);
        o->m_3c8 |= 0x10000;
        o->m_3c8 &= 0xFFBFFFFF;
        o->vfunc_96();
        o->actorFlags |= 0x01000000;
        o->reset_map_core((NJS_ARGB *)canadin_formation_reset_vec4);
        o->m_470 = 1;
        o->m_474 = 0;
        o->m_49c = 0;
        o->m_4a0 = 0;
        break;
    case 3:
        if (o->vfunc_108() == 0 && o->try_trigger_action() == 0 && o->m_470 == 6) {
            if (o->m_3c8 & 0x100000) {
                transition_enemy_state__9TObjEneDDFl(o, 8);
            } else {
                transition_enemy_state__9TObjEneDDFl(o, 9);
            }
        }
        break;
    case 0:
        advance_animation__10TObjMotionFv(this);
        if (o->m_470 == 1) {
            if (o->update_linked_position(TObjEneMe1Canadin__data_805D988C) == 0) {
                break;
            }
        } else if (((TObjEneEpsilon *)o)->update_death_check() == 0) {
            break;
        }
        o->enemy_copy_target_destination();
        switch (o->m_470) {
        case 1:
            o->update_velocity();
            if (o->check_target() != 0) {
                o->m_470 = 2;
                o->m_3c8 |= 0x40000;
                o->advance_state_4_to_5();
            } else {
                o->advance_state_5_to_4();
            }
            TObjEneEpsilon__sub_800B92F8((u8 *)o, 0x200, (f32)TObjEneMe1Canadin__data_805D98BC);
            break;
        case 2:
            o->update_velocity();
            o->update_angle();
            if (o->m_b8 == 1) {
                            o->m_470 = 3;
                o->reset_map_core((NJS_ARGB *)TObjEneMe1Canadin__map_core_default_vec4);
                VecCopy((Vec *)pos, (const Vec *)&o->m_394);
                p = __nw__7TObjectFUl(0x48);
                if (p != 0) {
                    p = TObjEneMe1Canadin_EffLine__ct((u8 *)p, (s32)o, (s32)o->m_414, (s32)pos);
                }
                o->m_49c = (TObject *)p;
                play_sound_effect(0x4002B71B, o->body_center(), 0, 0);
                play_sound_effect(0x4002B51E, o->body_center(), 0, 0);
            }
            break;
        case 3: {
            Vec v;
            o->update_velocity();
            o->update_angle();
            VecCopy((Vec *)&v, (const Vec *)&o->m_394);
            subtract_vector(&v, pos);
            if (normalize_vector_xz((Vec *)(&v)) < lbl_805D9910) {
                VecCopy((Vec *)pos, (const Vec *)&o->m_394);
            } else {
                pos->x = lbl_805D9910 * v.x + pos->x;
                pos->y = lbl_805D9910 * v.y + pos->y;
                pos->z = lbl_805D9910 * v.z + pos->z;
            }
            if (o->m_4a0 == 0) {
                o->m_4a0 = (TObject *)create_particle_emitter(o->m_414, 0xF7);
                if (o->m_4a0 != 0) {
                    ((TParticleCtrl *)(o->m_4a0))->enable();
                }
            } else {
                ((TParticleCtrl *)o->m_4a0)->set_position(o->m_414);
            }
            o->m_474++;
            if (o->m_474 > o->m_468->field_18) {
                o->m_470 = 4;
                o->m_474 = 0;
                o->m_49c->queue_destruction();
                o->m_49c = 0;
                if (o->m_4a0 != 0) {
                    o->m_4a0->queue_destruction();
                    o->m_4a0 = 0;
                }
            }
            break;
        }
        case 4:
            o->m_474++;
            if (o->m_474 >= o->m_468->field_1c) {
                o->m_470 = 5;
                o->m_474 = 0;
                o->m_3c8 &= 0xFFFBFFFF;
                o->reset_map_core((NJS_ARGB *)canadin_formation_reset_vec4);
                o->m_404++;
                {
                    void *q = __nw__7TObjectFUl(0x68);
                    if (q != 0) {
                        TObjEneMe1Canadin_EffDischarge__ct(q, o, o->m_414, pos);
                    }
                }
                play_sound_effect(0x4002A408, o->body_center(), 0, 0);
            }
            break;
        case 5:
            o->m_474++;
            if (o->m_474 > o->m_468->field_20) {
                o->m_474 = 0;
                if (o->m_404 >= o->m_468->field_24) {
                    o->m_470 = 6;
                } else {
                    o->m_470 = 1;
                }
            }
            break;
        }
        o->update_position_with_offset();
        o->vfunc_89();
        o->fn_8009E6B0();
        break;
    case 5:
        o->m_3c8 &= 0xFFFBFFFF;
        o->reset_map_core((NJS_ARGB *)canadin_formation_reset_vec4);
        if (o->m_49c != 0) {
            o->m_49c->queue_destruction();
            o->m_49c = 0;
        }
        if (o->m_4a0 != 0) {
            o->m_4a0->queue_destruction();
            o->m_4a0 = 0;
        }
        break;
    }
}
#pragma pop

#pragma push
#pragma fp_contract on
#pragma optimization_level 3
void TObjEneMe1Canadin::fn_8009CC74(s32 arg1) {
    TObjEneMe1Canadin *o = this;
    switch (arg1) {
    case 4:
        o->advance_state_4_to_5();
        o->set_field_378(7);
        o->m_3c8 &= 0xFFBFFFFF;
        o->vfunc_96();
        o->actorFlags &= 0xFEFFFFFF;
        o->m_3c8 &= 0xFFF7FFFF;
        o->m_470 = 0;
        o->m_474 = 40;
        o->m_478 = 0;
        o->m_484 = lbl_805D9898;
        o->m_488 = lbl_805D9898;
        break;
    case 3:
        if (o->vfunc_108() == 0 && o->try_trigger_action() == 0 && o->m_470 == 4) {
            o->transition_enemy_state(8);
        }
        break;
    case 0:
        advance_animation__10TObjMotionFv(this);
        if (o->m_470 == 0) {
            if (o->update_linked_position(TObjEneMe1Canadin__data_805D988C) == 0) {
                break;
            }
        } else if (((TObjEneEpsilon *)o)->update_death_check() == 0) {
            break;
        }
        switch (o->m_470) {
        case 4:
            break;
        case 0: {
            f32 d;
            o->enemy_copy_target_destination();
            o->update_velocity();
            o->update_angle();
            o->m_474++;
            if (o->m_474 > 40) {
                o->m_474 = 0;
                o->m_470 = 1;
                if (o->m_3c8 & 0x40000) {
                    if (o->m_3ac < lbl_805D9894) {
                        o->m_470 = 2;
                        o->reset_map_core((NJS_ARGB *)TObjEneMe1Canadin__map_core_default_vec4);
                    }
                } else if (o->m_3ac < lbl_805D98E8) {
                    o->m_3c0 = (TObjEneMe1Canadin *)find_entity_by_id(o->m_4c8);
                    if (((TObjEneMe1Canadin *)o->m_3c0)->vfunc_116((TObjChara *)o->m_390) != 0) {
                        o->m_3c8 |= 0x40000;
                    } else if (o->fn_8009E860(&d, lbl_805D98EC) != 0) {
                        if (d < lbl_805D98E8) {
                            o->m_3c8 |= 0x40000;
                        }
                    } else {
                        o->m_470 = 4;
                    }
                }
            }
            ((TObjEneMe1Canadin *)((u8 *)o))->update_hover_position(o->position.y + o->m_3f4);
            break;
        }
        case 1:
            if (o->m_474 == 0) {
                f32 s, c, inv, len;
                o->enemy_copy_target_destination();
                o->update_velocity();
                len = lbl_805D98F0;
                inv = lbl_805D98D4 / newton_sqrtf(len);
                c = lbl_805D98D0 * inv;
                s = lbl_805D98D0 * inv;
                len *= inv;
                if (o->m_478 == 1) {
                    o->m_478 = 0;
                    s = c * lbl_805D98F4;
                } else {
                    o->m_478 = 1;
                }
                {
                    f32 nx, nz;
                    nx = o->m_3a0.x * c + o->m_3a0.z * s;
                    nz = o->m_3a0.z * c - o->m_3a0.x * s;
                    o->m_3a0.x = nx;
                    o->m_3a0.z = nz;
                }
                o->m_484 = lbl_805D98F8 * len;
                o->m_488 = lbl_805D98F8 * (o->m_3ec - o->m_3f4);
                play_sound_effect(0x4003AD18, o->body_center(), 0, 0);
            }
            ((TObjEneMe1Canadin *)((u8 *)o))->fn_8009E948();
            o->m_474++;
            if (o->m_474 >= 4) {
                o->m_474 = 0;
                o->m_470 = 0;
                ((TObjEneMe1Canadin *)((u8 *)o))->fn_8009E930();
            }
            o->hover_y += o->m_488;
            o->move_to_wall_clamped_destination(o->m_3a0.x, o->m_3a0.z, o->m_484);
            push_history_entry__17TObjEneMe1CanadinFPvfPvi(o->m_408, lbl_805D98FC, o->m_414, o->m_4b4);
            break;
        case 2:
            o->enemy_copy_target_destination();
            o->update_velocity();
            o->update_angle();
            ((TObjEneMe1Canadin *)((u8 *)o))->approach_hover_y(o->position.y + o->m_3ec);
            if (o->m_3ac < lbl_805D9900) {
                if (((TObjEneMe1Canadin *)((u8 *)o))->fn_8009E76C() != 0) {
                    o->m_474 = 0;
                    o->m_470 = 3;
                }
            } else {
                if (o->m_3ac > lbl_805D9894) {
                    o->m_470 = 1;
                }
                TObjEneEpsilon__sub_800B92AC((u8 *)o, 0x200, o->m_468->field_0);
            }
            o->fn_8009E6B0();
            break;
        case 3:
            o->enemy_copy_target_destination();
            o->update_velocity();
            o->update_angle();
            o->m_474++;
            if (o->m_474 == 20) {
                Vec v;
                VecCopy((Vec *)&v, (const Vec *)&o->m_414[5]);
                vec3_add_to(&v, &o->m_414[6]);
                v.x *= TObjEneMe1Canadin__data_805D98BC;
                v.y *= TObjEneMe1Canadin__data_805D98BC;
                v.z *= TObjEneMe1Canadin__data_805D98BC;
                create_timed_particle_emitter(&v, 0x113, 0, 0x14);
            } else if (o->m_474 == 25) {
                o->m_404++;
                if (((TObjEneMe1Canadin *)((u8 *)o))->fn_8009E76C() != 0 && ((TObjEneMe1Canadin *)o->m_390)->select_melee_contact_body(o, lbl_805D98D4) != 0) {
                    ((TObjEneMe1Canadin *)o->m_390)->receive_physical_attack(o, lbl_805D98D4);
                    ((TObjEneMe1Canadin *)o->m_390)->apply_knockback_from_attacker((u8 *)o, lbl_805D9904);
                    if ((s32)is_player_entity_id(get_entity_id(o->m_390)) != 0 && is_target_android(o->m_390) != 0 && random_ratio__9TObjCharaFv((s32)o) < lbl_805D9908) {
                        ((TObjEneMe1Canadin *)o->m_390)->apply_shock_status();
                        ((TObjEneMe1Canadin *)o->m_390)->vfunc_74(0);
                    }
                }
                play_sound_effect(0x4003B219, o->body_center(), 0, 0);
            } else if (o->m_474 > 50) {
                if (o->m_404 >= 3) {
                    o->m_470 = 4;
                } else {
                    o->m_474 = 0;
                    if (o->m_3ac < lbl_805D990C) {
                        o->m_470 = 3;
                    } else if (o->m_3ac < lbl_805D9894) {
                        o->m_470 = 2;
                    } else {
                        o->m_470 = 1;
                        o->reset_map_core((NJS_ARGB *)canadin_formation_reset_vec4);
                        if (o->m_3ac > lbl_805D98E8) {
                            o->m_3c8 &= 0xFFFBFFFF;
                        }
                    }
                }
            }
            o->set_target_speed_z();
            break;
        }
        o->vfunc_89();
        break;
    case 5:
        o->m_3c8 &= 0xFFFBFFFF;
        o->reset_map_core((NJS_ARGB *)canadin_formation_reset_vec4);
        ((TObjEneMe1Canadin *)((u8 *)o))->fn_8009E930();
        break;
    }
}
#pragma pop

#pragma push
#pragma fp_contract on
void TObjEneMe1Canadin::fn_8009C91C(s32 arg1) {
    TObjEneMe1Canadin *o = this;
    Vec *dir = &o->m_490;
    switch (arg1) {
    case 4:
        o->advance_state_4_to_5();
        o->set_field_378(8);
        o->m_3c8 &= 0xFFBFFFFF;
        o->vfunc_96();
        o->m_404 = 0;
        o->m_470 = 1;
        ((TObjEneMe1Canadin *)((u8 *)o))->fn_8009E948();
        o->m_474 = 0;
        o->m_478 = 0;
        o->m_480 = 0;
        o->m_484 = lbl_805D9898;
        o->m_488 = lbl_805D9898;
        o->m_48c = lbl_805D9898;
        dir->x = lbl_805D9898;
        dir->y = lbl_805D9898;
        dir->z = lbl_805D9898;
        break;
    case 3:
        if (o->vfunc_108() == 0 && o->try_trigger_action() == 0 && o->m_478 >= 4) {
            o->vfunc_105();
        }
        break;
    case 0:
        advance_animation__10TObjMotionFv(this);
        if (o->update_linked_position(TObjEneMe1Canadin__data_805D988C) != 0) {
            switch (o->m_470) {
            case 1: {
                if (o->m_474 == 0) {
                    f32 t;
                    o->enemy_copy_target_destination();
                    o->update_velocity();
                    t = lbl_805D98D8 * calc_elapsed_scaled__9TObjEneDDFv(o);
                    if (t >= lbl_805D9898) {
                        t += lbl_805D98DC;
                    } else {
                        t -= lbl_805D98DC;
                    }
                    t *= lbl_805D98E0;
                    o->m_480 = t;
                    dir->x = -o->m_3a0.x;
                    dir->z = -o->m_3a0.z;
                    o->m_484 = lbl_805D98E0 * (o->m_3e8 - o->m_3f4);
                    o->m_48c = lbl_805D98E0 * (lbl_805D98E4 - o->m_3ac);
                    o->m_488 = o->m_3ac;
                }
                o->m_474++;
                if (o->m_474 >= 8) {
                    o->m_478++;
                    o->m_470 = 0;
                    ((TObjEneMe1Canadin *)((u8 *)o))->fn_8009E930();
                }
                o->hover_y += o->m_484;
                rotate_xz_pair_by_angle(&dir->x, &dir->z, o->m_480);
                {
                    Vec v;
                    f32 c;
                    o->m_488 += o->m_48c;
                    v.x = dir->x * o->m_488 + o->m_394.x;
                    v.z = dir->z * o->m_488 + o->m_394.z;
                    subtract_vector(&v, &o->position);
                    c = normalize_vector_xz((Vec *)(&v));
                    o->move_to_wall_clamped_destination(v.x, v.z, c);
                }
                o->rotation_y = (s32)(lbl_8043A3C8 * atan2_float(dir->x, dir->z)) + 0x8000;
                push_history_entry__17TObjEneMe1CanadinFPvfPvi(o->m_408, TObjEneMe1Canadin__data_805D98B4, o->m_414, o->m_4b4);
                break;
            }
            case 0:
                o->enemy_copy_target_destination();
                o->update_velocity();
                o->update_angle();
                o->update_hover_height();
                o->m_474++;
                if (o->m_474 > 30) {
                    o->m_474 = 0;
                    o->m_470 = 1;
                }
                break;
            }
            o->vfunc_89();
        }
        break;
    case 5:
        ((TObjEneMe1Canadin *)((u8 *)o))->fn_8009E930();
        break;
    }
}
#pragma pop

void TObjEneMe1Canadin::run_task(s32 arg1) {
    u8 *arg0 = (u8 *)this;
    switch (arg1) {
    case 4:
        this->advance_state_5_to_4();
        this->set_field_378(9);
        m_3c8 = (s32) (m_3c8 & 0xFFBFFFFF);
        ((TObjEneMe1Canadin *) arg0)->vfunc_95();
        actorFlags = (s32) (actorFlags | 0x01000000);
        if ((s32) m_3c4 == 1) {
            m_3c0 = (TObjEneMe1Canadin *)find_entity_by_id((m_4c8));
            m_3c0->set_flag3c8_bit8();
        }
        m_404 = 0;
        return;
    case 3:
        if ((((TObjEneMe1Canadin *) arg0)->vfunc_108() == 0) && (m_3ac < lbl_805D98D4)) {
            transition_enemy_state(5);
        }
    case 5:
        return;
    case 0:
        advance_animation__10TObjMotionFv(this);
        ((TObjEneEpsilon *)arg0)->copy_position((&home_position));
        this->update_velocity();
        update_angle();
        update_position_with_offset();
        this->move_with_wall_slide_commit((f32) (m_3a0.x), (f32) (m_3a0.z), TObjEneMe1Canadin__data_805D98B4);
        ((TObjEneMe1Canadin *) arg0)->vfunc_88();
        this->fn_8009E6B0();
        break;
    }
}

void TObjEneMe1Canadin::fn_8009C510(s32 arg1) {
    u8 * arg0 = (u8 *)this;
    f32 t;
    Vec v;
    f32 f;
    switch (arg1) {
    case 4:
        m_b8 = m_3fc;
        advance_animation__10TObjMotionFv(this);
        this->fn_8009E378();
        m_3c8 &= 0xFFBFFFFF;
        this->vfunc_96();
        actorFlags &= 0xFEFFFFFF;
        m_470 = 0;
        if (hover_y > TObjEneMe1Canadin__data_805D98AC + (position.y + m_3ec)) {
            m_474 = 0;
        } else {
            m_474 = 2;
        }
        m_488 = m_484 = lbl_805D9898;
        break;
    case 3:
        if (m_474 == 3) {
            transition_enemy_state(m_378);
        }
        break;
    case 0:
        advance_animation__10TObjMotionFv(this);
        VecCopy((Vec *)&v, (const Vec *)(velocity()));
        f = normalize_vector_xz((Vec *)(&v));
        this->move_with_wall_slide_on_ground(v.x, v.z, f);
        f *= TObjEneMe1Canadin__data_805D98BC;
        x_speed = v.x * f;
        m_310 = v.z * f;
        switch (m_474) {
        case 0:
            m_484 -= 0.13f;
            if (m_484 < -4.0f) {
                m_484 = -4.0f;
            }
            hover_y += m_484;
            if (hover_y < 12.0f + (position.y + m_3ec)) {
                m_474 = 1;
                if (m_484 > -2.0f) {
                    m_484 = -2.0f;
                }
                m_488 = m_484 * m_484 / lbl_805D98D0;
            }
            break;
        case 1:
            m_484 += m_488;
            hover_y += m_484;
            if (m_484 >= lbl_805D9898) {
                if (hover_y > position.y + m_3ec) {
                    hover_y = position.y + m_3ec;
                    m_470 = 0;
                    m_474 = 2;
                }
            }
            break;
        case 2:
            m_470++;
            if (m_470 >= m_468->field_28) {
                m_474 = 3;
            }
            break;
        }
        this->vfunc_89();
        break;
    case 5:
        clear_attack_receipts__9TObjEneDDFv();
        if (m_3fc == 5) {
            m_b8 = 1;
        } else {
            m_b8 = 0;
        }
        break;
    }
}

void TObjEneMe1Canadin::fn_8009C2EC(s32 arg1) {
    u8 * arg0 = (u8 *)this;
    switch (arg1) {
    case 4:
        this->advance_state_4_to_5();
        this->set_field_378(0xA);
        this->vfunc_96();
        m_3c8 &= 0xFFBFFFFF;
        m_3c8 |= 0x200000;
        actorFlags |= 0x01000000;
        m_410 = -0x7F80;
        break;
    case 3:
        if (m_470 >= 0x96) {
            transition_enemy_state(0xD);
            hp = 0;
            actorFlags |= 0x800;
            play_sound_effect(0x4003AD1F, body_center(), 0, 0);
        }
        break;
    case 1:
        break;
    case 0: {
        advance_animation__10TObjMotionFv(this);
        if (this->update_linked_position(TObjEneMe1Canadin__data_805D988C) != 0) {
            this->enemy_copy_target_destination();
        }
        this->update_velocity();
        this->approach_hover_y(position.y + m_3ec);
        TObjEneEpsilon__sub_800B92AC(arg0, 0x200, lbl_805D98B8);
        rotation_z += 0x2000;
        (m_470)++;
        if (m_470 >= 0x96) {
            CanadinActionParameters c = canadin_projectile_param_block;
            CanadinParameters *t = m_468;
            c.field_4 = t->field_8;
            TObjEneDD__sub_800BA5A4(arg0, &c, t);
            m_3c8 |= 0x800000;
        }
        if (m_470 % 10 < 5) {
            m_410 = 0xFFFF0000;
        } else {
            m_410 = 0xFF000000;
        }
        play_persistent_sound(0x4003B71D, (s32)arg0, (u32)(body_center()), 0, 0);
        this->vfunc_89();
        break;
    }
    case 5:
        rotation_z = 0;
        break;
    }
}

#pragma push
#pragma opt_common_subs off
void TObjEneMe1Canadin::fn_8009C178(s32 arg1) {
    u8 * arg0 = (u8 *)this;
    switch (arg1) {
    case 4:
        m_b8 = 0;
        this->set_field_378(0xB);
        this->vfunc_95();
        m_3c8 = (s32) (m_3c8 & 0xFFBFFFFF);
        actorFlags = (s32) (actorFlags | 0x800);
        if ((s32) m_3c4 == 1) {
            m_3c0 = (TObjEneMe1Canadin *)find_entity_by_id(m_4c8);
            m_3c0->vfunc_117((TObjEneMe1Canadin *)arg0);
        } else {
            this->send_entity_set_flags();
        }
        create_timed_particle_emitter((body_center()), 0x117, 0, 0x19);
        create_timed_particle_emitter((body_center()), 0x118, 0x19, 0xF);
        this->m_3cc.set_rate_from_divisor(0x19);
        this->m_3cc.reset_color();
        play_sound_effect(0x4003AD18, body_center(), 0, 0);
        return;
    case 3:
        if ((this->m_3cc.decay_value_toward_floor() != 0) && (this->vfunc_109() != 0)) {
            queue_destruction();
        }
    case 5:
    case 0:
        return;
    }
}

#pragma pop
void TObjEneMe1Canadin::fn_8009BFF8(s32 arg1) {
    u8 * arg0 = (u8 *)this;

    switch (arg1) {
    case 4:
        this->set_field_378(0xE);
        m_3c8 = (s32) (m_3c8 & 0xFFBFFFFF);
        this->vfunc_96();
        m_470 = 0;
        return;
    case 3:
        if ((s32) m_470 == 2) {
            this->vfunc_105();
        }
    case 5:
        return;
    case 0:
        advance_animation__10TObjMotionFv(this);
        if (this->update_linked_position(TObjEneMe1Canadin__data_805D988C) != 0) {
            m_470 = 2;
        }
        switch (m_470) {
        case 0:
            m_474 = (s32) (m_474 + 1);
            if ((s32) m_474 >= 0x3C) {
                m_470 = 1;
                this->advance_state_5_to_4();
            }
            this->update_hover_position(position.y + m_3f4);
            break;
        case 1:
            ((TObjEneEpsilon *)arg0)->copy_position(&home_position);
            this->update_velocity();
            this->update_angle();
            this->update_position_with_offset();
            if (m_3ac > lbl_805D98B0) {
                this->move_with_wall_slide_commit(m_3a0.x, m_3a0.z, TObjEneMe1Canadin__data_805D98B4);
            }
            break;
        }
        this->vfunc_89();
        this->fn_8009E6B0();
        break;
    }
}

void TObjEneMe1Canadin::vfunc_112(s32 arg1) {
    u8 *arg0 = (u8 *)this;
    Vec stack;
    f32 temp_f1;
    switch (arg1) {
    case 4:
        if ((s32) m_3c4 == 1) {
            m_3c0 = (TObjEneMe1Canadin *)find_entity_by_id(m_4c8);
            m_3c0->vfunc_117((TObjEneMe1Canadin *)arg0);
        }
        TBoss3Volopt::create_breakup_mdl(lbl_805D4FE0, 0, (s32)((int) (texlist)), (s32)(body_center()), (s32)((int) (rotation_y)));
        m_3c8 = (s32) (m_3c8 | 0x400000);
        VecCopy((Vec *)(&stack), (const Vec *)(body_center()));
        temp_f1 = stack.y;
        stack.y = temp_f1 - TObjEneMe1Canadin__data_805D98AC;
        trigger_dell_biter_events__10TObjPlayerFv(&stack, temp_f1);
        this->refresh_and_send_entity_flags();
        play_sound_effect(0x4003AA1E, body_center(), 0, 0);
        return;
    case 0:
        queue_destruction();
    case 3:
    case 5:
        return;
    }
}

void TObjEneMe1Canadin::update_walk_animation(s32 arg1) {
    switch (arg1) {
    case 4:
        m_b8 = 0;
        m_470 = 0;
        return;
    case 0:
        advance_animation__10TObjMotionFv(this);
        m_470 = (s32) (m_470 + 1);
        if ((s32) m_470 > 0x5A) {
            m_470 = 0;
            m_b8 = (s16) (m_b8 + 1);
            if ((s16) m_b8 >= 7) {
                m_b8 = 0;
            }
        }
    case 3:
    case 5:
    case 1:
        return;
    }
}

void TObjEneMe1Canadin::update_by_state(s32 arg1) {
    f32 temp_f1;

    switch (arg1) {
    case 4:
        m_b8 = 0;
        temp_f1 = position.y;
        hover_y = (f32) (temp_f1 + m_3ec);
        m_484 = sin_table_lookup(rotation_y);
        m_488 = cos_table_lookup(rotation_y);
        return;
    case 0:
        advance_animation__10TObjMotionFv(this);
        hover_y = (f32) (position.y + m_3ec);
        m_300 = (f32) hover_y;
        move_with_wall_slide_commit(m_484, m_488, lbl_805D98A8);
    case 3:
    case 5:
    case 1:
        return;
    }
}

void fn_8009BD00(void) {
    s32 temp_r4;
    s32 pos;
    s32 temp_r5;
    s32 temp_r5_2;
    switch (lbl_805D4FD4) {
    case 2:
    case 3:
        push_matrix();
        update_camera_sequence__9TObjEneDDFv();
        temp_r5 = TObjEneMe1Canadin__render_point_cursor;
        TObjEneMe1Canadin__render_point_cursor = temp_r5 + 0xC;
        matrix_mult_vec(0, lbl_80500960, temp_r5);
        temp_r4 = TObjEneMe1Canadin__render_point_cursor;
        temp_r5_2 = temp_r4;
        TObjEneMe1Canadin__render_point_cursor = temp_r4 + 0xC;
        rotate_vector_by_matrix(0, temp_r4, temp_r5_2);
        pop_matrix();
        break;
    case 6:
    case 11:
    case 14:
        pos = TObjEneMe1Canadin__render_point_cursor;
        TObjEneMe1Canadin__render_point_cursor = pos + 0xC;
        transform_point_to_view(lbl_80500960, pos);
        break;
    }
    lbl_805D4FD4 += 1;
}

void TObjEneMe1Canadin::render() {
    u8 *arg0 = (u8 *)this;
    s16 temp_r0;
    s16 temp_r0_2;
    s32 var_r30;
    s32 var_r29;
    if (TObjPlayer::check_demo_mode() != 0) {
        this->render_canadin_model_with_debug_type();
        return;
    }
    if (m_3c8 & 0x400000) {
        var_r30 = 0;
    } else if (is_main_phase_15__9TObjEneDDFv() != 0) {
        var_r30 = this->classify_actor_view_detail(lbl_805D9E88, lbl_805D9E84, lbl_805D98A4);
    } else if (this->update_object_view_visibility(lbl_805D98A0, lbl_805D98A4) != 0) {
        var_r30 = 1;
    } else {
        var_r30 = 0;
    }
    if (var_r30 != 0) {
        if (m_3c8 & 0x01000000) {
            draw_ground_shadow__9TObjEneDDFPC3Vecl(arg0, 0, 0);
        }
        this->update_secondary_light();
        TObjFish::set_global_param((int) (texlist));
        saved_model_render_flags = model_render_flags;
        TObjEneDD::clear_global_flag_400();
        TObjPlayer::toggle_particle_effect();
        this->vfunc_113();
        push_matrix();
        post_translate_matrix(&position);
        translate_matrix(0, lbl_805D9898, (f32) (m_3f4), lbl_805D9898);
        rotate_matrix_y(0, (int) (rotation_y));
        temp_r0 = mode;
        var_r29 = 1;
        if ((temp_r0 == 1) || (temp_r0 == 0xB)) {
            m_3cc.set_flags_and_apply_damage_color();
            if (defer_render__7TObjectFv(arg0) != 0) {
                var_r29 = 0;
            }
        }
        if (var_r29 != 0) {
            if ((s16) mode != 0xA) {
                lbl_805D4FD4 = 0;
                TObjEneMe1Canadin__render_point_cursor = (s32)(&m_414[0]);
                VecCopy((Vec *)(&m_414[3]), (const Vec *)(lbl_8043A268));
                VecCopy((Vec *)(&m_414[1]), (const Vec *)(lbl_8043A274));
                TObjEneRe7Berura::set_global_state((s32)&fn_8009BD00);
                if (var_r30 == 1) {
                    ((TObjMotion *)arg0)->draw();
                } else {
                    this->render_world_model();
                }
                TObjEneRe7Berura::set_global_state(NULL);
            } else {
                rotate_matrix_z(0, (int) (rotation_z));
                lbl_805D4FD4 = -1;
                TObjEneMe1Canadin__render_point_cursor = (s32)(&m_414[0]);
                VecCopy((Vec *)(&m_414[3]), (const Vec *)(lbl_8043A268));
                VecCopy((Vec *)(&m_414[1]), (const Vec *)(lbl_8043A274));
                TObjEneRe7Berura::set_global_state((s32)&fn_8009BD00);
                this->draw_with_alt_model((int) (m_410));
                TObjEneRe7Berura::set_global_state(NULL);
            }
        }
        temp_r0_2 = mode;
        if ((temp_r0_2 == 1) || (temp_r0_2 == 0xB)) {
            m_3cc.clear_flag_and_notify();
        }
        pop_matrix();
        TParticleCtrl::end_effect_render();
        model_render_flags = saved_model_render_flags;
        this->update_primary_light();
        return;
    }
    VecCopy((Vec *)(&m_414[3]), (const Vec *)(lbl_8043A268));
    VecCopy((Vec *)(&m_414[1]), (const Vec *)(lbl_8043A274));
    VecCopy((Vec *)(&m_414[2]), (const Vec *)(body_center()));
    VecCopy((Vec *)(&m_414[0]), (const Vec *)(body_center()));
    VecCopy((Vec *)(&m_414[4]), (const Vec *)(body_center()));
    VecCopy((Vec *)(&m_414[5]), (const Vec *)(body_center()));
    VecCopy((Vec *)(&m_414[6]), (const Vec *)(body_center()));
}

void TObjEneMe1Canadin::update_if_ready() { if (get_target_info() != 0) { this->update_by_field_0x354(); } }

void TObjEneMe1Canadin::render_canadin_model_with_debug_type() {
    u8 *arg0 = (u8 *)this;
    s32 temp_r3;
    if ((((s32)this->get_target_info()) != 0) && ((s32) m_3c4 == 0)) {
        temp_r3 = m_3c8;
        if (temp_r3 & 0x100) {
            TObjEneMe1Gee::queue_debug_text((s32)(pack_debug_text_position(0, 0)), (char *)lbl_8043A398);
        } else if (temp_r3 & 0x200) {
            TObjEneMe1Gee::queue_debug_text((s32)(pack_debug_text_position(0, 0)), (char *)lbl_8043A3A8);
        } else {
            TObjEneMe1Gee::queue_debug_text((s32)(pack_debug_text_position(0, 0)), (char *)lbl_8043A3BC);
        }
    }
    if (this->update_object_view_visibility(lbl_805D98A0, lbl_805D98A4) != 0) {
        draw_ground_shadow__9TObjEneDDFPC3Vecl(arg0, 0, 0);
        TObjPlayer::toggle_particle_effect();
        TObjFish::set_global_param((int) (texlist));
        push_matrix();
        post_translate_matrix(&position);
        rotate_matrix_y(0, (int) (rotation_y));
        TObjEneDD::clear_global_flag_400();
        draw_chunk_object(model);
        pop_matrix();
        TParticleCtrl::end_effect_render();
    }
}

void *TObjEneMe1CanadinLeader::create(void *arg0) {
    return new TObjEneMe1CanadinLeader((TObject *)tl_04, arg0);
}

TObjEneMe1CanadinLeader::TObjEneMe1CanadinLeader(TObject *parent, void *set_data)
    : TObjEneMe1Canadin(parent, set_data, 2) {
    m_name = (const char *)TObjEneMe1CanadinLeader__class_name;
    vfunc_106();
    m_3e8 += lbl_805D989C;
    m_4cc = 8;
    m_4d0 = 0;
    for (s32 i = 0; i < 8; i++) {
        m_4d4[i] = NULL;
    }
    m_4f4 = 0;
    initialize_enemy_state__9TObjEneDDFl(this, 0x1D);
}

TObjEneMe1CanadinLeader::~TObjEneMe1CanadinLeader() {}

void TObjEneMe1CanadinLeader::run_task() {
    if (TObjPlayer::check_demo_mode() != 0) {
        update_if_ready();
        return;
    }
    if (vfunc_83() != 4) {
        vfunc_85();
        update_fade_sequence();
        update_formation_state();
    }
    copy_pos();
    submit_default_cursor_candidate();
    vfunc_100();
}

void TObjEneMe1CanadinLeader::vfunc_106() {
    void *arg0 = this;
    model = (void *)lbl_805D4FD0->models[1].model;
    texlist = lbl_805D4FD0->models[1].m_c;
}

void TObjEneMe1CanadinLeader::vfunc_105() {
    TObjEneMe1CanadinLeader *self = this;
    switch (self->m_46c) {
    case 0:
    case 1:
        self->m_46c++;
        self->transition_enemy_state(6);
        break;
    case 2:
        self->m_46c = 0;
        self->transition_enemy_state(7);
        break;
    }
}

void TObjEneMe1CanadinLeader::vfunc_107() {
    TObjEneMe1CanadinLeader *self = this;
    s32 id;
    s32 sub;
    s32 angle;
    s32 n;
    s32 i;
    s32 j;
    Vec v;
    n = (s32)get_status_value_f32__23TObjEneMe1CanadinLeaderFv((f32)self->m_4cc / (f32)self->m_468->field_2c);
    if (n < 1) {
        n = 1;
    }
    angle = self->rotation_y;
    id = (self->entity_id + 1) & 0xFFFF;
    sub = self->set_index + 1;
    for (i = 0; i < n; i++) {
        v.x = lbl_805D9894 * sin_table_lookup(angle);
        v.y = lbl_805D9898;
        v.z = lbl_805D9894 * cos_table_lookup(angle);
        vec3_add_to(&v, &self->position);
        angle += 0x10000 / self->m_4cc;
        self->m_4d4[i] = TObjEneMe1CanadinLeader::create_canadin(self, &v, id++, sub++);
        self->m_4d4[i]->fn_8009E334();
        self->m_4d0++;
    }
    for (j = n; j < self->m_4cc; j++) {
        v.x = lbl_805D9894 * sin_table_lookup(angle);
        v.y = lbl_805D9898;
        v.z = lbl_805D9894 * cos_table_lookup(angle);
        vec3_add_to(&v, &self->position);
        angle += 0x10000 / self->m_4cc;
        self->m_4d4[j] = TObjEneMe1CanadinLeader::create_canadin(self, &v, id++, sub++);
        self->m_4d4[j]->fn_8009E350();
        self->m_4d0++;
    }
}

s32 TObjEneMe1CanadinLeader::vfunc_108() {
    TObjEneMe1CanadinLeader *self = this;
    s32 i;
    if (self->m_3c8 & 0x40) {
        self->m_3c8 &= ~0x40;
        self->transition_enemy_state(0xb);
        for (i = 0; i < self->m_4d0; i++) {
            self->m_4d4[i]->set_flag3c8_bit40();
        }
        return 1;
    }
    return 0;
}

void TObjEneMe1CanadinLeader::vfunc_117(TObjEneMe1Canadin *member) {
    TObjEneMe1CanadinLeader *self = this;
    TObjEneMe1Canadin *id = member;
    s32 i;
    for (i = 0; i < self->m_4d0; i++) {
        if (self->m_4d4[i] == id) {
            self->m_4d0--;
            TObjEneMe1Canadin *t = self->m_4d4[self->m_4d0];
            self->m_4d4[self->m_4d0] = id;
            self->m_4d4[i] = t;
            break;
        }
    }
    if (self->m_4f4 == 3) {
        s32 k = get_status_value_f32__23TObjEneMe1CanadinLeaderFv((f32)self->m_4cc / (f32)self->m_468->field_2c);
        if (self->m_4d0 <= self->m_4cc - k) {
            self->m_3c0 = (TObjEneMe1Canadin *)find_entity_by_id(self->m_4c8);
            self->m_3c0->set_flag3c8_bit8();
        }
    }
    if (!(self->m_3c8 & 0x100000) && self->m_4d0 <= self->m_4cc / 2) {
        self->m_3c8 |= 0x10;
    }
    if (self->m_4d0 <= 2) {
        self->m_3c8 |= 0x40;
    }
}

int TObjEneMe1CanadinLeader::vfunc_116(TObjChara *) {
    TObjEneMe1CanadinLeader *arg0 = this;
    s32 n = 0;
    s32 i;
    for (i = 0; i < arg0->m_4d0; i++) {
        if (arg0->m_4d4[i]->fn_8009E300() == arg0->m_390) {
            n++;
        }
    }
    if (TObjEneDD::check_v2_mode() != 0) {
        return n < 4;
    }
    return n < 2;
}

void TObjEneMe1CanadinLeader::vfunc_113() {
    void *arg0 = this;
    *lbl_805D4FE4 = m_4b4;
    *lbl_805D4FE8 = m_4b4;
}

int TObjEneMe1CanadinLeader::vfunc_109() {
    void *arg0 = this;
    return (u8) (m_4d0 <= 0);
}

void TObjEneMe1CanadinLeader::update_formation_state() {
    TObjEneMe1CanadinLeader *self = this;
    s32 i;
    s32 j;
    if (self->m_3c8 & 0x10) {
        self->m_3c8 &= ~0x10;
        self->m_4f4 = 7;
    }
    switch (self->m_4f4) {
    case 1:
        this->fn_8009E4AC(0);
        self->m_4f4 = 2;
        play_sound_effect(0x4003AD1B, self->body_center(), 0, 0);
        break;
    case 2:
        if (self->m_4b8 == 0) {
            self->m_4f4 = 3;
            self->m_3c8 &= ~8;
            copy_argb((NJS_ARGB *)&self->m_4a4, (NJS_ARGB *)((s32 *)canadin_formation_reset_vec4));
            for (i = 0; i < self->m_4d0; i++) {
                if (self->m_4d4[i]->fn_8009E31C(0x200) != 0) {
                    self->m_4d4[i]->fn_8009E27C();
                }
            }
        }
        break;
    case 3:
        if (self->m_3c8 & 8) {
            self->m_4f4 = 4;
        }
        break;
    case 4:
        this->fn_8009E4AC(2);
        self->m_4f4 = 5;
        play_sound_effect(0x4003AD1C, self->body_center(), 0, 0);
        break;
    case 5:
        if (self->m_4b8 == 0) {
            copy_argb((NJS_ARGB *)&self->m_4a4, (NJS_ARGB *)((s32 *)canadin_formation_reset_vec4));
            self->m_4f4 = 6;
            for (i = 0; i < self->m_4d0; i++) {
                if (self->m_4d4[i]->fn_8009E31C(0x100) != 0) {
                    self->m_4d4[i]->fn_8009E27C();
                }
            }
        }
        break;
    case 6:
        break;
    case 7:
        this->fn_8009E4AC(4);
        self->m_4f4 = 8;
        play_sound_effect(0x4003AD1B, self->body_center(), 0, 0);
        break;
    case 8:
        if (self->m_4b8 == 0) {
            self->m_4f4 = 9;
            copy_argb((NJS_ARGB *)&self->m_4a4, (NJS_ARGB *)((s32 *)canadin_formation_reset_vec4));
            for (j = 0; j < self->m_4d0; j++) {
                self->m_4d4[j]->fn_8009E258();
            }
            this->fn_8009E258();
        }
        break;
    case 0:
    case 9:
        break;
    }
}

void TObjEneMe1CanadinLeader::vfunc_110(s32 arg1) {
    u8 *arg0 = (u8 *)this;
    TObjEneMe1CanadinLeader *self = this;
    s32 k;
    s32 i;
    s32 j;

    switch (arg1) {
    case 4: {
        this->advance_state_5_to_4();
        this->set_field_378(3);
        this->vfunc_96();
        const f32 *p = (const f32 *)canadin_formation_reset_vec4;
        self->m_4a4.r = p[1];
        self->m_4a4.g = p[2];
        self->m_4a4.b = p[3];
        self->m_470 = 0;
        for (k = 2, i = 0; i < self->m_4d0; k += 2, i++) {
            self->m_4d4[i]->set_leader_index(self->m_390, k);
        }
        break;
    }
    case 3:
        if (self->m_3c8 & 2) {
            self->m_3c8 &= ~2;
            self->m_4f4 = 1;
            transition_enemy_state__9TObjEneDDFl(arg0, 4);
        }
        break;
    case 0:
        advance_animation__10TObjMotionFv(arg0);
        this->update_linked_position(TObjEneMe1Canadin__data_805D988C);
        switch (self->m_470) {
        case 0:
            self->m_400--;
            if (self->m_400 <= 0) {
                self->m_4b8 = 2;
                self->m_470 = 1;
                play_sound_effect(0x4003B21A, body_center(), 0, 0);
            }
            break;
        case 1:
            if (self->m_4b8 == 0) {
                self->m_3c8 |= 0x8000;
                for (j = 0; j < self->m_4d0; j++) {
                    if (self->m_4d4[j]->fn_8009E36C() == 0) {
                        break;
                    }
                }
                if (j == self->m_4d0) {
                    this->set_attack_flag();
                    s32 m;
                    for (m = 0; m < self->m_4d0; m++) {
                        ((TObjEneMe1CanadinLeader *)(self->m_4d4[m]))->set_attack_flag();
                    }
                }
            }
            update_move();
            break;
        }
        this->update_hover_position(lbl_805D9890 + self->position.y);
        this->vfunc_89();
        break;
    case 5:
        this->vfunc_92();
        break;
    }
}

void TObjEneMe1CanadinLeader::vfunc_111(s32 mode) {
    TObjEneMe1Canadin *self = this;
    switch (mode) {
    case 4:
        self->advance_state_5_to_4();
        self->set_field_378(4);
        self->vfunc_96();
        break;
    case 3:
        if (self->m_3c8 & 4) {
            self->vfunc_105();
        }
        break;
    case 0:
        advance_animation__10TObjMotionFv(this);
        self->update_linked_position(TObjEneMe1Canadin__data_805D988C);
        self->update_move();
        self->update_hover_height();
        self->vfunc_89();
        break;
    case 5:
        break;
    }
}

void TObjEneMe1CanadinLeader::vfunc_112(s32 mode) {
    TObjEneMe1CanadinLeader *obj = this;
    s32 i;
    TObjEneMe1CanadinLeader *self;
    self = (TObjEneMe1CanadinLeader *)obj;
    switch (mode) {
    case 4:
        TBoss3Volopt::create_breakup_mdl((s32)lbl_805D4FDC, 0, (s32)self->texlist, (s32)self->body_center(), (s32)self->rotation_y);
        for (i = 0; i < self->m_4d0; i++) {
            self->m_4d4[i]->set_flag3c8_bit20();
        }
        self->m_3c8 |= 0x400000;
        play_sound_effect(0x4003B71D, self->body_center(), 0, 0);
        ((TObjPlayer *)self)->refresh_lobby_state();
        break;
    case 0:
        if (obj->vfunc_109() != 0) {
            self->send_entity_set_flags();
            self->queue_destruction();
        }
        break;
    case 5:
        self->actorFlags &= ~0x200;
        break;
    case 1:
        return;
    case 3:
        return;
    }
}

}
