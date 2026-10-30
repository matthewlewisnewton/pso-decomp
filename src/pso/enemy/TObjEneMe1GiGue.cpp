#define TOBJECT_OUT_OF_LINE_HELPERS
#include "pso/system/BmlResource.h"
#include "pso/system/BmlResourceDescriptor.h"
#include "pso/misc/TBreakUpMdl.h"
#include "pso/TObjControl.h"
#include "pso/player/PlayerAttackParams.h"
#include "pso/player/TObjPlayer_803E4954.h"
#include <dolphin/mtx.h>
#include "pso/player/TObjPlayer.h"
#include "pso/player/TObjPlayer_801542CC.h"
#include "pso/player/TObjChara.h"
#include "pso/enemy/TObjEnemyCustom.h"
#include "pso/enemy/TObjEnemy.h"
#include "pso/object/TObjMotion.h"
#include "pso/enemy/TObjEneMe1GiGue.h"
#include "pso/enemy/TUnk_804E14E8.h"
#include "pso/map/FloorArea.h"
#include "pso/map/CsnQuery.h"
#include "pso/system/SoundEffect.h"
#include "pso/system/vector.h"
#include "pso/boss/TBoss3Volopt.h"
#include "pso/boss/TBoss4Type2.h"
#include "pso/enemy/TObjEneMe1GiGueBarrier.h"
#include "pso/enemy/TObjEneMe1GiGueMissile.h"
#include "pso/misc/TCameraCtrl.h"
#include "pso/misc/MaterialOpacityFade.h"
#include <stddef.h>
#include "pso/npc/NpcAnimationBinding.h"
#include "pso/npc/NpcModelRegistry.h"
#include "types.h"
#include "pso/system/NinjaUtil.h"
#include "pso/TParticleCtrl.h"
#include "pso/misc/RenderFadeState.h"
#include "pso/misc/TLobby.h"
#include "pso/object/TObjFish.h"



extern "C" {




extern const char lbl_80472118[];
extern const char lbl_80472128[];
extern const char lbl_8047213C[];
extern const char lbl_80472150[];
extern const char lbl_80472168[];
extern const char lbl_8047217C[];
extern const char lbl_80472194[];
extern const char lbl_804721A8[];
extern const char lbl_804721BC[];
extern const char lbl_804721D4[];
extern const char lbl_804721E8[];
extern const char lbl_804721FC[];
extern const char lbl_80472214[];
extern const char lbl_80472228[];
extern const char lbl_8047223C[];

const char *gigue_model_filenames[4] = {
    lbl_80472118, lbl_80472128, lbl_8047213C, NULL,
};
const char *gigue_motion_filenames[10] = {
    lbl_80472150, lbl_80472168, lbl_8047217C, lbl_80472194,
    lbl_804721A8, lbl_804721BC, lbl_804721D4, lbl_804721E8,
    lbl_804721FC, NULL,
};
BmlResourceDescriptor gigue_resource_descriptor = {
    lbl_80472214, gigue_model_filenames, gigue_motion_filenames, 3, 9,
};
const char *gigue_split_screen_model_filenames[4] = {
    lbl_80472228, lbl_80472128, lbl_8047213C, NULL,
};
const char *gigue_split_screen_motion_filenames[10] = {
    lbl_80472150, lbl_80472168, lbl_8047217C, lbl_80472194,
    lbl_804721A8, lbl_804721BC, lbl_804721D4, lbl_804721E8,
    lbl_804721FC, NULL,
};
BmlResourceDescriptor gigue_split_screen_resource_descriptor = {
    lbl_8047223C, gigue_split_screen_model_filenames, gigue_split_screen_motion_filenames, 3, 9,
};
TObjMotionAction gigue_motion_actions[9] = {
    {2, 0, 4, 0.7f, 0},
    {1, 1, 3, 0.7f, 1},
    {2, 0, 2, 0.6f, 4},
    {2, 7, 1, 0.6f, 4},
    {2, 0, 0, 0.5f, 8},
    {2, 7, 0, 0.5f, 8},
    {2, 7, 3, 0.7f, 1},
    {1, 7, 3, 0.7f, 1},
    {2, 0, 3, 0.7f, 1},
};
struct GiGueMovementParameters {
    f32 target_range;
    f32 speed;
    s32 turn_speed;
    s32 unknown[4];
};
GiGueMovementParameters gigue_movement_parameters = {
    150.0f, 0.46296295523643494f, 0x300, {0x1E0000, 0, 1, 0},
};
CollisionBody gigue_collision_bodies[2] = {
    {{0.0f, 15.0f, 0.0f}, 15.0f, 0.0f, 0, 0x8001, {0.0f, 0.0f, 0.0f}, 0.0f},
    {{0.0f, 15.0f, 0.0f}, 12.0f, 0.0f, 0, 0xA000002, {0.0f, 0.0f, 0.0f}, 0.0f},
};
struct GiGueParameters {
    f32 floats[6];
    s32 integers[5];
};

}


extern "C" {
}

extern f32 lbl_805D6840;
extern f32 lbl_805D6844;
extern f32 lbl_805D6848;
extern f32 lbl_805D684C;
extern s32 lbl_805D6850;
extern s32 lbl_805D6854;
extern "C" {
s32 push_matrix_from(void *src);
s32 pop_matrix(void);
s32 rotate_matrix_y(int, int);
void translate_matrix(u32 arg0, f32 x, f32 y, f32 z);

extern Mtx34 identity_matrix;
f64 atan2_float(f32, f32);
void vec3_add_to(void *, void *);
void matrix_mult_vec(int, Vec *, void *);
extern Vec lbl_80472280;
extern Vec lbl_8047228C;
extern const f64 TObjEneMe1GiGue__data_80472298;
s16 get_entity_id(void *);
s32 angle_difference_abs(s32, s32);
void subtract_vector(void *, void *);

    extern BmlResource *TObjEneMe1GiGue__data_805D6838;

}

extern "C" {
s32 apply_actor_gravity(void *, int, f32);
void calc_velocity_toward_destination(TObjEnemy *, Vec, Vec, f32);
void *spawn_particle_effect(void *pos, s32 id);
s32 play_persistent_sound(s32 id, s32 a1, u32 src, s32 a3, s32 flags);
s32 play_area_sound_effect__12TBoss3VoloptFv(void *, s32);
}

