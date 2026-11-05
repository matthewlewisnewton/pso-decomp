#pragma defer_codegen on
#pragma readonly_strings on
#define TOBJECT_OUT_OF_LINE_HELPERS
#include "pso/player/demo_mode.h"
#include "pso/misc/PersistentSound.h"
#include "pso/system/CurrentTextureList.h"
#include "pso/misc/ParticleFactory.h"
#include "pso/enemy/EnemyUnknownHooks.h"
#include "pso/math/VectorNormalize.h"
#include "pso/math/ViewPoint.h"
#include "pso/enemy/BattleParameters.h"
#include "pso/npc/NpcAnimationBinding.h"
#include "pso/system/BmlResourceDescriptor.h"
#include "pso/system/MatrixStack.h"
#include "pso/unk/text_803D8F74.h"
#include "pso/object/TObjFish.h"
#include "pso/system/MatrixOps.h"
#include "pso/math/MatrixTransforms.h"
#include "pso/system/SoundEffect.h"
#include "pso/misc/TOTrapAncient01_80226534.h"
#include "pso/enemy/TObjEnemy.h"
#include "pso/system/EnemyBmlResource.h"
#include "pso/system/BmlResourceClass.h"
#include "pso/enemy/TObjEneRe7Berura_803E4CE0.h"
#include "pso/player/TObjPlayer_803E4954.h"
#include "pso/system/vector.h"
#include "types.h"
#include "pso/enemy/TObjEneBm3FlyNest_CarryFly.h"
#include "pso/player/TObjPlayer.h"
#include "pso/player/TObjChara.h"
#include "pso/enemy/TObjEneBm3Fly.h"
#include "pso/enemy/TObjEneDD.h"
#include "pso/object/TObjMotion.h"
#include "pso/enemy/TObjEneBm3FlyNest.h"
#include "pso/system/BmlResource.h"
#include "pso/player/TObjPlayer_801542CC.h"
#include "pso/player/TObjPlayer_800D8FDC.h"
#include "pso/enemy/TEnemyTaskList.h"

#include "pso/enemy/TObjEneDD_ST.h"
#include <stddef.h>
#include "pso/TObject.h"
#include "pso/TParticleCtrl.h"
#include "pso/enemy/TObjEnePanarms.h"
#include "pso/enemy/TObjEneRe7Berura.h"
#include "pso/misc/RenderFadeState.h"
#include "pso/misc/TLobby.h"
#include "pso/misc/TCameraCtrl.h"

#include "pso/ui/TAdSinglePlyChrSelectGC.h"
#include "pso/npc/NpcModelRegistry.h"

