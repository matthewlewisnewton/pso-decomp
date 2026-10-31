#include "pso/player/demo_mode.h"
#include "pso/misc/PositionSoundEffects.h"
#include "pso/misc/GroundEffects.h"
#include "pso/map/CsnGroundQuery.h"
#include "pso/system/MatrixVectorArray.h"
#include "pso/npc/NpcModelRegistry.h"
#include "pso/npc/NpcAnimationBinding.h"
#include "pso/enemy/BattleParameters.h"
#include "pso/system/EnemyBmlResource.h"
#include "pso/system/BmlResourceClass.h"
#include "pso/enemy/EnemyTargetCandidate.h"
#include "pso/object/TObjChip.h"
#include "pso/system/BmlResource.h"
#include "pso/system/BmlResourceDescriptor.h"
#include "pso/misc/TBreakUpMdl.h"
#include "types.h"
#include "pso/system/NinjaUtil.h"
#include "pso/TObjControl.h"
#include "pso/player/TObjPlayer.h"
#include "pso/player/TObjChara.h"
#include "pso/enemy/TObjEnemyCustom.h"
#include "pso/enemy/TObjEnemy.h"
#include "pso/object/TObjMotion.h"
#include "pso/enemy/TObjEneGyaranzo.h"
#include "pso/system/vector.h"
#include "pso/object/TObjGyaranzoMissile.h"
#include "dolphin/mtx.h"
#include "pso/misc/TLobby.h"
#include "pso/TParticleCtrl.h"
#include "pso/boss/TBoss3Volopt.h"
#include "pso/enemy/TObjEneDD.h"
#include "pso/enemy/TObjEneMe1GiGue.h"
#include "pso/enemy/TObjEneMe3SinowZoa.h"
#include "pso/enemy/TObjEnePanarms.h"
#include "pso/enemy/TObjEneRe7Berura.h"
#include "pso/object/TObjFish.h"

typedef char GyaranzoPositionOffset[offsetof(TObjEneGyaranzo, position) == 0x38 ? 1 : -1];
typedef char GyaranzoYawOffset[offsetof(TObjEneGyaranzo, rotation_y) == 0x60 ? 1 : -1];

extern "C" {
s32 spawn_particle_effect(void *, int);
u8 * TObjGyaranzoMissile__sub_800D4668(void *, void *, void *, s32, s32);
s32 play_sound_effect(int, void *, int, int);
void * __nw__7TObjectFUl(int);
extern const f32 lbl_805DA268;
extern const f32 lbl_805DA26C;
extern const f32 lbl_805DA270;

u8 *__ct__8TObjChipFP7TObjectP14TObjChipParams(u8 *arg0, u8 *arg1, u8 *arg2);
extern NJS_OBJECT *gyaranzo_resource_ptrs[];
extern BmlResource *gyaranzo_bml_resource;
extern u8 *tl_05;
void update_collisions__10TObjPlayerFv(void *);
void apply_actor_gravity(void *, int, f32);
}
void move_with_wall_slide(u8 *arg0);
extern "C" {
void calc_velocity_toward_destination(void *, Vec, Vec, f32);
extern const f32 lbl_805DA258;
extern const f32 lbl_805DA25C;

}

struct GyaranzoMissileLaunch { Vec *position; s32 pitch; s32 yaw; f32 wobble_speed; f32 wobble_height; f32 unknown14; };

f32 get_gyaranzo_missile_float_parameter(s32);
extern f32 lbl_805D51F0;
extern f32 TObjGyaranzoMissile__speed_scale;
extern f32 TObjGyaranzoMissile__max_range;
extern "C" {
s32 check_path_obstructed(void *, void *);
u8 *get_player_data__10TObjPlayerFi(s32);
u16 get_entity_id(void *);
s32 subtract_vector(void *, void *);
extern EnemyTargetCandidate TObjGyaranzoMissile_target_slots[];
extern s32 registered_player_count;
extern s32 lbl_805D5870;
extern const f32 lbl_805DA260;
}
s32 get_gyaranzo_missile_int_parameter(s32 i);
extern "C" {
s32 TObjGyaranzoMissile__ct(void *, void *, void *, u16);
void *__nw__7TObjectFUl(int);
extern s32 gyaranzo_missile_volley_end_time;

}

