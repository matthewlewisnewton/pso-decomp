#pragma dont_inline off
#pragma inline_depth(4)
#define TOBJECT_OUT_OF_LINE_HELPERS
#include "pso/player/TObjPlayer_803E4954.h"
#include "pso/player/demo_mode.h"
#include "pso/player/PlayerAttackParams.h"
#include "pso/enemy/TObjEneRe7Berura_803E4CE0.h"
#include "pso/enemy/BattleParameters.h"
#include "pso/npc/NpcModelRegistry.h"
#include "pso/npc/NpcAnimationBinding.h"
#include "pso/math/ScratchVectorStorage.h"

#include <dolphin/mtx.h>
#include "pso/player/TObjPlayer_801542CC.h"
#include "pso/TParticleCtrl.h"
#include "pso/TObjControl.h"
#include "types.h"
#include "pso/player/TObjChara.h"
#include "pso/player/TObjPlayer.h"
#include "pso/enemy/TObjEnemy.h"
#include "pso/object/TObjMotion.h"
#include "pso/enemy/TObjEneGibbles.h"
#include "pso/map/FloorArea.h"
#include "pso/map/CsnGroundQuery.h"
#include "pso/system/BmlResourceDescriptor.h"
#include "pso/system/vector.h"
#include "pso/misc/MaterialOpacityFade.h"
#include <stddef.h>
#include "pso/boss/TBoss4DarkFalz.h"
#include "pso/enemy/TObjEneLappy.h"
#include "pso/enemy/TObjEneMe3SinowZoa.h"
#include "pso/enemy/TObjEnePanarms.h"
#include "pso/enemy/TObjEneRe7Berura.h"
#include "pso/misc/RenderFadeState.h"
#include "pso/misc/TLobby.h"
#include "pso/object/TObjFish.h"


s32 lerp_angle_half(s32 from, s32 to);

extern "C" {
f32 calc_xz_distance_sq(void *, void *, Vec *);
f64 atan2_float(f32, f32);
s32 angle_difference_abs(s32, s32);
extern const f64 TObjEneGibbles__data_80472798;
extern void **gibbles_combat_stat_entries;
extern const f32 lbl_805DE834;
extern const f32 lbl_805DE85C;
void apply_actor_gravity(TObjEnemy *arg0, s32 *arg1, f32 farg0);
s16 get_attack_params_atp_min(void *);
s32 get_current_floor();
u8 *get_enemy_entity(u16);



s32 submit_cursor_candidate(void *, int);
TObjPlayer *get_player_by_client_id(s32);
s32 minimap_render_dot(void *, int, int, int);
s32 play_sound_effect(int, void *, int, int);
extern const f32 TObjEneGibbles__data_805DE7E4;
extern const f32 lbl_805DE838;
void attach_particle_model(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, f32 farg0);
CsnGroundHit *csnVectorUnder(Vec *, void *, s32, f32);
void *spawn_particle_effect(void *pos, s32 id);
extern const f32 TObjEneGibbles__data_805DE7E8;
extern const f32 TObjEneGibbles__data_805DE7EC;
extern const f32 lbl_805DE7F0;
extern const f32 TObjEneGibbles__data_805DE7F8;
extern const f32 TObjEneGibbles__data_805DE830;
extern const f32 lbl_805DE874;
s32 enemy_move_toward(void *, s32, void *, int, f32);
s32 select_enemy_destination(void *, Vec *, int);
s32 copy_position_if_valid__10TObjPlayerFii(s32 arg0, s32 arg1);
f32 horizontal_distance_squared(int, void *);
extern GibblesAiParameters *TObjEneGibbles__ai_parameters;
extern const f32 lbl_805DE860;
extern const f32 lbl_805DE864;
s32 is_split_screen();
s32 get_camera_mode__11TCameraCtrlFv();
void restore_scene_lighting(void);
void select_actor_lighting(s32 obj);
void scale_matrix_vec3(u8 *arg0, u8 *arg1);
void translate_matrix_vec3(u8 *arg0, u8 *arg1);
s32 rotate_matrix_y(int, int);
s32 push_matrix_from(void *);
s32 pop_matrix();
f32 subtract_vector(void *, void *);
s32 check_path_obstructed(void *, void *);
s32 get_entity_id(void *);
void enemy_set_heading_velocity(f32 speed, TObjEnemy *enemy, s32 heading);
void calc_velocity_toward_destination(void *, Vec, Vec, f32);
f32 newton_sqrtf(f32);
s32 TObjEneGibbles__sub_800D8988(void *);
extern f32 lbl_805DE80C;
extern const f32 lbl_805DE814;
extern const f32 lbl_805DE828;
extern const f32 lbl_805DE82C;

void *mem_alloc(u32 size);
extern NpcAnimationBinding gibbles_resource_binding_desc;
extern s32 gibbles_boss_stat_handle;
extern s32 gibbles_combat_stats_handle;
extern BmlResource *TObjEneGibbles__resource_bundle;

extern const char *lbl_805D3F60;


s32 get_main_phase();
f32 calc_distance_to_client__10TObjPlayerFlUsUl(void *, u16, Vec *);
s32 obj_setFlags30(void *, int);

void TCameraCtrl__sub_8006A044(s32, f32);

s32 rotate_xz_pair_by_angle(f32 *, f32 *, s32, f32);
s32 test_action_mask__10TObjPlayerFl(void *, int);

void TObjPlayer__sub_800D93C4(s32 point, s32 delay);
s32 angle_diff_s16(s32, s32);

void mem_free(void*);
s32 get_room__8TObjBaseFv(void *);
s32 vec3_add_to(f32 *, void *);
s32 matrix_mult_vec(int, void *, void *);
s32 rotate_matrix_x(s32, s32);
f32 post_translate_matrix(void *);
extern const f32 TObjEneGibbles__data_805DE7F4;
extern const f32 TObjEneGibbles__data_805DE81C;
extern Vec gibbles_joint_zero_vec;
extern Mtx34 identity_matrix;
extern s32 local_client_id;
extern Mtx34 *anim_model_matrix_array;
extern s32 lbl_805D5868;
extern const f32 lbl_805DE7E0;
extern const f32 lbl_805DE7FC;
extern const f32 lbl_805DE800;
extern const f32 lbl_805DE804;
extern const f32 lbl_805DE808;
extern const f32 lbl_805DE810;
extern const f32 lbl_805DE858;
extern const f32 lbl_805DE868;
extern const f32 lbl_805DE86C;
extern const f32 lbl_805DE870;
extern void *tl_04;
extern const char lbl_80472628[];
extern const char lbl_80472638[];
extern const char lbl_80472650[];
extern const char lbl_80472668[];
extern const char lbl_8047267C[];
extern const char lbl_80472690[];
extern const char lbl_804726A4[];
extern const char lbl_804726B8[];
extern const char lbl_804726D0[];
extern const char lbl_804726E4[];
extern const char lbl_804726F8[];
extern const char lbl_8047270C[];
extern const char lbl_80472720[];
extern const char lbl_80472730[];
extern const char *TObjEneGibbles__model_filenames[2];
extern const char *TObjEneGibbles__motion_names_and_resource_descriptor[11];
extern const char *lbl_804E286C[2];
extern const char *gibbles_motion_name_table[11];

__declspec(section ".data") const char *TObjEneGibbles__model_filenames[2] = {
    lbl_80472628, NULL,
};
const char *TObjEneGibbles__motion_names_and_resource_descriptor[11] = {
    lbl_80472638, lbl_80472650, lbl_80472668, lbl_8047267C,
    lbl_80472690, lbl_804726A4, lbl_804726B8, lbl_804726D0,
    lbl_804726E4, lbl_804726F8, NULL,
};
BmlResourceDescriptor lbl_804E285C = {
    lbl_8047270C, TObjEneGibbles__model_filenames,
    TObjEneGibbles__motion_names_and_resource_descriptor, 1, 10,
};
__declspec(section ".data") const char *lbl_804E286C[2] = {
    lbl_80472720, NULL,
};
const char *gibbles_motion_name_table[11] = {
    lbl_80472638, lbl_80472650, lbl_80472668, lbl_8047267C,
    lbl_80472690, lbl_804726A4, lbl_804726B8, lbl_804726D0,
    lbl_804726E4, lbl_804726F8, NULL,
};
BmlResourceDescriptor lbl_804E28A0 = {
    lbl_80472730, lbl_804E286C, gibbles_motion_name_table, 1, 10,
};
TObjMotionAction gibbles_motion_actions[10] = {
    {1, 0, 8, 0.3f, 1},
    {1, 0, 9, 0.5f, 1},
    {2, 0, 0, 0.7f, 4},
    {2, 0, 7, 0.6f, 4},
    {1, 0, 5, 0.3f, 4},
    {2, 6, 4, 0.7f, 4},
    {1, 0, 6, 0.7f, 4},
    {1, 0, 3, 0.8f, 0x20},
    {2, 0, 1, 0.8f, 8},
    {3, 0, 2, 0.7f, 0x10},
};
GibblesMovementParameters gibbles_movement_parameters = {
    250.0f, 1.25f, 0x400, 0, 100, 0, 0,
};
CollisionBody gibbles_collision_body_templates[3] = {
    {{0.0f, 15.0f, 0.0f}, 15.0f, 0.0f, 0, 0x8003, {0.0f, 0.0f, 0.0f}, 0.0f},
    {{0.0f, 0.0f, 0.0f}, 15.0f, 0.0f, 0, 0x8003, {0.0f, 0.0f, 0.0f}, 0.0f},
    {{0.0f, 0.0f, 0.0f}, 30.0f, 0.0f, 0, 0x8003, {0.0f, 0.0f, 0.0f}, 0.0f},
};

}
void gibbles_render_node_callback(void);
extern s32 saved_model_render_flags;
extern s32 saved_chunk_polygon_flags_and_mask;
extern s32 saved_chunk_polygon_flags_or_mask;
extern s32 TObjEneGibbles__render_node_index;
extern s32 TObjEneGibbles__render_rotation_x;
extern s32 chunk_polygon_flags_or_mask;
extern s32 chunk_polygon_flags_and_mask;
extern s32 model_render_flags;
extern const f32 lbl_805DE884;
extern s32 lbl_80472768[];
extern s32 lbl_80472774[];