extern "C" {
extern TUnk_8048FA00 *TObjEneMe1GiGue__barrier_obj;
}
void move_with_wall_slide(u8 *arg0);
extern "C" {
void enemy_set_heading_velocity(f32 speed, TObjEnemy *enemy, s32 heading);
s32 create__9TTecJelinFllll(void *, void *, void *, s32);
s32 create_instance__9TTecZaruaFllll(void *, void *, void *, s32);
s32 enemy_turn_toward_dest(void *, s32);
f32 sin_table_lookup(s32);
f32 cos_table_lookup(s32);
u16 find_nearest_visible_player(void *, int, f32);
s32 check_path_obstructed(void *, Vec *);
u32 get_player_by_client_id(s32);

}

extern "C" {

s32 TObjPlayer__sub_800DC478(u8 *arg0, s32 arg1, f32 farg0);

}

extern "C" {

s32 enemy_turn_half_toward_dest(void *);
extern Vec lbl_80472274[];

s32 is_split_screen();
s32 init_from_model__11TBreakUpMdlFl(s32, s32);
s32 find_active_entity_by_id(int);
s32 submit_cursor_candidate(void *, int);
s32 minimap_render_dot(void *, int, int, int);
void TObjEneMe1GiGue__sub_802CE4E8(void);
void TObjEneMe1GiGue__sub_802CE4EC();
void TObjEneMe1GiGueBarrier__sub_80325CC0(void);

extern GiGueParameters *TObjEneMe1GiGue__param_table;
extern NpcAnimationBinding gigue_spawn_descriptor;
extern s32 ene_me1_gigue_boss_id;
extern s32 lbl_805D682C;
extern s32 lbl_805D6830;
extern TObject *tl_04;

}

extern "C" {

void restore_scene_lighting(void);
void select_actor_lighting(s32 obj);
void push_matrix(void);
void draw_chunk_object(void *child);
extern s32 saved_model_render_flags;
extern s32 model_render_flags;

}

extern "C" {
s32 obj_setFlags30(void *, int);
}
int initialize_enemy_photon_effect(void *p);
extern "C" {
extern const char *lbl_805D3F18;

}

#pragma fp_contract on
void TObjEneMe1GiGue::load_params_from_table(s32 i) {
    model = (void *)TObjEneMe1GiGue__data_805D6838->models[i].model;
    texlist = TObjEneMe1GiGue__data_805D6838->models[i].m_c;
}

void TObjEneMe1GiGue::fn_802CDAE8() {  }

f32 TObjEneMe1GiGue::get_float_parameter(s32 arg1) {
    return TObjEneMe1GiGue__param_table->floats[arg1];
}

s32 TObjEneMe1GiGue::get_int_parameter(s32 i) {
    return TObjEneMe1GiGue__param_table->integers[i];
}

void TObjEneMe1GiGue::vfunc_61() {  }

void TObjEneMe1GiGue::vfunc_59() {  }

void TObjEneMe1GiGue::vfunc_60() {  }

void TObjEneMe1GiGue::vfunc_58() {  }

TObjEneMe1GiGue::TObjEneMe1GiGue(TObject *parent, void *set_data)
    : TObjEnemyCustom(parent) {
    u8 *arg2 = (u8 *)set_data;
    this->m_name = lbl_805D3F18;
    this->apply_set_data(arg2);
    VecCopy((Vec *)&m_290, VecCopy((Vec *)&m_29c, &position));
    this->motion_list = TObjEneMe1GiGue__data_805D6838->motions;
    this->variant = 0;
    this->add_flags_2e4(0x11);
    this->state36C = *(s16 *)((s8 *)arg2 + 0x3E);
    this->load_params_from_table(this->variant);
    this->action_table = gigue_motion_actions;
    this->set_field_d8((s32)(this->action_table));
    init_collision_body_parts(this, gigue_collision_bodies, 2);
    bodies[1].flags &= ~1;
    this->movementParameters = &gigue_movement_parameters;
    this->bind_enemy_combat_stats((u8 *)ene_me1_gigue_boss_id, (u8 *)lbl_805D682C, (u8 *)lbl_805D6830);
    this->update_direction();
    load_params();
    this->requested_action = 0;
    this->set_animation(this->requested_action);
    this->set_field_b8(this->requested_action);
    this->hp = this->hpmax;
    this->tp = this->tpmax;
    this->referenceHp = this->hp;
    this->update_prev_position();
    initialize_enemy_photon_effect(this);
    this->m_38c = 0;
    this->scale.x = 1.0f;
    this->movement_speed = ((GiGueMovementParameters *)movementParameters)->speed * this->scale.x;
    VecCopy(&home_position, &position);
    VecCopy(&move_destination, &position);
    this->barrier_probability = 0.5f + this->parameters[3];
    this->technique_probability = 0.5f + this->parameters[4];
    this->initial_height = 150.0f + this->parameters[2];
    if (this->initial_height < 0.0f) {
        this->initial_height = 0.0f;
    }
    if ((s32) this->parameters[0] >= 1) {
        this->m_388 |= 0x40000;
        if (this->parameters[1] < 1.0f) {
            this->parameters[1] = 50.0f;
        }
        this->set_flags_30();
    }
    this->shake_timer = 0;
    this->attack_count = 0;
    this->set_param(0x37);
    this->model_y_offset = 0.0f;
    this->volley_count = 0;
    if (this->m_388 & 0x40000) {
        this->init_move();
    } else {
        this->sub_800C7860();
    }
    project_actor_to_ground(this, &position, 0);
    this->flight_height = 0.0f;
    camera_fade.activate_and_dispatch();
    obj_setFlags30(this, 0x01000000);
    VecCopy(&prev_position, &position);
    this->clear_lobby_object_state();
}

TObjEneMe1GiGue::~TObjEneMe1GiGue() {
    free_collision_body_parts(this);
}