extern "C" {
u16 find_nearest_visible_player(void *, int, int, f32);
extern const f32 lbl_805DA290;
void enemy_turn_toward_dest(void *, s32);
u8 *find_active_entity_by_id(u16);
extern s32 actor_frame_tick;
extern const f32 lbl_805DA274;
extern const f32 gyaranzo_volley_fire_frame;
extern const f32 lbl_805DA280;


s32 is_split_screen();
void queue_destruction__7TObjectFv(void *);




s32 get_bml_motion(u32, int);
s32 get_camera_mode__11TCameraCtrlFv();
TUnk_8048FA00 * init__11TBreakUpMdlFPviif(void *, s32, s32, f32);

void create_dead_spot__10TObjPlayerFllf(void *, s32, f32);
}
int initialize_enemy_photon_effect(void *p);
extern "C" {
s32 restore_scene_lighting();
s32 select_actor_lighting(void *);
s32 free_collision_body_parts(void *);
s32 init_collision_body_parts(void *, void *, int);
s32 submit_cursor_candidate(void *, s32);
s32 minimap_render_dot(void *, s32, s32, s32);
s32 defer_render__7TObjectFv(void *);
s32 rotate_matrix_y(int, int);
s32 push_matrix();
s32 pop_matrix();
s32 post_translate_matrix(void *);
s32 draw_chunk_object(int);

extern NpcAnimationBinding lbl_8043C25C;
extern Vec lbl_8043C26C;
extern const char lbl_8043C428[];
extern NJS_OBJECT *gyaranzo_model_resources[];
extern s32 lbl_805D2A78;
extern s32 gyaranzo_boss_stats_handle;
extern s32 gyaranzo_boss_stats_ptr_b;
extern s32 gyaranzo_object_handle;
extern s32 gyaranzo_missile_param_table;
extern NJS_OBJECT *lbl_805D5200;
extern NJS_OBJECT *lbl_805D5204;
extern TUnk_8048FA00 *gyaranzo_breakup_model_obj;
extern s32 saved_model_render_flags;

extern const f32 lbl_805DA284;
extern const f32 lbl_805DA288;
extern const f32 lbl_805DA28C;
extern const f32 lbl_805DA294;
extern const f32 lbl_805DA298;
extern s32 model_render_flags;
extern void *tl_04;

extern const char lbl_8043C100[];
extern const char lbl_8043C114[];
extern const char lbl_8043C128[];
extern const char lbl_8043C13C[];
extern const char lbl_8043C14C[];
extern const char lbl_8043C15C[];
extern const char lbl_8043C16C[];
extern const char lbl_8043C180[];
extern const char lbl_8043C198[];
extern const char lbl_8043C1B0[];
extern const char lbl_8043C1C8[];
extern const char lbl_8043C1DC[];
extern const char lbl_8043C1F0[];
extern const char lbl_8043C208[];
extern const char lbl_8043C220[];
extern const char lbl_8043C238[];
const char *bm_ene_gyaranzo_model_names[8] = {
    lbl_8043C100, lbl_8043C114, lbl_8043C128, lbl_8043C13C,
    lbl_8043C14C, lbl_8043C15C, lbl_8043C16C, NULL,
};
const char *bm_ene_gyaranzo_motion_names[9] = {
    lbl_8043C180, lbl_8043C198, lbl_8043C1B0, lbl_8043C1C8,
    lbl_8043C1DC, lbl_8043C1F0, lbl_8043C208, lbl_8043C220,
    NULL,
};
BmlResourceDescriptor bm_ene_gyaranzo_resource_descriptor = {
    lbl_8043C238, bm_ene_gyaranzo_model_names, bm_ene_gyaranzo_motion_names, 7, 8,
};
TObjMotionAction gyaranzo_action_table[8] = {
    { 2, 0, 4, 0.7f, 0 },
    { 2, 5, 5, 0.7f, 1 },
    { 2, 0, 0, 1.0f, 4 },
    { 2, 0, 2, 0.8f, 8 },
    { 3, 4, 3, 1.0f, 0x10 },
    { 1, 5, 6, 0.7f, 1 },
    { 2, 0, 7, 0.8f, 1 },
    { 2, 0, 1, 1.0f, 8 },
};
struct GyaranzoMovementParameters {
    f32 max_distance;
    f32 walk_speed;
    s32 turn_speed;
    s16 unknown_c;
    s16 unknown_e;
    s32 unknown10;
    s32 unknown14;
    s32 unknown18;
};
GyaranzoMovementParameters gyaranzo_movement_parameters = {
    150.0f, 0.5555555f, 0x400, 30, 0, 0, 1, 0,
};
CollisionBody gyaranzo_collision_body[1] = {
    { { 0.0f, 18.0f, 0.0f }, 18.0f, 0.0f, 0, 0x8003, { 0.0f, 0.0f, 0.0f }, 0.0f },
};
s16 gyaranzo_resource_index_table[22] = {
    6, 7, 10, 11, 12, 15, 14, 9, 8, 37, 33, 54, 44, 16, 17, 18, 19, 20, 21, 22, 23, 24,
};
s16 gyaranzo_flagged_resource_index_table[13] = {
    2, 3, 4, 11, 12, 0, 1, 5, 6, 7, 8, 9, 10,
};
struct GyaranzoBreakupParameters {
    s32 count;
    f32 unknown4;
    f32 unknown8;
    f32 unknown_c;
    f32 unknown10;
    f32 unknown14;
    f32 unknown18;
};
GyaranzoBreakupParameters gyaranzo_death_breakup_params = {
    20, 0.06f, 1.5f, 0.9f, 0.12f, 0.55f, 0.5f,
};

extern const f32 lbl_805DA264;

// Only the group is needed from this set-data record.
struct GyaranzoSetData {
    u8 unknown[0xA];
    s16 group;
};
typedef char GyaranzoSetGroupOffset[offsetof(GyaranzoSetData, group) == 0xA ? 1 : -1];

}

// Deferred code generation emits these definitions in reverse source order.
#pragma inline_depth(1)
#pragma auto_inline off
#pragma dont_inline off

