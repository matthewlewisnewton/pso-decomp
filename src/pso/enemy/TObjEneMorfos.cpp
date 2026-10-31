#pragma defer_codegen on
#define TOBJECT_OUT_OF_LINE_HELPERS
#include "pso/enemy/TObjEneMorfos.h"
#include "pso/enemy/BattleParameters.h"
#include "pso/enemy/TUnk_804EF130.h"
#include "pso/enemy/TObjEneMorfosArm.h"
#include "pso/enemy/TObjEneRecon.h"
#include "pso/enemy/TObjEneRe7Berura_803E4CE0.h"
#include "pso/boss/TBoss3Volopt.h"
#include "pso/TParticleCtrl.h"
#include "pso/animation/ActorAnimationState.h"
#include "pso/map/CsnGroundQuery.h"
#include "pso/math/AngleLookup.h"
#include "pso/math/FloatRounding.h"
#include "pso/math/ViewPoint.h"
#include "pso/math/MatrixTransforms.h"
#include "pso/npc/NpcAnimationBinding.h"
#include "pso/npc/NpcModelRegistry.h"
#include "pso/misc/TLobby.h"
#include "pso/object/TObjFish.h"
#include "pso/player/TObjPlayer.h"
#include "pso/player/demo_mode.h"
#include "pso/player/TObjPlayer_80011014.h"
#include "pso/player/TObjPlayer_800D8FDC.h"
#include "pso/player/TObjPlayer_801542CC.h"
#include "pso/player/TObjPlayer_801AF2F0.h"
#include "pso/player/TObjPlayer_803E4954.h"
#include "pso/render/reflection.h"
#include "pso/system/BmlResource.h"
#include "pso/system/BmlResourceDescriptor.h"
#include "pso/system/EnemyBmlResource.h"
#include "pso/system/vector.h"
#include "pso/unk/text_803D8F74.h"
#include "pso/unk/text_803E2D70.h"


struct MorfosParameters {
    f32 projectile_speed;
    f32 projectile_power;
    s32 field_08[4];
    s32 movement_turn_step;
    s32 attack_turn_step;
    s32 attack_delay;
    s32 charge_duration;
    s32 charge_turn_step;
};

extern "C" {
BattleBaseStats *morfos_base_stats[1];
ActorParamBlock *morfos_resistance_stats[1];
f32 lbl_805434D0[3];
AttackParams *morfos_attack_stats[3];
MorfosParameters *morfos_parameters;
BmlResource *morfos_resources;
s32 morfos_model_node_index;
Vec *morfos_node_position_cursor;
s16 *morfos_body_polygons;
s16 *morfos_projectile_polygons;
s32 morfos_body_texture_tick;
s32 morfos_projectile_texture_tick;
f32 morfos_projectile_speed;
f32 morfos_projectile_power;
}

struct CsnHit;

extern "C" {
CsnHit *csnLookAt(const Vec *, const Vec *);
CsnGroundHit *csnVectorUnder(Vec *, u32 *, s32);
s32 angle_difference_abs(s32, s32);
s32 angle_diff_s16(s32, s32);
extern const f64 morfos_angle_units_per_radian;
extern const f32 TObjEneMorfos__data_805DF86C;
extern const f32 TObjEneMorfos__data_805DF874;
extern const f32 lbl_805DF87C;
extern const f32 lbl_805DF890;
void spawn_particle_effect(void *, int);
s32 play_sound_effect(s32, u32, s16, s32);
extern const f32 TObjEneMorfos__data_805DF884;
extern const f32 lbl_805DF88C;
s32 enemy_validate_retained_target(u8 *arg0);
extern const f32 lbl_805DF880;
extern const f32 lbl_805DF888;
s32 get_camera_mode__11TCameraCtrlFv();
extern const Vec lbl_804775E4;
extern s32 saved_model_render_flags;
extern s32 model_render_flags;
extern const f32 lbl_805D9E84;
extern const f32 lbl_805D9E88;
extern const f32 TObjEneMorfos__data_805DF870;
void *create_particle_emitter(void *pos, s32 id);
extern s32 game_difficulty_selection;

s32 get_mode__11TCameraCtrlFPv(void *);
s32 is_patrol_active__21TObjEneRe7BeruraPunchFv(void *);
s32 TObjPlayer__sub_800A04F0(void *);
void enemy_set_target_id(void *, u16);
void TObjPlayer__sub_8023DEE0(s16 *p, s16 a, s16 b, u16 id);
s32 push_matrix();
s32 pop_matrix();
s32 post_translate_matrix(void *);
}
void restore_render_scissor(s32 arg0);

extern const f32 TObjEneMorfos__data_805DF89C;
extern const Vec morfos_node_position_origin;
extern const char *morfos_class_name;
extern s32 actor_frame_tick;
extern const f32 lbl_805DF878;
extern const f32 lbl_805DF894;
extern const f32 lbl_805DF898;
extern const f32 lbl_805DF8A0;
extern const f32 lbl_805DF8A4;
extern void *tl_04;

extern const char morfos_arm_model_filename[];
extern const char morfos_body_model_filename[];
extern const char morfos_wall_model_filename[];
extern const char morfos_arm_attack_motion_filename[];
extern const char morfos_body_attack_motion_filename[];
extern const char morfos_body_beam_motion_filename[];
extern const char morfos_body_damage_motion_filename[];
extern const char morfos_body_death_motion_filename[];
extern const char morfos_body_wait_motion_filename[];
extern const char morfos_archive_filename[];
extern const char morfos_low_arm_model_filename[];
extern const char morfos_low_body_model_filename[];
extern const char morfos_low_archive_filename[];

struct MorfosInitialParameters {
    f32 range;
    f32 speed;
    s32 turn_step;
    u32 unknown_0c[4];
};