extern "C" {

s32 is_split_screen();
f32 atan2_float(f32 y, f32 x);
void rotate_xz_pair_by_angle(f32 *x, f32 *z, s32 angle);

s32 pack_debug_text_position(s32, s32);

f32 sin_table_lookup(int);
f32 cos_table_lookup(int);
void debug_printf_at(s32, const char *, ...);
void draw_chunk_object(void *child);


extern const char fly_body_model_filename[];
extern const char fly_nest_model_filename[];
extern const char fly_attack_motion_filename[];
extern const char fly_damage_motion_filename[];
extern const char nest_damage_motion_filename[];
extern const char fly_death_motion_filename[];
extern const char nest_death_motion_filename[];
extern const char nest_fall_motion_filename[];
extern const char fallen_nest_damage_motion_filename[];
extern const char fallen_nest_emit_motion_filename[];
extern const char fallen_nest_wait_motion_filename[];
extern const char nest_emit_motion_filename[];
extern const char fly_flight_motion_filename[];
extern const char nest_land_motion_filename[];
extern const char fly_move_motion_filename[];
extern const char nest_trance_motion_filename[];
extern const char nest_wait_motion_filename[];
extern const char fly_bml_filename[];
struct Params_80491DA0 { f32 f00; u32 w[6]; };
Params_80491DA0 bm3_fly_nest_params = { 225.0f, { 0x0, 0x600, 0x0, 0x0, 0x0, 0x0 } };
CollisionBody bm3_flynest_collider_params = { { 0.0f, 0.0f, 0.0f }, 10.0f, 0.0f, 0, 0x8003, { 0.0f, 0.0f, 0.0f }, 0.0f };
const char *bm_ene_bm3_fly_model_names[3] = {
    fly_body_model_filename,
    fly_nest_model_filename,
    0
};
const char *bm_ene_bm3_fly_motion_names[16] = {
    fly_attack_motion_filename,
    fly_damage_motion_filename,
    nest_damage_motion_filename,
    fly_death_motion_filename,
    nest_death_motion_filename,
    nest_fall_motion_filename,
    fallen_nest_damage_motion_filename,
    fallen_nest_emit_motion_filename,
    fallen_nest_wait_motion_filename,
    nest_emit_motion_filename,
    fly_flight_motion_filename,
    nest_land_motion_filename,
    fly_move_motion_filename,
    nest_trance_motion_filename,
    nest_wait_motion_filename,
    0
};
BmlResourceDescriptor bm3_fly_nest_resource_desc = { fly_bml_filename, bm_ene_bm3_fly_model_names, bm_ene_bm3_fly_motion_names, 0x2, 0xf };
TObjMotionAction bm3_flynest_hit_action_table[10] = {
    { 1, 0, 14, 0.3f, 0 },
    { 3, 0, 9, 0.7f, 0 },
    { 3, 0, 2, 1.0f, 0 },
    { 3, 0, 5, 0.5f, 0 },
    { 1, 0, 8, 0.3f, 0 },
    { 3, 0, 7, 0.7f, 0 },
    { 3, 0, 6, 1.0f, 0 },
    { 3, 0, 4, 0.3f, 0 },
    { 1, 0, 13, 0.3f, 0 },
    { 3, 0, 11, 0.2f, 0 }
};
extern const s32 bm3_fly_nest_attachment_sample_table[8];
extern const NpcAnimationBinding bm3_flynest_anim_binding;
extern Vec child_spawn_velocity;
extern const Vec lbl_8043B310;
extern const Vec lbl_8043B31C;
extern const char normal_state_text[];
extern const char dead_state_text[];
extern const char fallen_state_text[];
extern const char start_count_format[];
extern const char total_count_format[];
struct Unk_80500B2C {
    f32 *pv;
    s32 *pc;
    s32 d;
    s32 e;
    s32 f;
};
Vec TObjEneBm3FlyNest__attachment_sample_origin;
f32 fly_nest_vertex_table[6];
__declspec(section ".data") s32 lbl_80500B24[2];
Unk_80500B2C lbl_80500B2C;
extern s32 debug_chunk_object;
extern const char *TObjEneBm3FlyNest_CarryFly__name;
BattleBaseStats *bm3_flynest_base_stats;
AttackParams *bm3_flynest_attack_params;
ActorParamBlock *bm3_flynest_resistance_params;
BattleMovementParams *bm3_flynest_movement_params;
BmlResource *nest_resources;
s32 attachment_node_index;
Vec *attachment_point_cursor;
Vec *carrier_point_cursor;
s32 carrier_sample_index;
extern s32 saved_model_render_flags;
extern s32 saved_chunk_polygon_flags_and_mask;
extern s32 saved_chunk_polygon_flags_or_mask;
extern s32 chunk_polygon_flags_or_mask;
extern s32 chunk_polygon_flags_and_mask;
extern const f32 lbl_805D9E84;
extern const f32 lbl_805D9E88;
extern s32 model_render_flags;
extern void *tl_04;

__declspec(section ".rodata") extern const char fly_body_model_filename[] = "bm3_fly_body.nj";
__declspec(section ".rodata") extern const char fly_nest_model_filename[] = "bm3_s_nest.nj";
__declspec(section ".rodata") extern const char fly_attack_motion_filename[] = "atack_bm3_fly_body.njm";
__declspec(section ".rodata") extern const char fly_damage_motion_filename[] = "damage_bm3_fly_body.njm";
__declspec(section ".rodata") extern const char nest_damage_motion_filename[] = "dam_bm3_s_nest.njm";
__declspec(section ".rodata") extern const char fly_death_motion_filename[] = "dead_bm3_fly_body.njm";
__declspec(section ".rodata") extern const char nest_death_motion_filename[] = "dead_bm3_s_nest.njm";
__declspec(section ".rodata") extern const char nest_fall_motion_filename[] = "down_bm3_s_nest.njm";
__declspec(section ".rodata") extern const char fallen_nest_damage_motion_filename[] = "dwndam_bm3_s_nest.njm";
__declspec(section ".rodata") extern const char fallen_nest_emit_motion_filename[] = "dwnexit_bm3_s_nest.njm";
__declspec(section ".rodata") extern const char fallen_nest_wait_motion_filename[] = "dwnwait_bm3_s_nest.njm";
__declspec(section ".rodata") extern const char nest_emit_motion_filename[] = "exit_bm3_s_nest.njm";
__declspec(section ".rodata") extern const char fly_flight_motion_filename[] = "fly_bm3_fly_body.njm";
__declspec(section ".rodata") extern const char nest_land_motion_filename[] = "land_bm3_s_nest.njm";
__declspec(section ".rodata") extern const char fly_move_motion_filename[] = "move_bm3_fly_body.njm";
__declspec(section ".rodata") extern const char nest_trance_motion_filename[] = "trance_bm3_s_nest.njm";
__declspec(section ".rodata") extern const char nest_wait_motion_filename[] = "wait_bm3_s_nest.njm";
__declspec(section ".rodata") extern const char fly_bml_filename[] = "bm_ene_bm3_fly.bml";
__declspec(section ".rodata") extern const s32 bm3_fly_nest_attachment_sample_table[8] = { 2, 4, 9, 11, 16, 18, 24, 26 };
__declspec(section ".rodata") extern const char nest_class_string[] = "TObjEneBm3FlyNest";
__declspec(section ".rodata") extern const char carrier_class_string[] = "TObjEneBm3FlyNest_CarryFly";
__declspec(section ".rodata") extern const NpcAnimationBinding bm3_flynest_anim_binding = { 0, bm3_flynest_hit_action_table, 0, 8, 10 };
__declspec(section ".rodata") Vec child_spawn_velocity = { 0.0f, 3.0f, 0.0f };
__declspec(section ".rodata") extern const Vec lbl_8043B310 = { 5.0f, 1.0f, 5.0f };
__declspec(section ".rodata") extern const Vec lbl_8043B31C = { 5.0f, 1.0f, 5.0f };
__declspec(section ".rodata") extern const char normal_state_text[] = "STATE : NORMAL";
__declspec(section ".rodata") extern const char dead_state_text[] = "STATE : DEAD";
__declspec(section ".rodata") extern const char fallen_state_text[] = "STATE : FALLEN";
__declspec(section ".rodata") extern const char start_count_format[] = "START NUM : %2d";
__declspec(section ".rodata") extern const char total_count_format[] = "TOTAL NUM : %2d";
const char *bm3_fly_nest_class_name = nest_class_string;
const char *TObjEneBm3FlyNest_CarryFly__name = carrier_class_string;


}