#pragma push
TObjEneGyaranzo::TObjEneGyaranzo(TObject *parent, void *set_data)
    : TObjEnemyCustom(parent) {
    m_name = (char *)lbl_805D2A78;
    apply_set_data(set_data);
    VecCopy((Vec *)&m_290, VecCopy((Vec *)&m_29c, &position));
    motion_list = gyaranzo_bml_resource->motions;
    action_table = gyaranzo_action_table;
    set_action_table(action_table);
    init_collision_body_parts(this, gyaranzo_collision_body, 1);
    variant = 0;
    movementParameters = &gyaranzo_movement_parameters;
    bind_enemy_combat_stats((u8 *)gyaranzo_boss_stats_handle,
        (u8 *)gyaranzo_boss_stats_ptr_b, (u8 *)gyaranzo_object_handle);
    init_params_from_table();
    requested_action = 0;
    set_animation(requested_action);
    set_field_b8(requested_action);
    hp = hpmax;
    tp = tpmax;
    referenceHp = hp;
    charge_hp_threshold = hp / 3;
    hidden_part_count = 0;
    armor_stage = 0;
    unknown_3ac = 0;
    charge_count = 0;
    hit_debris_cooldown = 0;
    set_param(0x19);
    add_flags_2e4(4);
    update_prev_position();
    initialize_enemy_photon_effect(this);
    actorFlags |= 0x40000;
    model = (void *)gyaranzo_bml_resource->models[3].model;
    texlist = gyaranzo_bml_resource->models[3].m_c;
    if (((GyaranzoSetData *)set_data)->group != 0) {
        sub_800C7860();
    }
    for (s32 i = 0; i < 4; ++i) {
        camera_fades[i].activate_and_dispatch();
    }
    clear_lobby_object_state();
}
#pragma pop

#pragma push
TObjEneGyaranzo::~TObjEneGyaranzo() {
    free_collision_body_parts(this);
}
#pragma pop

#pragma push
#pragma opt_propagation off
void TLobby::load_gyaranzo_resources() {
    s32 i;
    void *p;

    if (TObjEneDD::check_v2_mode() != 0) {
        gyaranzo_bml_resource = (BmlResource *)load_enemy_bml_resource_named(&bm_ene_gyaranzo_resource_descriptor, lbl_8043C428);
    } else {
        p = new BmlResource(5, &bm_ene_gyaranzo_resource_descriptor, 0, 0, NULL);
        gyaranzo_bml_resource = (BmlResource *)p;
    }
    for (i = 0; i < 0x16; i++) {
        gyaranzo_model_resources[i] = (NJS_OBJECT *)find_model_node(gyaranzo_bml_resource->models[3].model, gyaranzo_resource_index_table[i]);
    }
    for (i = 0; i < 0xD; i++) {
        gyaranzo_resource_ptrs[i] = (NJS_OBJECT *)find_model_node(gyaranzo_bml_resource->models[4].model, gyaranzo_resource_index_table[i]);
    }
    for (i = 0; i < 0xD; i++) {
        gyaranzo_resource_ptrs[i]->sibling = NULL;
    }
    lbl_805D5200 = (NJS_OBJECT *)find_model_node(gyaranzo_bml_resource->models[3].model, 0x19);
    lbl_805D5204 = (NJS_OBJECT *)find_model_node(gyaranzo_bml_resource->models[3].model, 0xD);
    p = ::operator new(0x10);
    if (p != NULL) {
        p = init__11TBreakUpMdlFPviif(p, gyaranzo_bml_resource->models[3].model, get_bml_motion((u32)gyaranzo_bml_resource, 3), lbl_805DA294);
    }
    gyaranzo_breakup_model_obj = (TUnk_8048FA00 *)p;
    gyaranzo_boss_stats_handle = ((s32)get_battle_base_stats(0x1D));
    gyaranzo_boss_stats_ptr_b = ((s32)get_battle_attack_params(0x1D));
    gyaranzo_object_handle = ((s32)get_battle_resistance_params(0x1D));
    gyaranzo_missile_param_table = ((s32)get_battle_movement_params(0x1D));
    {
        NpcAnimationBinding pos = lbl_8043C25C;
        pos.motions = gyaranzo_bml_resource->motions;
        NpcModelRegistry::register_animated_chunk(0x20, (void *)gyaranzo_bml_resource->models[3].model, (void *)gyaranzo_bml_resource->models[3].m_c, &pos, lbl_805DA298, lbl_805DA258);
        NpcModelRegistry::register_animated_chunk(0x21, (void *)gyaranzo_bml_resource->models[4].model, (void *)gyaranzo_bml_resource->models[3].m_c, &pos, lbl_805DA298, lbl_805DA258);
    }
}
#pragma pop

#pragma push
void TObjEneGyaranzo::free_static_instances() {
    if (gyaranzo_bml_resource != NULL) {
        delete gyaranzo_bml_resource;
        gyaranzo_bml_resource = NULL;
    }
    if (gyaranzo_breakup_model_obj != NULL) {
        delete gyaranzo_breakup_model_obj;
        gyaranzo_breakup_model_obj = NULL;
    }
}
#pragma pop

#pragma push
void *TObjEneGyaranzo::create(void *set_data) {
    TObjControl *parent = new TObjControl((TObject *)tl_04);
    return new TObjEneGyaranzo(parent, set_data);
}
#pragma pop

#pragma push
void TObjEneGyaranzo::run_task() {
    s32 temp_r3;

    if (check_demo_mode() == 1) {
        update_demo();
        return;
    }
    this->select_next_action();
    temp_r3 = this->hit_debris_cooldown;
    if (temp_r3 >= 0) {
        this->hit_debris_cooldown = (temp_r3 - 1);
    }
    if ((s16) this->mode != (s32) this->next_action) {
        if ((s32) this->state != -1) {
            this->state = -1;
            dispatch_state_update();
        }
        this->mode = (s16) this->next_action;
        this->state = 0;
    }
    dispatch_state_update();
    this->update_prev_position();
    ((TObjChara *)this)->copy_body_to_center();
    submit_cursor_candidate(this, -1);
    minimap_render_dot(&position, -0x5DB4, 1, 0);
}
#pragma pop