#pragma push
#pragma dont_inline off
#pragma inline_depth(4)
void TObjEneMe1GiGue::load_resources() {
    s32 o;
    CollisionBody *body;

    if (is_split_screen() != 0) {
        TObjEneMe1GiGue__data_805D6838 = new BmlResource(1, &gigue_split_screen_resource_descriptor, 0, 0, NULL);
    } else {
        TObjEneMe1GiGue__data_805D6838 = new BmlResource(1, &gigue_resource_descriptor, 0, 0, NULL);
    }
    ene_me1_gigue_boss_id = (s32)TLobby::register_boss(0x1A);
    lbl_805D682C = (s32)TLobby::dispatch_shared_handler_b(0x1A);
    lbl_805D6830 = (s32)TLobby::register_object(0x1A);
    TObjEneMe1GiGue__param_table = (GiGueParameters *)TLobby::dispatch_shared_handler_a(0x1A);
    o = (int)::operator new(0x10);
    if (o != 0) {
        o = init_from_model__11TBreakUpMdlFl(o, TObjEneMe1GiGue__data_805D6838->models[0].model);
    }
    TObjEneMe1GiGue__barrier_obj = (TUnk_8048FA00 *)o;
    TObjEneMe1GiGue__sub_802CE4EC();
    TObjEneMe1GiGueBarrier::init_global();
    body = gigue_collision_bodies;
    {
    NpcAnimationBinding sp = gigue_spawn_descriptor;
    sp.motions = TObjEneMe1GiGue__data_805D6838->motions;
    NpcModelRegistry::register_animated_chunk((s16)0x41, (void *)(TObjEneMe1GiGue__data_805D6838->models[0].model), (void *)(TObjEneMe1GiGue__data_805D6838->models[0].m_c), &sp, (f32)(body->radius), (f32)15.0f);
    }
}
#pragma pop

void TObjEneMe1GiGue::delete_barrier() {
    TObjEneMe1GiGueBarrier__sub_80325CC0();
    TObjEneMe1GiGue__sub_802CE4E8();
    if (TObjEneMe1GiGue__barrier_obj != NULL) {
        delete TObjEneMe1GiGue__barrier_obj;
        TObjEneMe1GiGue__barrier_obj = NULL;
    }
    if (TObjEneMe1GiGue__data_805D6838 != NULL) {
        delete TObjEneMe1GiGue__data_805D6838;
        TObjEneMe1GiGue__data_805D6838 = NULL;
    }
}

void *TObjEneMe1GiGue::create(void *set_data) {
    TObjControl *control = new TObjControl(tl_04);
    return new TObjEneMe1GiGue(control, set_data);
}

void TObjEneMe1GiGue::run_task() {
    s32 shake_countdown;

    if (TObjPlayer::check_demo_mode() == 1) {
        load_params();
        fn_802CD054();
        return;
    }
    target = (u8 *)find_active_entity_by_id(targetId);
    this->release_destroyed_target();
    select_next_action();
    if ((s16) this->mode != (s32) this->next_action) {
        if ((s32) this->state != -1) {
            this->state = -1;
            this->dispatch_state();
        }
        this->mode = (s16) this->next_action;
        this->state = 0;
    }
    this->dispatch_state();
    if ((s32) this->state == -1) {
        this->state = -1;
        this->dispatch_state();
        this->mode = (s16) this->next_action;
        this->state = 0;
    }
    VecCopy(&body_center_position, &position);
    this->body_center_position.y = (f32) (this->body_center_position.y + (15.0f + this->flight_height));
    bodies[0].offset.y = (f32) (25.0f + this->flight_height);
    if (!(this->m_388 & 0x40000)) {
        submit_cursor_candidate(this, -1);
        minimap_render_dot(&position, -0x5DB4, 1, 0);
    }
    shake_countdown = shake_timer;
    if (shake_countdown > 0) {
        shake_timer = shake_countdown - 1;
    }
    bodies[0].flags &= ~6;
    if (flight_height > 5.0f) {
        bodies[0].flags |= 4;
    } else {
        bodies[0].flags |= 2;
    }
    camera_fade.update();
    if (xz_distance_squared(&position, &this->prev_position) > 2500.0f) {
        VecCopy(&position, &prev_position);
    }
    VecCopy(&prev_position, &position);
}

void TObjEneMe1GiGue::dispatch_state() {
    switch (mode) {
      case 0:
        update_idle();
        return;
      case 1:
        this->update_search();
        return;
      case 2:
        fn_802CDAE8();
        return;
      case 3:
        this->update_state_machine();
        return;
      case 4:
        this->update_hit_reaction();
        return;
      case 5:
        this->break_apart();
        return;
      case 9:
        this->update_needle_attack();
        return;
      case 10:
        this->update_missile_attack();
        return;
      case 11:
        this->update_techniques();
        return;
      case 12:
        this->update_barrier();
        return;
      case 13:
        this->update_rush_attack();
        return;
      case 7:
        this->update_spawn();
        return;
      case 14:
        this->update_landing();
        break;
    }
}

void TObjEneMe1GiGue::render() {
    s32 vis;
    s32 ok;

    if (this->actorFlags & 0x2000000) {
        return;
    }
    if (get_current_floor_area() == AREA_TOWER) {
        vis = this->classify_actor_view_detail(600.0f, 600.0f, 20.0f);
    } else {
        vis = this->classify_actor_view_detail(150.0f, 400.0f, 20.0f);
    }
    if (vis == 0) {
        return;
    }
    if (TObjPlayer::check_demo_mode() != 1 && (this->m_388 & 0x40000)) {
        return;
    }
    saved_model_render_flags = model_render_flags;
    if (camera_fade.updateFromCamera(&body_center_position.x) != 0) {
        this->camera_fade.set_flags_and_apply_damage_color();
        if (defer_render() != 0) {
            model_render_flags = saved_model_render_flags;
            return;
        }
    }
    TObjFish::set_global_param(this->texlist);
    select_actor_lighting((s32)this);
    TObjPlayer::toggle_particle_effect();
    ok = 1;
    push_matrix();
    translate_matrix(0, this->position.x, this->flight_height + (this->position.y + this->model_y_offset), this->position.z);
    rotate_matrix_y(0, this->rotation_y);
    model_render_flags &= ~0x400;
    if (TObjPlayer::check_demo_mode() == 1) {
        draw_chunk_object((void *)this->model);
    } else if (this->m_388 & 4) {
        if (this->spawn_fade.has_visible_opacity() != 0) {
            this->spawn_fade.set_flags_and_apply_damage_color();
            if (vis == 1) {
                set_motion_packed_rotation();
                this->draw();
                clear_motion_packed_rotation();
            } else {
                set_motion_packed_rotation();
                this->draw_motion_model();
                clear_motion_packed_rotation();
            }
            this->spawn_fade.clear_flag_and_notify();
        } else {
            ok = 0;
        }
    } else {
        if (vis == 1) {
            set_motion_packed_rotation();
            this->draw();
            clear_motion_packed_rotation();
        } else {
            set_motion_packed_rotation();
            this->draw_motion_model();
            clear_motion_packed_rotation();
        }
    }
    pop_matrix();
    restore_scene_lighting();
    TParticleCtrl::end_effect_render();
    if (!(this->actorFlags & 0x800) && ok != 0) {
        Vec v;
        v.x = v.y = v.z = (1.0f - 0.01f * this->flight_height) * (5.0f * this->scale.x);
        render_with_position_override((u8 *)&v, 0);
    }
    this->camera_fade.clear_flag_and_notify();
    model_render_flags = saved_model_render_flags;
}