void TObjEneBm3FlyNest::render_shadows() {}

void TObjEneBm3FlyNest::init_vertex_table() {
    f32 *v = fly_nest_vertex_table;
    v[3] = v[2] = v[1] = v[0] = 0.0f;
    v[5] = v[4] = (6.0f);
    lbl_80500B24[0] = -1;
    lbl_80500B24[1] = -1;
    lbl_80500B2C.pv = fly_nest_vertex_table;
    lbl_80500B2C.pc = lbl_80500B24;
    lbl_80500B2C.d = 0;
    lbl_80500B2C.e = 2;
}

TObjEneBm3FlyNest_CarryFly::TObjEneBm3FlyNest_CarryFly(TObjEneBm3FlyNest *parent,
    const Vec *attachment, const Vec *destination, const Vec *, const s32 *counter,
    s32 order) : TObject(parent) {
    Vec direction;
    m_name = TObjEneBm3FlyNest_CarryFly__name;
    this->attachment = attachment;
    this->destination = destination;
    release_counter = counter;
    this->order = order;
    VecCopy(&direction, this->attachment);
    subtract_vector(&direction, this->destination);
    normalize_vector_checked(&direction);
    rotation_y = 10430.38043493439 * atan2_float(direction.x, direction.z);
    position.x = (6.0f) * direction.x;
    position.y = (6.0f);
    position.z = (6.0f) * direction.z;
    motion = nest_resources->motions[10].motion;
    frame = this->order * 2;
    unknown_3c = (1.0f);
    unknown_44 = 0;
    this->direction.x = 0.0f;
    this->direction.y = 0.0f;
    this->direction.z = 0.0f;
    distance = 0.0f;
    flight_height = 0.0f;
    curvature = 0.0f;
    state = 0;
}

TObjEneBm3FlyNest_CarryFly::~TObjEneBm3FlyNest_CarryFly() {}

#pragma push
#pragma fp_contract on
void TObjEneBm3FlyNest_CarryFly::run_task() {
    f32 last_frame;
    f32 path_position;
    f32 flight_distance;

    last_frame = (f32) (motion->frameCount - 1);
    frame += (0.8f);
    if (frame > last_frame) {
        frame -= last_frame;
    }
    switch (state) {
    case 0:
        if (*release_counter == order) {
            Vec start_position;
            state = 1;
            VecCopy(&start_position, &position);
            vec3_add_to(&start_position, attachment);
            VecCopy(&direction, &start_position);
            subtract_vector(&direction, destination);
            direction.y -= (5.0f);
            VecCopy(&position, &direction);
            distance = normalize_vector_xz(&direction);
            if (distance <= (0.01f)) {
                queue_destruction();
                break;
            }
            curvature = (-120.0f) / (distance * distance);
            flight_height = (30.0f);
        }
        play_persistent_sound(static_cast<TObjEneBm3FlyNest *>(m_up)->remap_child_sound(0x4003A828), this, attachment, 0, 0);
        TObjPlayer::play_effect_if_v2(-0x400);
        break;
    case 1:
        position.y += (1.0f);
        if (position.y > 0.0f) {
            state = 2;
            direction.y = (0.5f) * distance;
        }
        play_persistent_sound(static_cast<TObjEneBm3FlyNest *>(m_up)->remap_child_sound(0x4003A828), this, attachment, 0, 0);
        TObjPlayer::play_effect_if_v2(-0x400);
        break;
    case 2:
        flight_distance = distance;
        path_position = direction.y;
        path_position = path_position - (0.05f) * flight_distance;
        if (path_position < (0.5f) * -flight_distance) {
            spawn_particle_effect(destination, 0xC8);
            play_sound_effect(static_cast<TObjEneBm3FlyNest *>(m_up)->remap_child_sound(0x4003AB27), destination, 0, 0);
            TObjPlayer::play_effect_if_v2(-0x400);
            queue_destruction();
            break;
        }
        position.y = curvature * (path_position * path_position) + flight_height;
        direction.y = path_position;
        path_position += 0.5f * distance;
        position.x = direction.x * path_position;
        position.z = direction.z * path_position;
        play_persistent_sound(static_cast<TObjEneBm3FlyNest *>(m_up)->remap_child_sound(0x4003A828), this, destination, 0, 0);
        TObjPlayer::play_effect_if_v2(-0x400);
        break;
    }
}
#pragma pop

void TObjEneBm3FlyNest_CarryFly::render() {
    set_current_texture_list((GinjaTextureList *)nest_resources->models[0].m_c);
    push_matrix();
    if (state == 0) {
        post_translate_matrix(&attachment->x);
    } else {
        post_translate_matrix(&destination->x);
    }
    post_translate_matrix(&position.x);
    rotate_matrix_y(0, rotation_y);
    set_motion_packed_rotation();
    draw_model_motion((void *)nest_resources->models[0].model, motion, frame);
    clear_motion_packed_rotation();
    pop_matrix();
}