#pragma push
void TObjEneGyaranzo::dispatch_state_update() {
    switch (mode) {
    case 0: TObjEnemyCustom::update_state(); return;
    case 1: update_chase(); return;
    case 2: update_aim_and_fire(); return;
    case 4: update_knockback(); return;
    case 5: update_death_breakup(); return;
    case 7: update_fade_state(); return;
    case 9: update_chase(); return;
    case 8: update_return_home(); break;
    }
}
#pragma pop

#pragma push
void TObjEneGyaranzo::select_next_action() {
    s32 a;
    u16 r;
    switch (this->mode) {
    case 0:
    case 8:
        if (this->is_actor_cadence_frame(0x1E) != 0) {
            select_targets();
            if (this->target_count > 0) {
                switch (this->armor_stage) {
                case 0:
                    if (this->hp <= this->charge_hp_threshold) {
                        this->targetId = this->target_ids[3];
                        a = 9;
                    } else {
                        this->targetId = this->target_ids[1];
                        a = 1;
                    }
                    if (this->targetId != 0xFFFF) {
                        update_if_active(a);
                        this->m_378 = 2;
                    }
                    break;
                case 1:
                    this->targetId = this->target_ids[1];
                    if (this->targetId != 0xFFFF) {
                        update_if_active(9);
                        this->m_378 = 2;
                    }
                    break;
                case 2:
                    this->targetId = target_ids[0];
                    if (this->targetId != 0xFFFF) {
                        update_if_active(9);
                        this->m_378 = 2;
                    }
                    break;
                }
            } else if (this->is_actor_cadence_frame(0x1E) != 0 &&
                       xz_distance_squared(&position, &home_position) > lbl_805DA25C) {
                update_if_active(8);
            }
        }
        break;
    case 1:
        if (this->is_actor_cadence_frame(0x1E) != 0) {
            f32 *p = *(f32 * *)&this->movementParameters;
            r = find_nearest_visible_player(this, 0, (int)p, lbl_805DA290 + *p);
            if (this->targetId == 0xFFFF) {
                this->targetId = r;
            }
            if (this->targetId == 0xFFFF) {
                update_if_active(8);
            }
        }
        break;
    }
}
#pragma pop

#pragma push
#pragma opt_common_subs off
void TObjEneGyaranzo::render() {
    s32 temp_r3;
    s32 camera_index;
    RenderFadeState *camera_fade;
    s32 var_r29;
    if (!(this->actorFlags & 0x02000000)) {
        camera_index = 0;
        if (is_split_screen() != 0) {
            camera_index = get_camera_mode__11TCameraCtrlFv();
        }
        var_r29 = 1;
        temp_r3 = classify_actor_view_detail(lbl_805DA284, lbl_805DA288, lbl_805DA28C);
        if (temp_r3 != 0) {
            saved_model_render_flags = model_render_flags;
            camera_fade = &camera_fades[camera_index];
            camera_fade->update_fast();
            if (camera_fade->updateFromCamera(&body_center_position.x) != 0) {
                camera_fade->set_flags_and_apply_damage_color();
                if (defer_render__7TObjectFv(this) != 0) {
                    model_render_flags = saved_model_render_flags;
                    return;
                }
            }
            update_model_visibility();
            TObjFish::set_global_param(this->texlist);
            select_actor_lighting(this);
            TObjPlayer::toggle_particle_effect();
            push_matrix();
            post_translate_matrix(&position);
            rotate_matrix_y(0, this->rotation_y);
            if (check_demo_mode() == 1) {
                draw_chunk_object((int) (model));
            } else if (this->m_388 & 4) {
                if (fade.has_visible_opacity() != 0) {
                    fade.set_flags_and_apply_damage_color();
                    if (temp_r3 == 1) {
                        this->draw();
                    } else {
                        this->draw_motion_model();
                    }
                    fade.clear_flag_and_notify();
                } else {
                    var_r29 = 0;
                }
            } else if (temp_r3 == 1) {
                this->draw();
            } else {
                this->draw_motion_model();
            }
            pop_matrix();
            restore_scene_lighting();
            TParticleCtrl::end_effect_render();
            if (!(this->actorFlags & 0x800) && (var_r29 != 0)) {
                Vec sp8 = lbl_8043C26C;
                draw_ground_shadow(&sp8, 0);
            }
            camera_fade->clear_flag_and_notify();
        }
    }
}
#pragma pop

#pragma push
void TObjEneGyaranzo::update_demo() {}
#pragma pop