void TObjEneMe1GiGue::fn_802CD054() {  }

void TObjEneMe1GiGue::update_idle() {
    if (this->m_388 & 0x40000) {
        return;
    }
    switch (this->state) {
    case -1:
        break;
    case 0:
        this->requested_action = 1;
        this->state = 1;
        this->m_384 = 0x96;
        this->sub_8004292C();
    case 1:
        advance_animation();
        this->move_around_center(&home_position, this->parameters[1]);
        this->m_384 -= 1;
        if (this->m_384 <= 0) {
            this->requested_action = 0;
            this->state = 2;
            this->m_384 = 0x5A;
        }
        check_object_collisions();
        check_enemy_body_collisions(this);
        update_enemy_collision_flags();
        apply_actor_gravity(this, 0, 0.0f);
        break;
    case 2:
        advance_animation();
        check_object_collisions();
        check_enemy_body_collisions(this);
        update_enemy_collision_flags();
        this->m_384 -= 1;
        if (this->m_384 <= 0) {
            this->state = 0;
        }
        break;
    }
}

void TObjEneMe1GiGue::vfunc_62() {
    switch (mode) {
    case 10:
    case 11:
    case 13:
        referenceHp = hp;
        actorFlags &= ~0x200;
        return;
    }
    set_state(4);
    m_380 = m_378;
    m_378 = 4;
    m_388 |= 0x10001;
}

void TObjEneMe1GiGue::vfunc_63() {
    this->set_state(5);
    this->m_380 = (s32) this->m_378;
    this->m_378 = 5;
    this->m_388 = (s32) (this->m_388 | 1);
}

void TObjEneMe1GiGue::update_search() {
    this->actorFlags &= ~0x01000000;
    switch (this->state) {
    case 0:
        this->m_388 &= ~0x00040000;
        sub_8004292C();
        this->requested_action = 1;
        this->search_turn = 0;
        if (this->target != NULL) {
            VecCopy((Vec *)&this->m_29c, (const Vec *)&((TObjChara *)this->target)->body_center_position.x);
        }
        this->state = 1;
    case 1:
        advance_animation();
        apply_actor_gravity(this, 0, 0.0f);
        if (this->target != NULL) {
            Vec d = ((TObjChara *)this->target)->position;
            subtract_vector(&d, &this->position);
            if (d.x * d.x + d.z * d.z <= this->attack_range * this->attack_range &&
                angle_difference_abs(-(s32)(TObjEneMe1GiGue__data_80472298 * atan2_float(d.z, d.x)) + 0x4000, this->rotation_y) < this->attack_angle / 2) {
                s32 st;
                this->attack_count++;
                if (this->attack_count > 2) {
                    this->attack_count = 0;
                    st = 0xD;
                } else {
                    this->volley_count = 0;
                    st = 9;
                }
                update_if_active(st);
                break;
            }
        }
        this->rotation_y += ((GiGueMovementParameters *)movementParameters)->turn_speed / 2;
        enemy_set_heading_velocity(movement_speed, this, rotation_y);
        move_with_wall_slide((u8 *)this);
        this->search_turn += ((GiGueMovementParameters *)movementParameters)->turn_speed / 2;
        if (this->search_turn > 0x10000) {
            this->wander_distance = 0.0f;
            this->state = 2;
        }
        break;
    case -1:
        break;
    case 2:
        enemy_wander_home(movement_speed, 100.0f, 50.0f, ((GiGueMovementParameters *)movementParameters)->turn_speed);
        advance_animation();
        apply_actor_gravity(this, 0, 0.0f);
        this->wander_distance += this->movement_speed;
        if (this->wander_distance > 100.0f) {
            if (find_target_in_range( ((GiGueMovementParameters *)movementParameters)->target_range) != 0) {
                this->search_turn = 0;
                this->state = 1;
            } else {
                update_if_active(0);
            }
        }
        check_object_collisions();
        check_enemy_body_collisions(this);
        update_enemy_collision_flags();
        break;
    }
}

void TObjEneMe1GiGue::update_missile_attack() {

    u32 r;

    switch (this->state) {
    case 0:
        sub_8004292C();
        this->m_384 = this->attack_duration;
        if (this->m_384 <= 0x28) {
            this->m_384 = 0x28;
        }
        if (!(this->actorFlags & 0x01000000)) {
            this->requested_action = 2;
            goto set1;
        }
        update_if_active(0xD);
        this->m_388 &= ~0x40000;
        break;
    set1:
        this->state = 1;
        advance_animation();
        this->m_388 &= ~0x40000;
        break;
    case 1:
    case 2:
    case 3:
        if (this->target == NULL) {
            this->state = 4;
            break;
        }
        switch (this->state) {
        case 1:
            if (this->frame >= 5.0f) {
                this->update_animation_nodes();
                this->state = 2;
            }
            break;
        case 2:
            play_persistent_sound((s32)(remap_sound_id(0x3A81D)), (s32)this, (u32)&this->position, 0, 0);
            if (this->frame >= 20.0f) {
                this->update_animation_nodes();
                if ((r = (u32)spawn_particle_effect(&this->missile_origin, 0x203)) != 0) {
                    Vec v = lbl_80472274[0];
                    ((TParticleCtrl *)r)->set_direction(&v);
                }
                TObjEneMe1GiGueMissile::create((s32)this, (s32)&this->missile_origin, (s32)&((TObjChara *)target)->body_center_position.x, (f32)lbl_805D6840, (f32)lbl_805D6850);
                play_sound_effect(remap_sound_id(0x3A31E), &this->position, 0, 0);
                this->state = 3;
            }
            break;
        }
        VecCopy((Vec *)&this->m_29c, (const Vec *)&((TObjChara *)target)->body_center_position.x);
        enemy_turn_half_toward_dest(this);
        advance_animation();
        if (!(this->actorFlags & 0x01000000)) {
            apply_actor_gravity(this, 0, 0.0f);
        }
        ((TObjPlayer *)this)->update_collisions();
        if (--this->m_384 <= 0) {
            this->state = 4;
        }
        break;
    case 4:
        if (this->actorFlags & 0x01000000) {
            this->m_378 = 0;
            update_if_active(0xD);
        } else if (!(this->m_388 & 0x80000) && random_ratio() <= this->barrier_probability) {
            update_if_active(0xC);
        } else {
            update_if_active(0);
        }
        break;
    case -1:
        break;
    }
}