extern s32 lbl_805D5870;
extern const f32 lbl_805DE824;
void move_with_wall_slide(u8 *arg0);
int initialize_enemy_photon_effect(void *p);

extern "C" {

extern const f32 lbl_805DE818;
extern const f32 lbl_805DE820;
s16 TObjPlayer__sub_800A776C(void *p);


extern const f32 lbl_805DE83C;
extern const f32 lbl_805DE840;
extern const f32 lbl_805DE844;
extern const f32 lbl_805DE848;
extern const f32 lbl_805DE84C;
extern const f32 lbl_805DE850;
extern const f32 lbl_805DE854;

extern s32 actor_frame_tick;
s32 obj_is_hit_receivable(TObjChara *);

extern s32 actor_frame_tick;
s32 obj_is_hit_receivable(TObjChara *);

}

extern "C" {



}

void TObjEneGibbles::set_min_clamped_entry_value(s32 index, f32 value) {
    if (value < lbl_805DE7E0) {
        value = lbl_805DE7E0;
    }
    gibbles_motion_actions[index].speed = value;
}

void TObjEneGibbles::fn_802D7A54() {
    s16 t;
    s16 u;
    u32 r;
    TObjEneGibbles *self = this;
    if ((get_main_phase() == 0xF || is_split_screen() == 0) && (r = (u32)get_player_by_client_id(local_client_id)) != 0) {
        t = get_room__8TObjBaseFv((void *)r);
        u = get_room__8TObjBaseFv(self);
        if (u == t) {
            TCameraCtrl__sub_8006A044(0x1E, lbl_805DE7E0);
        }
    }
}

s32 TObjEneGibbles::spawn_ground_impact_effects(const Vec *pos, f32 farg0) {
    Vec point;
    f32 y;
    CsnGroundHit *hit;
    TParticleCtrl *particle;
    if (farg0 <= TObjEneGibbles__data_805DE7E4) {
        return 0;
    }
    VecCopy(&point, pos);
    y = point.y;
    point.y = y + TObjEneGibbles__data_805DE7E8;
    hit = csnVectorUnder(&point, &m_120, 5, y);
    if (hit != NULL && (hit->flags & 4)) {
        particle = (TParticleCtrl *)spawn_particle_effect(&hit->surface->point_38, 0x49);
        if (particle != NULL) {
            attach_particle_model((u8 *)particle, TParticleCtrl::get_particle_model(2), TParticleCtrl::get_instance(), 0, 1, TObjEneGibbles__data_805DE7EC);
            particle->set_scale(farg0, TObjEneGibbles__data_805DE7EC);
        }
        particle = (TParticleCtrl *)spawn_particle_effect(&hit->surface->point_38, 0xA4);
        if (particle != NULL) {
            particle->set_scale(farg0, lbl_805DE7F0);
        }
        return 1;
    }
    return 0;
}

s32 TObjEneGibbles::spawn_ground_contact_effect() {
    Vec point;
    VecCopy(&point, &position);
    f32 y = point.y;
    point.y = y + TObjEneGibbles__data_805DE7E8;
    CsnGroundHit *hit = csnVectorUnder(&point, &m_120, 0x15, y);
    if (hit != NULL) {
        if (hit->flags & 4) {
            spawn_ground_impact_effects(&position, TObjEneGibbles__data_805DE7F4);
            return 0;
        }
        spawn_particle_effect(&position, 0x20E);
        return 1;
    }
    return 2;
}

void TObjEneGibbles::play_distance_sound() {
    if (this->is_passing_frame(TObjEneGibbles__data_805DE7F8)) {
        if (spawn_ground_impact_effects(&position, TObjEneGibbles__data_805DE7F4)) {
            TObjEneGibbles__sub_800D8988(&position);
            return;
        }
        play_sound_effect(resolve_sound_id(0x3A83D), &position, 0, 0);
        return;
    }
    if (this->is_passing_frame(lbl_805DE7FC)) {
        if (spawn_ground_impact_effects(&position, TObjEneGibbles__data_805DE7F4)) {
            TObjEneGibbles__sub_800D8988(&position);
            return;
        }
        play_sound_effect(resolve_sound_id(0x3A83E), &position, 0, 0);
        return;
    }
    if (this->is_passing_frame(lbl_805DE800)) {
        if (spawn_ground_impact_effects(&position, TObjEneGibbles__data_805DE7F4)) {
            TObjEneGibbles__sub_800D8988(&position);
            return;
        }
        play_sound_effect(resolve_sound_id(0x3A83F), &position, 0, 0);
    }
}

void TObjEneGibbles::play_ground_contact_sound() {
    if (this->is_passing_frame(lbl_805DE804) || this->is_passing_frame(lbl_805DE808)) {
        if (spawn_ground_impact_effects(&position, TObjEneGibbles__data_805DE7F4)) {
            TObjEneGibbles__sub_800D8988(&position);
            return;
        }
        play_sound_effect(resolve_sound_id(0x3A82B), &position, 0, 0);
    }
}

void TObjEneGibbles::fn_802D7E3C() {
      }

void TObjEneGibbles::update_shadow_height() {
    bodies->offset.y = body_center_position.y - position.y;
}

void TObjEneGibbles::update_position() {
    VecCopy(body_center(), &position);
    body_center_position.y += TObjEneGibbles__data_805DE7E8;
    switch (mode) {
    case 2:
    case 6:
    case 10:
        body_center_position.y += height_offset;
        break;
    }
}

void TObjEneGibbles::render_and_get_joint_pos(Vec *result, s32 joint) {
    set_motion_packed_rotation();
    push_matrix_from(identity_matrix);
    post_translate_matrix(&position);
    rotate_matrix_y(0, rotation_y);
    scale_matrix_vec3(0, (u8 *)&scale);
    set_motion_packed_rotation();
    calc_joint_matrices(frame);
    clear_motion_packed_rotation();
    pop_matrix();
    push_matrix_from(anim_model_matrix_array[joint]);
    Vec origin = gibbles_joint_zero_vec;
    matrix_mult_vec(0, &origin, result);
    pop_matrix();
    clear_motion_packed_rotation();
}

u32 TObjEneGibbles::resolve_sound_id(u32 sound_id) {
  s32 area;
  u32 pvVar2;
  area = get_current_floor_area();
  if (sound_id == 0x3a83d) {
    pvVar2 = (u32)(0x4003a321);
    if (area != AREA_TOWER) {
      pvVar2 = sound_id;
    }
  }
  else if (sound_id == 0x3a83e) {
    pvVar2 = (u32)(0x4003a322);
    if (area != AREA_TOWER) {
      pvVar2 = sound_id;
    }
  }
  else if (sound_id == 0x3a83f) {
    pvVar2 = (u32)(0x4003a323);
    if (area != AREA_TOWER) {
      pvVar2 = sound_id;
    }
  }
  else {
    pvVar2 = (u32)(remap_sound_for_area(sound_id));
  }
  return pvVar2;
}

void TObjEneGibbles::fn_802D8034() {}

void TObjEneGibbles::sync_state() {
    switch (state_code) {
    case 0:
        break;
    default:
        update_move_state();
    case 0x107:
    case 0x10E:
        if (flags & 4) {
            if (last_state_code != state_code) {
                last_state_code = state_code;
            }
        }
        break;
    }
}

void TObjEneGibbles::update_move_state() {
    s16 reference = reference_388;
    s16 current = m_388;
    if (reference == current) {
        state_code = 0x101;
        return;
    }
    if (lbl_805DE80C * (f32)reference < (f32)current) {
        state_code = 0x102;
        return;
    }
    if (current > 0) {
        state_code = 0x103;
        return;
    }
    state_code = 0;
}

void TObjEneGibbles::sub_802D8140() {
    Vec point;
    switch (phase) {
    case 0:
        phase = 1;
        state_distance = TObjEneGibbles__data_805DE7E4;
        apply_actor_gravity(this, NULL, TObjEneGibbles__data_805DE7E4);
        play_sound_effect(resolve_sound_id(0x3A333), &position, 0, 0);
        return;
    case 1:
        this->advance_animation();
        if (motion_flags & 0x10) {
            phase = 4;
            point.x = TObjEneGibbles__data_805DE7E4;
            point.y = TObjEneGibbles__data_805DE7E4;
            point.z = lbl_805DE810;
            rotate_xz_pair_by_angle(&point.x, &point.z, rotation_y, TObjEneGibbles__data_805DE7E4);
            vec3_add_to(&point.x, &position);
            TObjPlayer__sub_800D93C4((s32)&point, 10);
            ((TObjPlayer *)&point)->spawn_effect_at_ground(0x46);
        }
    case 2:
        return;
    case 4:
        position.y -= lbl_805DE7E0;
        state_distance += lbl_805DE7E0;
        if (state_distance > lbl_805DE814) {
            phase = 3;
            return;
        }
        break;
    case 3:
        queue_destruction();
        break;
    }
}