#pragma push
void TObjEneGyaranzo::update_chase() {
    Vec v;
    CollisionBody *p;
    target = find_active_entity_by_id(targetId);
    switch (state) {
    case 0:
        p = bodies;
        p->flags &= ~0x380000;
        actorFlags &= ~0x100;
        sub_8004292C();
        distance_travelled = lbl_805DA258;
        missile_distance = lbl_805DA258;
        requested_action = 1;
        if (mode == 1) {
            chase_limit = get_gyaranzo_missile_float_parameter(0);
        } else {
            chase_limit = lbl_805DA270;
            (charge_count)++;
        }
        play_sound_effect(((TObjEnemy *)(this))->remap_sound_for_area(((TObjEnemy *)(this))->remap_sound_for_area(0x4003B209)), &position, 0, 0);
        if (target != NULL) {
            VecCopy((Vec *)(&m_29c), (const Vec *)(&((TObjChara *)target)->body_center_position));
        }
        state = 1;
        break;
    case 1:
        if (target != NULL) {
            VecCopy((Vec *)(&chase_destination), (const Vec *)(&((TObjChara *)target)->body_center_position));
            VecCopy((Vec *)(&m_29c), (const Vec *)(&((TObjChara *)target)->body_center_position));
        } else {
            vfunc_58();
            return;
        }
        enemy_turn_toward_dest(this, ((EnemyMoveParams *)movementParameters)->turn_speed);
        move_along_ground_avoiding_walls(chase_destination, ((GyaranzoMovementParameters *)movementParameters)->walk_speed, bodies->radius);
        distance_travelled += ((GyaranzoMovementParameters *)movementParameters)->walk_speed;
        advance_animation();
        apply_actor_gravity(this, 0, lbl_805DA258);
        if (mode == 9) {
            missile_distance += ((GyaranzoMovementParameters *)movementParameters)->walk_speed;
            if (missile_distance >= 20.0f) {
                missile_distance -= 20.0f;
                spawn_missile();
            }
        }
        if (!(actor_frame_tick & 3)) {
            render_anim_model_at_pos();
            get_anim_node_position(0x1F, &v);
            spawn_particle_effect(&v, 0xF3);
            get_anim_node_position(0x27, &v);
            spawn_particle_effect(&v, 0xF3);
        }
        update_collisions__10TObjPlayerFv(this);
        if (bodies->flags & 0x380000) {
            state = -1;
        } else if (distance_travelled >= chase_limit) {
            state = -1;
        }
        break;
    case -1:
        update_if_active(m_378);
        break;
    }
}
#pragma pop

#pragma push
void TObjEneGyaranzo::vfunc_62() {
    u8 *arg0 = (u8 *)this;
  s32 temp_r0;
  unsigned long var_r3;
  if ((this->mode) != 4)
  {
    if (((s32)this->hit_debris_cooldown) <= 0)
    {
      this->hit_debris_cooldown = 0x3C;
      spawn_hit_debris();
    }
    temp_r0 = this->armor_stage;
    var_r3 = 0;
    switch (temp_r0)
    {
      case 0:
        var_r3 = (this->hp) <= ((this->hpmax) / 3);
        break;
      case 1:
        var_r3 = (this->hp) <= ((this->hpmax) / 4);
        break;
    }
    if (((s32) var_r3) != 0)
    {
      shed_armor();
    }
    this->referenceHp = this->hp;
    play_sound_effect(((TObjEnemy *)((void *) arg0))->remap_sound_for_area(0x4003AD0F), (u8 *)&this->position, 0, 0);
    if (!((this->m_388) & 0x40000))
    {
      set_state(4);
      this->m_388 = (s32) ((this->m_388) | 1);
      return;
    }
    obj_clearFlags30(0x200200);
  }
}
#pragma pop

#pragma push
void TObjEneGyaranzo::update_knockback() {
    switch (state) {
    case 0:
        actorFlags &= ~0x200000;
        requested_action = 3;
        state = 1;
    case 1: {
        advance_animation();
        Vec v = *(Vec *)&body_center_position;
        v.x += movement_velocity.x;
        v.z += movement_velocity.z;
        if (check_path_obstructed(this, &v) == 0) {
            move_with_wall_slide((u8 *)this);
        } else {
            movement_velocity.x = movement_velocity.z = lbl_805DA258;
        }
        movement_velocity.x *= lbl_805DA280;
        movement_velocity.z *= lbl_805DA280;
        apply_actor_gravity(this, 0, lbl_805DA258);
        update_collisions__10TObjPlayerFv(this);
        if (action_flags != 8) {
            state = -1;
        }
        break;
    }
    case -1:
        actorFlags &= ~0x200;
        m_388 &= ~1;
        next_action = 1;
        break;
    }
}
#pragma pop

#pragma push
void TObjEneGyaranzo::vfunc_63() {
    u8 *arg0 = (u8 *)this;
    set_state(5);
    this->m_388 = (s32) (this->m_388 | 1);
}
#pragma pop

#pragma push
void TObjEneGyaranzo::update_death_breakup() {
    switch (state) {
    case 0:
        this->requested_action = 4;
        distribute_experience_and_request_drop();
        timer = 0x5A;
        create_dead_spot__10TObjPlayerFllf(&body_center_position, 0x5A, 20.0f);
        create_dead_spot__10TObjPlayerFllf(&body_center_position, 0x5A, 20.0f);
        state = 1;
    case 1:
        advance_animation();
        timer--;
        if (timer < 0) {
            TBoss3Volopt::create_breakup_mdl((s32)gyaranzo_breakup_model_obj, (s32)&gyaranzo_death_breakup_params, (s32)this->texlist, (s32)&body_center_position, (s32)this->rotation_y);
            ((TObjEnemy *)this)->send_entity_set_flags();
            ((TObjPlayer *)(&body_center_position))->trigger_dell_biter_events();
            play_sound_effect(((TObjEnemy *)(this))->remap_sound_for_area(0x4003AD10), &position, 0, 0);
            queue_destruction__7TObjectFv(this);
        }
        break;
    case -1:
        return;
    }
}
#pragma pop