void TObjEneMe1GiGue::update_needle_attack() {
    s32 n;
    s32 r;

    switch (this->state) {
    case -1:
        break;
    case 0:
        sub_8004292C();
        r = 0;
        if (!(this->actorFlags & 0x01000000)) {
            r = this->collect_targets();
        }
        if (r > 0) {
            this->requested_action = 3;
            this->m_384 = this->attack_duration;
            if (this->m_384 <= 0x14) {
                this->m_384 = 0x14;
            }
            this->state = 1;
        } else if (this->actorFlags & 0x01000000) {
            update_if_active(0xD);
        } else if (!(this->m_388 & 0x80000) && random_ratio() <= this->barrier_probability) {
            update_if_active(0xC);
        } else {
            update_if_active(0);
        }
        this->m_388 &= ~0x40000;
        break;
    case 1:
    case 2:
    case 3:
        switch (this->state) {
        case 1:
            if (this->frame >= 5.0f) {
                this->update_animation_nodes();
                this->state = 2;
            }
            break;
        case 2:
            play_persistent_sound((s32)(remap_sound_id(0x3A820)), (s32)this, (u32)(&position), 0, 0);
            if (this->frame >= 10.0f) {
                this->update_animation_nodes();
                n = this->target_count;
                this->spawn_needle((s32)((s32)((f32)n * random_ratio()) % n));
                this->state = 3;
            }
            break;
        }
        advance_animation();
        apply_actor_gravity(this, 0, 0.0f);
        ((TObjPlayer *)this)->update_collisions();
        (this->m_384)--;
        if (this->m_384 <= 0) {
            (this->volley_count)++;
            if (this->volley_count >= 3) {
                this->m_384 = 0x2D;
                this->requested_action = 1;
                this->state = 4;
            } else {
                this->state = 0;
                this->frame = 0.0f;
            }
        }
        break;
    case 4:
        enemy_wander_home(movement_speed, 100.0f, 100.0f, ((GiGueMovementParameters *)movementParameters)->turn_speed);
        advance_animation();
        apply_actor_gravity(this, 0, 0.0f);
        ((TObjPlayer *)this)->update_collisions();
        (this->m_384)--;
        if (this->m_384 <= 0) {
            if (!(this->m_388 & 0x80000) && random_ratio() <= this->barrier_probability) {
                update_if_active(0xC);
            } else {
                update_if_active(0);
            }
        }
        break;
    }
}

void TObjEneMe1GiGue::update_techniques() {
    s32 r;
    switch (this->state) {
    case -1:
        break;
    case 0:
        sub_8004292C();
        r = 0;
        if (!(this->actorFlags & 0x01000000)) {
            r = this->collect_targets();
        }
        if (r > 0) {
            this->state = 1;
            this->requested_action = 3;
        } else if (this->actorFlags & 0x01000000) {
            update_if_active(0xD);
        } else {
            update_if_active(0);
        }
        this->m_388 &= ~0x40000;
        break;
    case 1:
    case 2:
    case 3:
        switch (this->state) {
        case 1:
            if (this->frame >= 5.0f) {
                this->update_animation_nodes();
                spawn_particle_effect(&needle_origin, 0x204);
                this->state = 2;
            }
            break;
        case 2:
            play_sound_effect(remap_sound_id(0x3A344), &position, 0, 0);
            if (this->frame >= 10.0f) {
                this->update_animation_nodes();
                this->state = 3;
                create_instance__9TTecZaruaFllll(this, &body_center_position.x, &body_center_position.x, get_int_parameter(2));
                create__9TTecJelinFllll(this, &body_center_position.x, &body_center_position.x, get_int_parameter(2));
            }
            break;
    }
        advance_animation();
        apply_actor_gravity(this, 0, 0.0f);
        ((TObjPlayer *)this)->update_collisions();
        if (this->requested_action != 3) {
            update_if_active(0xD);
        }
        break;
    }
}

void TObjEneMe1GiGue::update_barrier() {

    switch (this->state) {
    case 0:
        sub_8004292C();
        this->m_388 &= ~0x40000;
        this->requested_action = 1;
        this->state = 1;
        return;
    case 1:
        TObjEneMe1GiGueBarrier::create(this, this);
        this->state = 2;
        this->m_384 = 0x2D;
        advance_animation();
        apply_actor_gravity(this, 0, 0.0f);
        ((TObjPlayer *)this)->update_collisions();
        return;
    case 2:
        enemy_wander_home(movement_speed, 100.0f, 100.0f, ((GiGueMovementParameters *)movementParameters)->turn_speed);
        advance_animation();
        apply_actor_gravity(this, 0, 0.0f);
        ((TObjPlayer *)this)->update_collisions();
        this->m_384 = (s32) (this->m_384 - 1);
        if ((s32) this->m_384 <= 0) {
            update_if_active(0);
        }
    case -1:
        return;
    }
}