void TObjEneGibbles::vfunc_63() {
    if (mode != 9) {
        mode = 9;
        phase = 0;
        requested_action = 9;
        bodies->flags &= ~1;
        distribute_experience_and_request_drop();
        send_entity_set_flags();
    }
}

void TObjEneGibbles::update_action_state() {
    this->advance_animation();
    clamp_angle(0);
    switch (phase) {
    case 2:
        break;
    case 0:
        phase = 1;
        apply_actor_gravity(this, NULL, TObjEneGibbles__data_805DE7E4);
        play_sound_effect(resolve_sound_id(0x3AD34), &position, 0, 0);
        break;
    case 1:
        movement_velocity.z = TObjEneGibbles__data_805DE7E4;
        movement_velocity.x = TObjEneGibbles__data_805DE7E4;
        apply_actor_gravity(this, NULL, TObjEneGibbles__data_805DE7E4);
        if (action_flags != 8) {
            phase = 3;
        }
        break;
    case 3:
        if (!(actorFlags & 0x800000)) {
            apply_actor_gravity(this, NULL, TObjEneGibbles__data_805DE7E4);
        }
        actorFlags &= ~0x600;
        bodies->flags &= ~0x04000000;
        referenceHp = hp;
        if (random_ratio() < recoil_jump_probability) {
            mode = 6;
            phase = 0;
            requested_action = 4;
            flags |= 0x90;
        }
        break;
    }
    check_object_collisions();
    check_enemy_body_collisions(this);
    update_enemy_collision_flags();
    minimap_render_dot(&position, -0x5DB4, 1, 0);
    submit_cursor_candidate(this, -1);
    actorFlags &= ~0x200000;
}

void TObjEneGibbles::vfunc_62() {
    TObjEneGibbles *self = this;
    if (self->mode != 8) {
        if (self->flags & 0x100) {
            s32 i;
            self->referenceHp = self->hp;
            self->actorFlags &= ~0x200;
            self->m_2dc = 0;
            for (i = 0; i < self->body_count; i++) {
                self->bodies[i].flags &= ~0x04000000;
            }
        } else {
            Vec v;
            u32 pl = (u32)get_player_by_client_id(self->m_2d4);
            if (pl != 0) {
                VecCopy(&v, (const Vec *)(((TObjChara *)pl)->body_center()));
                subtract_vector(&v, (u8 *)&self->body_center_position.x);
                angle_difference_abs(self->rotation_y, (s32) (TObjEneGibbles__data_80472798 * atan2_float(v.x, v.z)));
            }
            self->mode = 8;
            self->requested_action = 8;
            self->phase = 0;
            self->actorFlags &= 0xF9DBFFFF;
        }
    }
    self->bodies->flags |= 1;
}

#pragma push
#pragma fp_contract on
void TObjEneGibbles::fn_802D8580() {
    TObjEneGibbles *self = this;
    this->advance_animation();
    self->clamp_angle(0);
    if (!(self->actorFlags & 0x800000)) {
        apply_actor_gravity(self, (s32 *)0, TObjEneGibbles__data_805DE7E4);
    }
    switch (self->phase) {
    case 0:
        self->phase = 1;
        apply_actor_gravity(self, (s32 *)0, TObjEneGibbles__data_805DE7E4);
        if (self->m_3b0 != NULL) {
            self->m_388 = (s16)((f32)self->m_388 - lbl_805DE818 * (f32)(((TObjPlayer *)self->m_3b0)->get_field_2c8() + ((TObjChara *)self->m_3b0)->get_actor_attack_params_atp_min() + TObjPlayer__sub_800A776C(self->m_3b0) - self->m_2ce));
            if (self->m_388 <= 0) {
                self->m_388 = 0;
                self->flags |= 8;
            }
        }
        self->actorFlags |= 0x04000000;
        play_sound_effect(self->resolve_sound_id(0x3A330), (u8 *)&self->position, 0, 0);
        break;
    case 1:
        if (self->is_passing_frame(TObjEneGibbles__data_805DE81C) != 0) {
            self->state_code = 0x107;
        }
        if (self->is_passing_frame(lbl_805DE820) != 0) {
            self->actorFlags &= 0xFBFFFEFF;
            self->flags &= ~0x20;
            if (self->test_flag_256() != 0) {
                self->phase = 0;
                self->frame = TObjEneGibbles__data_805DE7E4;
            } else {
                self->phase = 3;
            }
            self->update_move_state();
        }
        break;
    case 3:
    default:
        self->actorFlags &= 0xFBFFFEFF;
        self->flags &= ~0x20;
        break;
    }
    self->check_object_collisions();
    check_enemy_body_collisions(self);
    self->update_enemy_collision_flags();
    minimap_render_dot((u8 *)&self->position, -0x5DB4, 1, 0);
    self->actorFlags &= 0xFFDFFFFF;
}
#pragma pop

void TObjEneGibbles::vfunc_61() {
    s16 current_mode = mode;
    if (current_mode != 7 && current_mode != 6) {
        mode = 7;
        phase = 0;
        requested_action = 7;
    }
    bodies->flags |= 1;
    actorFlags &= 0xF99BFFFF;
}

int TObjEneGibbles::test_flag_256() {
    TObjEneGibbles *self = this;
    Vec v;
    u8 *pl;
    s32 i;
    s32 flags;
    flags = this->flags;
    if (flags & 0x20) {
        return 1;
    }
    if ((flags & 4) && this->mode != 6 && this->m_388 > 0) {
        for (i = 0; i < registered_player_count; i++) {
            pl = (u8 *)TObjPlayer::get_player_data(i);
            if (pl != NULL && !(((TObjPlayer *)pl)->actorFlags & 0x800)
                && calc_distance_to_client__10TObjPlayerFlUsUl(self, i, &v) < lbl_805DE824
                && angle_difference_abs(this->rotation_y, (s32) (TObjEneGibbles__data_80472798 * atan2_float(v.x, v.z))) < 0x2AAA
                && test_action_mask__10TObjPlayerFl(pl, 0xE0) != 0) {
                VecCopy(&v, (const Vec *)((Vec *) (body_center())));
                subtract_vector(&v, ((TObjChara *)pl)->body_center());
                if (angle_difference_abs(((TObjPlayer *)pl)->rotation_y, (s32) (TObjEneGibbles__data_80472798 * atan2_float(v.x, v.z))) < 0x2AAA) {
                    this->m_3b0 = pl;
                    this->flags |= 0x20;
                    return 1;
                }
            }
        }
    }
    return 0;
}