#pragma push
void TObjEneGyaranzo::update_model_visibility() {
    s32 i;
    for (i = 0; i < hidden_part_count; i++) {
        gyaranzo_model_resources[gyaranzo_flagged_resource_index_table[i]]->evalflags |= 8;
    }
    for (; i < 13; i++) {
        gyaranzo_model_resources[gyaranzo_flagged_resource_index_table[i]]->evalflags &= ~8;
    }
    if (armor_stage >= 1) {
        lbl_805D5200->evalflags |= 8;
        lbl_805D5204->evalflags |= 8;
    } else {
        lbl_805D5200->evalflags &= ~8;
        lbl_805D5204->evalflags &= ~8;
    }
}
#pragma pop

#pragma push
void TObjEneGyaranzo::update_aim_and_fire() {
    s32 temp_r3;
    s32 temp_r4;
    s32 temp_r5;
    s32 var_r30;
    u8 *temp_r6;
    switch (state) {
    case 0:
        m_388 = (s32) (m_388 | 0x40000);
        this->requested_action = 0;
        state = 1;
    case 1:
        var_r30 = 0;
        if (this->is_actor_cadence_frame(0x1E) != 0) {
            find_target_in_range(lbl_805DA274);
        }
        temp_r6 = this->target;
        if (temp_r6 != NULL) {
            Vec v = ((TObjChara *)temp_r6)->position;
            subtract_vector(&v, (void *) (&position));
            temp_r3 = turn_toward_direction( ((EnemyMoveParams *)movementParameters)->turn_speed, &v);
            temp_r4 = temp_r3 >> 0x1F;
            if ((s32) ((temp_r4 ^ temp_r3) - temp_r4) < 0xE38) {
                var_r30 = 1;
            }
        } else {
            var_r30 = 1;
        }
        if (var_r30 != 0) {
            timer = get_gyaranzo_missile_int_parameter(0);
            this->requested_action = 2;
            state = 2;
        }
        break;
    case 2:
        if (this->frame >= gyaranzo_volley_fire_frame) {
            spawn_missile_volley();
            state = 3;
        }
        break;
    case 3:
        timer = (s16) (timer - 1);
        if (timer <= 0) {
            state = -1;
            update_if_active(0);
        }
        break;
    case -1:
        m_388 = (s32) (m_388 & 0xFFFBFFFF);
        break;
    }
    advance_animation();
    apply_actor_gravity(this, 0, lbl_805DA258);
    update_collisions__10TObjPlayerFv(this);
}
#pragma pop

#pragma push
#pragma fp_contract on
void TObjEneGyaranzo::spawn_missile() {
    Vec launch_position;
    s32 temp_r31;
    u8 *temp_r3;
    render_anim_model_at_pos();
    get_anim_node_position(0x18, &launch_position);
    temp_r31 = (s32) (lbl_805DA268 * ((lbl_805DA26C * random_ratio()) - lbl_805DA270));
    temp_r3 = (u8 *)(((u8 *)__nw__7TObjectFUl(0xF0)));
    if (temp_r3 != NULL) {
        TObjGyaranzoMissile__sub_800D4668(temp_r3, this, &launch_position, rotation_y, temp_r31);
    }
    spawn_particle_effect((void *)((s32) &launch_position), 0xF3);
    play_sound_effect((((TObjEnemy *)(this))->remap_sound_for_area(0x4003B20D)), &position, 0, 0);
}
#pragma pop

#pragma push
#pragma pool_data off
void TObjEneGyaranzo::spawn_hit_debris() {
    Vec pos = position;
    pos.y += lbl_805DA264;
    const TObjChipParams first = {
        { 0.5f, 0.04f, 0.28f }, { pos.x, pos.y, pos.z },
        { 6.0f, 7.0f, 6.0f }, { 0x400, 0x100, 0x400 },
        { 5, 50 }, { position.y, 1.0f },
        gyaranzo_bml_resource->models[0].model,
        gyaranzo_bml_resource->models[0].m_c, 2,
    };
    const TObjChipParams second = {
        { 0.5f, 0.04f, 0.2f }, { pos.x, pos.y, pos.z },
        { 5.5f, 6.5f, 5.5f }, { 0x400, 0x100, 0x400 },
        { 4, 50 }, { position.y, 1.0f },
        gyaranzo_bml_resource->models[1].model,
        gyaranzo_bml_resource->models[1].m_c, 2,
    };
    const TObjChipParams third = {
        { 0.5f, 0.04f, 0.22f }, { pos.x, pos.y, pos.z },
        { 5.5f, 7.0f, 5.5f }, { 0x400, 0x100, 0x400 },
        { 5, 50 }, { position.y, 1.0f },
        gyaranzo_bml_resource->models[2].model,
        gyaranzo_bml_resource->models[2].m_c, 2,
    };
    void *obj = __nw__7TObjectFUl(0x234);
    if (obj != NULL) __ct__8TObjChipFP7TObjectP14TObjChipParams((u8 *)obj, tl_05, (u8 *)&first);
    obj = __nw__7TObjectFUl(0x234);
    if (obj != NULL) __ct__8TObjChipFP7TObjectP14TObjChipParams((u8 *)obj, tl_05, (u8 *)&second);
    obj = __nw__7TObjectFUl(0x234);
    if (obj != NULL) __ct__8TObjChipFP7TObjectP14TObjChipParams((u8 *)obj, tl_05, (u8 *)&third);
}
#pragma pool_data reset

