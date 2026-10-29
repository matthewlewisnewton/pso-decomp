#include "pso/enemy/TObjEneRe7Berura.h"
#include "pso/system/ModelNodePositionCapture.h"
#include "pso/system/GroundEffect.h"
#include "types.h"
#include "pso/TObjControl.h"
#include "pso/system/BmlResource.h"
#include "pso/player/TObjPlayer_800F0810.h"
#include "pso/unk/text_803D96A8.h"
#include "pso/system/vector.h"
#include "pso/system/MatrixStack.h"
#include "pso/enemy/TObjEnemy.h"
#include "pso/object/TObjMotion.h"
#include "pso/enemy/TObjEnePanBARA.h"
#include "pso/enemy/TObjEnePanarms.h"
#include "dolphin/mtx.h"
#include <stddef.h>
#include "pso/TParticleCtrl.h"
#include "pso/unk/text_80087278.h"

struct Matrix34;
#include "pso/misc/RenderFadeState.h"
#include "pso/misc/TLobby.h"
#include "pso/misc/TTecJelin.h"
#include "pso/misc/TTecResta.h"
#include "pso/misc/TTecZarua.h"
#include "pso/object/TObjFish.h"
#include "pso/player/TObjPlayer.h"

typedef char PanBaraActionTimerOffset[offsetof(TObjEnePanBARA, action_timer) == 0x3B4 ? 1 : -1];


struct PanarmsAnimationBinding {
    BmlMotionEntry *motions;
    TObjMotionAction *actions;
    u32 unknown08;
    u32 count_and_flags;

    PanarmsAnimationBinding &operator=(const PanarmsAnimationBinding &other) {
        motions = other.motions;
        actions = other.actions;
        unknown08 = other.unknown08;
        count_and_flags = other.count_and_flags;
        return *this;
    }

};

extern "C" {
s32 angle_diff_s16(s32, s32);
s32 vec3_add_to(void *, void *);
s32 subtract_vector(void *, void *);
extern const f32 lbl_8043CD98[];
extern const f32 lbl_8043CD80[];



struct PanBaraBehaviorParameters {
    f32 value_00;
    f32 attack_power_or_jellen_probability;
    f32 zalure_probability;
    u32 unknown_0c;
    u32 unknown_10;
    u32 unknown_14;
    s32 resta_level;
    s32 jellen_level;
    s32 zalure_level;
};

s32 find_nearest_hittable_enemy__10TObjPlayerFiPvf(void *, void *, f32);
u16 find_nearest_visible_player(void *, Vec *, f32);
s32 is_split_screen();
f32 atan2_float(f32, f32);
s32 get_camera_mode__11TCameraCtrlFv();
u32 csnLookAt(void *, void *);
s32 copy_target_state__14TObjEnePanarmsFPv(void *, s32);
void refresh_lobby_state__10TObjPlayerFv();
f32 horizontal_distance_squared(void *, void *);
s32 angle_difference_abs(s32, s32);
}
void direction_to_rotation_xz(u8 *arg0, s32 *arg1, s32 *arg2);
extern "C" {
s32 approach_angle_limited(s32, s32, s32);
void advance_animation_playback(void *);
void *find_entity_by_id(u16 id);
void free_collision_body_parts(void *);
s32 project_actor_to_ground(TObjCollidable *, Vec *, Vec *);
void submit_cursor_candidate(void *, s32);
u8 * get_player_by_client_id(s32);
void minimap_render_dot(void *, s32, s32, s32);
s32 play_sound_effect(s32, void *, s32, s32);
f32 sin_table_lookup(s32);
f32 cos_table_lookup(s32);
s32 scale_matrix(int, f32, f32, f32);
f32 vector_length(void *);
s32 rotate_matrix_y(int, int);
s32 rotate_matrix_z(int, int);
void rotate_matrix_x(Matrix34 *, s32);
s32 normalize_vector(void *);

extern u8 *TObjEnePanarms__entry_params_resource;
extern u8 __dt__15RenderFadeStateFv[];
extern const Vec panarms_part_offset_table[];
extern const s32 lbl_8043CD58[];
extern const Vec panarms_parent_offset_table[];
extern const s32 lbl_8043CD78[];
extern const DirectAttackPayload lbl_8043CD88[];
extern const DirectAttackPayload lbl_8043CD90[];
extern const s32 lbl_8043CDA0[];
extern const PanarmsAnimationBinding panarms_npc_binding_desc_a;
extern const PanarmsAnimationBinding panarms_npc_binding_desc_b;
extern TObjMotionAction lbl_80495484[];
extern TObjEnePanBARA::ActionPair TObjEnePanarms__state_fn_table[];
extern s32 panarms_turn_delta_table[];
extern s32 panarms_sound_effect_pair[];
extern s32 TObjEnePanarms__sound_ids[];
extern u8 lbl_80495934[];
extern s8 lbl_805D5288;
extern s8 TObjEnePanarms__sound_ids_initialized;
extern f32 panarms_particle_frame_window;
extern u8 panarms_particle_frame_window_initialized;
extern s32 saved_model_render_flags;
extern s32 model_render_flags;
extern TObject *tl_04;

extern const char *lbl_805D2AB8;
extern const s32 lbl_8043CD38[];
CollisionBody *init_collision_body_parts(TObjCollidable *, CollisionBody *, s32);
s32 TObjFish__sub_8001EDB0(BmlResource *, s32);
void reset_photon_effect__12TBoss3VoloptFv(TObjEnemy *);

extern TObjMotionAction lbl_80495524[];
extern const char lbl_8043CD28[] = "TObjEnePanBARA";
extern const s32 lbl_8043CD38[] = {1, 2};
extern const Vec panarms_part_offset_table[] = {
    {14.851f, 0.0f, -5.1765f}, {-14.1604f, 0.0f, -5.2659f}
};
extern const s32 lbl_8043CD58[] = {-26578, 26578};
extern const Vec panarms_parent_offset_table[] = {
    {17.3438f, 0.0f, 5.6544f}, {-17.3438f, 0.0f, 5.6544f}
};
extern const s32 lbl_8043CD78[] = {-10558, 10558};
extern const f32 lbl_8043CD80[] = {100.0f, 80.0f};
extern const DirectAttackPayload lbl_8043CD88[] = {{0, 0.0f}};
extern const DirectAttackPayload lbl_8043CD90[] = {{0, 0.0f}};
extern const f32 lbl_8043CD98[] = {0.6f, 0.3f};
extern const s32 lbl_8043CDA0[] = {0x800, -0x800};
extern const PanarmsAnimationBinding panarms_npc_binding_desc_a = {NULL, lbl_80495484, 1, 10U << 16};
extern const PanarmsAnimationBinding panarms_npc_binding_desc_b = {NULL, lbl_80495524, 1, 10U << 16};
const char *lbl_805D2AB8 = lbl_8043CD28;
s8 lbl_805D5288;
s8 TObjEnePanarms__sound_ids_initialized;
f32 panarms_particle_frame_window;
u8 panarms_particle_frame_window_initialized;

}