#pragma push
#pragma opt_loop_invariants off
void TObjEneGibbles::sub_802D8984() {
    TObjEneGibbles *o = this;
    if (o->targetId < 0x1000) {
        TObjPlayer *p = get_player_by_client_id(o->targetId);
        if (p != NULL && p->get_floor() == get_current_floor()) {
            o->target = (u8 *)p;
        } else {
            o->target = NULL;
        }
    } else if (o->targetId < 0x4000) {
        o->target = (u8 *)get_enemy_entity(o->targetId);
    } else {
        o->targetId = 0xFFFF;
        o->target = NULL;
    }
    o->advance_animation();
    o->clamp_angle(0);
    switch (o->phase) {
    case 2:
        break;
    case 0:
        o->height_offset = TObjEneGibbles__data_805DE7E4;
        if (!(o->actorFlags & 0x800000)) {
            apply_actor_gravity(o, NULL, TObjEneGibbles__data_805DE7E4);
        }
        o->phase_frames = 0;
        if (o->flags & 0x80) {
            o->wait_frames = TObjEneGibbles__ai_parameters->jump_wait_frames;
            o->set_min_clamped_entry_value(6, TObjEneGibbles__ai_parameters->jump_animation_speed);
        } else {
            o->wait_frames = TObjEneGibbles__ai_parameters->jump_wait_frames;
            o->set_min_clamped_entry_value(6, TObjEneGibbles__ai_parameters->jump_animation_speed);
        }
        o->phase = 4;
        o->actorFlags &= 0xF9FFFFFF;
        o->flags &= ~0x80;
        o->flags |= 0x100;
        break;
    case 4:
        o->phase_frames++;
        if (o->phase_frames >= o->wait_frames) {
            if (o->target != NULL) {
                Vec v;
                Vec t = *((TObjChara *)o->target)->body_center();
                if (select_enemy_destination(o, &t, 1) != 0) {
                    f32 dist;
                    o->phase = 1;
                    {
                        Vec q = *o->body_center();
                        copy_position_if_valid__10TObjPlayerFii((s32)o, (s32)&q);
                    }
                    VecCopy(&v, o->destination());
                    subtract_vector(&v, o->body_center());
                    dist = newton_sqrtf(v.x * v.x + v.z * v.z);
                    dist -= TObjEneGibbles__data_805DE7E8;
                    calc_velocity_toward_destination(o, *(Vec *)&o->m_290, *o->destination(), lbl_805DE828 * dist);
                    play_sound_effect(o->resolve_sound_id(0x3A82F), &o->position, 0, 0);
                    o->vertical_step = lbl_805DE82C;
                    o->requested_action = 5;
                    o->actorFlags |= 0x06000000;
                    o->bodies->flags &= ~1;
                    goto done;
                }
            }
            enemy_set_heading_velocity(TObjEneGibbles__data_805DE7E4, o, o->rotation_y);
            o->flags &= ~0x100;
            o->mode = 3;
            o->phase = 0;
            o->requested_action = 1;
            o->actorFlags &= 0xF9FBFFFF;
        done:
            o->spawn_ground_contact_effect();
        }
        submit_cursor_candidate(o, -1);
        break;
    case 1:
        if (o->frame >= TObjEneGibbles__data_805DE7F8) {
            move_with_wall_slide((u8 *)o);
            o->height_offset += o->vertical_step;
            if (o->frame >= lbl_805DE814) {
                o->vertical_step -= TObjEneGibbles__data_805DE830;
            } else {
                o->vertical_step -= lbl_805DE80C;
            }
        }
        if (o->is_passing_frame(o->frame_count - TObjEneGibbles__data_805DE7EC - o->play_speed) != 0) {
            o->phase = 3;
            o->height_offset = TObjEneGibbles__data_805DE7E4;
            switch (o->apply_landing_area_attack()) {
            case 0:
                TObjEneGibbles__sub_800D8988(&o->position);
                break;
            case 1:
            default:
                play_sound_effect(o->resolve_sound_id(0x3AD32), &o->position, 0, 0);
                break;
            }
            o->actorFlags &= 0xF9FFFFFF;
            o->bodies->flags |= 1;
            o->flags &= ~0x10;
            o->requested_action = 6;
            o->fn_802D7A54();
        }
        break;
    case 3:
        if (!(o->actorFlags & 0x800000)) {
            apply_actor_gravity(o, NULL, TObjEneGibbles__data_805DE7E4);
        }
        if (o->is_passing_frame(o->frame_count - TObjEneGibbles__data_805DE7EC - o->play_speed) != 0) {
            o->actorFlags &= ~0x200000;

            enemy_set_heading_velocity(TObjEneGibbles__data_805DE7E4, o, o->rotation_y);
            o->flags &= ~0x100;
            o->mode = 3;
            o->phase = 0;
            o->requested_action = 1;
            o->actorFlags &= 0xF9FBFFFF;

        }
        submit_cursor_candidate(o, -1);
        break;
    }
    minimap_render_dot(&o->position, -0x5DB4, 1, 0);
}
#pragma pop

#pragma push
#pragma opt_loop_invariants off
void TObjEneGibbles::fn_802D8E8C() {
    TObjEneGibbles *self = this;
    u32 p;
    u16 id;
    id = this->targetId;
    if (id < 0x1000) {
        p = (u32)get_player_by_client_id(id);
        if (p != 0 && ((TObjPlayer *)p)->get_floor() == get_current_floor()) {
            target = (u8 *)p;
        } else {
            target = NULL;
        }
    } else if (id < 0x4000) {
        target = (u8 *)get_enemy_entity(id);
    } else {
        this->targetId = 0xFFFF;
        target = NULL;
    }
    bodies->flags |= 1;
    this->actorFlags &= 0xF9FBFFFF;
    play_ground_contact_sound();
    self->advance_animation();
    self->clamp_angle(0);
    switch (this->phase) {
    case 0:
        this->phase = 1;
        apply_actor_gravity((TObjEnemy *)self, NULL, TObjEneGibbles__data_805DE7E4);
        this->flags |= 0x100;
        play_sound_effect(((TObjEneGibbles*)(self))->resolve_sound_id((u32)(0x3AD2E)), (u8 *)&position, 0, 0);
        break;
    case 1:
    case 2:
        if (!(this->actorFlags & 0x800000)) {
            apply_actor_gravity((TObjEnemy *)self, NULL, TObjEneGibbles__data_805DE7E4);
        }
        if (self->is_passing_frame(lbl_805DE834) != 0) {
            play_sound_effect(((TObjEneGibbles*)(self))->resolve_sound_id((u32)(0x3A82D)), body_center(), 0, 0);
        }
        if (self->is_passing_frame(lbl_805DE838) != 0) {
            this->phase = 2;
        }
        if (this->phase == 1) {
            self->attack_from_joint_31(1, get_attack_params_atp_min(gibbles_combat_stat_entries[2]));
        }
        if (this->action_flags != 4) {
            this->phase = 3;
            this->attack_count++;
        }
        break;
    case 3:
        self->update_move_state();
        if (this->attack_count >= 2) {
            this->attack_count = 0;
            this->flags &= ~0x108;
        }
        this->actorFlags &= 0xFFDFFFFF;
        break;
    }
    self->check_object_collisions();
    check_enemy_body_collisions(self);
    self->update_enemy_collision_flags();
    minimap_render_dot((u8 *)&position, -0x5DB4, 1, 0);
    submit_cursor_candidate(self, -1);
}
#pragma pop

#pragma defer_codegen on

void TObjEneGibbles::sub_802DBC94(s32 i) {
    model = (void *)TObjEneGibbles__resource_bundle->models[i].model;
    texlist = TObjEneGibbles__resource_bundle->models[i].m_c;
}

void *TObjEneGibbles::get_center() {
    return body_center();
}

TObjEneGibbles::TObjEneGibbles(TObject *parent, void *set_data) : TObjEnemy(parent) {
    s32 i;
    m_name = lbl_805D3F60;
    apply_set_data(set_data);
    initialize_position_copies();
    scale.x = scale.y = scale.z = TObjEneGibbles__data_805DE7EC;
    init_params();
    mode = 0;
    phase = 0;
    variant = 0;
    set_param(0x3D);
    subtype = 0;
    sub_802DBC94(variant);
    action_table = gibbles_motion_actions;
    set_action_table(action_table);
    motion_list = TObjEneGibbles__resource_bundle->motions;
    requested_action = 0;
    set_animation(requested_action);
    set_field_b8(requested_action);
    init_collision_body_parts(this, gibbles_collision_body_templates, 1);
    attack_index = 0;
    attack_count = 0;
    movementParameters = (void *)&gibbles_movement_parameters;
    bind_enemy_combat_stats((u8 *)gibbles_boss_stat_handle, (u8 *)(gibbles_combat_stat_entries[attack_index]), (u8 *)gibbles_combat_stats_handle);
    referenceHp = hp;
    update_position();
    update_shadow_height();
    copy_body_to_center();
    initialize_enemy_photon_effect(this);
    flags = 1;
    m_3b0 = NULL;
    render_angle = 0;
    add_flags_2e4(0x11);
    actorFlags |= 0x06040000;
    state_code = 0x101;
    last_state_code = 0x101;
    attack_body = new TObjCollidable(NULL);
    init_collision_body_parts(attack_body, &gibbles_collision_body_templates[1], 1);
    m_3b8 = new TObjCollidable(NULL);
    init_collision_body_parts(m_3b8, &gibbles_collision_body_templates[2], 1);
    material_fade.reset_obstruction_fade();
    for (i = 0; i < 4; i++) {
        camera_fades[i].activate_and_dispatch();
    }
    clear_lobby_object_state();
}

TObjEneGibbles::~TObjEneGibbles() {
    if (attack_body != NULL) {
        free_collision_body_parts(attack_body);
        delete attack_body;
        attack_body = NULL;
    }
    if (m_3b8 != NULL) {
        free_collision_body_parts(m_3b8);
        delete m_3b8;
        m_3b8 = NULL;
    }
    free_collision_body_parts(this);
}

void TObjEneGibbles::load_resources() {
    if (is_split_screen() != 0) {
        TObjEneGibbles__resource_bundle = new BmlResource(1, &lbl_804E28A0, 0, 0, 0);
    } else {
        TObjEneGibbles__resource_bundle = new BmlResource(1, &lbl_804E285C, 0, 0, 0);
    }
    TObjEneGibbles__render_node_index = 0;
    TObjEneGibbles__render_rotation_x = 0;
    gibbles_combat_stat_entries = (void **)mem_alloc(3 * sizeof(void *));
    gibbles_boss_stat_handle = (s32)get_battle_base_stats(0x3D);
    gibbles_combat_stat_entries[0] = get_battle_attack_params(0x3D);
    gibbles_combat_stat_entries[2] = get_battle_attack_params(0x3E);
    gibbles_combat_stat_entries[1] = get_battle_attack_params(0x3F);
    gibbles_combat_stats_handle = (s32)get_battle_resistance_params(0x3D);
    TObjEneGibbles__ai_parameters = (GibblesAiParameters *)get_battle_movement_params(0x3D);
    NpcAnimationBinding binding = gibbles_resource_binding_desc;
    binding.motions = TObjEneGibbles__resource_bundle->motions;
    NpcModelRegistry::register_animated_chunk(0x44, (void *)TObjEneGibbles__resource_bundle->models->model,
        (void *)TObjEneGibbles__resource_bundle->models->m_c, &binding,
        gibbles_collision_body_templates[0].radius, TObjEneGibbles__data_805DE7E4);
}