void TObjEneMe1GiGue::update_rush_attack() {
    switch (this->state) {
    case 0:
        this->actorFlags |= 0x800000;
        this->actorFlags &= ~0x1000000;
        this->requested_action = this->state = 1;
        this->flight_height = 0.0f;
        this->rush_timer = 0x3C;
        sub_8004292C();
        break;
    case 1:
        this->actorFlags &= ~0x1000000;
        enemy_wander_home(movement_speed, 100.0f, 50.0f, ((GiGueMovementParameters *)movementParameters)->turn_speed);
        advance_animation();
        apply_actor_gravity(this, 0, 0.0f);
        this->rush_timer--;
        if (this->rush_timer <= 0) {
            this->state = 2;
            play_sound_effect(remap_sound_id(0x3A818), &this->position, 0, 0);
            this->actorFlags |= 0x1000000;
            this->actorFlags &= ~0x800000;
            find_target_in_range(((GiGueMovementParameters *)movementParameters)->target_range);
            if (this->target != NULL) {
                Vec d;
                VecCopy((Vec *)&d, (const Vec *)&this->position);
                subtract_vector(&d, &((TObjChara *)target)->position);
                this->find_open_direction(&d);
                calc_velocity_toward_destination(this, position, move_destination, movement_speed);
            } else {
                VecCopy(&move_destination, (const Vec *)&this->home_position);
                calc_velocity_toward_destination(this, position, move_destination, movement_speed);
            }
        }
        check_object_collisions();
        check_enemy_body_collisions(this);
        update_enemy_collision_flags();
        break;
    case 2: {
        s32 ok;
        this->actorFlags &= ~0x800000;
        advance_animation();
        calc_velocity_toward_destination(this, position, move_destination, get_float_parameter(0));
        ok = 1;
        if (this->requested_action == 6 && this->frame < 22.0f) {
            ok = 0;
        }
        if (ok) {
            this->flight_height += 2.2f;
        }
        ((TObjPlayer *)this)->update_collisions();
        if (TObjPlayer__sub_800DC478((u8 *)this, 1, 22.0f) != 0 && this->check_vector_bit(&position) != 0) {
            spawn_particle_effect(&this->position, 0xF0);
        }
        if (this->flight_height >= 50.0f) {
            this->state = 3;
        }
        play_persistent_sound((s32)(remap_sound_id(0x3A819)), (s32)this, (u32)&this->position, 0, 0);
        break;
    }
    case 3:
        advance_animation();
        calc_velocity_toward_destination(this, position, move_destination, get_float_parameter(0));
        this->movement_velocity.y = 0.0f;
        VecCopy(&prev_position, (const Vec *)&this->position);
        vec3_add_to(&this->position, &this->movement_velocity.x);
        if (csnVector(&this->prev_position, &this->position, 0x88E0) != 0) {
            VecCopy(&position, (const Vec *)&this->prev_position);
            this->state = 4;
            this->movement_velocity.x = this->movement_velocity.z = 0.0f;
        } else {
            if (xz_distance_squared(&position, &move_destination) <= (10.0f + this->movement_speed) * (10.0f + this->movement_speed)) {
                this->state = 4;
                this->movement_velocity.x = this->movement_velocity.z = 0.0f;
            }
        }
        if (is_passing_frame(10.0f) != 0 && this->check_vector_bit(&position) != 0) {
            spawn_particle_effect(&this->position, 0xF0);
        }
        this->refresh_collision_body_centers();
        if (this->flight_height > 15.0f) {
            this->turn_toward_direction(((GiGueMovementParameters *)movementParameters)->turn_speed * 2, &movement_velocity);
        }
        play_persistent_sound((s32)(remap_sound_id(0x3A819)), (s32)this, (u32)&this->position, 0, 0);
        project_actor_to_ground(this, &this->position, 0);
        break;
    case 4:
        this->actorFlags &= ~0x800000;
        this->bodies[1].flags |= 1;
        advance_animation();
        this->flight_height += (-2.3f);
        if (this->flight_height <= 0.0f) {
            this->flight_height = 0.0f;
            this->actorFlags |= 0x800000;
            this->actorFlags &= ~0x1000000;
            this->movement_velocity.y = 0.0f;
            if (this->requested_action != 8) {
                if (!(this->m_388 & 0x80000) && random_ratio() <= this->barrier_probability) {
                    update_if_active(0xC);
                } else {
                    update_if_active(0);
                }
            }
        } else if (this->requested_action == 7) {
            if (this->flight_height <= 2.3f * (40.0f + 1.0f / this->blend_speed)) {
                this->requested_action = 8;
            }
        } else {
            s32 t = (s32)this->frame;
            if ((t == 0x14 || t == 0x28) && this->check_vector_bit(&position) != 0) {
                spawn_particle_effect(&this->position, 0xF0);
            }
        }
        play_persistent_sound((s32)(remap_sound_id(0x3A819)), (s32)this, (u32)&this->position, 0, 0);
        check_object_collisions();
        check_enemy_body_collisions(this);
        update_enemy_collision_flags();
        apply_actor_gravity(this, 0, 0.0f);
        break;
    case -1:
        if ((s32)this->next_action != 4 && (s32)this->next_action != 5) {
            this->flight_height = 0.0f;
        }
        this->bodies[1].flags &= ~1;
        this->m_388 &= ~0x40000;
        this->attack_count = 0;
        break;
    }
}

void TObjEneMe1GiGue::update_hit_reaction() {
    s16 previous_hp;
    s16 animation;
    TObjChara *entity;
    s32 counterattack;
    switch (this->state) {
    case 0:
        animation = 4;
        this->actorFlags &= ~0x200000;
        if (this->actorFlags & 0x01000000) {
            animation = 5;
        }
        this->requested_action = animation;
        spawn_particle_effect(&body_center_position.x, 0xF2);
        this->state = 1;
    case 1:
        advance_animation();
        if (!(this->actorFlags & 0x01000000)) {
            Vec v = body_center_position;
            v.x += this->movement_velocity.x;
            v.z += this->movement_velocity.z;
            if (check_path_obstructed(this, &v) == 0) {
                move_with_wall_slide((u8 *)this);
            } else {
                this->movement_velocity.x = this->movement_velocity.z = 0.0f;
            }
            this->movement_velocity.x *= 0.5f;
            this->movement_velocity.z *= 0.5f;
        }
        apply_actor_gravity(this, 0, 0.0f);
        ((TObjPlayer *)(u8 *)this)->update_collisions();
        if ((u32) this->action_flags != 8U) {
            this->state = -1;
        }
        break;
    case -1:
        counterattack = 0;
        this->actorFlags &= ~0x200;
        this->m_388 &= ~1;
        this->m_378 = 1;
        previous_hp = this->referenceHp;
        if (((s32) (previous_hp - this->hp) > (s32) (previous_hp / 4)) && !(this->actorFlags & 2)) {
            entity = (TObjChara *)find_entity_by_id(m_2d4);
            if (entity != 0) {
                counterattack = 1;
                if ((this->actorFlags & 0x01000000) && (xz_distance_squared(&position, &entity->position) > 400.0f)) {
                    counterattack = 0;
                }
            }
        }
        if (counterattack == 1) {
            this->targetId = (u16) this->m_2d4;
            this->next_action = 9;
        } else if (this->actorFlags & 0x01000000) {
            update_if_active(0xD);
            this->m_378 = (s32) this->m_380;
        } else {
            update_if_active(0);
        }
        this->referenceHp = (s16) this->hp;
        break;
    }
}

void TObjEneMe1GiGue::break_apart() {
    Vec breakup_position;
    VecCopy(&breakup_position, &position);
    breakup_position.y += 40.0f + flight_height;
    TBoss3Volopt::create_breakup_mdl((s32)TObjEneMe1GiGue__barrier_obj, 0, this->texlist, (s32)&breakup_position, this->rotation_y);
    ((TObjPlayer *)(u8 *)this)->refresh_lobby_state();
    this->send_entity_set_flags();
    spawn_particle_effect(&breakup_position, 0x205);
    spawn_particle_effect(&breakup_position, 0x206);
    play_sound_effect((remap_sound_id(0x3AF1C)), &breakup_position, 0, 0);
    queue_destruction();
}