#pragma pop

#pragma push
#pragma pool_data off
void TObjEneGyaranzo::shed_armor() {
    s32 start;
    s32 end;
    s32 i;
    s32 idx;
    Vec v;
    void *obj;
    if (armor_stage < 2) {
        (armor_stage)++;
        switch (armor_stage) {
        case 1:
            start = 0;
            hidden_part_count = 5;
            end = 5;
            break;
        case 2:
            start = 5;
            hidden_part_count = 0xD;
            end = 0xD;
            break;
        }
        render_anim_model_at_pos();
        for (i = start; i < end; i++) {
            idx = gyaranzo_flagged_resource_index_table[i];
            get_anim_node_position(gyaranzo_resource_index_table[idx], &v);
            {
                TObjChipParams p = {
                    { 0.5f, 0.03f, 0.15f }, { v.x, v.y, v.z },
                    { 3.5f, 5.0f, 3.5f }, { 0x400, 0x100, 0x400 },
                    { 3, 50 }, { position.y, 1.0f },
                    (s32)gyaranzo_resource_ptrs[idx],
                    gyaranzo_bml_resource->models[3].m_c, 2,
                };
                obj = __nw__7TObjectFUl(0x234);
                if (obj != NULL) {
                    __ct__8TObjChipFP7TObjectP14TObjChipParams((u8 *)obj, tl_05, (u8 *)&p);
                }
            }
        }
    }
}
#pragma pop

#pragma push
#pragma pool_data off
#define NEW(d, id) { void *o = __nw__7TObjectFUl(0xDC); if (o != NULL) { TObjGyaranzoMissile__ct(o, this, &d, id); } }
void TObjEneGyaranzo::spawn_missile_volley() {
    Vec pos;
    s32 i;
    gyaranzo_missile_volley_end_time = get_gyaranzo_missile_int_parameter(1) + 0x96;
    render_anim_model_at_pos();
    {
        GyaranzoMissileLaunch d1 = { &pos, -0x1000, rotation_y + 0x800, 1024.0f, 3.0f, 0.0f };
        GyaranzoMissileLaunch d2 = { &pos, -0x2000, rotation_y + 0x800, 2048.0f, 10.0f, 0.4f };
        GyaranzoMissileLaunch d3 = { &pos, -0x1000, rotation_y - 0x800, 1024.0f, 3.0f, 0.0f };
        GyaranzoMissileLaunch d4 = { &pos, -0x2000, rotation_y - 0x800, 2048.0f, 10.0f, 0.4f };
        u16 ids[4] = { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF };
        s32 idx[4] = { 0, 3, 1, 2 };
        for (i = 0; i < 4; i++) {
            ids[i] = target_ids[idx[i]];
        }
        get_anim_node_position(0x10, &pos);
        NEW(d1, ids[0]);
        NEW(d2, ids[1]);
        spawn_particle_effect(&pos, 0xF3);
        get_anim_node_position(0x14, &pos);
        NEW(d3, ids[0]);
        NEW(d4, ids[1]);
        spawn_particle_effect(&pos, 0xF3);
        if (armor_stage >= 1) {
            get_anim_node_position(0x11, &pos);
            NEW(d1, ids[0]);
            NEW(d2, ids[1]);
            spawn_particle_effect(&pos, 0xF3);
            get_anim_node_position(0x15, &pos);
            NEW(d3, ids[2]);
            NEW(d4, ids[3]);
            spawn_particle_effect(&pos, 0xF3);
        }
        if (armor_stage >= 2) {
            get_anim_node_position(0x12, &pos);
            NEW(d1, ids[0]);
            NEW(d2, ids[1]);
            spawn_particle_effect(&pos, 0xF3);
            get_anim_node_position(0x16, &pos);
            NEW(d3, ids[2]);
            NEW(d4, ids[3]);
            spawn_particle_effect(&pos, 0xF3);
            get_anim_node_position(0x13, &pos);
            NEW(d1, ids[2]);
            NEW(d2, ids[3]);
            spawn_particle_effect(&pos, 0xF3);
            get_anim_node_position(0x17, &pos);
            NEW(d3, ids[2]);
            NEW(d4, ids[3]);
            spawn_particle_effect(&pos, 0xF3);
        }
    }
    play_sound_effect(((TObjEnemy *)(this))->remap_sound_for_area(0x4003AD0A), &position, 0, 0);
}
#undef NEW
#pragma pop

#pragma push
#pragma scheduling off
void EnemyTargetCandidate::copy_from(const EnemyTargetCandidate *source) {
    id = source->id;
    distance_squared = source->distance_squared;
}
#pragma pop