void TObjEneGibbles::free_static() {
    if (gibbles_combat_stat_entries != NULL) {
        mem_free((void*)gibbles_combat_stat_entries);
        gibbles_combat_stat_entries = NULL;
    }
    if ((u32) TObjEneGibbles__resource_bundle != 0U) {
        delete TObjEneGibbles__resource_bundle;
        TObjEneGibbles__resource_bundle = NULL;
    }
}

void *TObjEneGibbles::create(void *set_data) {
    TObjControl *control = new TObjControl((TObject *)tl_04);
    return new TObjEneGibbles(control, set_data);
}

void TObjEneGibbles::init_params() {
    s16 value = (s16)(100.0f + parameters[0]);
    m_388 = value;
    reference_388 = value;
    target_class_index = (s32)parameters[1];
    s32 index = target_class_index;
    if (index < 0) {
        target_class_index = 0;
    } else if (index > 8) {
        target_class_index = 8;
    }
    target_class_mask = 0;
    target_class_mask |= 1 << target_class_index;
    jump_probability = parameters[2];
    recoil_jump_probability = parameters[3];
}

void TObjEneGibbles::run_task() {
    u8 *candidate;
    if (check_demo_mode() == 1) {
        fn_802D7E3C();
        return;
    }
    {
        switch (this->mode) {
        case 0:
            this->init_state();
            break;
        case 1:
            this->update_spawn_state();
            break;
        case 2:
            this->update_death_sequence();
            break;
        case 3:
            this->sub_802DA0BC();
            break;
        case 4:
            fn_802D9110();
            break;
        case 5:
            fn_802D8E8C();
            break;
        case 6:
            this->sub_802D8984();
            break;
        case 7:
            fn_802D8580();
            break;
        case 8:
            this->update_action_state();
            break;
        case 9:
            this->sub_802D8140();
            break;
        case 10:
            this->sub_802DA7A4();
            break;
        case 11:
            this->update_wander();
            break;
        }
    }
    candidate = (u8 *)(this->target);
    if ((candidate != NULL) && (((TObjChara *)candidate)->actorFlags & 0x02000800)) {
        this->attack_count = 0;
        this->actorFlags = (s32) (this->actorFlags & 0xFFDFFFFF);
        flags &= 0xFFFF0000;
        this->target = NULL;
    }
    this->update_position();
    this->update_shadow_height();
    copy_body_to_center();
    this->sync_state();
    this->m_2b4 = (f32) (this->m_2b4 + TObjEneGibbles__data_805DE7EC);
}

void TObjEneGibbles::render() {
    TObjEneGibbles *self = this;
    Vec v;
    s32 fade;
    s32 vis;
    s32 cam;
    cam = 0;
    if (is_split_screen() != 0) {
        cam = get_camera_mode__11TCameraCtrlFv();
    }
    if (get_current_floor_area() == AREA_TOWER) {
        vis = classify_actor_view_detail(600.0f, 600.0f, 30.0f);
    } else {
        vis = classify_actor_view_detail(lbl_805DE884, 600.0f, 30.0f);
    }
    if (vis != 0) {
        camera_fades[cam].update();
        fade = camera_fades[cam].updateFromCamera(&self->body_center_position.x);
        select_actor_lighting((s32)self);
        TObjFish::set_global_param(self->texlist);
        push_matrix_from(0);
        VecCopy(&v, (const Vec *)((Vec *)((u8 *)&self->position)));
        switch (self->mode) {
        case 2:
        case 6:
        case 10:
            v.y += self->height_offset;
            break;
        }
        translate_matrix_vec3(NULL, (u8 *)&v);
        rotate_matrix_y(0, self->rotation_y);
        scale_matrix_vec3(0, (u8 *)&self->scale);
        TObjEneGibbles__render_node_index = 0;
        TObjEneGibbles__render_rotation_x = self->render_angle;
        set_chunk_model_node_callback((s32)((void *)gibbles_render_node_callback));
        TObjPlayer::toggle_particle_effect();
        switch (self->mode) {
        case 0:
            break;
        case 1:
        case 2:
        case 10:
            if (material_fade.has_visible_opacity() != 0) {
                saved_model_render_flags = model_render_flags;
                saved_chunk_polygon_flags_and_mask = chunk_polygon_flags_and_mask;
                saved_chunk_polygon_flags_or_mask = chunk_polygon_flags_or_mask;
                model_render_flags |= 1;
                material_fade.set_flags_and_apply_damage_color();
                if (self->defer_render() == 0) {
                    self->draw();
                }
                material_fade.clear_flag_and_notify();
                chunk_polygon_flags_and_mask = saved_chunk_polygon_flags_and_mask;
                chunk_polygon_flags_or_mask = saved_chunk_polygon_flags_or_mask;
                model_render_flags = saved_model_render_flags;
            }
            break;
        default:
            if (fade != 0) {
                saved_model_render_flags = model_render_flags;
                saved_chunk_polygon_flags_and_mask = chunk_polygon_flags_and_mask;
                saved_chunk_polygon_flags_or_mask = chunk_polygon_flags_or_mask;
                camera_fades[cam].set_flags_and_apply_damage_color();
                if (self->defer_render() == 0) {
                    if (vis == 1) {
                        self->draw();
                    } else {
                        self->draw_motion_model();
                    }
                }
                camera_fades[cam].clear_flag_and_notify();
                chunk_polygon_flags_and_mask = saved_chunk_polygon_flags_and_mask;
                chunk_polygon_flags_or_mask = saved_chunk_polygon_flags_or_mask;
                model_render_flags = saved_model_render_flags;
            } else if (vis == 1) {
                self->draw();
            } else {
                self->draw_motion_model();
            }
            break;
        }
        TParticleCtrl::end_effect_render();
        set_chunk_model_node_callback((s32)NULL);
        pop_matrix();
        restore_scene_lighting();
        if (!(self->flags & 1)) {
            self->draw_ground_shadow(0, 0);
        }
    } else {
        self->update_position();
    }
}

void gibbles_render_node_callback(void) {
    if ((s32) TObjEneGibbles__render_node_index == 0x18) {
        rotate_matrix_x(0, TObjEneGibbles__render_rotation_x);
    }
    TObjEneGibbles__render_node_index += 1;
}

void TObjEneGibbles::clamp_angle(s32 arg1) {
    s32 target_rot;

    target_rot = arg1;
    if (target_rot < -0x238E) {
        target_rot = -0x238E;
    } else if (target_rot > 0x238E) {
        target_rot = 0x238E;
    }
    this->render_angle = lerp_angle_half(this->render_angle, target_rot);
}

void TObjEneGibbles::turn_toward_target() {
    Vec difference;
    VecCopy(&difference, ((TObjChara *)target)->body_center());
    subtract_vector(&difference, body_center());
    clamp_angle(angle_diff_s16(rotation_y, (s32)(TObjEneGibbles__data_80472798 * atan2_float(difference.x, difference.z))));
}

#pragma push
#pragma opt_common_subs off
void TObjEneGibbles::vfunc_28() {
    TObjEneGibbles *self = this;
    if (self->flags & 0x40) {
        self->targetId = 0xFFFF;
        self->target = NULL;
        return;
    }
    if (self->is_actor_cadence_frame(0x1E) == 0) {
        return;
    }
    if (self->obj_testFlags30(0x10) != 0) {
        s32 best_id;
        s32 i;
        u8 *p;
        s32 id;
        f32 best;
        f32 d;
        u16 tid;
        i = 0;
        best_id = 0xFFFF;
        Vec v = *(Vec *)lbl_80472768;
        best = ((GibblesMovementParameters *)self->movementParameters)->target_range * ((GibblesMovementParameters *)self->movementParameters)->target_range;
        for (; i < registered_player_count + lbl_805D5870; i++) {
            p = (u8 *)TObjPlayer::get_player_data(i);
            if (TObjPlayer::is_valid_and_active((u32)p) != 0 && p != (u8 *)self) {
                id = get_entity_id(p);
                if ((u16)id < 0x4000 && (u16)id != self->entity_id && !(((TObjChara *)p)->actorFlags & 0x02000800)) {
                    VecCopy(&v, ((TObjChara *)p)->body_center());
                    subtract_vector(&v, self->body_center());
                    d = v.x * v.x + v.z * v.z;
                    if (d < best && check_path_obstructed(self, ((TObjChara *)p)->body_center()) != 1) {
                        best_id = id;
                        best = d;
                    }
                }
            }
        }
        self->targetId = best_id;
        tid = self->targetId;
        if (tid < 0x1000U) {
            u8 *q = (u8 *)get_player_by_client_id(tid);
            if (q != NULL) {
                if (((TObjPlayer *)q)->get_floor() == get_current_floor()) {
                    self->target = q;
                    return;
                }
            }
            self->target = NULL;
            return;
        }
        if (tid < 0x4000U) {
            self->target = get_enemy_entity(tid);
        }
        return;
    }
    {
        s32 best_id2;
        s32 best_id;
        u8 *p;
        u8 *best_p2;
        u8 *best_p;
        s32 i;
        f32 best2;
        f32 best;
        f32 d;
        Vec v = *(Vec *)lbl_80472774;
        best_id = 0xFFFF;
        best_p2 = NULL;
        best_id2 = best_id;
        best_p = NULL;
        i = 0;
        best = ((GibblesMovementParameters *)self->movementParameters)->target_range * ((GibblesMovementParameters *)self->movementParameters)->target_range;
        best2 = best;
        for (; i < registered_player_count; i++) {
            p = (u8 *)TObjPlayer::get_player_data(i);
            if (p == NULL) continue;
            if ((u16)get_entity_id(p) >= 0x1000) continue;
            if (((TObjPlayer *)p)->get_floor() != get_current_floor()) continue;
            if (((TObjChara *)p)->actorFlags & 0x02000800) continue;
            VecCopy(&v, ((TObjChara *)p)->body_center());
            subtract_vector(&v, self->body_center());
            d = v.x * v.x + v.z * v.z;
            if ((((TObjPlayer *)p)->class_flags & self->target_class_mask) && d < best &&
                check_path_obstructed(self, ((TObjChara *)p)->body_center()) != 1) {
                best_id = get_entity_id(p);
                best = d;
                best_p = p;
            }
            if (d < best2 && check_path_obstructed(self, ((TObjChara *)p)->body_center()) != 1) {
                best_id2 = get_entity_id(p);
                best2 = d;
                best_p2 = p;
            }
        }
        if (best2 < lbl_805DE824 && best_p2 != NULL) {
            self->targetId = best_id2;
            self->target = best_p2;
            return;
        }
        if (best_p != NULL) {
            self->targetId = best_id;
            self->target = best_p;
            return;
        }
        if (best_p2 != NULL) {
            self->targetId = best_id2;
            self->target = best_p2;
            return;
        }
        self->targetId = 0xFFFF;
        self->target = NULL;
    }
}
#pragma pop