#pragma push
#pragma readonly_strings on
void TObjEneBm3FlyNest::load_resources() {
    TObjEneBm3FlyNest__attachment_sample_origin.x = 0.0f;
    TObjEneBm3FlyNest__attachment_sample_origin.y = 0.0f;
    TObjEneBm3FlyNest__attachment_sample_origin.z = 0.0f;
    attachment_node_index = 0;
    attachment_point_cursor = 0;
    carrier_point_cursor = 0;
    carrier_sample_index = 0;
    if (TObjEneDD::check_v2_mode() != 0) {
        nest_resources = load_enemy_bml_resource_named(&bm3_fly_nest_resource_desc, "bm_ene_bm3_fly_a.bml");
    } else {
        nest_resources = load_enemy_bml_resource(&bm3_fly_nest_resource_desc);
    }
    bm3_flynest_base_stats = get_battle_base_stats(1);
    bm3_flynest_attack_params = get_battle_attack_params(1);
    bm3_flynest_resistance_params = get_battle_resistance_params(1);
    bm3_flynest_movement_params = get_battle_movement_params(1);
    TObjEneBm3Fly::load_resources();
    TObjEneBm3FlyNest::init_vertex_table();
    {
        NpcAnimationBinding anim = bm3_flynest_anim_binding;
        anim.motions = nest_resources->motions;
        BmlModelEntry *models = nest_resources->models;
        NpcModelRegistry::register_animated_chunk(8, (void *)models[1].model,
            (void *)models[0].m_c, &anim, bm3_flynest_collider_params.radius, 0.0f);
    }
}

#pragma pop

void *TObjEneBm3FlyNest::create(void *set_data) {
    return new TObjEneBm3FlyNest(static_cast<TObject *>(tl_04), static_cast<EnemySetRecord *>(set_data));
}

void TObjEneBm3FlyNest::free_fly() {
    TObjEneBm3Fly::release_shared_data();
    if (nest_resources != 0) {
        delete nest_resources;
        nest_resources = 0;
    }
}

BmlResource *TObjEneBm3FlyNest::get_resources() { return nest_resources; }

#pragma push
#pragma opt_loop_invariants off
TObjEneBm3FlyNest::TObjEneBm3FlyNest(TObject *parent, EnemySetRecord *set_data)
    : TObjEneDD(parent) {
    s32 i;
    m_name = bm3_fly_nest_class_name;
    invoke_initialization_hook(set_data);
    init_position_vectors();
    model = (void *)nest_resources->models[1].model;
    texlist = nest_resources->models[0].m_c;
    init_model(&bm3_flynest_collider_params, 1);
    body_center_position.y = (20.0f) + position.y;
    vfunc_88();
    set_action_table(bm3_flynest_hit_action_table);
    set_motion_list(nest_resources->motions);
    requested_action = 0;
    set_animation(requested_action);
    set_field_b8(requested_action);
    reset_hp(bm3_flynest_base_stats, bm3_flynest_attack_params, bm3_flynest_resistance_params);
    check_state_flag_1();
    movementParameters = &bm3_fly_nest_params;
    initialize_enemy_state(4);
    m_37c = (10.0f);
    init_params();
    if (spawn_limit > set_data->flags) {
        spawn_limit = set_data->flags;
    }
    for (i = 0; i < 4; i++) {
        unknown_398[i] = 0;
    }
    damage_phase = 0;
    visible = 0;
    child_count = 0;
    children_spawned = 0;
    next_child_id = entity_id + 1;
    for (i = 0; i < 6; i++) {
        child_ids[i] = 0xFFFF;
    }
    for (i = 0; i < 2; i++) {
        VecCopy(&attachment_points[i], &position);
    }
    attachment_points[1].y += (25.0f);
    for (i = 0; i < 8; i++) {
        VecCopy(&carrier_points[i], &position);
    }
    for (i = 0; i < 4; i++) {
        camera_fades[i].activate_and_dispatch();
    }
    model_height = 0.0f;
    replenish_phase = 0;
    pending_spawns = 0;
    replenish_timer = 0;
    replenish_count = 0;
    replenish_delay = 0;
    state_timer = 0;
    state_counter = 0;
    substate = 0;
    state_angle = 0;
    sink_distance = 0.0f;
    mode = 0;
    dispatch_action(mode, 4);
}
#pragma pop

TObjEneBm3FlyNest::~TObjEneBm3FlyNest() { free_collision_body_parts(this); }

#pragma push
#pragma fp_contract on
void TObjEneBm3FlyNest::run_task() {
    if (check_demo_mode() != 0) {
        init();
        return;
    }
    if (this->vfunc_83() != 4) {
        this->vfunc_85();
    } else if (this->mode == 0) {
        transition_enemy_state(1);
    }
    this->vfunc_88();
    this->copy_pos();
    submit_default_cursor_candidate();
    this->vfunc_100();
}
#pragma pop

void TObjEneBm3FlyNest::dispatch_action(u32 state, s32 reason) {
    switch (state) {
    case 1:
        state_initial_emit(reason);
        return;
    case 0:
        handle_appear(reason);
        return;
    case 2:
        state_wait(reason);
        return;
    case 3:
        handle_event(reason);
        return;
    case 4:
        fn_800B318C(reason);
        return;
    case 5:
        update_state(reason);
        return;
    case 6:
        state_spawn(reason);
        return;
    case 7:
        handle_motion_event(reason);
        return;
    case 8:
        state_dying(reason);
        return;
    case 9:
        handle_state(reason);
    default:
        return;
    }
}