MorfosInitialParameters morfos_initial_parameters = {
    225.0f, 0.0f, 0x600, {0, 0, 0, 0}
};
CollisionBody morfos_collision_body = {
    {0.0f, 0.0f, 0.0f}, 8.0f, 0.0f, 0, 0x8003,
    {0.0f, 0.0f, 0.0f}, 0.0f
};
const char *bm_ene_morfos_model_names[4] = {
    morfos_arm_model_filename, morfos_body_model_filename, morfos_wall_model_filename, NULL,
};
const char *bm_ene_morfos_motion_names[7] = {
    morfos_arm_attack_motion_filename, morfos_body_attack_motion_filename, morfos_body_beam_motion_filename, morfos_body_damage_motion_filename,
    morfos_body_death_motion_filename, morfos_body_wait_motion_filename, NULL,
};
BmlResourceDescriptor morfos_resource_descriptor = {
    morfos_archive_filename, bm_ene_morfos_model_names, bm_ene_morfos_motion_names, 3, 6
};
const char *bm_ene_morfos_low_model_names[4] = {
    morfos_low_arm_model_filename, morfos_low_body_model_filename, morfos_wall_model_filename, NULL,
};
const char *bm_ene_morfos_low_motion_names[7] = {
    morfos_arm_attack_motion_filename, morfos_body_attack_motion_filename, morfos_body_beam_motion_filename, morfos_body_damage_motion_filename,
    morfos_body_death_motion_filename, morfos_body_wait_motion_filename, NULL,
};
BmlResourceDescriptor bm_ene_morfos_low_resource_descriptor = {
    morfos_low_archive_filename, bm_ene_morfos_low_model_names, bm_ene_morfos_low_motion_names, 3, 6
};
TObjMotionAction morfos_motion_param_table[5] = {
    {MOTION_MODE_LOOP, 0, 5, 0.5f, 0},
    {MOTION_MODE_ONCE, 0, 1, 0.7f, 0},
    {MOTION_MODE_ONCE, 0, 2, 0.7f, 0},
    {MOTION_MODE_ONCE, 0, 3, 0.7f, 0},
    {MOTION_MODE_ONCE, 0, 4, 0.7f, 0}
};
extern "C" {

extern const Vec lbl_804775F0;

extern s32 morfos_base_stat_indices[];
extern s32 morfos_attack_stat_indices[];
extern s32 morfos_resistance_stat_indices[];

extern const f32 lbl_805DF8A8;

extern const s32 morfos_base_stat_ids[1];
extern const s32 morfos_resistance_stat_ids[1];
extern const s32 morfos_behavior_parameter_ids[1];
extern const s32 morfos_attack_stat_ids[2];
extern const NpcAnimationBinding morfos_npc_animation_binding;

void TObjEneMorfos::load_resources() {
    BmlResource *mgr;
    s32 i;

    if (is_split_screen() != 0) {
        mgr = load_enemy_bml_resource(&bm_ene_morfos_low_resource_descriptor);
    } else {
        mgr = load_enemy_bml_resource(&morfos_resource_descriptor);
    }
    morfos_resources = mgr;
    lbl_805434D0[0] = TObjEneMorfos__data_805DF874;
    lbl_805434D0[1] = TObjEneMorfos__data_805DF874;
    lbl_805434D0[2] = TObjEneMorfos__data_805DF874;
    morfos_model_node_index = 0;
    morfos_node_position_cursor = 0;
    morfos_body_polygons = ((NJS_CNK_MODEL *)((NJS_OBJECT *)mgr->models[1].model)->child->model)->polygon_list;
    morfos_projectile_polygons = ((NJS_CNK_MODEL *)((NJS_OBJECT *)mgr->models[2].model)->model)->polygon_list;
    morfos_body_texture_tick = 0;
    morfos_projectile_texture_tick = 0;
    for (i = 0; i < 1; i++) {
        morfos_base_stats[i] = get_battle_base_stats(morfos_base_stat_ids[i]);
    }
    for (i = 0; i < 2; i++) {
        morfos_attack_stats[i] = get_battle_attack_params(morfos_attack_stat_ids[i]);
    }
    for (i = 0; i < 1; i++) {
        morfos_resistance_stats[i] = get_battle_resistance_params(morfos_resistance_stat_ids[i]);
    }
    for (i = 0; i < 1; i++) {
        (&morfos_parameters)[i] = reinterpret_cast<MorfosParameters *>(get_battle_movement_params(morfos_behavior_parameter_ids[i]));
    }
    TObjEneMorfosArm::init_global();
    {
        NpcAnimationBinding desc = morfos_npc_animation_binding;
        desc.motions = morfos_resources->motions;
        NpcModelRegistry::register_animated_chunk(0x4D, (void *)morfos_resources->models[1].model,
                                (void *)morfos_resources->models[1].m_c, &desc,
                                lbl_805DF880, TObjEneMorfos__data_805DF874);
    }
}

void *TObjEneMorfos::create(void *set_data) {
    return new TObjEneMorfos((TObject *)tl_04, set_data);
}

void TObjEneMorfos::unload_static_data() {
    TObjEneMorfosArm::unload_static_data();
    if (morfos_resources != NULL) {
        delete morfos_resources;
        morfos_resources = NULL;
    }
}

TObjEneMorfos::TObjEneMorfos(TObject *parent, void *set_data) : TObjEneDD_ST(parent) {
    m_name = morfos_class_name;
    invoke_initialization_hook(set_data);
    initialize_behavior_parameters();
    init_instance();
    charge_effect = NULL;
}

void TObjEneMorfos::init_instance() {
    s32 i;

    init_position_vectors();
    model = (void *)morfos_resources->models[1].model;
    this->texlist = morfos_resources->models[1].m_c;
    init_model(&morfos_collision_body, 1);
    set_action_table(morfos_motion_param_table);
    set_motion_list(morfos_resources->motions);
    this->requested_action = 0;
    set_animation(this->requested_action);
    set_field_b8(this->requested_action);
    reset_hp(morfos_base_stats[morfos_base_stat_indices[0]], morfos_attack_stats[morfos_attack_stat_indices[0]], morfos_resistance_stats[morfos_resistance_stat_indices[0]]);
    get_parameters();
    set_state_8();
    this->movementParameters = &morfos_initial_parameters;
    initialize_enemy_state(0x42);
    m_37c = lbl_805DF8A8;
    enemy_init_acquire_period(0x3C);
    enemy_init_validate_period(0x3C);
    this->flags = 0;
    this->ground_flags = 0;
    VecCopy(&ground_position, &position);
    this->texture_offset = 0;
    damage_fade.reset_color();
    body_fade.reset_color();
    for (i = 0; i < 4; i++) {
        camera_fade[i].activate_and_dispatch();
    }
    this->model_node_positions[PROJECTILE_POSITION].x = TObjEneMorfos__data_805DF874;
    this->model_node_positions[PROJECTILE_POSITION].y = TObjEneMorfos__data_805DF874;
    this->model_node_positions[PROJECTILE_POSITION].z = TObjEneMorfos__data_805DF874;
    this->model_node_positions[ARM_POSITION].x = TObjEneMorfos__data_805DF874;
    this->model_node_positions[ARM_POSITION].y = TObjEneMorfos__data_805DF874;
    this->model_node_positions[ARM_POSITION].z = TObjEneMorfos__data_805DF874;
    this->action_phase = 0;
    this->phase_counter = 0;
    this->target_angle = 0;
    this->burst_start_angle = 0;
    this->action_progress = TObjEneMorfos__data_805DF874;
    this->m_4c8 = TObjEneMorfos__data_805DF874;
    this->movement_direction.x = TObjEneMorfos__data_805DF874;
    this->movement_direction.y = TObjEneMorfos__data_805DF874;
    this->movement_direction.z = TObjEneMorfos__data_805DF874;
    this->vfunc_95();
    this->mode = 0;
    dispatch_action(this->mode, 4);
}

TObjEneMorfos::~TObjEneMorfos() {
    if (charge_effect != NULL) {
        charge_effect->queue_destruction();
        charge_effect = NULL;
    }
    free_collision_body_parts(this);
}

void TObjEneMorfos::run_task() {
    if (check_demo_mode() != 0) {
        this->update_demo();
        return;
    }
    if (this->vfunc_83() != 4) {
        this->vfunc_85();
        if ((s32) morfos_body_texture_tick != (s32) actor_frame_tick) {
            morfos_body_texture_tick = actor_frame_tick;
            TObjPlayer__sub_8023DEE0((s16 *)morfos_body_polygons, (s16)((s16) this->texture_offset), (s16)(0), (u16)(2U));
        }
        if ((s32) morfos_projectile_texture_tick != (s32) actor_frame_tick) {
            morfos_projectile_texture_tick = actor_frame_tick;
            TObjPlayer__sub_8023DEE0((s16 *)morfos_projectile_polygons, (s16)(0), (s16) ((f32) this->texture_offset * lbl_805DF894), (u16)(0U));
        }
    }
    this->update_body_center();
    this->submit_default_cursor_candidate();
    this->vfunc_100();
    this->update_ground_probe();
}

void TObjEneMorfos::vfunc_28() {  }

void TObjEneMorfos::vfunc_63() { if (this->mode != 11) { this->transition_enemy_state(11); } }

f32 TObjEneMorfos::receive_physical_attack(void *attacker, f32 scale) {
    Vec v;
    f32 ret = TObjEneMorfos__data_805DF874;
    s32 d;
    if (attacker != 0) {
        VecCopy(&v, &((TObjChara *)attacker)->body_center_position);
        subtract_vector(&v, &body_center_position);
        d = angle_difference_abs(this->rotation_y, (s32)(morfos_angle_units_per_radian * atan2_float(v.x, v.z)));
    } else {
        d = 0;
    }
    if (this->flags & 0x10) {
        if (d < 0x4000) {
            spawn_particle_effect(&this->model_node_positions[PROJECTILE_POSITION], 0x214);
            spawn_particle_effect(&this->model_node_positions[PROJECTILE_POSITION], 0x21A);
        } else {
            this->flags &= ~0x10;
            this->flags |= 0x20;
            ret = this->TObjChara::receive_physical_attack(attacker, scale);
        }
    } else {
        ret = this->TObjChara::receive_physical_attack(attacker, scale);
    }
    return ret;
}

void TObjEneMorfos::vfunc_62() {
    Vec v;
    TObjPlayer *pl;
    s32 d;
    if (this->mode == 0xA) {
        return;
    }
    pl = get_player_by_client_id(this->m_2d4);
    if (pl != 0) {
        VecCopy(&v, &pl->body_center_position);
        subtract_vector(&v, &body_center_position);
        d = angle_difference_abs(this->rotation_y, (s32)(morfos_angle_units_per_radian * atan2_float(v.x, v.z)));
    } else {
        d = 0;
    }
    if (d < 0x4000) {
        this->clear_attack_receipts();
        if (this->check_low_hp_trigger() == 0) {
            this->try_enter_low_hp_state();
        }
    } else if (this->flags & 4) {
        this->clear_attack_receipts();
    } else {
        this->transition_enemy_state(0xA);
    }
}

void TObjEneMorfos::vfunc_61() {  }

s32 TObjEneMorfos::check_low_hp_trigger() {
    if (!(this->flags & 0x10) && ((s16) this->hp <= (s32) ((s16) this->hpmax / 2)) && (this->random_ratio() <= this->guard_probability)) {
        this->flags = (s32) (this->flags | 0x10);
        return 1;
    }
    return 0;
}

s32 TObjEneMorfos::try_enter_low_hp_state() {
    if (((s16) this->hp <= (s32) ((s16) this->hpmax / 2)) && (this->random_ratio() <= this->burst_probability)) {
        this->transition_enemy_state(9);
        return 1;
    }
    return 0;
}

s32 TObjEneMorfos::turn_toward_angle(s32 target_heading, s32 max_step) {
    s32 difference;
    s32 reached;

    reached = 0;
    difference = angle_diff_s16(this->rotation_y, target_heading);
    if (difference > max_step) {
        this->rotation_y = (s32) (this->rotation_y + max_step);
    } else if (difference < (s32) -max_step) {
        this->rotation_y = (s32) (this->rotation_y - max_step);
    } else {
        this->rotation_y = target_heading;
        reached = 1;
    }
    return reached;
}

void TObjEneMorfos::update_body_center() {
    this->body_center_position.x = (f32) this->position.x;
    this->body_center_position.y = (f32) (TObjEneMorfos__data_805DF89C + this->position.y);
    this->body_center_position.z = (f32) this->position.z;
    VecCopy(&center, &body_center_position);
}

void TObjEneMorfos::vfunc_88() {
    bodies[0].offset.y = (f32) (this->body_center_position.y - this->position.y);
}

#pragma push
#pragma opt_common_subs off
#pragma opt_propagation off
void TObjEneMorfos::initialize_behavior_parameters() {
    if ((s32) this->variant <= 0) {
        this->ground_movement = 1;
    } else {
        this->ground_movement = 0;
    }
    this->movement_speed = (f32) (lbl_805DF8A0 + this->parameters[0]);
    if (this->movement_speed < lbl_805DF8A4) {
        this->movement_speed = (f32) lbl_805DF8A4;
    }
    this->movement_interval = (f32) (TObjEneMorfos__data_805DF89C + this->parameters[1]);
    if (this->movement_interval < lbl_805DF888) {
        this->movement_interval = (f32) lbl_805DF888;
    }
    this->guard_probability = (f32) (lbl_805DF8A4 + this->parameters[2]);
    this->burst_probability = (f32) (lbl_805DF8A4 + this->parameters[3]);
}
#pragma pop

MorfosParameters *TObjEneMorfos::get_parameters() {
    morfos_projectile_speed = morfos_parameters->projectile_speed;
    morfos_projectile_power = morfos_parameters->projectile_power;
    return morfos_parameters;
}

#pragma push
#pragma fp_contract on
s32 TObjEneMorfos::select_target_in_view() {
    Vec v;
    s32 n;
    TObjPlayer *p;
    u16 id;
    s32 i;
    f32 dz;
    f32 dx;
    f32 cosLim;
    f32 d;
    f32 best;
    best = TObjEneMorfos__data_805DF874;
    id = 0xFFFF;
    cosLim = cos_table_lookup(0xAAA);
    dx = sin_table_lookup(this->rotation_y);
    dz = cos_table_lookup(this->rotation_y);
    n = TLobby::get_game_mode();
    for (i = 0; i < n; i++) {
        p = TObjPlayer::get_player_data(i);
        if (p->is_alive() == 0) {
            continue;
        }
        VecCopy(&v, &p->position);
        subtract_vector(&v, &body_center_position);
        v.y = TObjEneMorfos__data_805DF874;
        d = normalize_vector_xz(&v);
        if (d < TObjEneMorfos__data_805DF86C && d > best && dx * v.x + dz * v.z > cosLim &&
            csnLookAt(&body_center_position, &p->body_center_position) == 0) {
            id = get_entity_id(p);
            best = d;
        }
    }
    if (id != 0xFFFF) {
        enemy_set_target_id(this, id);
        return 1;
    }
    return 0;
}
#pragma pop

void TObjEneMorfos::play_frame_sounds() {
    if ((this->is_passing_frame((f32)lbl_805DF898) != 0) || (this->is_passing_frame((f32)((f32)TObjEneMorfos__data_805DF89C)) != 0)) {
        play_sound_effect(0x4003A823, (u32)(&this->position), 0, 0);
    }
}

s32 TObjEneMorfos::fn_803344F0() {
    return vfunc_99() ? 1 : 0;
}

void TObjEneMorfos::dispatch_action(u32 arg1, s32 ev) {
    switch (arg1) {
    case 0: this->handle_event_transition(ev); break;
    case 1: this->state_fade_in(ev); break;
    case 3: this->state_appear(ev); break;
    case 2: this->state_hidden(ev); break;
    case 7: this->state_disappear(ev); break;
    case 4: this->state_move(ev); break;
    case 5: this->state_melee_attack(ev); break;
    case 6: this->state_projectile_attack(ev); break;
    case 9: this->state_rotating_projectile_burst(ev); break;
    case 8: this->state_patrol(ev); break;
    case 10: this->state_damaged(ev); break;
    case 11: this->state_death(ev); break;
    }
}

void TObjEneMorfos::handle_event_transition(s32 ev) {
    switch (ev) {
    case 0:
        return;
    case 3:
        this->transition_enemy_state(1);
        break;
    }
}

void TObjEneMorfos::state_fade_in(s32 reason) {
    s32 fade_finished;
    switch (reason) {
    case 4:
        this->requested_action = 0;
        this->vfunc_95();
        this->flags = (s32) (this->flags & ~5);
        this->flags = (s32) (this->flags | 2);
        this->set_field_378(3);
        this->damage_fade.start_negative_fade_phase();
        this->body_fade.start_fade_in();
        ((TBoss3Volopt *)(&this->position))->play_area_se_with_particle();
        return;
    case 3:
        fade_finished = this->body_fade.advance_toward_max();
        if ((this->damage_fade.advance_toward_max() != 0) && (fade_finished != 0)) {
            this->transition_enemy_state(3);
        }
        return;
    case 0:
        this->advance_animation();
        this->vfunc_102();
        this->vfunc_88();
        return;
    case 5:
        this->flags = (s32) (this->flags & 0xFFFFFFFD);
        break;
    }
}

void TObjEneMorfos::state_appear(s32 reason) {

    switch (reason) {
    case 4:
        this->requested_action = 0;
        this->vfunc_95();
        this->flags = (s32) (this->flags & 0xFFFFFFF8);
        set_field_378(4);
        this->texture_offset = 0;
        this->action_phase = 0;
        this->action_progress = (f32) TObjEneMorfos__data_805DF874;
        return;
    case 3:
        if (((s32) this->action_phase == 2) && (this->fn_803344F0() == 0)) {
            this->transition_enemy_state(4);
        }
        break;
    case 0:
        switch (this->action_phase) {
        case 0:
            if (update_linked_position(TObjEneMorfos__data_805DF86C) != 0) {
                this->action_phase = 1;
                enemy_copy_target_destination();
                update_velocity();
            }
            break;
        case 1:
            this->action_progress = (f32) (this->action_progress + lbl_805DF894);
            this->texture_offset = (s32) floor_to_float(this->action_progress);
            if ((s32) this->texture_offset >= 0xC) {
                this->texture_offset = 0xC;
                this->action_phase = 2;
            }
            TObjPlayer::play_effect_if_v2(-0x100);
            break;
        }
        this->vfunc_102();
        this->vfunc_89();
        return;
    case 5:
        this->texture_offset = 0xC;
        this->vfunc_96();
        break;
    }
}

void TObjEneMorfos::state_hidden(s32 reason) {
    switch (reason) {
    case 4:
        this->requested_action = 0;
        this->vfunc_95();
        this->flags = (s32) (this->flags & 0xFFFFFFF9);
        this->flags = (s32) (this->flags | 1);
        this->set_field_378(2);
        VecCopy((Vec *)(&this->position), (const Vec *)(&this->home_position));
        VecCopy((Vec *)(&this->prev_position), (const Vec *)(&this->position));
        VecCopy((Vec *)(&body_center_position), (const Vec *)(&this->position));
        this->damage_fade.reset_color();
        this->body_fade.reset_color();
        return;
    case 3:
        if (update_linked_position(TObjEneMorfos__data_805DF86C) != 0) {
            this->transition_enemy_state(1);
        }
    case 5:
    case 0:
        return;
    }
}

void TObjEneMorfos::state_disappear(s32 reason) {
    s32 step;
    s32 dispatch_step;
    s32 fade_finished;

    switch (reason) {
    case 4:
        this->requested_action = 0;
        this->vfunc_95();
        this->flags = (s32) (this->flags & 0xFFFFFFF8);
        this->set_field_378(7);
        this->action_phase = 0;
        this->phase_counter = 0;
        return;
    case 3:
        if (this->fn_803344F0() == 0) {
            step = this->action_phase;
            if (step == 2) {
                this->transition_enemy_state(4);
            } else if (step == 3) {
                this->transition_enemy_state(2);
            }
        }
        break;
    case 5:
        break;
    case 0:
        this->advance_animation();
        dispatch_step = this->action_phase;
        switch (dispatch_step) {
        case 0:
            if (this->update_linked_position(TObjEneMorfos__data_805DF86C) != 0) {
                this->enemy_copy_target_destination();
                this->update_velocity();
                this->action_phase = 2;
            } else {
                this->phase_counter = (s32) (this->phase_counter + 1);
                if ((s32) this->phase_counter > 0x3C) {
                    this->phase_counter = 0;
                    this->action_phase = 1;
                    this->damage_fade.reset_color();
                    this->body_fade.reset_color();
                    this->flags = (s32) (this->flags | 2);
                }
            }
            break;
        case 1:
            fade_finished = this->body_fade.decay_value_toward_floor();
            if ((this->damage_fade.decay_value_toward_floor() != 0) && (fade_finished != 0)) {
                this->action_phase = 3;
            }
            break;
        }
        this->vfunc_102();
        this->vfunc_89();
        break;
    }
}

void TObjEneMorfos::state_move(s32 reason) {
    switch (reason) {
    case 4:
        this->requested_action = 0;
        this->vfunc_96();
        this->flags = (s32) (this->flags & 0xFFFFFFF8);
        this->set_field_378(4);
        this->action_phase = 0;
        this->target_angle = 0;
        this->phase_counter = 0;
        this->action_progress = (f32) TObjEneMorfos__data_805DF874;
        this->movement_direction.x = (f32) TObjEneMorfos__data_805DF874;
        this->movement_direction.y = (f32) TObjEneMorfos__data_805DF874;
        this->movement_direction.z = (f32) TObjEneMorfos__data_805DF874;
        return;
    case 3:
        if (this->fn_803344F0() == 0) {
            if ((u32) this->target == 0U) {
                this->transition_enemy_state(7);
            } else if (this->target_distance <= lbl_805DF87C) {
                if (this->random_ratio() < lbl_805DF890) {
                    this->transition_enemy_state(6);
                } else {
                    this->transition_enemy_state(5);
                }
            } else if ((s32) this->phase_counter == 3) {
                this->transition_enemy_state(6);
            }
        }
        break;
    case 5:
        break;
    case 0:
        this->advance_animation();
        this->play_frame_sounds();
        if (this->update_linked_position(TObjEneMorfos__data_805DF86C) != 0) {
            this->enemy_copy_target_destination();
            this->update_velocity();
        }
        switch (this->phase_counter) {
        case 0:
            if (this->enemy_has_live_target() != 0) {
                this->target_angle = (s32) (u16) (s32) (morfos_angle_units_per_radian * atan2_float((f32) (this->target_direction.x), (f32) (this->target_direction.z)));
            } else {
                this->target_angle = (s32) this->rotation_y;
            }
            this->phase_counter = 1;
        case 1:
            if (this->turn_toward_angle((s32)((int) (this->target_angle)), (s32)((int) (morfos_parameters->movement_turn_step))) != 0) {
                this->phase_counter = 2;
                this->movement_direction.x = sin_table_lookup((int) (this->rotation_y));
                this->movement_direction.z = cos_table_lookup((int) (this->rotation_y));
            }
            this->vfunc_102();
            break;
        case 2:
            if (TObjEneDD::check_v2_mode() != 0) {
                if (this->select_target_in_view() != 0) {
                    this->enemy_copy_target_destination();
                    this->update_velocity();
                    this->phase_counter = 3;
                } else if (this->enemy_has_live_target() != 0) {
                    this->target_angle = (s32) (u16) (s32) (morfos_angle_units_per_radian * atan2_float((f32) (this->target_direction.x), (f32) (this->target_direction.z)));
                } else {
                    this->target_angle = (s32) this->rotation_y;
                }
                this->turn_toward_angle((s32)((int) (this->target_angle)), (s32)((int) (morfos_parameters->movement_turn_step)));
            } else {
                this->action_progress = (f32) (this->action_progress + this->movement_speed);
                if (this->action_progress >= this->movement_interval) {
                    this->action_progress = (f32) TObjEneMorfos__data_805DF874;
                    this->action_phase = (s32) (this->action_phase + 1);
                    if (((s32) this->action_phase >= 2) && (this->select_target_in_view() != 0)) {
                        this->action_phase = 0;
                        this->enemy_copy_target_destination();
                        this->update_velocity();
                        this->phase_counter = 3;
                    } else {
                        this->phase_counter = 0;
                    }
                }
                if ((s32) this->ground_movement == 1) {
                    this->move_clamped_on_ground((f32) (this->movement_direction.x), (f32) (this->movement_direction.z), (f32) (this->movement_speed));
                }
            }
            break;
        }
        this->vfunc_89();
        break;
    }
}

void TObjEneMorfos::state_projectile_attack(s32 reason) {
    switch (reason) {
    case 4:
        this->vfunc_96();
        this->flags = (s32) (this->flags & 0xFFFFFFF8);
        this->set_field_378(6);
        if (this->enemy_has_live_target() != 0) {
            this->target_angle = (s32) (u16) ((s32) (morfos_angle_units_per_radian * atan2_float(this->target_direction.x, this->target_direction.z)) + 0x8000);
            this->action_phase = 0;
            this->phase_counter = 0;
            this->requested_action = 0;
            play_sound_effect(0x4003A528, (u32)&position, 0, 0);
            return;
        }
        this->action_phase = 6;
        return;
    case 3:
        if (((s32) this->action_phase == 6) && (this->fn_803344F0() == 0)) {
            this->transition_enemy_state(4);
        }
        break;
    case 5:
        break;
    case 0:
        this->advance_animation();
        switch (this->action_phase) {
        case 0:
            if (this->turn_toward_angle(this->target_angle, morfos_parameters->attack_turn_step) != 0) {
                this->action_phase = 1;
                this->requested_action = 2;
                spawn_particle_effect(&model_node_positions[PROJECTILE_POSITION], 0x212);
            }
            break;
        case 1:
            if (this->is_passing_frame((f32)TObjEneMorfos__data_805DF884) != 0) {
                this->action_phase = 2;
            }
            break;
        case 2:
            if (this->is_passing_frame((f32)lbl_805DF88C) != 0) {
                play_sound_effect(0x4003AD24, (u32)&position, 0, 0);
                new TUnk_804EF130(&model_node_positions[PROJECTILE_POSITION], (u16)(target_angle + 0x8000), this);
                this->action_phase = 3;
            }
            break;
        case 3:
            if (this->get_flag_b4() != 0) {
                this->requested_action = 0;
                this->phase_counter = (this->phase_counter + 1);
                if (this->enemy_has_live_target() != 0) {
                    if ((s32) this->phase_counter >= 2) {
                        this->target_angle = (s32) (morfos_angle_units_per_radian * atan2_float(this->target_direction.x, this->target_direction.z));
                        this->action_phase = 5;
                    } else {
                        this->requested_action = 0;
                        this->action_phase = 4;
                        this->burst_timer = 0;
                    }
                } else if (this->select_target_in_view() != 0) {
                    this->enemy_copy_target_destination();
                    this->update_velocity();
                    if ((s32) this->phase_counter >= 2) {
                        this->target_angle = (s32) (morfos_angle_units_per_radian * atan2_float(this->target_direction.x, this->target_direction.z));
                        this->action_phase = 5;
                        play_sound_effect(0x4003A528, (u32)&position, 0, 0);
                    } else {
                        this->requested_action = 0;
                        this->action_phase = 4;
                        this->burst_timer = 0;
                    }
                } else {
                    this->target_angle = (s32) (u16) (this->target_angle + 0x8000);
                    this->action_phase = 5;
                }
            }
            break;
        case 4:
            this->burst_timer = (s32) (this->burst_timer + 1);
            if ((s32) this->burst_timer >= (s32) morfos_parameters->attack_delay) {
                if (this->enemy_has_live_target() != 0) {
                    this->enemy_copy_target_destination();
                    this->update_velocity();
                    this->target_angle = (s32) (u16) ((s32) (morfos_angle_units_per_radian * atan2_float(this->target_direction.x, this->target_direction.z)) + 0x8000);
                    this->action_phase = 0;
                    play_sound_effect(0x4003A528, (u32)&position, 0, 0);
                } else {
                    this->action_phase = 6;
                }
            }
            break;
        case 5:
            if (this->turn_toward_angle(this->target_angle, morfos_parameters->attack_turn_step) != 0) {
                this->action_phase = 6;
            }
            break;
        }
        this->vfunc_102();
        this->vfunc_89();
        break;
    }
}

#pragma push
#pragma opt_common_subs off
void TObjEneMorfos::state_rotating_projectile_burst(s32 reason) {
    s32 old;
    s32 n;
    s32 i;
    TObjPlayer *pl;
    switch (reason) {
    case 4:
        this->vfunc_96();
        this->flags &= ~3;
        this->flags |= 4;
        this->set_field_378(4);
        this->target_angle = 0;
        this->burst_start_angle = 0;
        this->action_phase = 0;
        this->burst_timer = 0;
        this->requested_action = 0;
        this->charge_effect = (TParticleCtrl *)create_particle_emitter(&this->model_node_positions[PROJECTILE_POSITION], 0x10A);
        break;
    case 3:
        if (this->action_phase == 5 && this->fn_803344F0() == 0) {
            this->transition_enemy_state(4);
        }
        break;
    case 0:
        this->advance_animation();
        switch (this->action_phase) {
        case 0:
            if (this->charge_effect != 0) {
                ((TParticleCtrl *)this->charge_effect)->set_position(&this->model_node_positions[PROJECTILE_POSITION]);
            }
            this->burst_start_angle = this->rotation_y;
            this->rotation_y = this->rotation_y + morfos_parameters->charge_turn_step;
            this->burst_timer = this->burst_timer + 1;
            if (this->burst_timer >= morfos_parameters->charge_duration) {
                this->action_phase = 1;
                this->phase_counter = 0;
                if (this->charge_effect != 0) {
                    this->charge_effect->queue_destruction();
                    this->charge_effect = 0;
                }
            }
            break;
        case 1: {
            old = this->rotation_y;
            this->rotation_y += morfos_parameters->attack_turn_step;
            n = TLobby::get_game_mode();
            for (i = 0; i < n; i++) {
                pl = TObjPlayer::get_player_data(i);
                if (pl->is_alive() != 0) {
                    if (((TObjBase *)this)->get_room() == ((TObjBase *)pl)->get_room()) {
                        this->enemy_copy_target_destination();
                        this->update_velocity();
                        this->target_angle = (u16)((s32)(morfos_angle_units_per_radian * atan2_float(this->target_direction.x, this->target_direction.z)) + 0x8000);
                        if (crosses_heading(old, this->rotation_y, this->target_angle) != 0) {
                            this->rotation_y = this->target_angle;
                            this->action_phase = 2;
                            this->requested_action = 2;
                            break;
                        }
                    }
                }
            }
            if (this->action_phase == 1 && crosses_heading(old, this->rotation_y, this->burst_start_angle) != 0) {
                this->action_phase = 2;
                this->requested_action = 2;
            }
            break;
        }
        case 2:
            spawn_particle_effect(&this->model_node_positions[PROJECTILE_POSITION], 0x212);
            if (this->is_passing_frame((f32)TObjEneMorfos__data_805DF884) != 0) {
                this->action_phase = 3;
            }
            break;
        case 3:
            if (this->is_passing_frame((f32)lbl_805DF88C) != 0) {
                play_sound_effect(0x4003AD24, (u32)(&this->position), 0, 0);
                new TUnk_804EF130(&model_node_positions[PROJECTILE_POSITION], (u16)(rotation_y + 0x8000), this);
                this->action_phase = 4;
            }
            break;
        case 4:
            if (this->get_flag_b4() != 0) {
                this->requested_action = 0;
                this->phase_counter = this->phase_counter + 1;
                if (game_difficulty_selection == 3 || game_difficulty_selection == 2) {
                    if (this->phase_counter >= 5) {
                        this->action_phase = 5;
                        break;
                    }
                } else if (this->phase_counter >= 4) {
                    this->action_phase = 5;
                    break;
                }
                this->burst_start_angle = this->rotation_y;
                this->rotation_y = this->rotation_y + morfos_parameters->attack_turn_step;
                this->action_phase = 1;
            }
            break;
        }
        this->vfunc_102();
        this->vfunc_89();
        break;
    case 5:
        if (this->charge_effect != 0) {
            this->charge_effect->queue_destruction();
            this->charge_effect = 0;
        }
        break;
    }
}
#pragma pop

void TObjEneMorfos::state_melee_attack(s32 reason) {
    switch (reason) {
    case 4:
        this->requested_action = 0;
        this->vfunc_96();
        this->flags = (s32) (this->flags & 0xFFFFFFF8);
        this->set_field_378(5);
        this->action_phase = 0;
        this->phase_counter = 0;
        break;
    case 3:
        switch (this->action_phase) {
        case 0:
            if ((this->fn_803344F0() == 0) && ((void *) this->target == NULL)) {
                this->transition_enemy_state(7);
            }
            break;
        case 3:
            this->transition_enemy_state(4);
            break;
        }
        break;
    case 5:
        break;
    case 0:
        this->advance_animation();
        switch (this->action_phase) {
        case 0:
            if (enemy_validate_retained_target((u8 *)this) != 0) {
                this->enemy_copy_target_destination();
                this->update_velocity();
                if (this->turn_toward_angle((s32) (morfos_angle_units_per_radian * atan2_float(this->target_direction.x, this->target_direction.z)), morfos_parameters->attack_turn_step) != 0) {
                    this->action_phase = 1;
                    this->requested_action = 1;
                    play_sound_effect(0x4003A725, (u32)&position, 0, 0);
                    TObjEneMorfosArm::create((void *)this, (void *)this);
                } else if (this->target_distance >= lbl_805DF87C) {
                    this->action_phase = 3;
                }
                this->play_frame_sounds();
            }
            break;
        case 1:
            if ((this->is_passing_frame((f32)lbl_805DF880) != 0) && (this->enemy_check_target_valid() != 0)) {
                if (((TObjChara *)this->target)->select_melee_contact_body(this, TObjEneMorfos__data_805DF884) != 0) {
                    ((TObjChara *)this->target)->receive_physical_attack(this, TObjEneMorfos__data_805DF884);
                    ((TObjChara *)this->target)->apply_knockback_from_attacker((u8 *)this, lbl_805DF888);
                }
            }
            if (this->get_flag_b4() != 0) {
                this->action_phase = 2;
                this->phase_counter = 0;
                this->requested_action = 0;
            }
            break;
        case 2:
            this->phase_counter = (this->phase_counter + 1);
            if ((s32) this->phase_counter >= 0x32) {
                this->action_phase = 3;
                this->requested_action = 0;
            }
            break;
        }
        this->vfunc_102();
        this->vfunc_89();
        break;
    }
}

void TObjEneMorfos::state_patrol(s32 reason) {
    s32 previous_heading;

    switch (reason) {
    case 4:
        this->requested_action = 0;
        this->vfunc_96();
        this->flags = (s32) (this->flags & 0xFFFFFFF8);
        set_field_378(8);
        this->action_phase = 0;
        this->target_angle = (this->rotation_y + 0x3800);
        break;
    case 3:
        if ((s32) this->rotation_y >= (s32) this->target_angle) {
            this->transition_enemy_state(6);
        }
        break;
    case 5:
        break;
    case 0:
        advance_animation();
        if (is_patrol_active__21TObjEneRe7BeruraPunchFv(this) == 0) {
            this->play_speed = (f32) lbl_805DF878;
        }
        previous_heading = this->rotation_y;
        this->rotation_y = (previous_heading + 0x280);
        this->vfunc_102();
        this->vfunc_89();
        break;
    }

}

void TObjEneMorfos::state_damaged(s32 reason) {
    s32 previous_flags;
    switch (reason) {
    case 4:
        this->requested_action = 3;
        this->vfunc_96();
        this->flags = (s32) (this->flags & 0xFFFFFFF8);
        this->advance_animation();
        this->set_active();
        return;
    case 3:
        if (get_flag_b4() != 0) {
            previous_flags = this->flags;
            if (previous_flags & 0x20) {
                this->flags = (s32) (previous_flags & 0xFFFFFFDF);
                if (this->try_enter_low_hp_state() == 0) {
                    this->transition_enemy_state((s32)((int) (this->m_378)));
                }
            } else {
                if (this->check_low_hp_trigger() != 0) {
                    this->transition_enemy_state((s32)((int) (this->m_378)));
                } else if (this->try_enter_low_hp_state() == 0) {
                    this->transition_enemy_state((s32)((int) (this->m_378)));
                }
            }
        }
        break;
    case 0:
        this->advance_animation();
        return;
    case 5:
        clear_attack_receipts();
        this->clear_field_388();
        break;
    }
}

void TObjEneMorfos::state_death(s32 reason) {
    s32 step;
    s32 body_fade_finished;

    switch (reason) {
    case 4:
        this->requested_action = 4;
        this->vfunc_96();
        this->flags = (s32) (this->flags & 0xFFFFFFF8);
        this->advance_animation();
        this->refresh_and_send_entity_flags();
        this->action_progress = (f32) this->texture_offset;
        this->phase_counter = 0;
        this->action_phase = 0;
        this->body_fade.start_fade_out();
        play_sound_effect(0x4003A626, (u32)(&this->position), 0, 0);
        return;
    case 3:
        if ((s32) this->phase_counter == 2) {
            queue_destruction();
        }
    case 5:
        return;
    case 0:
        step = this->phase_counter;
        switch (step) {
        case 0:
            this->advance_animation();
            body_fade_finished = this->body_fade.decay_value_toward_floor();
            if ((this->get_flag_b4() != 0) && (body_fade_finished != 0)) {
                fn_800D911C((Vec *)(&this->position));
                play_sound_effect(0x4003A830, (u32)(&this->position), 0, 0);
                TObjPlayer__sub_800A04F0(&this->damage_fade);
                this->flags = (s32) (this->flags | 2);
                this->phase_counter = 1;
                return;
            }
            break;
        case 1:
            if (this->damage_fade.decay_value_toward_floor() != 0) {
                this->phase_counter = 2;
                this->flags = (s32) (this->flags | 1);
                TObjPlayer::apply_effect_variant_b((s32)(&this->position), 0);
                return;
            }
            break;
        default:
            this->phase_counter = 2;
            break;
        }
        break;
    }
}

void TObjEneMorfos::record_model_node_position() {
    switch (morfos_model_node_index) {
    case 6:
    case 10: {
        Vec point = morfos_node_position_origin;
        transform_point_to_view(&point, morfos_node_position_cursor);
        ++morfos_node_position_cursor;
        break;
    }
    }
    ++morfos_model_node_index;
}

void TObjEneMorfos::render_with_camera_fade(s32 idx, s32 mode) {
    s32 vis;
    RenderFadeState *part;
    part = &this->camera_fade[idx];
    part->update();
    vis = part->updateFromCamera((const f32 *)&body_center_position);
    TObjFish::set_global_param(this->texlist);
    TObjPlayer::toggle_particle_effect();
    push_matrix();
    post_translate_matrix(&this->position);
    rotate_matrix_y(0, this->rotation_y);
    morfos_model_node_index = 0;
    morfos_node_position_cursor = &this->model_node_positions[PROJECTILE_POSITION];
    set_chunk_model_node_callback((s32)((void *)TObjEneMorfos::record_model_node_position));
    if (this->flags & 2) {
        if (this->damage_fade.has_visible_opacity() != 0) {
            this->damage_fade.set_flags_and_apply_damage_color();
            if (get_mode__11TCameraCtrlFPv(((s32 *)&main_task)) & 0x200) {
                this->draw();
            }
            this->damage_fade.clear_flag_and_notify();
        }
    } else if (vis != 0) {
        part->set_flags_and_apply_damage_color();
        if (get_mode__11TCameraCtrlFPv(((s32 *)&main_task)) & 0x200) {
            this->draw();
        }
        part->clear_flag_and_notify();
    } else if (!(get_mode__11TCameraCtrlFPv(((s32 *)&main_task)) & 0x200)) {
        if (mode == 1) {
            this->draw();
        } else {
            this->draw_motion_model();
        }
    }
    set_chunk_model_node_callback((s32)NULL);
    pop_matrix();
    this->update_primary_light();
    TParticleCtrl::end_effect_render();
}

void TObjEneMorfos::render() {
    s32 cam;
    s32 vis;
    if (check_demo_mode() != 0) {
        this->render_demo();
        return;
    }
    cam = 0;
    if (is_split_screen() != 0) {
        cam = get_camera_mode__11TCameraCtrlFv();
    }
    if (this->flags & 1) {
        vis = 0;
    } else if (is_main_phase_15() != 0) {
        vis = this->classify_actor_view_detail(lbl_805D9E88, lbl_805D9E84, TObjEneMorfos__data_805DF870);
    } else if (this->update_object_view_visibility(TObjEneMorfos__data_805DF86C, TObjEneMorfos__data_805DF870) != 0) {
        vis = 1;
    } else {
        vis = 0;
    }
    if (vis != 0 && this->render_reflection() == 0) {
        this->defer_render();
        this->render_with_camera_fade(cam, vis);
        if (this->mode != 0xB && !(this->ground_flags & 0x4000)) {
            Vec v = lbl_804775E4;
            draw_ground_shadow(&v, 0);
        }
        this->update_secondary_light();
        saved_model_render_flags = model_render_flags;
        TObjEneDD::clear_global_flag_400();
        model_render_flags &= ~0x810;
        if (this->flags & 0x10) {
            this->draw_guard_wall();
        }
        model_render_flags = saved_model_render_flags;
    }
}

s32 TObjEneMorfos::render_reflection() {
    if (get_mode__11TCameraCtrlFPv((void *) (((s32 *)&main_task))) & 0x20) {
        if (push_reflection_matrix(&ground_position) != 0) {
            TObjFish::set_global_param(this->texlist);
            push_matrix();
            post_translate_matrix(&position);
            rotate_matrix_y(0, this->rotation_y);
            this->draw();
            pop_matrix();
            if (flags & 0x10) {
                this->draw_guard_wall();
            }
            restore_render_scissor(1);
        }
        return 1;
    }
    return 0;
}

#pragma push
#pragma opt_common_subs off
void TObjEneMorfos::draw_guard_wall() {
    if (get_mode__11TCameraCtrlFPv(&main_task) & 0x200) {
        TObjFish::set_global_param(morfos_resources->models[2].m_c);
        push_matrix();
        post_translate_matrix(&this->model_node_positions[PROJECTILE_POSITION]);
        rotate_matrix_y(0, rotation_y);
        if (flags & 2) {
            if (this->body_fade.has_visible_opacity() != 0) {
                this->body_fade.set_flags_and_apply_damage_color();
                draw_chunk_model(((NJS_OBJECT *)morfos_resources->models[2].model)->model);
                this->body_fade.clear_flag_and_notify();
            }
        } else {
            draw_chunk_model(((NJS_OBJECT *)morfos_resources->models[2].model)->model);
        }
        pop_matrix();
    }
}
#pragma pop

BmlResource *TObjEneMorfos::get_resources() {  return morfos_resources; }

s32 TObjEneMorfos::get_heading() {
    return rotation_y;
}

Vec *TObjEneMorfos::get_arm_position() {
    return &model_node_positions[ARM_POSITION];
}

s32 TObjEneMorfos::crosses_heading(s32 start, s32 end, s32 heading) {
    u8 result;
    s32 difference;
    s32 point;
    s32 finish;
    s32 begin;
    begin = (start & 0xFFFF);
    finish = (end & 0xFFFF);
    if (begin > finish) {
        point = (heading & 0xFFFF);
        result = 0;
        difference = begin - point;
        if ((difference >= 0 && finish - point >= 0) ||
            (difference <= 0 && finish - point <= 0)) {
            result = 1;
        }
        return result;
    } else {
        u8 result;
        s32 difference;
        s32 point;
        point = (heading & 0xFFFF);
        result = 0;
        difference = begin - point;
        if ((difference <= 0 && finish - point >= 0) ||
            (difference >= 0 && finish - point <= 0)) {
            result = 1;
        }
        return result;
    }
}

void TObjEneMorfos::update_ground_probe() {
    Vec probe;
    CsnGroundHit *hit;
    if (actor_frame_tick % 5 == 0) {
        VecCopy(&probe, &position);
        probe.y += TObjEneMorfos__data_805DF870;
        hit = csnVectorUnder(&probe, (u32 *)&m_120, 0x4000);
        if (hit != NULL) {
            ground_flags = hit->flags;
            VecCopy(&ground_position, &hit->surface->point);
        } else {
            VecCopy(&ground_position, &position);
        }
    }
    if (ground_flags & 0x4000) {
        TObjEneRecon::set_active();
    }
}

void TObjEneMorfos::update_demo() {
    if (get_target_info() != 0) {
        initialize_behavior_parameters();
    }
}

void TObjEneMorfos::render_demo() {
    s32 index;
    f32 animation_frame;
    AnimationMotion *motion;
    get_target_info();
    if (update_object_view_visibility(TObjEneMorfos__data_805DF86C, TObjEneMorfos__data_805DF870) != 0) {
        if (mode != 0xB) {
            Vec offset = lbl_804775F0;
            draw_ground_shadow(&offset, 0);
        }
        TObjPlayer::toggle_particle_effect();
        TObjFish::set_global_param(texlist);
        push_matrix();
        post_translate_matrix(&position);
        rotate_matrix_y(0, rotation_y);
        index = (s32)parameters[0];
        if (index < 0) {
            index = 0;
        } else if (index >= 5) {
            index = 4;
        }
        motion = motion_list[action_table[index].motion].motion;
        animation_frame = parameters[1];
        if (animation_frame < TObjEneMorfos__data_805DF874) {
            animation_frame = TObjEneMorfos__data_805DF874;
        } else if (animation_frame > motion->frameCount - 1) {
            animation_frame = (f32)motion->frameCount;
        }
        set_motion_packed_rotation();
        draw_model_motion(model, motion, animation_frame);
        clear_motion_packed_rotation();
        pop_matrix();
        TParticleCtrl::end_effect_render();
    }
}
}