s32 TObjEneGibbles::update_action_hold_status() {
    TObjEneGibbles *self = this;
    if (TObjChara::update_action_hold_status() != 0) {
        switch (this->mode) {
        case 0:
        case 1:
        case 2:
        case 0xa:
            if (material_fade.advance_toward_max() == 1) {
                this->flags &= ~0x143;
                this->flags |= 4;
                this->mode = 3;
                this->phase = 0;
                this->requested_action = 1;
                self->obj_clearFlags30(0x06240000);
            }
            break;
        }
        return 1;
    }
    return 0;
}

s32 TObjEneGibbles::update_movement_status() {
    TObjEneGibbles *self = this;
    if (TObjChara::update_movement_status() != 0) {
        switch (this->mode) {
        case 0:
        case 1:
        case 2:
        case 0xa:
            if (material_fade.advance_toward_max() == 1) {
                this->flags &= ~0x143;
                this->flags |= 4;
                this->mode = 3;
                this->phase = 0;
                this->requested_action = 1;
                self->obj_clearFlags30(0x06240000);
            }
            break;
        }
        return 1;
    }
    return 0;
}

void TObjEneGibbles::vfunc_58() {
    TObjEneGibbles *self = this;
    CollisionBody *body;

    switch (this->mode) {
    case 0:
        if (material_fade.has_visible_opacity() != 0) {
            this->mode = 0xA;
            this->phase = 0;
            this->requested_action = 0;
            self->obj_clearFlags30(0x200000);
            obj_setFlags30(self, 0x06040000);
            flags &= 0xFFFF0000;
            body = bodies;
            body->flags = (s32) (body->flags & 0xFFFFFFFE);
        }
    case 6:
    case 11:
        return;
    case 10:
        if (!(this->flags & 0x40)) {
            this->mode = 0;
            return;
        }
        break;
    default:
        this->phase = 0;
        this->mode = 0xB;
        this->requested_action = 1;
        this->actorFlags = (s32) (this->actorFlags & 0xF99BFFFF);
        break;
    }
}

void TObjEneGibbles::init_state() {
    set_position_from(&home_position);
    refresh_collision_body_centers();
    actorFlags &= ~0x200000;
    actorFlags |= 0x06040000;
    bodies->flags &= ~1;
}

void TObjEneGibbles::update_wander() {
    this->advance_animation();
    if (target != NULL) {
        mode = 3;
        phase = 0;
        obj_clearFlags30(0x06240000);
        flags &= 0xFFFF0000;
        flags |= 4;
        bodies->flags |= 1;
    } else {
        flags &= ~4;
    }
    f32 home_range = 100.0f;
    GibblesMovementParameters *movement = (GibblesMovementParameters *)movementParameters;
    f32 turn_range = home_range;
    enemy_wander_home(movement->speed, home_range, turn_range, movement->turn_speed);
    refresh_collision_body_centers();
    check_object_collisions();
    check_enemy_body_collisions(this);
    update_enemy_collision_flags();
    obj_clearFlags30(0x200000);
    play_ground_contact_sound();
    minimap_render_dot(&position, -0x5DB4, 1, 0);
    submit_cursor_candidate(this, -1);
}

void TObjEneGibbles::sub_802DA7A4() {
    CollisionBody *body;
    actorFlags &= ~0x200000;
    actorFlags |= 0x06040000;
    this->flags = (s32) (this->flags & ~0x107);
    body = bodies;
    body->flags = (s32) (body->flags & 0xFFFFFFFE);
    this->advance_animation();
    switch (this->phase) {
    default:
    case 0:
        this->phase = 1;
        this->requested_action = 5;
        this->height_offset = (f32) TObjEneGibbles__data_805DE7E4;
        this->vertical_step = (f32) lbl_805DE874;
        apply_actor_gravity((TObjEnemy *)(this), NULL, TObjEneGibbles__data_805DE7E4);
        break;
    case 1:
        if (is_passing_frame( TObjEneGibbles__data_805DE7F8) != 0) {
            this->phase = 2;
            spawn_ground_contact_effect();
            play_sound_effect((int)(this->resolve_sound_id((u32)(0x3A82F))), &position, 0, 0);
            material_fade.reset_color();
        }
        apply_actor_gravity((TObjEnemy *)(this), NULL, TObjEneGibbles__data_805DE7E4);
        break;
    case 2:
        if (material_fade.decay_value_toward_floor() == 1) {
            this->phase = 3;
        } else {
            this->height_offset = (f32) (this->height_offset + this->vertical_step);
            this->vertical_step = (f32) (this->vertical_step - TObjEneGibbles__data_805DE830);
        }
        break;
    case 3:
        set_position_from(&home_position);
        this->update_prev_position();
        this->scale.z = (f32) TObjEneGibbles__data_805DE7EC;
        this->scale.y = (f32) TObjEneGibbles__data_805DE7EC;
        this->scale.x = (f32) TObjEneGibbles__data_805DE7EC;
        flags &= 0xFFFF0000;
        flags |= 1;
        break;
    }
    minimap_render_dot(&position, -0x5DB4, 1, 0);
}

void TObjEneGibbles::vfunc_59() {
    switch (mode) {
    default:
        if (flags & 4) {
            mode = 3;
            phase = 0;
            requested_action = 1;
            actorFlags &= 0xF9FBFFFF;
        } else if (flags & 1) {
            mode = 1;
            phase = 0;
            actorFlags |= 0x06040000;
        }
        bodies->flags |= 1;
        return;
    case 1:
        if (flags & 2) {
            mode = 2;
            phase = 0;
            actorFlags |= 0x06040000;
        }
        return;
    case 2:
        if (flags & 4) {
            mode = 3;
            phase = 0;
            requested_action = 1;
            actorFlags &= 0xF9FBFFFF;
            return;
        }
        break;
    case 3:
        if (flags & 3) {
            mode = 1;
            phase = 0;
            actorFlags |= 0x06040000;
            flags &= 0xFFFF0000;
            flags |= 1;
            bodies->flags |= 1;
            return;
        }
        break;
    }
}

void TObjEneGibbles::update_spawn_state() {
    TObjEneGibbles *self = this;

    actorFlags &= ~0x200000;
    actorFlags |= 0x06040000;
    bodies->flags = (s32) (bodies->flags & 0xFFFFFFFE);
    switch (this->phase) {
    case 0:
        this->phase = 1;
        apply_actor_gravity((TObjEnemy *)self, NULL, TObjEneGibbles__data_805DE7E4);
        return;
    case 1:
        if (horizontal_distance_squared((int) (((TObjChara *)target)->body_center()), (void *) (body_center())) < lbl_805DE870) {
            this->phase = 3;
        }
    case 2:
        return;
    case 3:
        flags &= 0xFFFF0000;
        flags |= 2;
        break;
    }
}