void TObjEneBm3FlyNest::vfunc_28() {  }

void TObjEneBm3FlyNest::vfunc_63() {
    s16 current_mode;

    current_mode = this->mode;
    if ((current_mode != 9) && (current_mode != 8) && (current_mode != 4)) {
        if (damage_phase == 0) {
            transition_enemy_state(4);
            return;
        }
        transition_enemy_state(8);
    }
}

void TObjEneBm3FlyNest::vfunc_62() {
    s16 current_mode;

    if (((s16) this->mode == 3) && (TObjEneDD::check_v2_mode() != 0)) {
        clear_attack_receipts();
        return;
    }
    current_mode = this->mode;
    if (current_mode == 4) {
        clear_attack_receipts();
        return;
    }
    if (current_mode != 7) {
        transition_enemy_state(7);
    }
}

void TObjEneBm3FlyNest::vfunc_61() {  }

void TObjEneBm3FlyNest::copy_pos() { VecCopy(&center, &body_center_position); }

void TObjEneBm3FlyNest::vfunc_88() { set_part_local_pos(&body_center_position, 0); }

void TObjEneBm3FlyNest::update_replenish() {
    s32 count;
    s32 available;
    s32 remaining;
    switch (replenish_phase) {
    case 0:
        if (child_count <= initial_child_count / 2 || damage_phase != 0) {
            replenish_phase = 1;
            replenish_timer = 0;
        }
        return;
    case 1:
        if (replenish_count > 0) {
            replenish_timer++;
            if (replenish_timer > replenish_delay) {
                replenish_timer = 0;
                count = replenish_count;
                available = 6 - child_count;
                if (available < count) {
                    count = available;
                }
                remaining = spawn_limit - children_spawned;
                if (remaining < count) {
                    count = remaining;
                }
                pending_spawns = count;
                return;
            }
        }
        break;
    }
}

s32 TObjEneBm3FlyNest::has_pending_spawns() const {
    return pending_spawns > 0;
}

void TObjEneBm3FlyNest::spawn_child() {
    Vec velocity = child_spawn_velocity;
    Vec spawn_position;
    s32 n;
    if (child_count <= 6) {
        n = (set_index + 1) + children_spawned;
        VecCopy(&spawn_position, get_spawn_point());
        if (TObjEneBm3Fly::create(this, next_child_id, n, &spawn_position, &velocity) != 0) {
            child_ids[child_count++] = next_child_id;
            next_child_id++;
            children_spawned++;
            spawn_particle_effect(&attachment_points[1], 0xC8);
            play_sound_effect(TObjEnemy::remap_sound_for_area(0x4003AB27), &position, 0, 0);
            TObjPlayer::play_effect_if_v2(-0x400);
        }
    }
}

void TObjEneBm3FlyNest::init_params() {
    demo_state = 2;
    initial_child_count = parameters[1];
    if (initial_child_count < 0) {
        initial_child_count = 0;
    } else if (initial_child_count > 6) {
        initial_child_count = 6;
    }
    spawn_limit = parameters[2];
    if (spawn_limit < 0) {
        spawn_limit = 0;
        return;
    }
    if (spawn_limit > 30) {
        spawn_limit = 30;
    }
}

#pragma push
#pragma fp_contract on
void TObjEneBm3FlyNest::handle_appear(s32 reason) {
    s32 *cnt = &state_counter;
    s32 i;

    switch (reason) {
    case 4:
        this->requested_action = 8;
        this->vfunc_95();
        this->set_field_378(2);
        this->model_height = (100.0f);
        this->state_timer = 0;
        this->substate = 0;
        this->state_angle = 0;
        break;
    case 3:
        if (this->substate == 2 && get_flag_b4() != 0) {
            transition_enemy_state(1);
        }
        break;
    case 0:
        this->advance_animation();
        switch (this->substate) {
        case 0:
            this->state_timer += 1;
            if (this->state_timer == 1) {
                *cnt = 0;
                for (i = 0; i < 6; i++) {
                    new TObjEneBm3FlyNest_CarryFly(this, &carrier_points[i],
                        &attachment_points[1], &position, cnt, i + 1);
                }
            }
            this->model_height = this->model_height - (((0.3f) * ((1.0f) + sin_table_lookup(this->state_angle))) + (0.2f));
            this->state_angle += 0x700;
            if (this->model_height < (18.0f) && this->requested_action != 9) {
                this->requested_action = 9;
            }
            if (this->model_height < -5.0f) {
                this->model_height = -5.0f;
                this->substate = 1;
                this->state_timer = 0;
                spawn_particle_effect(&position, 0xF0);
                play_sound_effect(this->remap_sound_for_area(0x4003B72A), &position, 0, 0);
            }
            break;
        case 1:
            this->state_timer += 1;
            if (this->state_timer > 3) {
                this->state_timer = 0;
                *cnt += 1;
                if (*cnt >= 6) {
                    this->substate = 2;
                }
            }
            break;
        }
        this->vfunc_102();
        break;
    case 5:
        *cnt = 6;
        break;
    }
}
#pragma pop