extern "C" {
__declspec(section ".rodata") extern const char morfos_arm_model_filename[] = "kabe_arm.nj";
__declspec(section ".rodata") extern const char morfos_body_model_filename[] = "kabe_body.nj";
__declspec(section ".rodata") extern const char morfos_wall_model_filename[] = "kabe_wall.nj";
__declspec(section ".rodata") extern const char morfos_arm_attack_motion_filename[] = "attack_kabe_arm.njm";
__declspec(section ".rodata") extern const char morfos_body_attack_motion_filename[] = "attack_kabe_body.njm";
__declspec(section ".rodata") extern const char morfos_body_beam_motion_filename[] = "beam_kabe_body.njm";
__declspec(section ".rodata") extern const char morfos_body_damage_motion_filename[] = "damage_kabe_body.njm";
__declspec(section ".rodata") extern const char morfos_body_death_motion_filename[] = "dead_kabe_body.njm";
__declspec(section ".rodata") extern const char morfos_body_wait_motion_filename[] = "wait_kabe_body.njm";
__declspec(section ".rodata") extern const char morfos_archive_filename[] = "bm_ene_morfos.bml";
__declspec(section ".rodata") extern const char morfos_low_arm_model_filename[] = "lo_kabe_arm.nj";
__declspec(section ".rodata") extern const char morfos_low_body_model_filename[] = "lo_kabe_body.nj";
__declspec(section ".rodata") extern const char morfos_low_archive_filename[] = "bm_ene_morfos_low.bml";
__declspec(section ".rodata") extern const char morfos_class_string[] = "TObjEneMorfos";
__declspec(section ".rodata") extern const NpcAnimationBinding morfos_npc_animation_binding = {NULL, morfos_motion_param_table, 0, 0, 6};
__declspec(section ".rodata") extern const Vec morfos_node_position_origin = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") extern const Vec lbl_804775E4 = {2.0f, 1.0f, 2.0f};
__declspec(section ".rodata") extern const Vec lbl_804775F0 = {2.0f, 1.0f, 2.0f};
}