void TObjEneGibbles::update_death_sequence() {
    TObjEneGibbles *self = this;
    f32 end_frame;
    f32 end_frame_2;
    CollisionBody *body;

    actorFlags &= ~0x200000;
    actorFlags |= 0x06040000;
    body = bodies;
    body->flags = (s32) (body->flags & 0xFFFFFFFE);
    self->advance_animation();
    switch (this->phase) {
    case 2:
        break;
    case 0:
        this->phase = 1;
        this->requested_action = 5;
        material_fade.start_fade_in();
        this->height_offset = (f32) lbl_805DE868;
        this->vertical_step = (f32) TObjEneGibbles__data_805DE830;
        apply_actor_gravity((TObjEnemy *)(self), NULL, TObjEneGibbles__data_805DE7E4);
        break;
    case 1:
        if (material_fade.advance_toward_max() != 0) {
            this->height_offset = (f32) (this->height_offset - this->vertical_step);
            this->vertical_step = (f32) (this->vertical_step + TObjEneGibbles__data_805DE830);
        } else {
            this->frame = (f32) lbl_805DE86C;
        }
        end_frame = this->frame_count;
        if (this->is_passing_frame((end_frame - TObjEneGibbles__data_805DE7EC) - play_speed) != 0) {
            this->height_offset = (f32) TObjEneGibbles__data_805DE7E4;
            this->vertical_step = (f32) TObjEneGibbles__data_805DE7E4;
            switch (((TObjEneGibbles *)(self))->apply_landing_area_attack()) {
            case 0:
                TObjEneGibbles__sub_800D8988(&position);
                break;
            default:
            case 1:
                play_sound_effect(resolve_sound_id(0x3AD32), &position, 0, 0);
                break;
            }
            fn_802D7A54();
            this->phase = 3;
        }
        break;
    case 3:
        end_frame_2 = this->frame_count;
        if (this->is_passing_frame((end_frame_2 - TObjEneGibbles__data_805DE7EC) - play_speed) != 0) {
            flags &= 0xFFFF0000;
            this->flags = (s32) (this->flags | 4);
        }
        break;
    }
    minimap_render_dot(&position, -0x5DB4, 1, 0);
}

void TObjEneGibbles::sub_802DA0BC() {
    f32 d;
    s32 ok;
    bodies->flags |= 1;
    this->actorFlags &= 0xF9DBFFFF;
    if (this->target == NULL) {
        return;
    }
    switch (this->phase) {
    case 2:
        break;
    case 0: {
        Vec v = *((TObjChara *)target)->body_center();
        if (select_enemy_destination(this, &v, 7) != 0) {
            this->phase = 1;
            {
                Vec v2 = *(Vec *)(body_center());
                copy_position_if_valid__10TObjPlayerFii((s32)this, (s32)&v2);
            }
            apply_actor_gravity((TObjEnemy *)this, NULL, TObjEneGibbles__data_805DE7E4);
            state_distance = TObjEneGibbles__data_805DE7E4;
        } else {
            this->phase = 0;
            this->mode = 0xB;
            this->requested_action = 1;
            this->actorFlags &= 0xF99BFFFF;
        }
        break;
    }
    case 1:
        {
            f32 dt = TObjEneGibbles__ai_parameters->pursuit_step;
            state_distance += dt;
            Vec v = *((TObjChara *)target)->body_center();
            enemy_move_toward(this, ((GibblesMovementParameters *)movementParameters)->turn_speed, &v, 0, dt);
        }
        d = horizontal_distance_squared((int)&m_29c, (u8 *)&position);
        {
            Vec v = *((TObjChara *)target)->body_center();
            ok = select_enemy_destination(this, &v, 1);
        }
        if (d >= lbl_805DE860 && ok != 0) {
            this->flags |= 0x10;
        } else if (state_distance >= lbl_805DE864) {
            state_distance = TObjEneGibbles__data_805DE7E4;
            if (random_ratio() < this->jump_probability && ok != 0) {
                this->flags |= 0x10;
            } else {
                this->flags &= ~0x10;
            }
        } else {
            this->flags &= ~0x10;
        }
        {
            f32 r = ((GibblesMovementParameters *)movementParameters)->speed + bodies->radius;
            if (d < r * r) {
                this->phase = 3;
            }
        }
        break;
    case 3:
        this->flags &= ~0x10;
        this->phase = 0;
        break;
    }
    play_ground_contact_sound();
    this->advance_animation();
    turn_toward_target();
    check_object_collisions();
    check_enemy_body_collisions(this);
    update_enemy_collision_flags();
    minimap_render_dot((u8 *)&position, -0x5DB4, 1, 0);
    submit_cursor_candidate(this, -1);
}