void TObjEneBm3FlyNest::state_initial_emit(s32 reason) {
    switch (reason) {
    case 4:
        this->requested_action = 0;
        this->vfunc_95();
        this->set_field_378(2);
        this->model_height = -5.0f;
        this->state_timer = 0;
        this->state_counter = 0;
        this->substate = 0;
        break;
    case 3:
        this->advance_animation();
        if (this->substate == 3) {
            switch (this->demo_state) {
            case 2:
                transition_enemy_state(this->demo_state);
                break;
            case 5:
                transition_enemy_state(this->demo_state);
                break;
            case 9:
                this->requested_action = 7;
                this->advance_animation();
                this->frame = (2.0f);
                this->advance_animation();
                this->frame = this->frame_count - (1.0f);
                this->actorFlags |= 0x800;
                this->damage_phase = 1;
                transition_enemy_state(this->demo_state);
                break;
            }
        }
        break;
    case 5:
        break;
    case 0:
        this->advance_animation();
        this->state_timer += 1;
        switch (this->substate) {
        case 0:
            if (this->state_timer > 0x3C) {
                this->substate = 2;
                this->requested_action = 1;
            }
            break;
        case 1:
            if (this->is_passing_frame((15.0f)) != 0) {
                this->substate = 2;
            }
            break;
        case 2:
            if (get_flag_b4() != 0) {
                this->requested_action = 0;
            }
            if ((this->state_timer % 10) == 0) {
                if (this->state_counter < *(s32 *)&this->initial_child_count) {
                    this->spawn_child();
                    this->state_counter += 1;
                } else {
                    this->substate = 3;
                }
            }
            break;
        }
        break;
    }
}

void TObjEneBm3FlyNest::state_wait(s32 reason) {
    switch (reason) {
    case 4:
        this->requested_action = 0;
        vfunc_96();
        this->set_field_378(2);
        this->model_height = (f32) -5.0f;
        this->replenish_count = 1;
        this->replenish_delay = 0x96;
        return;
    case 3:
        if (has_pending_spawns() != 0) {
            transition_enemy_state(3);
        }
        break;
    case 5:
        break;
    case 0:
        this->advance_animation();
        this->update_replenish();
        vfunc_102();
        break;
    }
}

void TObjEneBm3FlyNest::handle_event(s32 reason) {
    switch (reason) {
    case 4:
        this->requested_action = 1;
        this->vfunc_96();
        this->set_field_378(2);
        this->model_height = (f32) -5.0f;
        return;
    case 3:
        if (this->motion_flags & 0x10) {
            transition_enemy_state(2);
        }
        break;
    case 5:
        break;
    case 0:
        this->advance_animation();
        if (this->is_passing_frame((15.0f)) != 0) {
            this->spawn_child();
            this->pending_spawns = (s32) (this->pending_spawns - 1);
        }
        this->vfunc_102();
        break;
    }
}

#pragma push
#pragma opt_common_subs off
#pragma fp_contract on
void TObjEneBm3FlyNest::fn_800B318C(s32 reason) {
    Vec effect_position;
    s32 effect_angle;
    switch (reason) {
    case 4:
        this->vfunc_91();
        this->requested_action = 3;
        this->vfunc_96();
        this->set_field_378(5);
        this->model_height = (f32) -5.0f;
        break;
    case 3:
        if (this->motion_flags & 0x10) {
            transition_enemy_state(5);
            break;
        }
        break;
    case 0:
        (this->advance_animation());
        if ((this->is_passing_frame((10.0f)) != 0) || (this->is_passing_frame((28.0f)) != 0)) {
            play_sound_effect(this->remap_sound_for_area(0x4003B72A), &position, 0, 0);
        }
        if (this->is_passing_frame((9.0f)) != 0) {
            spawn_particle_effect((&position), 0xF0);
        } else if (this->is_passing_frame((27.0f)) != 0) {
            effect_angle = this->rotation.yaw - 0x4000;
            VecCopy(&effect_position, &position);
            effect_position.x += (16.0f) * sin_table_lookup(effect_angle);
            effect_position.z += (16.0f) * cos_table_lookup(effect_angle);
            spawn_particle_effect(&effect_position, 0xF0);
        }
        this->model_height += 0.1f;
        if (this->model_height > 0.0f) {
            this->model_height = (f32) 0.0f;
        }
        this->vfunc_102();
        break;
    case 5:
        this->vfunc_92();
        break;
    }
}
#pragma pop

void TObjEneBm3FlyNest::update_state(s32 reason) {
    switch (reason) {
    case 4:
        this->requested_action = 4;
        this->vfunc_96();
        this->set_field_378(5);
        this->model_height = (f32) 0.0f;
        if ((s32) this->damage_phase == 0) {
            this->damage_phase = 1;
            this->replenish_count = 2;
            this->replenish_delay = 0x78;
        }
        break;
    case 5:
        break;
    case 3:
        if (has_pending_spawns() != 0) {
            transition_enemy_state(6);
            return;
        }
        break;
    case 0:
        this->advance_animation();
        this->update_replenish();
        this->vfunc_102();
        break;
    }
}

void TObjEneBm3FlyNest::state_spawn(s32 reason) {
    switch (reason) {
    case 4:
        this->requested_action = 5;
        this->vfunc_96();
        this->set_field_378(5);
        this->model_height = (f32) 0.0f;
        return;
    case 3:
        if (this->motion_flags & 0x10) {
            transition_enemy_state(5);
        }
        break;
    case 5:
    case 1:
        break;
    case 0:
        if (this->is_passing_frame((15.0f)) != 0) {
            this->spawn_child();
            this->pending_spawns = (s32) (this->pending_spawns - 1);
        }
        this->advance_animation();
        this->vfunc_102();
        break;
    }
}