void TObjEneMe1GiGue::move_around_center(Vec *center, f32 radius) {
    if (xz_distance_squared(&position, &move_destination) < 400.0f) {
        s32 k = (s32)(182.04445f * (360.0f * random_ratio()));
        f32 d = 0.4f * (radius * (1.0f + random_ratio()));
        this->move_destination.x = d * cos_table_lookup(k) + center->x;
        this->move_destination.z = d * sin_table_lookup(k) + center->z;
    }
    VecCopy((Vec *)&this->m_29c, &move_destination);
    enemy_turn_toward_dest(this, ((GiGueMovementParameters *)movementParameters)->turn_speed);
    enemy_set_heading_velocity(movement_speed, this, rotation_y);
    move_with_wall_slide((u8 *)this);
}

void TObjEneMe1GiGue::spawn_needle(s32 index) {
    if (find_entity_by_id(target_ids[index]) != 0) {
        GiGueProjectileAngles v;
        v.x = 0;
        v.y = this->rotation_y + ((index & 1) ? -0x2000 : 0x2000);
        v.z = 0;
        new TUnk_804E14E8(&needle_origin, target_ids[index], &v, index * 3,
                          random_ratio() <= get_float_parameter(5), entity_id);
    }
}

void TObjEneMe1GiGue::select_next_action() {
    switch (this->mode) {
    case 0:
        if (this->is_actor_cadence_frame(0x1E) != 0) {
            if (find_nearest_visible_player(this, 0, ((GiGueMovementParameters *)movementParameters)->target_range) != 0xFFFF) {
                find_target_in_range( ((GiGueMovementParameters *)movementParameters)->target_range);
                if (this->m_388 & 0x40000) {
                    init_move();
                } else {
                    update_if_active(1);
                }
            }
        }
        break;
    case 1:
        if (find_nearest_visible_player(this, 0, 50.0f) != 0xFFFF) {
            if (random_ratio() <= this->technique_probability) {
                update_if_active(0xB);
            } else {
                update_if_active(0xD);
                this->m_378 = 1;
            }
        } else if (find_nearest_visible_player(this, 0, 50.0f + ((GiGueMovementParameters *)movementParameters)->target_range) == 0xFFFF) {
            update_if_active(0);
        }
        break;
    case 13:
        break;
    }
}

#pragma fp_contract off
void TObjEneMe1GiGue::init_move() {
    VecCopy(&prev_position, &position);
    this->actorFlags = (s32) (this->actorFlags | 0x01000000);
    update_if_active(0xE);
    this->m_378 = 1;
    refresh_collision_body_centers();
}

void TObjEneMe1GiGue::apply_hit_shake(u32 arg1) {
    if ((arg1 == get_player_by_client_id(0)) && ((s32) this->shake_timer <= 0)) {
        this->shake_timer = 0x1E;
        TCameraCtrl::set_shake_preset(1);
    }
}

s32 TObjEneMe1GiGue::remap_sound_id(s32 id) {
    s32 area = get_current_floor_area();
    if (id == 0x3A344) return area == AREA_TOWER ? 0x40039E14 : id;
    if (id == 0x3A345) return area == AREA_TOWER ? 0x40039415 : id;
    return remap_sound_for_area(id);
}

void TObjEneMe1GiGue::update_landing() {
    f32 height;
    s32 frame;
    switch (this->state) {
    case 0:
        VecCopy(&move_destination, &home_position);
        calc_velocity_toward_destination(this, position, move_destination, movement_speed);
        this->m_388 &= ~0x40000;
        sub_8004292C();
        this->flight_height = (f32) this->initial_height;
        this->requested_action = 7;
        this->state = 1;
    case 1:
        advance_animation();
        bodies[1].flags |= 1;
        this->flight_height += (-2.3f);
        height = this->flight_height;
        if (height <= 0.0f) {
            this->flight_height = 0.0f;
            this->actorFlags = (s32) (this->actorFlags | 0x800000);
            this->actorFlags = (s32) (this->actorFlags & 0xFEFFFFFF);
            this->movement_velocity.y = 0.0f;
            if ((s16) this->requested_action != 8) {
                this->state = -1;
                play_sound_effect(remap_sound_id(0x3A345), &position, 0, 0);
            }
        } else if ((s16) this->requested_action == 7) {
            if (height <= (2.3f * (40.0f + (1.0f / this->blend_speed)))) {
                this->requested_action = 8;
            }
        } else {
            frame = (s32) this->frame;
            if (((frame == 0x14) || (frame == 0x28)) && (this->check_vector_bit(&position) != 0)) {
                spawn_particle_effect((&position), 0xF0);
            }
        }
        play_persistent_sound((s32)(remap_sound_id(0x3A819)), (s32)this, (u32)(&position), 0, 0);
        ((TObjPlayer *)this)->update_collisions();
        break;
    case -1:
        update_if_active(1);
        break;
    }
    apply_actor_gravity(this, 0, (f32) (0.0f));
}

void TObjEneMe1GiGue::update_spawn() {
    s32 flags;
    s32 spawn_flags;

    switch (this->state) {
    case 0:
        this->m_388 = (s32) (this->m_388 | 4);
        flags = this->actorFlags | 0x04000000;
        this->actorFlags = flags;
        this->requested_action = 0;
        play_area_sound_effect__12TBoss3VoloptFv(&body_center_position.x, flags);
        spawn_fade.start_fade_in();
        this->state = 1;
    case 1:
        advance_animation();
        if (this->spawn_fade.advance_toward_max() == 1) {
            this->state = -1;
            play_sound_effect(remap_sound_id(0x3A345), &position, 0, 0);
        }
        ((TObjPlayer *)this)->update_collisions();
        return;
    case -1:
        spawn_flags = this->m_388;
        this->m_388 = (s32) (spawn_flags & ~5);
        this->actorFlags = (s32) (this->actorFlags & 0xFBFFFFFF);
        update_if_active(0);
        return;
    }
}

void TObjEneMe1GiGue::add_target_in_cone(TObjChara *target) {
  s32 target_angle;
  if ((((this->target_count < 12) && (target != 0)) && (((void *) target) != ((void *) this))) && (!(target->actorFlags & 0x06000800)))
  {
    Vec v = target->position;
    subtract_vector(&v, &this->position);
    if (!(((v.x * v.x) + (v.z * v.z)) > (this->attack_range * this->attack_range)))
    {
      target_angle = (-((s32) (TObjEneMe1GiGue__data_80472298 * atan2_float(v.z, v.x)))) + 0x4000;
      if (angle_difference_abs(target_angle, this->rotation_y) <= (this->attack_angle / 2))
      {
        this->target_ids[this->target_count++] = get_entity_id(target);
      }
    }
  }
}