s32 TObjEneGibbles::is_target_in_attack_range() {
    TObjEneGibbles *self = this;
    Vec v;
    f32 rad;
    f32 dist;
    s32 ang;
    u8 *obj;
    CollisionBody *sub;
    if (this->mode >= 3) {
        obj = this->target;
        if (obj != NULL && this->m_318 != 0 && !(((TObjChara *)obj)->actorFlags & 0x02000800)) {
            dist = calc_xz_distance_sq(self, obj, &v);
            ang = angle_difference_abs(this->rotation_y, (s32)(TObjEneGibbles__data_80472798 * atan2_float(v.x, v.z)));
            sub = ((TObjChara *)target)->bodies;
            if (sub != NULL) {
                rad = sub->radius;
            } else {
                rad = lbl_805DE834;
            }
            if (this->flags & 8) {
                this->attack_index = 2;
                if (dist <= (rad + ((AttackParams *)gibbles_combat_stat_entries[attack_index])->get_attack_range()) * (rad + ((AttackParams *)gibbles_combat_stat_entries[attack_index])->get_attack_range()) && ang <= ((AttackParams *)gibbles_combat_stat_entries[attack_index])->get_attack_angle()) {
                    return 1;
                }
            } else if (this->flags & 0x10) {
                this->attack_index = 1;
                if (dist <= (lbl_805DE85C + rad) * (lbl_805DE85C + rad) && ang <= 0xAAA) {
                    return 1;
                }
            } else {
                this->attack_index = 0;
                if (dist <= (rad + ((AttackParams *)gibbles_combat_stat_entries[attack_index])->get_attack_range()) * (rad + ((AttackParams *)gibbles_combat_stat_entries[attack_index])->get_attack_range()) && ang <= ((AttackParams *)gibbles_combat_stat_entries[attack_index])->get_attack_angle()) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

void TObjEneGibbles::vfunc_60() {
    TObjEneGibbles *self = this;
    Vec v;
    switch (this->attack_index) {
    case 0:
    default: {
        VecCopy(&v, (const Vec *)((Vec *) (((TObjChara *)target)->body_center())));
        subtract_vector(&v, body_center());
        f64 t = atan2_float(v.x, v.z);
        this->mode = 4;
        if ((s32) (TObjEneGibbles__data_80472798 * t) < 0x10) {
            this->phase = 1;
            this->requested_action = 2;
        } else {
            this->phase = 0;
            this->requested_action = 1;
        }
        break;
    }
    case 2:
        this->mode = 5;
        this->phase = 0;
        this->requested_action = 3;
        break;
    case 1:
        this->mode = 6;
        this->phase = 0;
        this->requested_action = 4;
        this->flags = (s32) (this->flags & 0xFFFFFF7F);
        break;
    }
    self->bind_enemy_combat_stats(NULL, (u8 *)(gibbles_combat_stat_entries[this->attack_index]), NULL);
    bodies->flags |= 1;
    this->actorFlags = (s32) (this->actorFlags & 0xF9FBFFFF);
    this->actorFlags = (s32) (this->actorFlags | 0x200000);
}

void TObjEneGibbles::slam_damage_players(s32 arg1) {
    Vec point;
    DirectAttackPayload attack;
    f32 distance;
    s32 i;
    TObjChara *player;
    if (arg1 == 0x35) {
        render_and_get_joint_pos(&point, 0x35);
    } else if (arg1 == 0x1F) {
        render_and_get_joint_pos(&point, 0x1F);
    } else {
        return;
    }
    point.y += lbl_805DE808;
    if (csnVecterUnder(&point, 0x16EF) != NULL) {
        if (spawn_ground_impact_effects(&point, lbl_805DE858) == 0) {
            point.y += TObjEneGibbles__data_805DE81C;
            spawn_particle_effect(&point, 0x64);
        }
        for (i = 0; i < lbl_805D5868; i++) {
            player = (TObjChara *)TObjPlayer::get_player_data(i);
            if (TObjPlayer::is_valid_and_active((u32)player) != 0 && (u16)get_entity_id(player) < 0x1000) {
                distance = horizontal_distance_squared((int)player->body_center(), &point);
                if (distance <= ((AttackParams *)gibbles_combat_stat_entries[0])->get_damage_radius() * ((AttackParams *)gibbles_combat_stat_entries[0])->get_damage_radius()) {
                    attack.kind = 0;
                    attack.power = get_attack_params_atp_min(gibbles_combat_stat_entries[0]);
                    f32 damage = player->receive_direct_attack(this, attack, NULL, -1, -1);
                    player->apply_knockback_from_attacker((u8 *)this, damage);
                }
            }
        }
    }
}

#pragma push
#pragma opt_loop_invariants off
s32 TObjEneGibbles::apply_landing_area_attack() {
    s32 i;
    TObjChara *player;
    for (i = 0; i < lbl_805D5868; i++) {
        player = (TObjChara *)TObjPlayer::get_player_data(i);
        if (TObjPlayer::is_valid_and_active((u32)player) != 0 && (u16)get_entity_id(player) < 0x1000) {
            f32 distance = horizontal_distance_squared((int)player->body_center(), &position);
            if (distance <= ((AttackParams *)gibbles_combat_stat_entries[1])->get_damage_radius() * ((AttackParams *)gibbles_combat_stat_entries[1])->get_damage_radius()) {
                DirectAttackPayload attack;
                attack.kind = 0;
                attack.power = get_attack_params_atp_min(gibbles_combat_stat_entries[1]);
                f32 damage = player->receive_direct_attack(this, attack, NULL, -1, -1);
                player->apply_knockback_from_attacker((u8 *)this, damage);
                if (damage > TObjEneGibbles__data_805DE7E4) {
                    obj_setFlags30(player, 0x600);
                }
            }
        }
    }
    return spawn_ground_contact_effect();
}
#pragma pop

#pragma push
#pragma opt_loop_invariants off
bool TObjEneGibbles::attack_from_joint_53(s32 trigger_hit_reaction, f32 power) {
    bool hit = false;
    s32 i;
    TObjCollidable *candidate;
    DirectAttackPayload attack;
    if (actor_frame_tick % 5 != 0) {
        return false;
    }
    render_and_get_joint_pos(&attack_body->position, 0x35);
    TObjPlayer::init_all_slots();
    this->attack_body->check_object_collisions();
    if (this->attack_body->bodies->flags & 0x80000) {
        for (i = 0; i < 16; i++) {
            candidate = (TObjCollidable *)TObjPlayer::get_battle_param(i);
            if (candidate == NULL) {
                break;
            }
            if (!obj_is_hit_receivable((TObjChara *)candidate)) {
                continue;
            }
            TObjChara *target = (TObjChara *)candidate;
            if (!target->select_melee_contact_body(this, TObjEneGibbles__data_805DE7EC)) {
                continue;
            }
            if (power <= TObjEneGibbles__data_805DE7E4) {
                power = target->receive_physical_attack(this, TObjEneGibbles__data_805DE7EC);
            } else {
                attack.kind = 0;
                attack.power = power;
                power = target->receive_direct_attack(this, attack, NULL, -1, -1);
            }
            target->apply_knockback_from_attacker((u8 *)this, power);
            if (trigger_hit_reaction == 1 && power > TObjEneGibbles__data_805DE7E4) {
                obj_setFlags30(target, 0x600);
                this->m_388 = (s16)(this->m_388 + power);
                this->state_code = 0x10e;
            }
            hit = true;
        }
    }
    return hit;
}
#pragma pop

#pragma push
#pragma opt_loop_invariants off
bool TObjEneGibbles::attack_from_joint_31(s32 trigger_hit_reaction, f32 power) {
    bool hit = false;
    s32 i;
    TObjCollidable *candidate;
    DirectAttackPayload attack;
    if (actor_frame_tick % 5 != 0) {
        return false;
    }
    render_and_get_joint_pos(&attack_body->position, 0x1F);
    TObjPlayer::init_all_slots();
    this->attack_body->check_object_collisions();
    if (this->attack_body->bodies->flags & 0x80000) {
        for (i = 0; i < 16; i++) {
            candidate = (TObjCollidable *)TObjPlayer::get_battle_param(i);
            if (candidate == NULL) {
                break;
            }
            if (!obj_is_hit_receivable((TObjChara *)candidate)) {
                continue;
            }
            TObjChara *target = (TObjChara *)candidate;
            if (!target->select_melee_contact_body(this, TObjEneGibbles__data_805DE7EC)) {
                continue;
            }
            if (power <= TObjEneGibbles__data_805DE7E4) {
                power = target->receive_physical_attack(this, TObjEneGibbles__data_805DE7EC);
            } else {
                attack.kind = 0;
                attack.power = power;
                power = target->receive_direct_attack(this, attack, NULL, -1, -1);
            }
            target->apply_knockback_from_attacker((u8 *)this, power);
            if (trigger_hit_reaction == 1 && power > TObjEneGibbles__data_805DE7E4) {
                obj_setFlags30(target, 0x600);
                this->m_388 = (s16)(this->m_388 + power);
                this->state_code = 0x10e;
            }
            hit = true;
        }
    }
    return hit;
}
#pragma pop

#pragma push
#pragma opt_loop_invariants off
void TObjEneGibbles::fn_802D9110() {
    TObjEneGibbles *self = this;

    self->bodies->flags |= 1;
    self->actorFlags &= 0xF9FBFFFF;
    u16 id = self->targetId;
    if (id < 0x1000) {
        u32 p = (u32)get_player_by_client_id(id);
        if (p != 0 && ((TObjPlayer *)p)->get_floor() == get_current_floor()) {
            self->target = (u8 *)p;
        } else {
            self->target = NULL;
        }
    } else if (id < 0x4000) {
        self->target = (u8 *)get_enemy_entity(id);
    } else {
        self->targetId = 0xFFFF;
        self->target = NULL;
    }
    switch (self->phase) {
    case 0:
        if (self->target == NULL) {
            self->phase = 0;
            self->actorFlags &= 0xFFDFFFFF;
            self->resetTimer = 0;
        } else {
            Vec d;
            s32 diff;
            VecCopy(&d, ((TObjChara *)self->target)->body_center());
            subtract_vector(&d, self->body_center());
            diff = self->turn_toward_direction(((GibblesMovementParameters *)self->movementParameters)->turn_speed, &d);
            if (!(self->actorFlags & 0x800000)) {
                apply_actor_gravity((TObjEnemy *)((u8 *)self), NULL, TObjEneGibbles__data_805DE7E4);
            }
            if (diff < 0x10) {
                self->flags |= 0x100;
                self->phase = 1;
                self->requested_action = 2;
                if (check_path_obstructed(self, ((TObjChara *)self->target)->body_center()) == 1) {
                    self->movement_velocity.x = self->movement_velocity.y = self->movement_velocity.z = TObjEneGibbles__data_805DE7E4;
                } else {
                    calc_velocity_toward_destination(self, *self->body_center(), *((TObjChara *)self->target)->body_center(), ((GibblesMovementParameters *)self->movementParameters)->speed);
                }
            }
        }
        break;
    case 1:
        self->requested_action = 2;
        if (self->is_passing_frame(TObjEneGibbles__data_805DE81C) != 0) {
            self->phase = 2;
            play_sound_effect(((TObjEneGibbles*)(self))->resolve_sound_id((u32)(0x3AD34)), &self->position, 0, 0);
        }
        break;
    case 2:
        self->requested_action = 2;
        if (self->is_passing_frame(TObjEneGibbles__data_805DE7F8) != 0) {
            ((TObjEneGibbles *)self)->slam_damage_players(0x1F);
        } else {
            ((TObjEneGibbles *)self)->attack_from_joint_31(0, TObjEneGibbles__data_805DE7E4);
        }
        if (lbl_805DE83C <= self->frame && self->frame <= lbl_805DE840) {
            fn_802D8034();
        }
        if (self->is_passing_frame(TObjEneGibbles__data_805DE7E8) != 0) {
            self->phase = 3;
        }
        break;
    case 3:
        self->requested_action = 2;
        move_with_wall_slide((u8 *)self);
        if (self->is_passing_frame(lbl_805DE840) != 0) {
            self->phase = 4;
            play_sound_effect(((TObjEneGibbles*)(self))->resolve_sound_id((u32)(0x3AD34)), &self->position, 0, 0);
        }
        break;
    case 4:
        self->requested_action = 2;
        if (self->is_passing_frame(lbl_805DE7FC) != 0) {
            ((TObjEneGibbles *)self)->slam_damage_players(0x35);
        } else {
            ((TObjEneGibbles *)self)->attack_from_joint_53(0, TObjEneGibbles__data_805DE7E4);
        }
        if (lbl_805DE838 <= self->frame && self->frame <= lbl_805DE844) {
            fn_802D8034();
        }
        if (self->is_passing_frame(lbl_805DE848) != 0) {
            self->phase = 5;
        }
        break;
    case 5:
        self->requested_action = 2;
        move_with_wall_slide((u8 *)self);
        if (self->is_passing_frame(lbl_805DE84C) != 0) {
            self->phase = 6;
            play_sound_effect(((TObjEneGibbles*)(self))->resolve_sound_id((u32)(0x3AD34)), &self->position, 0, 0);
        }
        break;
    case 6:
        self->requested_action = 2;
        if (self->is_passing_frame(lbl_805DE800) != 0) {
            ((TObjEneGibbles *)self)->slam_damage_players(0x1F);
        } else {
            ((TObjEneGibbles *)self)->attack_from_joint_31(0, TObjEneGibbles__data_805DE7E4);
        }
        if (lbl_805DE850 <= self->frame && self->frame <= lbl_805DE854) {
            fn_802D8034();
        }
        if (self->is_passing_frame((self->frame_count - TObjEneGibbles__data_805DE7EC) - self->play_speed) != 0) {
            self->requested_action = 0;
            self->phase = 7;
            self->resetTimer = (s16)TObjEneGibbles__ai_parameters->combo_wait;
        }
        break;
    case 7:
        if (--self->resetTimer < 0) {
            self->requested_action = 1;
            self->phase = 0;
            self->actorFlags &= 0xFFDFFFFF;
            self->resetTimer = 0;
            self->flags &= ~0x100;
        }
        break;
    }
    ((TObjEneGibbles *)self)->play_distance_sound();
    self->advance_animation();
    ((TObjEneGibbles *)self)->clamp_angle(0);
    self->check_object_collisions();
    check_enemy_body_collisions(self);
    self->update_enemy_collision_flags();
    minimap_render_dot(&self->position, -0x5DB4, 1, 0);
    submit_cursor_candidate(self, -1);
}
#pragma pop