void TObjEneBm3FlyNest::handle_motion_event(s32 reason) {
    switch (reason) {
    case 4:
        this->vfunc_96();
        fn_800BB7D0(this);
        fn_800BB7D4(this, 0xF1);
        play_sound_effect(remap_sound_for_area(0x4003A829), &position, 0, 0);
        if ((s32) this->damage_phase != 0) {
            this->requested_action = 6;
            this->model_height = (f32) 0.0f;
            return;
        }
        this->requested_action = 2;
        this->model_height = (f32) -5.0f;
        return;
    case 3:
        if (get_flag_b4() != 0) {
            if ((s32) this->damage_phase != 0) {
                transition_enemy_state(5);
                return;
            }
            if ((s16) this->hp <= (s32) ((s16) this->hpmax / 2)) {
                transition_enemy_state(4);
                return;
            }
            transition_enemy_state(m_378);
            return;
        }
        break;
    case 0:
        this->advance_animation();
        this->vfunc_102();
        return;
    case 5:
        clear_attack_receipts();
        break;
    }
}

#pragma push
#pragma fp_contract on
void TObjEneBm3FlyNest::state_dying(s32 reason) {
    Vec v;
    Vec p;
    f32 r;
    s32 a;
    switch (reason) {
    case 4:
        this->requested_action = 7;
        this->vfunc_96();
        this->model_height = 0.0f;
        distribute_experience_and_request_drop();
        this->state_timer = 4;
        this->state_counter = 0x14;
        this->substate = 0;
        this->sink_distance = 0.0f;
        break;
    case 3:
        if (this->sink_distance >= (20.0f)) {
            transition_enemy_state(9);
        }
        break;
    case 5:
        break;
    case 0:
        switch (this->substate) {
        case 0:
            this->advance_animation();
            if (get_flag_b4() != 0) {
                this->substate = 1;
                v.x = (-10.0f);
                v.y = 0.0f;
                v.z = (-8.0f);
                rotate_xz_pair_by_angle(&v.x, &v.z, this->rotation.yaw);
                vec3_add_to(&v, &position);
                spawn_dead_spot_scale15(&v, 0x32);
                spawn_dead_spot_e4(&v, 0x46, (10.0f));
            }
            if (this->frame < (25.0f)) {
                this->state_timer += 1;
                if (this->state_timer >= 4) {
                    r = rand_range((5.0f), (10.0f));
                    a = get_random_scaled();
                    VecCopy(&p, &body_center_position);
                    p.x = r * sin_table_lookup(a) + p.x;
                    p.y += (5.0f);
                    p.z = r * cos_table_lookup(a) + p.z;
                    spawn_particle_effect(&p, 0xF1);
                    this->state_timer = 0;
                }
                this->state_counter += 1;
                if (this->state_counter >= 0x14) {
                    play_sound_effect(remap_sound_for_area(0x4003AD2B), &position, 0, 0);
                    this->state_counter = 0;
                }
            }
            this->vfunc_102();
            break;
        case 1:
            this->sink_distance += (0.1f);
            position.y -= (0.1f);
            break;
        }
        break;
    }
}
#pragma pop

void TObjEneBm3FlyNest::handle_state(s32 reason) {
    switch (reason) {
    case 4:
        vfunc_95();
        return;
    case 3:
        if ((s32) this->child_count == 0) {
            send_entity_set_flags();
            queue_destruction();
        }
    case 5:
    case 0:
        return;
    }
}

s32 TObjEneBm3FlyNest::has_free_attack_slot(u16 id) {
    s32 count = 0;
    for (s32 i = 0; i < child_count; i++) {
        TObjEneBm3Fly *child = static_cast<TObjEneBm3Fly *>(find_entity_by_id(child_ids[i]));
        if (child != 0 && id == child->get_active_id()) {
            count++;
        }
    }
    if (TObjEneDD::check_v2_mode()) {
        return count < 4;
    }
    return count < 2;
}

void TObjEneBm3FlyNest::remove_child(TObjCollidable *child) {
    for (s32 i = 0; i < 6; i++) {
        if (find_entity_by_id(child_ids[i]) == child) {
            child_count--;
            child_ids[i] = child_ids[child_count];
            child_ids[child_count] = 0xFFFF;
            return;
        }
    }
}

Vec *TObjEneBm3FlyNest::get_spawn_point() { return &attachment_points[1]; }

s32 TObjEneBm3FlyNest::remap_child_sound(s32 sound_id) {
    return TObjEnemy::remap_sound_for_area(sound_id);
}

void TObjEneBm3FlyNest::init() { init_params(); }

void TObjEneBm3FlyNest::capture_attachment(NJS_OBJECT *) {
    switch (attachment_node_index) {
    case 36: case 45:
        transform_point_to_view(&TObjEneBm3FlyNest__attachment_sample_origin, attachment_point_cursor++);
        break;
    }
    ++attachment_node_index;
}

void TObjEneBm3FlyNest::sample_carrier_attachments(NJS_OBJECT *node) {
    Vec *pos;
    if ((s32) attachment_node_index == (s32) bm3_fly_nest_attachment_sample_table[carrier_sample_index]) {
        pos = carrier_point_cursor;
        carrier_sample_index += 1;
        carrier_point_cursor = pos + 1;
        transform_point_to_view(&TObjEneBm3FlyNest__attachment_sample_origin, pos);
    }
    TObjEneBm3FlyNest::capture_attachment(node);
}