s32 TObjEneMe1GiGue::collect_targets() {
    s32 i;
    this->target_count = 0;
    for (i = 0; i < registered_player_count; i++) {
        TObjPlayer *target = TObjPlayer::get_player_data(i);
        add_target_in_cone(target);
    }
    return this->target_count;
}

void TObjEneMe1GiGue::update_animation_nodes() {
    push_matrix_from(identity_matrix);
    translate_matrix(0, (f32) (this->position.x), (f32) (this->flight_height + (this->position.y + this->model_y_offset)), (f32) (this->position.z));
    rotate_matrix_y(0, (int) (this->rotation_y));
    set_motion_packed_rotation();
    this->calc_joint_matrices(this->frame);
    clear_motion_packed_rotation();
    pop_matrix();
    get_anim_node_position(0, &barrier_origin);
    get_anim_node_position(0x2A, &missile_origin);
    get_anim_node_position(0x16, &needle_origin);
}

void TObjEneMe1GiGue::update_direction() {
    this->attack_range = ((AttackParams *)(this->m_318))->get_attack_range();
    this->attack_angle = ((AttackParams *)(this->m_318))->get_attack_angle();
}

#pragma fp_contract on
void TObjEneMe1GiGue::load_params() {
    lbl_805D6840 = get_float_parameter(1);
    lbl_805D6844 = get_float_parameter(2);
    lbl_805D6848 = get_float_parameter(3);
    lbl_805D684C = get_float_parameter(4);
    lbl_805D6850 = get_int_parameter(0);
    lbl_805D6854 = get_int_parameter(1);
    this->barrier_duration = (s32) (30.0f * (f32) get_int_parameter(3));
    this->attack_duration = get_int_parameter(4);
}

#pragma push
#pragma fp_contract off
#pragma opt_common_subs off
void TObjEneMe1GiGue::find_open_direction(Vec *direction) {
    f32 best;
    s32 ang;
    s32 bestAng;
    s32 i;
    CsnHit *hit;
    f32 d;
    ang = (s32) (TObjEneMe1GiGue__data_80472298 * atan2_float(direction->x, direction->z));
    best = 0.0f;
    bestAng = ang;
    push_matrix_from(identity_matrix);
    Vec v = lbl_80472280;
    rotate_matrix_y(0, ang);
    for (i = 0; i < 3; i++) {
        matrix_mult_vec(0, &v, &move_destination);
        vec3_add_to(&move_destination, &body_center_position.x);
        hit = csnVector((const Vec *)&body_center_position.x, &move_destination, -1);
        if (hit == NULL) {
            pop_matrix();
            return;
        }
        d = vec_xz_distance(&position, &hit->contact->point) - 20.0f;
        if (best < d) {
            best = d;
            bestAng = ang;
        }
        rotate_matrix_y(0, 0x5555);
        ang += 0x5555;
    }
    pop_matrix();
    push_matrix_from(identity_matrix);
    Vec w = lbl_8047228C;
    w.x = best;
    rotate_matrix_y(0, bestAng);
    matrix_mult_vec(0, &w, &move_destination);
    vec3_add_to(&move_destination, &body_center_position.x);
    pop_matrix();
}
#pragma pop

#pragma fp_contract off
s32 TObjEneMe1GiGue::update_action_hold_status() {
    if (TObjChara::update_action_hold_status() != 0) {
        this->reset_spawn_after_hold();
        return 1;
    }
    return 0;
}

#pragma fp_contract on
void TObjEneMe1GiGue::reset_spawn_after_hold() {
    s32 flags;
    flags = this->m_388;
    if (flags & 0x40000) {
        this->m_388 = (s32) (flags & 0xFFFBFFFF);
        VecCopy(&position, &home_position);
        project_actor_to_ground(this, &position, 0);
        return;
    }
    if ((s32) this->next_action == 7) {
        this->m_388 = (s32) (flags & 0xFFFFFFFE);
        update_if_active(0);
    }
}

#pragma fp_contract off
s32 TObjEneMe1GiGue::check_vector_bit(Vec *point) {
    s32 *ground_flags;

    ground_flags = csnVectorUnder(point, (u32 *)&m_120, 5);
    if (ground_flags == NULL) {
        return 0;
    }
    return (u32)__cntlzw(*ground_flags & 4) >> 5;
}

BmlResource *TObjEneMe1GiGue::get_resources() { return TObjEneMe1GiGue__data_805D6838; }

Vec *TObjEneMe1GiGue::update_barrier_origin() {
    update_animation_nodes();
    return &barrier_origin;
}

s32 TObjEneMe1GiGue::get_barrier_rotation() { return rotation_y; }

s32 TObjEneMe1GiGue::get_barrier_duration() { return barrier_duration; }

s32 TObjEneMe1GiGue::should_end_barrier() {
    return mode == 9 || mode == 10 || mode == 11 || mode == 4 || mode == 5;
}

void TObjEneMe1GiGue::set_barrier_active() { m_388 |= 0x80000; }

void TObjEneMe1GiGue::clear_barrier_active() { m_388 &= ~0x80000; }

f32 TObjEneMe1GiGue::receive_physical_attack(void *attacker, f32 damage) {
    f32 damage_received;

    damage_received = 0.0f;
    if (this->m_388 & 0x80000) {
        this->show_miss_popup(&body_center_position.x);
        this->set_state(0xA);
    } else {
        damage_received = TObjChara::receive_physical_attack(attacker, damage);
    }
    return damage_received;
}

f32 TObjEneMe1GiGue::receive_direct_attack(void *attacker, DirectAttackPayload attack, void *hit, s32, s32) {
    f32 result = 0.0f;
    if (m_388 & 0x80000) {
        show_miss_popup(&body_center_position.x);
        set_state(10);
    } else {
        result = TObjChara::receive_direct_attack(attacker, attack, hit, -1, -1);
    }
    return result;
}

f32 TObjEneMe1GiGue::receive_weapon_special_attack(void *attacker, void *attack) {
    f32 damage_received;

    damage_received = 0.0f;
    if (this->m_388 & 0x80000) {
        this->show_miss_popup(&body_center_position.x);
        this->set_state(0xA);
    } else {
        damage_received = TObjChara::receive_weapon_special_attack(attacker, attack);
    }
    return damage_received;
}