#pragma push
void TObjEneGyaranzo::select_targets() {
    s32 count;
    s32 n;
    s32 best;
    s32 i;
    TObjChara *p;
    s32 j;
    s32 k;
    f32 dist;
    Vec d;
    TObjGyaranzoMissile_target_slots[0].id = 0xFFFF;
    TObjGyaranzoMissile_target_slots[0].distance_squared = lbl_805DA258;
    n = 0;
    best = 0;
    k = obj_testFlags30(0x10);
    count = registered_player_count;
    if (k != 0) {
        count += lbl_805D5870;
    }
    for (i = 0; i < count; i++) {
        p = (TObjChara *)get_player_data__10TObjPlayerFi(i);
        if (TObjPlayer::is_valid_and_active((u32)p) == 0) continue;
        if (p == this) continue;
        if (p->actorFlags & 0x2000800) continue;
        VecCopy(&d, p->body_center());
        subtract_vector(&d, body_center());
        dist = d.x * d.x + d.z * d.z;
        if (!(dist < lbl_805DA260)) continue;
        if (check_path_obstructed(this, p->body_center()) == 1) continue;
        TObjGyaranzoMissile_target_slots[n].distance_squared = dist;
        TObjGyaranzoMissile_target_slots[n].id = get_entity_id(p);
        if (n > 0 && TObjGyaranzoMissile_target_slots[n].distance_squared > TObjGyaranzoMissile_target_slots[best].distance_squared) {
            best = n;
        }
        n++;
        if (n >= 4) break;
    }
    {
        EnemyTargetCandidate def = { 0xFFFF, 0.0f };
        switch (n) {
        case 0:
            for (i = 0; i < 4; i++) {
                TObjGyaranzoMissile_target_slots[i].copy_from(&def);
            }
            break;
        case 2:
            for (i = n; i < 4; i++) {
                TObjGyaranzoMissile_target_slots[i].copy_from(&TObjGyaranzoMissile_target_slots[i % n]);
            }
            break;
        default:
            for (i = n; i < 4; i++) {
                TObjGyaranzoMissile_target_slots[i].copy_from(&TObjGyaranzoMissile_target_slots[best]);
            }
            break;
        }
    }
    target_count = n;
    for (i = 0; i < 3; i++) {
        for (j = i + 1; j < 4; j++) {
            if (TObjGyaranzoMissile_target_slots[i].distance_squared > TObjGyaranzoMissile_target_slots[j].distance_squared) {
                EnemyTargetCandidate tmp;
                tmp.copy_from(&TObjGyaranzoMissile_target_slots[i]);
                TObjGyaranzoMissile_target_slots[i].copy_from(&TObjGyaranzoMissile_target_slots[j]);
                TObjGyaranzoMissile_target_slots[j].copy_from(&tmp);
            }
        }
    }
    for (i = 0; i < 4; i++) {
        target_ids[i] = TObjGyaranzoMissile_target_slots[i].id;
    }
}
#pragma pop

#pragma push
void TObjEneGyaranzo::update_fade_state() {
    s32 temp_r4;
    s32 temp_r5;

    switch (state) {
    case 0:
        m_388 = (s32) (m_388 | 4);
        temp_r4 = actorFlags | 0x04000000;
        actorFlags = temp_r4;
        requested_action = 0;
        play_area_sound_and_particles_a(&body_center_position, temp_r4);
        fade.start_fade_in();
        state = 1;
    case 1:
        advance_animation();
        if (fade.advance_toward_max() == 1) {
            state = -1;
        }
        return;
    case -1:
        temp_r5 = m_388;
        m_388 = (s32) (temp_r5 & ~5);
        actorFlags = (s32) (actorFlags & 0xFBFFFFFF);
        update_if_active(0);
        break;
    }
}
#pragma pop

#pragma push
void TObjEneGyaranzo::init_params_from_table() {
    ((GyaranzoMovementParameters *)movementParameters)->walk_speed = get_gyaranzo_missile_float_parameter(1);
    lbl_805D51F0 = get_gyaranzo_missile_float_parameter(2);
    TObjGyaranzoMissile__speed_scale = get_gyaranzo_missile_float_parameter(3);
    TObjGyaranzoMissile__max_range = get_gyaranzo_missile_float_parameter(4);
}
#pragma pop

#pragma push
void TObjEneGyaranzo::update_return_home() {
    switch (state) {
    case -1:
        break;
    case 0:
        bodies->flags &= ~0x380000;
        actorFlags &= ~0x100;
        requested_action = 1;
        VecCopy((Vec *)&m_29c, &home_position);
        state = 1;
    case 1:
        advance_animation();
        apply_actor_gravity(this, 0, lbl_805DA258);
        VecCopy((Vec *)&m_290, (const Vec *)&body_center_position);
        calc_velocity_toward_destination(this, *(Vec *)&m_290, *(Vec *)&m_29c, ((GyaranzoMovementParameters *)movementParameters)->walk_speed);
        turn_toward_direction(((EnemyMoveParams *)movementParameters)->turn_speed, &movement_velocity);
        move_with_wall_slide((u8 *)this);
        update_collisions__10TObjPlayerFv(this);
        if (xz_distance_squared(&position, &home_position) <= lbl_805DA25C) {
            update_if_active(0);
        }
        break;
    }
}
#pragma pop

#pragma push
s32 TObjEneGyaranzo::update_shock_clock() {
    if (TObjChara::update_shock_clock() != 0) {
        cancel_fade_state();
        return 1;
    }
    return 0;
}
#pragma pop

#pragma push
s32 TObjEneGyaranzo::update_movement_status() {
    if (TObjChara::update_movement_status() != 0) {
        cancel_fade_state();
        return 1;
    }
    return 0;
}
#pragma pop

#pragma push
void TObjEneGyaranzo::cancel_fade_state() {
    if ((s32)next_action == 7) {
        m_388 &= ~1;
        update_if_active(0);
    }
}
#pragma pop

extern "C" {
__declspec(section ".sdata2") const f32 gyaranzo_volley_fire_frame = 28.0f;
}