void TObjEneBm3FlyNest::render() {
    RenderFadeState *fade;
    s32 camera;
    s32 detail;
    s32 draw_now;
    f32 factor;
    if (check_demo_mode() != 0) {
        render_with_state_debug();
        return;
    }
    camera = 0;
    if (is_split_screen() != 0) {
        camera = TCameraCtrl::get_camera_mode();
    }
    visible = 0;
    if (mode != 9) {
        if (is_main_phase_15() != 0) {
            detail = classify_actor_view_detail((25.0f) + lbl_805D9E88, (50.0f) + lbl_805D9E84, 120.0f);
        } else if (update_object_view_visibility(500.0f, 120.0f) != 0) {
            detail = 1;
        } else {
            detail = 0;
        }
        if (detail != 0) {
            draw_now = 1;
            visible = 1;
            saved_model_render_flags = model_render_flags;
            saved_chunk_polygon_flags_and_mask = chunk_polygon_flags_and_mask;
            saved_chunk_polygon_flags_or_mask = chunk_polygon_flags_or_mask;
            fade = &camera_fades[camera];
            fade->update();
            if (fade->updateFromCamera(&body_center_position.x) != 0) {
                fade->set_flags_and_apply_damage_color();
                if (defer_render() != 0) {
                    draw_now = 0;
                }
            }
            if (mode != 9) {
                Vec shadow_scale = lbl_8043B310;
                if (mode == 0) {
                    factor = (10.0f) / (model_height - (2.0f));
                    if (factor < (1.0f) && factor > 0.0f) {
                        shadow_scale.x = shadow_scale.z = (5.0f) * factor;
                    }
                }
                TObjEneDD::draw_ground_shadow(&shadow_scale, 1);
            }
            if (draw_now != 0) {
                update_secondary_light();
                set_current_texture_list((GinjaTextureList *)texlist);
                push_matrix();
                attachment_node_index = 0;
                attachment_point_cursor = attachment_points;
                post_translate_matrix(&position.x);
                translate_matrix(0, 0.0f, model_height, 0.0f);
                if (mode == 0) {
                    carrier_sample_index = 0;
                    carrier_point_cursor = carrier_points;
                    set_chunk_model_node_callback(TObjEneBm3FlyNest::sample_carrier_attachments);
                } else {
                    set_chunk_model_node_callback(TObjEneBm3FlyNest::capture_attachment);
                }
                rotate_matrix_y(0, this->rotation.yaw);
                TObjEneDD::clear_global_flag_400();
                TObjPlayer::toggle_particle_effect();
                if (detail == 1) {
                    draw();
                } else {
                    draw_motion_model();
                }
                TParticleCtrl::end_effect_render();
                set_chunk_model_node_callback(0);
                pop_matrix();
            }
            update_primary_light();
            if (fade->updateFromCamera(&body_center_position.x) != 0) {
                fade->clear_flag_and_notify();
            }
            model_render_flags = saved_model_render_flags;
            chunk_polygon_flags_and_mask = saved_chunk_polygon_flags_and_mask;
            chunk_polygon_flags_or_mask = saved_chunk_polygon_flags_or_mask;
        }
    }
    VecCopy(&body_center_position, &attachment_points[0]);
}

#pragma push
#pragma pool_data off
void TObjEneBm3FlyNest::render_with_state_debug() {
    f32 motion_frame;
    AnimationMotion *motion;
    if (get_target_info() != 0) {
        switch (demo_state) {
        default:
        case 2:
            debug_printf_at(pack_debug_text_position(0, 0), normal_state_text);
            break;
        case 9:
            debug_printf_at(pack_debug_text_position(0, 0), dead_state_text);
            break;
        case 5:
            debug_printf_at(pack_debug_text_position(0, 0), fallen_state_text);
            break;
        }
        debug_printf_at(pack_debug_text_position(0, 1), start_count_format, initial_child_count);
        debug_printf_at(pack_debug_text_position(0, 2), total_count_format, spawn_limit);
    }
    switch (demo_state) {
    default:
    case 2:
        motion_frame = 0.0f;
        motion = motion_list[action_table[0].motion].motion;
        break;
    case 9:
        motion = motion_list[action_table[7].motion].motion;
        motion_frame = motion->frameCount - 1;
        break;
    case 5:
        motion = motion_list[action_table[3].motion].motion;
        motion_frame = motion->frameCount - 1;
        break;
    }
    if (update_object_view_visibility(500.0f, 120.0f) != 0) {
        Vec shadow_scale = lbl_8043B31C;
        TObjEneDD::draw_ground_shadow(&shadow_scale, 1);
        set_current_texture_list((GinjaTextureList *)texlist);
        push_matrix();
        post_translate_matrix(&position.x);
        translate_matrix(0, 0.0f, -5.0f, 0.0f);
        rotate_matrix_y(0, this->rotation.yaw);
        TObjEneDD::clear_global_flag_400();
        TObjPlayer::toggle_particle_effect();
        set_motion_packed_rotation();
        draw_model_motion(model, motion, motion_frame);
        clear_motion_packed_rotation();
        TParticleCtrl::end_effect_render();
        pop_matrix();
    }
    push_matrix();
    post_translate_matrix(&position.x);
    rotate_matrix_y(0, this->rotation.yaw);
    translate_matrix(0, parameters[2], parameters[3], parameters[4]);
    draw_chunk_object((void *)debug_chunk_object);
    pop_matrix();
}

#pragma pop