extern "C" {
extern const s32 morfos_base_stat_ids[1] = {64};
extern const s32 morfos_resistance_stat_ids[1] = {64};
extern const s32 morfos_behavior_parameter_ids[1] = {64};
}

extern "C" {
extern const f32 TObjEneMorfos__data_805DF86C = 400.0f;
extern const f32 TObjEneMorfos__data_805DF870 = 15.0f;
extern const f32 TObjEneMorfos__data_805DF874 = 0.0f;
extern const f32 lbl_805DF878 = 1.6f;
extern const f32 lbl_805DF87C = 30.0f;
extern const f32 lbl_805DF880 = 8.0f;
extern const f32 TObjEneMorfos__data_805DF884 = 1.0f;
extern const f32 lbl_805DF888 = 5.0f;
extern const f32 lbl_805DF88C = 6.0f;
extern const f32 lbl_805DF890 = 0.3f;
extern const f32 lbl_805DF894 = 0.5f;
extern const f32 lbl_805DF898 = 4.0f;
extern const f32 TObjEneMorfos__data_805DF89C = 20.0f;
extern const f32 lbl_805DF8A0 = 0.28f;
extern const f32 lbl_805DF8A4 = 0.1f;
extern const f32 lbl_805DF8A8 = 10.0f;
}
const char *morfos_class_name = morfos_class_string;