extern "C" {
CollisionBody lbl_80495458[] = {
    {{0.0f, 16.5f, 0.0f}, 7.5f, 0.0f, 0, 0x8003, {0.0f, 0.0f, 0.0f}, 0.0f}
};
TObjMotionAction lbl_80495484[] = {
    {1, 0, 24, 0.8f, 0}, {1, 0, 27, 0.7f, 0}, {1, 0, 21, 1.0f, 0},
    {3, 0, 0, 0.8f, 0}, {3, 0, 20, 0.8f, 0}, {3, 0, 10, 1.3f, 0},
    {3, 0, 13, 0.7f, 0}, {3, 0, 16, 0.7f, 0}, {3, 0, 18, 0.7f, 0},
    {3, 0, 6, 0.6f, 0}
};
TObjMotionAction lbl_80495524[] = {
    {1, 0, 25, 0.8f, 0}, {1, 0, 28, 0.7f, 0}, {1, 0, 22, 1.0f, 0},
    {3, 0, 1, 0.8f, 0}, {0, 0, 0, 0.0f, 0}, {3, 0, 11, 1.3f, 0},
    {3, 0, 14, 0.7f, 0}, {3, 0, 17, 0.7f, 0}, {3, 0, 19, 0.7f, 0},
    {3, 0, 7, 0.6f, 0}
};

TObjEnePanBARA::ActionPair TObjEnePanarms__state_fn_table[] = {
    { &TObjEnePanBARA::reset_state, &TObjEnePanBARA::snap_to_parent_position },
    { &TObjEnePanBARA::init_split, &TObjEnePanBARA::handle_split_flag },
    { &TObjEnePanBARA::start_action, &TObjEnePanBARA::fn_800E10D0 },
    { &TObjEnePanBARA::init_state_1, &TObjEnePanBARA::update_move_to_target },
    { &TObjEnePanBARA::init_state_16, &TObjEnePanBARA::fn_800E0D1C },
    { &TObjEnePanBARA::restore_from_linked_object, &TObjEnePanBARA::update_hit_state },
    { &TObjEnePanBARA::fn_800E0B9C, &TObjEnePanBARA::apply_effect_if_flagged },
    { &TObjEnePanBARA::fn_800E0A44, &TObjEnePanBARA::fn_800E0950 },
    { &TObjEnePanBARA::fn_800E0930, &TObjEnePanBARA::fn_800E092C },
    { &TObjEnePanBARA::init_state_2, &TObjEnePanBARA::update_chase_target },
    { &TObjEnePanBARA::init_action, &TObjEnePanBARA::fn_800E055C },
    { &TObjEnePanBARA::init_attack_state2, &TObjEnePanBARA::update_attack },
    { &TObjEnePanBARA::fn_800E0344, &TObjEnePanBARA::fn_800E0214 },
    { &TObjEnePanBARA::start_phase2_timer150, &TObjEnePanBARA::fn_800E0048 },
    { &TObjEnePanBARA::start_phase3_timer12, &TObjEnePanBARA::update_move_timer },
    { &TObjEnePanBARA::init_open_state, &TObjEnePanBARA::fn_800DFE08 },
    { &TObjEnePanBARA::init_attack_state, &TObjEnePanBARA::update_action_timer },
};

ModelNodePositionEntry panbara_draw_callback_entries[] = {
    {3, {0.0f, 0.0f, 0.0f}}, {-1, {0.0f, 0.0f, 0.0f}}
};
TObjMotionAction *panbara_action_tables[] = {lbl_80495484, lbl_80495524};
s32 panarms_turn_delta_table[] = {0x4000, -0x4000};
s32 panarms_sound_effect_pair[2] = {0, 0};
s32 TObjEnePanarms__sound_ids[2] = {0, 0};

#pragma push
TObjEnePanBARA *TObjEnePanarms::create_bara(void *set_data, s32 part) {
    return new TObjEnePanBARA(new TObjControl(tl_04), set_data, part);
}
#pragma pop

#pragma push
TObjEnePanBARA::TObjEnePanBARA(TObject *parent, void *set_data, s32 part) : TObjEnemy(parent) {
    struct SavedState { s32 flags; s16 field_4; s16 field_6; s8 effect_a; s8 effect_a_value; s8 effect_b; s8 effect_b_value; } saved;
    m_name = lbl_805D2AB8;
    add_flags_2e4(2);
    apply_set_data(set_data);
    if (exchange_object_state(&saved, 1)) {
        saved.flags = 0;
        saved.field_6 = 0;
        exchange_object_state(&saved, 0);
    }
    part_index = part;
    texlist = TObjFish__sub_8001EDB0((BmlResource *)TObjEnePanarms__entry_params_resource, lbl_8043CD38[part_index]);
    model = (void *)get_bml_model((BmlResource *)TObjEnePanarms__entry_params_resource, lbl_8043CD38[part_index]);
    VecCopy(&prev_position, VecCopy(&home_position, VecCopy(&center, &position)));
    collision_body = init_collision_body_parts(this, lbl_80495458, 1);
    set_field_d8((s32)panbara_action_tables[part_index]);
    set_field_dc((s32)((BmlResource *)TObjEnePanarms__entry_params_resource)->motions);
    set_animation(0);
    set_field_b8(0);
    VecCopy(body_center(), &position);
    x_speed = y_speed = m_310 = 0.0f;
    target = NULL;
    switch (part_index) {
    case 0:
        bind_enemy_combat_stats((u8 *)TLobby::register_boss(0x32), (u8 *)TLobby::dispatch_shared_handler_b(0x32), (u8 *)TLobby::register_object(0x32));
        break;
    case 1:
        bind_enemy_combat_stats((u8 *)TLobby::register_boss(0x33), (u8 *)TLobby::dispatch_shared_handler_b(0x33), (u8 *)TLobby::register_object(0x33));
        break;
    default:
        return;
    }
    referenceHp = hp;
    reset_photon_effect__12TBoss3VoloptFv(this);
    movementParameters = NULL;
    if (part_index == 0) {
        set_param(0x17);
    } else {
        set_param(0x16);
    }
    draw_callbacks = ModelNodePositionCapture::create(panbara_draw_callback_entries, &draw_callback_position);
    if (draw_callbacks == NULL) {
        return;
    }
    movement_speed = 0.0f;
    m_3c4 = 0;
    if (part_index == 0) {
        m_460 = ((PanBaraBehaviorParameters *)TLobby::dispatch_shared_handler_a(0x32))->value_00;
        attack_power = ((PanBaraBehaviorParameters *)TLobby::dispatch_shared_handler_a(0x32))->attack_power_or_jellen_probability;
    } else {
        m_460 = ((PanBaraBehaviorParameters *)TLobby::dispatch_shared_handler_a(0x33))->value_00;
        jellen_probability = ((PanBaraBehaviorParameters *)TLobby::dispatch_shared_handler_a(0x33))->attack_power_or_jellen_probability;
        if (jellen_probability < 0.0f) {
            jellen_probability = 0.0f;
        } else if (jellen_probability > 1.0f) {
            jellen_probability = 1.0f;
        }
        zalure_probability = ((PanBaraBehaviorParameters *)TLobby::dispatch_shared_handler_a(0x33))->zalure_probability;
        if (zalure_probability < 0.0f) {
            zalure_probability = 0.0f;
        } else if (zalure_probability > 1.0f) {
            zalure_probability = 1.0f;
        }
        if (jellen_probability + zalure_probability > 1.0f) {
            zalure_probability = 1.0f - jellen_probability;
        }
    }
    VecCopy(&effect_position, &position);
    for (s32 i = 0; i < 4; i++) {
        camera_fades[i].activate_and_dispatch();
    }
    previous_state = state = 0;
    set_state(0);
}
#pragma pop

#pragma push
TObjEnePanBARA::~TObjEnePanBARA() {
    free_collision_body_parts(this);
    collision_body = NULL;
    ModelNodePositionCapture::destroy(draw_callbacks);
}
#pragma pop

#pragma push
void TObjEnePanBARA::run_task() {
    Action update;
    Vec a;
    f32 scale;
    if (state != 0 && TObjPlayer::check_demo_mode() != 0) {
        set_state(0);
    }
    other_half_direction.x = other_half->position.x - position.x;
    other_half_direction.y = 0.0f;
    other_half_direction.z = other_half->position.z - position.z;
    other_half_angle = 10430.38043493439 * atan2_float(other_half_direction.x, other_half_direction.z);
    other_half_distance = vector_length(&other_half_direction);
    frame_counter++;
    update = TObjEnePanarms__state_fn_table[state].update;
    if (update == 0) {
        return;
    }
    (this->*update)();
    if (visible != 0) {
        actorFlags &= ~0x02000000;
    } else {
        actorFlags |= 0x02000000;
    }
    update_prev_position();
    if (state == 0) {
        return;
    }
    if (visible != 0) {
        if (state != 7) {
            submit_cursor_candidate(this, -1);
        }
        advance_animation_playback(this);
        switch (state) {
        case 7:
            break;
        case 1:
            scale = m_c0 / 35.0f;
            calc_part_position(&a, NULL);
            subtract_vector(&a, body_center());
            a.x *= scale;
            a.z *= scale;
            vec3_add_to(&a, body_center());
            minimap_render_dot(&a, -0x5DB4, 1, 0);
            break;
        case 5:
            {
                scale = m_c0 / 45.0f;
                Vec b = *body_center();
                subtract_vector(&b, &split_position);
                b.x *= scale;
                b.z *= scale;
                vec3_add_to(&b, &split_position);
                minimap_render_dot(&b, -0x5DB4, 1, 0);
            }
            break;
        default:
            minimap_render_dot(body_center(), -0x5DB4, 1, 0);
            break;
        }
    }
    if (collision_active == 0) {
        collision_body->flags &= ~1;
    }
}
#pragma pop

#pragma push
void TObjEnePanBARA::render() {
    s32 flags;
    s32 camera;
    RenderFadeState *fade;
    s32 draw_now;
    if (update_object_view_visibility(500.0f, 20.0f) == 0 || visible == 0) {
        effect_position.x = effect_position.y = effect_position.z = 0.0f;
        return;
    }
    camera = 0;
    if (is_split_screen() != 0) {
        camera = get_camera_mode__11TCameraCtrlFv();
    }
    TObjPlayer::toggle_particle_effect();
    flags = model_render_flags;
    saved_model_render_flags = flags;
    model_render_flags = flags | 0x01000000 | 1;
    fade = &camera_fades[camera];
    fade->update();
    if (fade->updateFromCamera(&body_center()->x) != 0) {
        fade->set_flags_and_apply_damage_color();
        draw_now = 1;
        if (defer_render() != 0) draw_now = 0;
        if (draw_now != 0) draw();
        fade->clear_flag_and_notify();
    } else {
        draw();
    }
    model_render_flags = saved_model_render_flags;
    TParticleCtrl::end_effect_render();
    update_linked_effect();
}
#pragma pop

#pragma push
void TObjEnePanBARA::draw() {
    push_matrix();
    post_translate_matrix(&position.x);
    rotate_matrix_y(0, rotation_y);
    TObjFish::set_global_param(texlist);
    draw_callbacks->install();
    TObjMotion::draw();
    draw_callbacks->clear();
    pop_matrix();
}
#pragma pop

#pragma push
void TObjEnePanBARA::update_linked_effect() {
    Vec normal;
    s32 spC;
    s32 sp8;
    f32 temp_f1;
    s32 temp_r0;

    VecCopy(&effect_position, &draw_callback_position);
    if (project_actor_to_ground(this, &effect_position, &normal) != 0) {
        push_matrix();
        temp_f1 = this->effect_position.y;
        effect_position.y += 0.2f;
        post_translate_matrix(&effect_position.x);
        direction_to_rotation_xz((u8 *)&normal, &spC, &sp8);
        rotate_matrix_z(0, sp8);
        rotate_matrix_y(0, this->rotation_y);
        rotate_matrix_x(NULL, spC + 0x4000);
        scale_matrix(0, 2.0f, 2.0f, 1.0f);
        temp_r0 = this->state;
        if ((temp_r0 != 7) && (temp_r0 != 8)) {
            draw_blob_shadow(0);
        }
        pop_matrix();
    }
}
#pragma pop

#pragma push
#pragma fp_contract on
void TObjEnePanBARA::vfunc_63() {
    s32 st = this->state;
    switch (st) {
    case 7:
    case 8:
        return;
    default:
        if (st == 0) {
            this->rotation_y = this->combined_body->rotation_y + panarms_turn_delta_table[this->part_index];
            VecCopy(&this->position, &this->combined_body->position);
            position.x += 10.0f * sin_table_lookup(this->rotation_y);
            position.z += 10.0f * cos_table_lookup(this->rotation_y);
            VecCopy(body_center(), &this->position);
        }
        this->set_state(7);
        break;
    }
}
#pragma pop

#pragma push
void TObjEnePanBARA::vfunc_62() {
    switch (state) {
    case 0: case 1: case 5: case 6:
        break;
    default:
        actorFlags &= ~0x200;
        set_state(6);
        break;
    }
}
#pragma pop

#pragma push
void TObjEnePanBARA::vfunc_61() { this->actorFlags &= 0xfffffeff; }
#pragma pop

#pragma push
void TObjEnePanBARA::fn_800E1E14() {
    VecCopy(&position, &combined_body->position);
    rotation_y = combined_body->rotation_y;
    set_state(1);
}
#pragma pop

#pragma push
#pragma inline_depth (1)
#pragma auto_inline off
#pragma dont_inline off
void TObjEnePanBARA::init_state() { update_offset_from_parent(); set_state(3); }
#pragma pop

#pragma push
#pragma inline_depth (1)
#pragma auto_inline off
#pragma dont_inline off
void TObjEnePanBARA::do_action_2() { set_state(2); }
#pragma pop

#pragma push
#pragma inline_depth (1)
#pragma auto_inline off
#pragma dont_inline off
void TObjEnePanBARA::fn_800E1D94() { set_state(5); }
#pragma pop

#pragma push
#pragma inline_depth (1)
#pragma auto_inline off
#pragma dont_inline off
void TObjEnePanBARA::reset_split() { if (state != 0) set_state(0); }
#pragma pop

#pragma push
#pragma inline_depth (1)
#pragma auto_inline off
#pragma dont_inline off
void TObjEnePanBARA::fn_800E1D38() { vfunc_63(); }
#pragma pop

#pragma push
void TObjEnePanBARA::set_state(s32 next_state) {
    Action enter;
    s32 *current = &state;
    if (previous_state != state) {
        previous_state = *current;
    }
    state = next_state;
    if (state < 0 || state >= 17) {
        return;
    }
    enter = TObjEnePanarms__state_fn_table[state].enter;
    if (enter) {
        (this->*enter)();
    }
}
#pragma pop

#pragma push
#pragma inline_depth (1)
#pragma auto_inline off
#pragma dont_inline off
void TObjEnePanBARA::bind_parts(TObjEnePanarms *body, TObjEnePanBARA *half) {
    combined_body = body;
    other_half = half;
}
#pragma pop

#pragma push
#pragma inline_depth (1)
#pragma auto_inline off
#pragma dont_inline off
#pragma fp_contract on
void TObjEnePanBARA::calc_part_position(Vec *arg1, s32 *arg2) {
    f32 x;
    f32 z;
    f32 s;
    f32 c;

    x = panarms_part_offset_table[this->part_index].x;
    z = panarms_part_offset_table[this->part_index].z;
    s = sin_table_lookup(this->combined_body->rotation_y);
    c = cos_table_lookup(this->combined_body->rotation_y);
    VecCopy((Vec *)arg1, &this->combined_body->position);
    arg1->x += x * c + z * s;
    arg1->z += -x * s + z * c;
    if (arg2 != NULL) {
        *arg2 = this->combined_body->rotation_y - lbl_8043CD58[this->part_index];
    }
}
#pragma pop

#pragma push
#pragma inline_depth (1)
#pragma auto_inline off
#pragma dont_inline off
void TObjEnePanBARA::calc_default_part_position() {
    calc_part_position(&position, &rotation_y);
}
#pragma pop

#pragma push
#pragma inline_depth (1)
#pragma auto_inline off
#pragma dont_inline off
#pragma fp_contract on
void TObjEnePanBARA::update_offset_from_parent() {
    f32 x;
    f32 z;
    f32 s;
    f32 c;
    x = panarms_parent_offset_table[this->part_index].x;
    z = panarms_parent_offset_table[this->part_index].z;
    s = sin_table_lookup(combined_body->rotation_y);
    c = cos_table_lookup(combined_body->rotation_y);
    VecCopy(&split_position, &combined_body->position);
    split_position.x += x * c + z * s;
    split_position.z += -x * s + z * c;
    this->m_398 = combined_body->rotation_y;
    this->m_398 += lbl_8043CD78[this->part_index];
}
#pragma pop

#pragma push
#pragma inline_depth (1)
#pragma auto_inline off
#pragma dont_inline off
#pragma fp_contract on
s32 TObjEnePanBARA::try_move_with_detour(Vec *arg1) {
    Vec dir = *arg1;
    Vec t;
    Vec p;
    s32 i;
    s32 ang;
    f32 s;
    f32 c;
    f32 nx;
    dir.y = 0.0f;
    if (0.0f == vector_length(&dir)) {
        return 0;
    }
    VecCopy((Vec *)&t, (const Vec *)(&position));
    vec3_add_to(&t, arg1);
    if (horizontal_distance_squared(&t, &home_position) > 250000.0f) {
        return 0;
    }
    for (i = 1; i < 16; i++) {
        VecCopy((Vec *)&p, (const Vec *)(&position));
        vec3_add_to(&p, &dir);
        p.y += 10.0f;
        if (project_actor_to_ground(this, &p, 0) != 0 && csnLookAt(&position, &p) == 0) {
            VecCopy((Vec *)(&prev_position), (const Vec *)(&position));
            VecCopy((Vec *)(&position), (const Vec *)&p);
            update_collisions();
            return 1;
        }
        ang = i << 12;
        if (i & 1) {
            ang *= -1;
        }
        s = sin_table_lookup(ang);
        c = cos_table_lookup(ang);
        nx = c * dir.x - s * dir.z;
        dir.x = nx;
        dir.z = s * nx + c * dir.z;
    }
    return 0;
}
#pragma pop

#pragma push
#pragma inline_depth (1)
#pragma auto_inline off
#pragma dont_inline off
#pragma fp_contract on
s32 TObjEnePanBARA::fn_800E1774() {
    Vec direction;
    return get_state_flag()
        ? (s32)(!other_half->fn_800E2FB4() &&
            (target_id = find_nearest_enemy_with_flag_alt_target(
                &direction, lbl_8043CD80[part_index])) != 0xFFFF &&
            angle_difference_abs(rotation_y,
                (s32)(10430.38043493439 * atan2_float(direction.x, direction.z))) < 0x400)
        : (s32)(!other_half->fn_800E2FB4() &&
            (target_id = find_nearest_visible_player(
                this, &direction, lbl_8043CD80[part_index])) != 0xFFFF &&
            angle_difference_abs(rotation_y,
                (s32)(10430.38043493439 * atan2_float(direction.x, direction.z))) < 0x400);
}
#pragma pop

#pragma push
#pragma inline_depth (1)
#pragma auto_inline off
#pragma dont_inline off
void TObjEnePanBARA::attack_target_player(s32 arg1) {
    TObjPlayer *t;
    f32 sc;
    s32 lv;
    t = (TObjPlayer *)get_player_by_client_id(arg1);
    if (t != NULL) {
        if (this->part_index == 0) {
            DirectAttackPayload tmp = lbl_8043CD88[0];
            tmp.power = this->attack_power;
            {
                t->receive_direct_attack(this, tmp, NULL, -1, -1);
            }
            return;
        }
        sc = random_ratio();
        if (sc <= jellen_probability) {
            lv = ((PanBaraBehaviorParameters *)TLobby::dispatch_shared_handler_a(0x33))->jellen_level;
            if (lv < 0 || lv > 0xE) {
                lv = 0;
            }
            TTecJelin::create((s32)this, (s32)body_center(), (s32)(t->body_center()), (s32)lv);
            return;
        }
        if (sc <= jellen_probability + this->zalure_probability) {
            lv = ((PanBaraBehaviorParameters *)TLobby::dispatch_shared_handler_a(0x33))->zalure_level;
            if (lv < 0 || lv > 0xE) {
                lv = 0;
            }
            TTecZarua::create_instance((s32)this, (s32)body_center(), (s32)(t->body_center()), (s32)lv);
            return;
        }
        {
            DirectAttackPayload h2 = lbl_8043CD90[0];
            t->receive_direct_attack(this, h2, NULL, -1, -1);
        }
    }
}
#pragma pop

#pragma push
#pragma inline_depth (1)
#pragma auto_inline off
#pragma dont_inline off
void TObjEnePanBARA::spawn_periodic_particle() {
    Vec position;
    if (!(this->frame_counter & 7)) {
        VecCopy((Vec *)(&position.x), (const Vec *)(&effect_position));
        position.y += 5.0f;
        spawn_particle_effect(&position, 0xF3);
    }
}
#pragma pop

#pragma push
#pragma inline_depth (1)
#pragma auto_inline off
#pragma dont_inline off
void TObjEnePanBARA::reset_state() {
    collision_body->flags &= ~1;
    movement_speed = 0.0f;
    visible = 0;
    collision_active = 0;
}
#pragma pop

#pragma push
#pragma opt_common_subs off
#pragma opt_propagation off
void TObjEnePanBARA::snap_to_parent_position() {
    VecCopy((Vec *)(&position), &this->combined_body->position);
    position.x += 1000.0f;
    position.y += 1000.0f;
    VecCopy(body_center(), (const Vec *)(&position));
}
#pragma pop

#pragma push
void TObjEnePanBARA::init_split() {
    CollisionBody *temp_r7;

    temp_r7 = collision_body;
    temp_r7->flags = (s32) (temp_r7->flags & 0xFFFFFFFE);
    visible = 1;
    this->collision_active = 0;
    this->hp = (s16) ((combined_body->hp + 1) / 2);
    this->initial_hp = (s32) this->hp;
    m_3c0 = 0;
    sub_800E2DE4(0x10);
    animationFlags = (s32) (animationFlags | 1);
    set_field_b8(9);
}
#pragma pop

#pragma push
void TObjEnePanBARA::handle_split_flag() {
    if (this->animationFlags & 0x10) {
        this->calc_default_part_position();
        this->set_state(2);
    }
}
#pragma pop

#pragma push
void TObjEnePanBARA::start_action() {
    CollisionBody *temp_r4;

    this->set_random_action_timer(0xF, 0x3C);
    temp_r4 = collision_body;
    temp_r4->flags = (s32) (temp_r4->flags | 1);
    this->collision_active = 1;
    if ((s32) previous_state == 1) {
        animationFlags = (s32) (animationFlags | 1);
    } else {
        animationFlags = (s32) (animationFlags & 0xFFFFFFFE);
    }
    set_field_b8(0);
}
#pragma pop

#pragma push
#pragma fp_contract on
void TObjEnePanBARA::fn_800E10D0() {
    Vec v;
    Vec a;
    f32 scale;
    s32 idx;
    f32 max;
    s32 angle;
    s32 ok;
    s32 t;
    u8 *p;
    TObjChara *e;
    f32 w;

    t = action_timer - 1;
    action_timer = t;
    if (t > 0) {
        return;
    }
    if (action_timer == 0) {
        this->animationFlags &= ~1;
        set_field_b8(1);
    }
    if (part_index == 1 && other_half->is_phase_12() != 0) {
        if (other_half_distance < 27.5f) {
            this->set_state(0xA);
            return;
        }
        this->set_state(0xD);
        return;
    }
    idx = find_nearest_visible_player(this, &v, 500.0f);
    ok = 0;
    if (idx != 0xFFFF) {
        angle = (s32)(10430.38043493439 * atan2_float(v.x, v.z));
        if (angle_difference_abs(this->rotation_y, angle) < 0x208) {
            ok = 1;
        }
    }
    if (ok != 0) {
        this->rotation_y = approach_angle_limited(this->rotation_y, angle, 0x208);
        scale = 75.0f;
        p = get_player_by_client_id(idx);
        if (p != NULL) {
            if (part_index == 1) {
                scale *= -1.0f;
            }
            VecCopy((Vec *)&a, (const Vec *)(p + 0x38));
            a.x += scale * cos_table_lookup(this->rotation_y);
            a.z -= scale * sin_table_lookup(this->rotation_y);
            subtract_vector(&a, &position);
            a.y = 0.0f;
            if (vector_length(&a) <= 0.01f) {
                a.x = a.z = 0.0f;
            } else {
                normalize_vector(&a);
            }
        }
    } else {
        if (part_index == 0) {
            this->rotation_y -= 0x208;
        } else {
            this->rotation_y += 0x208;
        }
        a.x = sin_table_lookup(this->rotation_y);
        a.z = cos_table_lookup(this->rotation_y);
        a.y = 0.0f;
    }
    max = lbl_8043CD98[part_index];
    w = (movement_speed += 0.025f);
    if (w > max) {
        movement_speed = max;
    }
    a.x *= movement_speed;
    a.z *= movement_speed;
    try_move_with_detour(&a);
    if (this->is_below_half_hp() != 0) {
        this->set_state(0xC);
        return;
    }
    if (this->check_can_attack() != 0) {
        this->set_state(0x10);
        return;
    }
    if (this->fn_800E1774() != 0) {
        e = (TObjChara *)find_entity_by_id(target_id);
        if (e != NULL && horizontal_distance_squared(&e->position, &position) < 756.25f) {
            this->set_state(0xA);
            return;
        }
        this->set_state(9);
    }
}
#pragma pop

#pragma push
void TObjEnePanBARA::init_state_1() {
    CollisionBody *temp_r5;
    temp_r5 = collision_body;
    temp_r5->flags = (s32) (temp_r5->flags | 1);
    animationFlags = (s32) (animationFlags & 0xFFFFFFFE);
    set_field_b8(1);
}
#pragma pop

#pragma push
void TObjEnePanBARA::update_move_to_target() {
    Vec sp8;
    f32 dist;
    f32 v;
    if (this->check_can_attack() != 0) {
        this->set_state(0x10);
        return;
    }
    if (other_half->fn_800DFB44() != 0) {
        this->set_state(2);
        return;
    }
    VecCopy((Vec *)&sp8, (const Vec *)&this->split_position.x);
    subtract_vector(&sp8, (u8 *)&this->position);
    sp8.y = 0.0f;
    dist = vector_length(&sp8);
    if (dist <= 0.01f) {
        sp8.x = 1.0f;
        sp8.z = 0.0f;
    } else {
        normalize_vector(&sp8);
    }
    if (collision_body->flags & 0x01C00000) {
        f32 t = sp8.x;
        sp8.x = sp8.z;
        sp8.z = -t;
    }
    this->rotation_y = approach_angle_limited(this->rotation_y, (s32) (10430.38043493439 * atan2_float(sp8.x, sp8.z)), 0x208);
    if (dist > 15.0f) {
        v = (this->movement_speed += 0.025f);
        if (v > 0.6f) {
            this->movement_speed = 0.6f;
        }
    } else {
        this->movement_speed = v = this->movement_speed - 0.025f;
        if (v < 0.3f) {
            this->movement_speed = 0.3f;
        }
    }
    sp8.x *= this->movement_speed;
    sp8.z *= this->movement_speed;
    try_move_with_detour(&sp8);
    if (horizontal_distance_squared((u8 *)&this->split_position.x, (u8 *)&this->position) < 56.25f) {
        this->set_state(4);
    }
}
#pragma pop

#pragma push
void TObjEnePanBARA::init_state_16() {
    CollisionBody *temp_r6;
    temp_r6 = collision_body;
    temp_r6->flags = (s32) (temp_r6->flags | 1);
    this->action_timer = 0x16;
    animationFlags = (s32) (animationFlags & 0xFFFFFFFE);
    set_field_b8(1);
}
#pragma pop

#pragma push
#pragma fp_contract on
void TObjEnePanBARA::fn_800E0D1C() {
    Vec stack;
    f32 temp_f1;
    f32 temp_f2;
    f32 temp_f31;
    s32 temp_r0;
    if (this->check_can_attack() != 0) {
        this->set_state(0x10);
        return;
    }
    if (other_half->fn_800DFB44() != 0) {
        this->set_state(2);
        return;
    }
    temp_r0 = action_timer - 5;
    if (temp_r0 > 0) {
        temp_f31 = 1.0f / (f32) temp_r0;
        VecCopy(&stack, &split_position);
        subtract_vector(&stack.x, &position);
        stack.x *= temp_f31;
        stack.y *= temp_f31;
        stack.z *= temp_f31;
        vec3_add_to(&position, &stack.x);
        this->rotation_y = (s32) ((temp_f31 * (f32) angle_diff_s16((int) (this->rotation_y), (int) (m_398))) + (f32) this->rotation_y);
    } else if (temp_r0 == 0) {
        set_field_b8(0);
    }
    action_timer = (s32) (action_timer - 1);
}
#pragma pop

#pragma push
void TObjEnePanBARA::restore_from_linked_object() {
    CollisionBody *temp_r4;
    temp_r4 = collision_body;
    temp_r4->flags = (s32) (temp_r4->flags & 0xFFFFFFFE);
    VecCopy((Vec *)(&position), &combined_body->position);
    this->rotation_y = combined_body->rotation_y;
    animationFlags = (s32) (animationFlags | 1);
    set_field_b8(8);
}
#pragma pop

#pragma push
void TObjEnePanBARA::update_hit_state() {
    if (other_half->fn_800DFB44() != 0) {
        this->set_state(2);
        return;
    }
    if (this->animationFlags & 0x10) {
        this->set_state(0);
    }
}
#pragma pop

#pragma push
void TObjEnePanBARA::fn_800E0B9C() {
    TObjEnePanBARA *arg0 = this;
    arg0->visible = 1;
    arg0->collision_active = 1;
    if (lbl_805D5288 == 0) {
        panarms_sound_effect_pair[0] = ((s32)copy_target_state__14TObjEnePanarmsFPv(arg0, 0x4003BC34));
        s32 t = ((s32)copy_target_state__14TObjEnePanarmsFPv(arg0, 0x4003BC33));
        lbl_805D5288 = 1;
        panarms_sound_effect_pair[1] = t;
    }
    play_sound_effect(panarms_sound_effect_pair[arg0->part_index], &arg0->position, 0, 0);
    arg0->animationFlags &= 0xFFFFFFFE;
    set_field_b8(5);
}
#pragma pop

#pragma push
void TObjEnePanBARA::apply_effect_if_flagged() {
    if (animationFlags & 0x10) {
        this->set_state((s32)(previous_state));
    }
}
#pragma pop

#pragma push
#pragma fp_contract on
void TObjEnePanBARA::fn_800E0A44() {
    Vec direction;
    s32 animation;
    visible = 1;
    collision_active = 0;
    refresh_lobby_state__10TObjPlayerFv();
    animation = 7;
    animationFlags &= ~1;
    if (find_nearest_visible_player(this, &direction, 500.0f) != 0xFFFF) {
        if (direction.x * sin_table_lookup(rotation_y) + direction.z * cos_table_lookup(rotation_y) < 0.0f) {
            animation = 6;
        }
    }
    set_field_b8(animation);
    if (TObjEnePanarms__sound_ids_initialized == 0) {
        TObjEnePanarms__sound_ids[0] = copy_target_state__14TObjEnePanarmsFPv(this, 0x4003B836);
        TObjEnePanarms__sound_ids[1] = copy_target_state__14TObjEnePanarmsFPv(this, 0x4003BB35);
        TObjEnePanarms__sound_ids_initialized = 1;
    }
    play_sound_effect(TObjEnePanarms__sound_ids[part_index], &position, 0, 0);
    action_timer = 0xA4;
}
#pragma pop

#pragma push
void TObjEnePanBARA::fn_800E0950() {
    u8 *panarms = (u8  *)this;
    Vec stack;
    f32 temp_f1;
    f32 temp_f2;
    s32 temp_r0;
    action_timer = (s32) (action_timer - 1);
    if ((s8) panarms_particle_frame_window_initialized == 0) {
        panarms_particle_frame_window_initialized = 1;
        panarms_particle_frame_window = lbl_80495484[6].speed;
    }
    temp_f2 = m_c0;
    if ((temp_f2 >= 24.0f) && (temp_f2 < (24.0f + panarms_particle_frame_window))) {
        VecCopy((Vec *)(&stack.x), (const Vec *)(&effect_position));
        temp_f1 = stack.y;
        stack.y += 5.0f;
        spawn_particle_effect(&stack, 0xF3);
    }
    temp_r0 = action_timer;
    if (temp_r0 <= 0x78) {
        if (temp_r0 == 0x78) {
            spawn_ground_effect(&effect_position, 0x78);
            TObjPlayer::spawn_dead_spot_default((s32)(&effect_position), 6);
        }
        position.y += -0.15625f;
        if ((s32) action_timer < 0) {
            ((TObjEnePanBARA *)((void *)panarms))->set_state(8);
        }
    }
}
#pragma pop

#pragma push
void TObjEnePanBARA::fn_800E0930() {
    CollisionBody *temp_r5;
    temp_r5 = collision_body;
    temp_r5->flags = (s32) (temp_r5->flags & 0xFFFFFFFE);
    visible = 0;
    collision_active = 0;
}
#pragma pop

#pragma push
void TObjEnePanBARA::fn_800E092C() {  }
#pragma pop

#pragma push
void TObjEnePanBARA::init_state_2() {
    CollisionBody *temp_r7;
    temp_r7 = collision_body;
    temp_r7->flags = (s32) (temp_r7->flags | 1);
    visible = 1;
    this->collision_active = 1;
    this->action_timer = 0x5A;
    animationFlags = (s32) (animationFlags & 0xFFFFFFFE);
    set_field_b8(2);
}
#pragma pop

#pragma push
void TObjEnePanBARA::update_chase_target() {
    Vec sp8;
    f32 v;
    TObjChara *p;

    p = (TObjChara *)find_entity_by_id((u16) target_id);
    if (p == NULL || (p->actorFlags & 0x02000800)) {
        this->set_state(2);
        return;
    }
    (this->action_timer)--;
    VecCopy((Vec *)&sp8, (const Vec *)(&p->position));
    subtract_vector(&sp8, (u8 *)&this->position);
    sp8.y = 0.0f;
    if (vector_length(&sp8) <= 0.01f) {
        sp8.x = 1.0f;
        sp8.z = 0.0f;
    } else {
        normalize_vector(&sp8);
    }
    this->rotation_y = approach_angle_limited(this->rotation_y, (s32) (10430.38043493439 * atan2_float(sp8.x, sp8.z)), 0x101);
    if (this->action_timer > 0) {
        v = (this->movement_speed += 0.075f);
        if (v > 1.25f) {
            this->movement_speed = 1.25f;
        }
    } else {
        this->movement_speed = v = this->movement_speed - 0.075f;
        if (v < 0.0f) {
            this->movement_speed = 0.0f;
        }
    }
    sp8.x *= this->movement_speed;
    sp8.z *= this->movement_speed;
    try_move_with_detour(&sp8);
    if (0.0f == this->movement_speed) {
        this->set_state(0xA);
        return;
    }
    if (horizontal_distance_squared(&p->position, (u8 *)&this->position) < 625.0f) {
        this->set_state(0xB);
        return;
    }
    if (this->is_below_half_hp() != 0) {
        this->set_state(0xC);
        return;
    }
    if (this->check_can_attack() != 0) {
        this->set_state(0x10);
        return;
    }
    spawn_periodic_particle();
}
#pragma pop

#pragma push
void TObjEnePanBARA::init_action() {
    collision_body->flags |= 1;
    this->set_random_action_timer(0xF, 0x1E);
    visible = 1;
    collision_active = 1;
    movement_speed = 0.0f;
    animationFlags = (animationFlags & 0xfffffffe);
    set_field_b8(2);
}
#pragma pop

#pragma push
void TObjEnePanBARA::fn_800E055C() {
    Vec v;
    s32 t;
    f32 sp;

    t = this->action_timer - 1;
    this->action_timer = t;
    if (t > 0) {
        if ((this->movement_speed += -0.075f) < -1.0f) {
            this->movement_speed = -1.0f;
        }
    } else {
        if ((this->movement_speed += 0.025f) >= 0.0f) {
            this->movement_speed = 0.0f;
            this->set_state(2);
            return;
        }
    }
    v.x = this->movement_speed * sin_table_lookup(this->rotation_y);
    v.z = this->movement_speed * cos_table_lookup(this->rotation_y);
    v.y = 0.0f;
    try_move_with_detour(&v);
    if (this->is_below_half_hp() != 0) {
        this->set_state(0xC);
        return;
    }
    if (this->check_can_attack() != 0) {
        this->set_state(0x10);
        return;
    }
    this->spawn_periodic_particle();
}
#pragma pop

#pragma push
void TObjEnePanBARA::init_attack_state2() {
    collision_body->flags |= 1;
    visible = 1;
    this->collision_active = 1;
    this->movement_speed = 0.0f;
    this->action_timer = 12;
    this->animationFlags = (this->animationFlags & 0xfffffffe);
    set_field_b8(3);
}
#pragma pop

#pragma push
void TObjEnePanBARA::update_attack() {
    u8 *arg0 = (u8 *)this;
    f32 temp_f3;
    s32 temp_r0;
    TObjChara *entity;

    entity = (TObjChara *)find_entity_by_id((u16) target_id);
    if ((entity == NULL) || (entity->actorFlags & 0x02000800)) {
        this->set_state(2);
        return;
    }
    temp_r0 = this->action_timer - 1;
    this->action_timer = temp_r0;
    if (temp_r0 == 0) {
        this->attack_target_player(target_id);
        play_sound_effect(copy_target_state__14TObjEnePanarmsFPv(arg0, 0x4003B72F), (u8 *)&this->position, 0, 0);
    }
    if (this->m_c0 < 5.0f) {
        temp_f3 = entity->position.x;
        this->rotation_y = approach_angle_limited(this->rotation_y, lbl_8043CDA0[this->part_index] + (s32) (10430.38043493439 * atan2_float(temp_f3 - this->position.x, entity->position.z - this->position.z)), 0x200);
    }
    if (animationFlags & 0x10) {
        this->set_state(0xA);
    }
}
#pragma pop

#pragma push
void TObjEnePanBARA::fn_800E0344() {
    u8 *ene_panarms = (u8  *)this;
    CollisionBody *temp_r7;
    if ((s32) this->part_index != 1) {
        temp_r7 = collision_body;
        temp_r7->flags = (s32) (temp_r7->flags | 1);
        visible = 1;
        this->collision_active = 1;
        this->movement_speed = (f32) 0.0f;
        this->action_timer = 0x96;
        m_3c0 = 1;
        play_sound_effect((s32)((void *) (((s32)copy_target_state__14TObjEnePanarmsFPv(ene_panarms, 0x4003BC2D)))), &position, 0, 0);
        this->animationFlags = (s32) (this->animationFlags & 0xFFFFFFFE);
        set_field_b8(2);
    }
}
#pragma pop

#pragma push
#pragma fp_contract on
void TObjEnePanBARA::fn_800E0214() {
    u8 *ene_panarms = (u8  *)this;
    s32 temp_r0;

    if (other_half->fn_800E2E68() != 0) {
        this->set_state(0xF);
        return;
    }
    if (this->check_can_attack() != 0) {
        this->set_state(0x10);
        return;
    }
    temp_r0 = this->action_timer - 1;
    this->action_timer = temp_r0;
    if (((temp_r0 < 0) && (other_half->fn_800E2E54() == 0)) || (other_half->fn_800DFB44() != 0)) {
        this->set_state(2);
        return;
    }
    this->rotation_y = approach_angle_limited((int) (this->rotation_y), (int) ((s32) ((6144.0f * sin_table_lookup((int) (this->action_timer << 0xC))) + (f32) this->other_half_angle)), 0x1111);
    if (!(this->action_timer & 0x3F)) {
        play_sound_effect(copy_target_state__14TObjEnePanarmsFPv(ene_panarms, 0x4003BC2D), &position, 0, 0);
    }
    this->spawn_periodic_particle();
}
#pragma pop

#pragma push
void TObjEnePanBARA::start_phase2_timer150() {
    CollisionBody *temp_r7;
    if ((s32) this->part_index != 0) {
        temp_r7 = collision_body;
        temp_r7->flags = (s32) (temp_r7->flags | 1);
        visible = 1;
        this->collision_active = 1;
        this->movement_speed = (f32) 0.0f;
        this->action_timer = 0x96;
        animationFlags = (s32) (animationFlags & 0xFFFFFFFE);
        set_field_b8(2);
    }
}
#pragma pop

#pragma push
void TObjEnePanBARA::fn_800E0048() {
    Vec v;
    if (this->check_can_attack() != 0) {
        this->set_state(0x10);
        return;
    }
    if (--this->action_timer < 0 || other_half->is_phase_12() == 0) {
        this->set_state(2);
        return;
    }
    VecCopy((Vec *)&v, (const Vec *)(&other_half_direction));
    if (vector_length(&v) <= 0.01f) {
        v.x = 1.0f;
        v.z = 0.0f;
    } else {
        normalize_vector(&v);
    }
    this->rotation_y = approach_angle_limited(this->rotation_y, (s32)(10430.38043493439 * atan2_float(v.x, v.z)), 0x888);
    if (this->action_timer < 0x87) {
        f32 t = (this->movement_speed += 0.075f);
        if (t > 1.25f) {
            this->movement_speed = 1.25f;
        }
        v.x *= this->movement_speed;
        v.z *= this->movement_speed;
        try_move_with_detour(&v);
    }
    if (other_half_distance < 25.0f) {
        this->set_state(0xE);
        return;
    }
    this->spawn_periodic_particle();
}
#pragma pop

#pragma push
void TObjEnePanBARA::start_phase3_timer12() {
    CollisionBody *temp_r7;
    if ((s32) this->part_index != 0) {
        temp_r7 = collision_body;
        temp_r7->flags = (s32) (temp_r7->flags | 1);
        visible = 1;
        this->collision_active = 1;
        this->movement_speed = (f32) 0.0f;
        this->action_timer = 0xC;
        animationFlags = (s32) (animationFlags & 0xFFFFFFFE);
        set_field_b8(3);
    }
}
#pragma pop

#pragma push
void TObjEnePanBARA::update_move_timer() {
    u8 *arg0 = (u8 *)this;
    s32 temp_r0;

    if ((other_half->fn_800DFB44() != 0) || (animationFlags & 0x10)) {
        this->set_state(0xA);
        return;
    }
    temp_r0 = this->action_timer - 1;
    this->action_timer = temp_r0;
    if (temp_r0 == 0) {
        play_sound_effect(copy_target_state__14TObjEnePanarmsFPv(arg0, 0x4003B72F), (u8 *)&this->position, 0, 0);
    }
    this->rotation_y = approach_angle_limited(this->rotation_y, this->other_half_angle - 0x800, 0x200);
}
#pragma pop

#pragma push
void TObjEnePanBARA::init_open_state() {
    CollisionBody *temp_r7;
    if ((s32) this->part_index != 1) {
        temp_r7 = collision_body;
        temp_r7->flags = (s32) (temp_r7->flags | 1);
        visible = 1;
        this->collision_active = 1;
        this->movement_speed = (f32) 0.0f;
        this->action_timer = 6;
        animationFlags = (s32) (animationFlags & 0xFFFFFFFE);
        set_field_b8(0);
    }
}
#pragma pop

#pragma push
void TObjEnePanBARA::fn_800DFE08() {
    u8 *arg0 = (u8  *)this;
    s32 temp_r0;
    s32 var_r5;
    temp_r0 = action_timer - 1;
    action_timer = temp_r0;
    if (temp_r0 == 0) {
        set_field_b8(4);
    }
    if (-15.0f == (f32) action_timer) {
        var_r5 = ((PanBaraBehaviorParameters *)TLobby::dispatch_shared_handler_a(0x33))->resta_level;
        if ((var_r5 < 0) || (var_r5 > 0xE)) {
            var_r5 = 0;
        }
        TTecResta::create((void *)arg0, &position, (void *)var_r5);
        play_sound_effect(copy_target_state__14TObjEnePanarmsFPv(this, 0x4003BC31), &position, 0, 0);
    }
    if (animationFlags & 0x10) {
        this->set_state(2);
    }
}
#pragma pop

#pragma push
void TObjEnePanBARA::init_attack_state() {
    CollisionBody *temp_r5;

    temp_r5 = collision_body;
    temp_r5->flags = (s32) (temp_r5->flags | 1);
    visible = 1;
    this->collision_active = 1;
    this->movement_speed = (f32) 0.0f;
    this->action_timer = 0x3C;
    this->m_3c4 = 1;
    if (angle_difference_abs(rotation_y, other_half_angle) < 0x2000) {
        if (angle_diff_s16(this->rotation_y, this->other_half_angle) >= 0) {
            this->rotation_y = (this->other_half_angle - 0x2000);
        } else {
            this->rotation_y = (this->other_half_angle + 0x2000);
        }
    }
    animationFlags = (s32) (animationFlags & 0xFFFFFFFE);
    set_field_b8(2);
}
#pragma pop

#pragma push
void TObjEnePanBARA::update_action_timer() {
    s32 temp_r0;
    s32 temp_r3;

    temp_r0 = this->action_timer - 1;
    this->action_timer = temp_r0;
    if (temp_r0 < 0) {
        this->set_state(2);
        return;
    }
    temp_r3 = this->rotation_y;
    this->rotation_y = approach_angle_limited(this->rotation_y, this->other_half_angle, 0x888);
    if (angle_difference_abs(temp_r3, this->rotation_y) == 0) {
        set_field_b8(0);
    }
}
#pragma pop

#pragma push
void TObjEnePanarms::spawn_npc_pair() {
    const PanarmsAnimationBinding *source_a = &panarms_npc_binding_desc_a;
    const PanarmsAnimationBinding *source_b = &panarms_npc_binding_desc_b;
    PanarmsAnimationBinding a;
    a = *source_a;
    BmlResource *resource = (BmlResource *)TObjEnePanarms__entry_params_resource;
    BmlMotionEntry *motions = resource->motions;
    a.motions = motions;
    PanarmsAnimationBinding b;
    b = *source_b;
    b.motions = motions;
    TLobby::spawn_npc_enemy(0x24, resource->models[1].model, resource->models[1].m_c, (s32)&a, 7.5f, 0.0f);
    BmlModelEntry *models = ((BmlResource *)TObjEnePanarms__entry_params_resource)->models;
    TLobby::spawn_npc_enemy(0x25, models[2].model, models[2].m_c, (s32)&b, 7.5f, 0.0f);
}
#pragma pop

#pragma push
int TObjEnePanarms::find_nearest_enemy_with_flag(s32 arg1, f32 farg0) {
    u8 *arg0 = (u8 *)this;
    u16 temp_r3;
    this->actorFlags = (s32) (this->actorFlags | 0x02000000);
    temp_r3 = find_nearest_hittable_enemy__10TObjPlayerFiPvf((void *)arg0, (void *)arg1, (f32)farg0);
    this->actorFlags = (s32) (this->actorFlags & 0xFDFFFFFF);
    return temp_r3;
}
#pragma pop

// These source-private definitions share this translation unit and its constant pool.
// Debug source-file sections place them after the compiler-generated initializer.
// This matching organization does not establish the original filenames or flags.
#include "pso/enemy/panarms/ModelNodePositionCaptureMethods.h"
#include "pso/enemy/panarms/TObjEnePanBARAMethods.h"
#include "pso/enemy/panarms/TObjMotionMethods.h"
}
