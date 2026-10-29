#include "types.h"
#include "pso/enemy/TUnk_80493450.h"
#include "pso/player/TObjPlayer.h"
#include "pso/player/TObjChara.h"
#include "pso/enemy/TObjEnemy.h"
#include "pso/object/TObjMotion.h"
#include "pso/enemy/TObjEneMerillLia.h"
#include "pso/misc/TLobby.h"
#include "pso/system/BmlResource.h"
#include "pso/system/BmlResourceDescriptor.h"
#include "pso/misc/TOBoss4Rock.h"
#include "pso/object/obj_band.h"
#include "pso/system/vector.h"
#include "pso/map/CsnGroundQuery.h"
#include "pso/map/CsnQuery.h"
#include "pso/math/MatrixVector.h"
#include "pso/math/MatrixTransforms.h"
#include "pso/player/TObjPlayer_801542CC.h"
#include "pso/TObjControl.h"
#include "pso/misc/TTecKafun.h"

#include <stddef.h>
#include "pso/TParticleCtrl.h"
#include "pso/boss/TBoss3Volopt.h"
#include "pso/enemy/TObjEneMe3SinowZoa.h"
#include "pso/object/TObjFish.h"
void move_with_wall_slide(u8 *arg0);

extern "C" {
s32 copy_target_state__14TObjEnePanarmsFPv(void *, int);
s32 play_sound_effect(void *, void *, int, int);
void TObjPlayer__sub_800D92BC(s32 point, s32 delay);
f32 vec3_add_to(void *, void *);
s32 rotate_matrix_y(int, int);
s32 push_matrix_from(void *);
s32 pop_matrix();
extern Mtx34 identity_matrix;
extern const f32 TObjEneMerillLia__data_805DA300;
extern const f32 lbl_805DA304;
extern const f32 TObjEneMerillLia__data_805DA308;
extern const f32 lbl_805DA2EC;
extern const f32 lbl_805DA334;
extern const f32 lbl_805DA338;
s32 get_current_floor();
f32 xz_distance_squared(void *, void *);
void *get_player_by_client_id(s32 i);
s32 submit_cursor_candidate(void *, int);
extern const f32 TObjEneMerillLia__data_805DA2F4;
void restore_scene_lighting(void);
void select_actor_lighting(s32 obj);
void translate_matrix(u32 arg0, f32 x, f32 y, f32 z);
s32 push_matrix();
f32 post_translate_matrix(void *);
void draw_chunk_object(void *child);
extern s32 saved_model_render_flags;
extern s32 model_render_flags;
extern const f32 lbl_805DA314;
extern const f32 lbl_805DA324;
extern const f32 lbl_805DA328;
extern const f32 lbl_805DA32C;
extern const f32 lbl_805DA330;
extern BmlResource *TObjEneMerillLia__entry_params_resource;
extern s32 game_difficulty_selection;
s32 TObjEneMe3SinowZoa__sub_800D758C(void *);
s32 advance_animation_playback(void *);
s16 find_nearest_visible_player(void *, s32, f32);
s32 obj_setFlags30(void *, s32);
s32 minimap_render_dot(void *, int, int, int);
s32 matrix_mult_vec(int, void *, void *);
extern MerillLiaCombatParameters **TObjEneMerillLia__rock_param_table;
extern s32 anim_model_matrix_array;
extern const f32 lbl_805DA30C;
extern const f32 lbl_805DA310;
s32 apply_actor_gravity(void *, int, f32);
s32 enemy_move_toward(void *, s32, void *, int, f32);
f32 horizontal_distance_squared(void *, void *);
extern const f32 lbl_805DA31C;
extern const f32 lbl_805DA320;
void attach_particle_model(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, f32 farg0);
void *spawn_particle_effect(void *pos, s32 id);
void fn_800D88E4(void *pos);
s32 rand(void);
extern s32 actor_frame_tick;
extern const f32 lbl_805DA2F0;
extern const f32 lbl_805DA2F8;
extern const f32 lbl_805DA2FC;
f32 enemy_backstep_from_point(void *, void *, f32);
f32 normalize_vector(void *);
extern const f32 lbl_805DA318;
f32 fabs_float(f32);
f64 atan2_float(f32, f32);
s32 approach_angle_limited(s32, s32, s32);
s32 pop_matrices(int);
extern Vec lbl_8050BEE0;
extern Vec lbl_8050BF00;
void * TObjEneMerillLia__create(void *arg0);
void TLobby__sub_8001FE7C(void*, int);
s32 is_split_screen(void);
u8 *load_resource_from_descriptor(void *, s32, BmlResourceDescriptor *, s32, s32, s32);
void TObjEneMerillLia__sub_800D6D64(void);

extern "C" u8 lbl_8043C478[];
extern "C" u8 lbl_8043C494[];
extern "C" u8 lbl_8043C4B0[];
extern "C" u8 lbl_8043C4D4[];
extern "C" u8 lbl_8043C4F4[];
extern "C" u8 lbl_8043C514[];
extern "C" u8 lbl_8043C538[];
extern "C" u8 lbl_8043C558[];
extern "C" u8 lbl_8043C578[];
extern "C" u8 lbl_8043C598[];
extern "C" u8 lbl_8043C5BC[];
extern "C" u8 lbl_8043C5DC[];
extern "C" u8 lbl_8043C5F4[];
extern "C" u8 lbl_8043C614[];
extern "C" u8 lbl_8043C634[];
extern "C" u8 lbl_8043C650[];
extern "C" u8 lbl_8043C66C[];
extern "C" u8 lbl_8043C68C[];
const char *lbl_804944D0[3] = {
    (const char *)lbl_8043C478, (const char *)lbl_8043C494, NULL,
};
const char *lbl_804944DC[13] = {
    (const char *)lbl_8043C4B0, (const char *)lbl_8043C4D4, (const char *)lbl_8043C4F4, (const char *)lbl_8043C514,
    (const char *)lbl_8043C538, (const char *)lbl_8043C558, (const char *)lbl_8043C578, (const char *)lbl_8043C598,
    (const char *)lbl_8043C5BC, (const char *)lbl_8043C5DC, (const char *)lbl_8043C5F4, (const char *)lbl_8043C614,
    NULL,
};
BmlResourceDescriptor bm_ene_re8_merill_lia_resource_descriptor = {
    (const char *)lbl_8043C634, (const char *const *)lbl_804944D0, (const char *const *)lbl_804944DC, 2, 12,
};
const char *lbl_80494520[3] = {
    (const char *)lbl_8043C650, (const char *)lbl_8043C66C, NULL,
};
const char *lbl_8049452C[13] = {
    (const char *)lbl_8043C4B0, (const char *)lbl_8043C4D4, (const char *)lbl_8043C4F4, (const char *)lbl_8043C514,
    (const char *)lbl_8043C538, (const char *)lbl_8043C558, (const char *)lbl_8043C578, (const char *)lbl_8043C598,
    (const char *)lbl_8043C5BC, (const char *)lbl_8043C5DC, (const char *)lbl_8043C5F4, (const char *)lbl_8043C614,
    NULL,
};
BmlResourceDescriptor bm_ene_re8_merill_lia_low_resource_descriptor = {
    (const char *)lbl_8043C68C, (const char *const *)lbl_80494520, (const char *const *)lbl_8049452C, 2, 12,
};
TObjMotionAction lbl_80494570[14] = {
    {1, 0, 5, 0.6f, 1}, {1, 1, 6, 0.8f, 1}, {1, 2, 8, 0.6f, 1},
    {2, 0, 1, 0.8f, 4}, {2, 0, 2, 1.0f, 4}, {1, 0, 9, 1.0f, 1},
    {2, 0, 3, 0.8f, 8}, {2, 0, 7, 0.8f, 0x20},
    {3, 0, 4, 0.6f, 0x10}, {3, 0, 4, 0.6f, 0x10},
    {2, 0, 5, 0.6f, 0x20}, {2, 0, 0, 0.5f, 0x20},
    {2, 0, 10, 0.7f, 4}, {2, 1, 11, 0.6f, 0x20},
};
MerillLiaMovementParameters lbl_80494650[3] = {
    {225.0f, 0.4f, 0x400, 0, 0x1e0000, 1, 0},
    {250.0f, 0.55f, 0x400, 0, 0x1e0000, 1, 0},
    {300.0f, 0.7f, 0x400, 0, 0x1e0000, 1, 0},
};
CollisionBody lbl_804946A4[3] = {
    {{0.0f, 7.5f, 0.0f}, 8.0f, 0.0f, 0, 0x8003, {0.0f, 0.0f, 0.0f}, 0.0f},
    {{0.0f, 7.5f, 0.0f}, 8.0f, 0.0f, 0, 0x8003, {0.0f, 0.0f, 0.0f}, 0.0f},
    {{0.0f, 10.0f, 0.0f}, 8.0f, 0.0f, 0, 0x8003, {0.0f, 0.0f, 0.0f}, 0.0f},
};
// The motion set TLobby::spawn_npc_enemy copies for each spawned part.
struct NpcSpawnMotions { void *motions; void *actions; s32 initial_action; s32 counts; };

__declspec(section ".rodata") static NpcSpawnMotions merill_lia_spawn_motions = {0, lbl_80494570, 2, 0xC0000};
static const Vec zero_offset = {0, 0, 0};

void TObjEneMerillLia::vfunc_101() {}

void TObjEneMerillLia::spawn_ground_effect() {
    Vec stack;
    s32 particle_effect;
    CsnGroundHit *hit;
    VecCopy(&stack, &position);
    stack.y += lbl_805DA2EC;
    hit = (CsnGroundHit *)csnVectorUnder(&stack, (u32 *)&m_120, 5);
    if ((hit != NULL) && (hit->flags & 4)) {
        if (((s32) ((f32) actor_frame_tick * (lbl_805DA2F0 * (f32) rand())) % 5) == 0) {
            particle_effect = (s32)spawn_particle_effect(&hit->surface->point_38, 0x49);
            if (particle_effect != 0) {
                attach_particle_model((u8 *)particle_effect, (s32)(TParticleCtrl::get_particle_model(2)), (s32)(TParticleCtrl::get_instance()), 0, 1, (f32)TObjEneMerillLia__data_805DA2F4);
            }
            spawn_particle_effect(&hit->surface->point_38, 0xA4);
        }
        if ((objInBand((GameObj *)this, (f32)lbl_805DA2F8) != 0) || (objInBand((GameObj *)this, lbl_805DA2FC) != 0)) {
            fn_800D88E4(&position);
        }
    }
}

void TObjEneMerillLia::fn_800D4EC8() {
    play_sound_effect((void *) (copy_target_state__14TObjEnePanarmsFPv(this, 0x3AD04)), &position, 0, 0);
}

void TObjEneMerillLia::vfunc_99() {
    play_sound_effect((void *) (copy_target_state__14TObjEnePanarmsFPv(this, 0x3B205)), &position, 0, 0);
}

void TObjEneMerillLia::vfunc_98() {
    play_sound_effect((void *) (copy_target_state__14TObjEnePanarmsFPv(this, 0x3AD00)), &position, 0, 0);
}

void TObjEneMerillLia::vfunc_97() {
    play_sound_effect((void *) (copy_target_state__14TObjEnePanarmsFPv(this, 0x3B201)), &position, 0, 0);
}

void TObjEneMerillLia::vfunc_96() {
    play_sound_effect((void *) (copy_target_state__14TObjEnePanarmsFPv(this, 0x3AB02)), &position, 0, 0);
}

void TObjEneMerillLia::fn_800D501C() {
    play_sound_effect((void *) (copy_target_state__14TObjEnePanarmsFPv(this, 0x3B206)), &position, 0, 0);
}

void TObjEneMerillLia::vfunc_94() {
    Vec stack;
    stack.x = TObjEneMerillLia__data_805DA300;
    stack.y = lbl_805DA304;
    stack.z = TObjEneMerillLia__data_805DA308 * ((MerillLiaAttackParameters *)m_2b0)->field_10;
    push_matrix_from((void *)&identity_matrix);
    rotate_matrix_y(0, this->rotation_y);
    rotate_vector_by_matrix(0, &stack, &stack);
    pop_matrix();
    vec3_add_to((void *)&stack.x, &position);
    ((TObjPlayer *)(&stack.x))->spawn_ground_effect(0x23);
    TObjPlayer__sub_800D92BC((s32)&stack.x, 0xF);
}

void TObjEneMerillLia::vfunc_93() {}

s32 TObjEneMerillLia::get_clamped_level() {
    MerillLiaAttackParameters *p = (MerillLiaAttackParameters *)this->m_2b0;
    s32 v = 0;
    if (p != 0) {
        v = p->technique_level;
        if (v < 0) {
            v = 0;
        } else if (game_difficulty_selection == 3) {
            if (v > 0x1d) {
                v = 0x1d;
            }
        } else if (v > 0xe) {
            v = 0xe;
        }
    }
    return v;
}

void TObjEneMerillLia::clamp_and_apply_mode_param() {
    if ((s32)subtype < 0) {
        subtype = 0;
    } else if ((s32)subtype > 1) {
        subtype = 1;
    }
    switch ((s32)subtype) {
    case 1:
        variant = 1;
        set_param(0x35);
        break;
    default:
        variant = 0;
        set_param(0x34);
        break;
    }
}

void TObjEneMerillLia::vfunc_59() {
    if (obj_testFlags30(0x1000) != 0) {
        this->mode = 4;
    }
    switch (this->mode) {
    case 0:
    case 2:
    case 3:
    case 10:
    case 11:
    case 12:
    case 13:
        break;
    case 1:
        this->phase = 0;
        if (this->children == NULL) {
            this->mode = 3;
            this->m_b8 = 7;
        } else {
            this->mode = 2;
            this->m_b8 = 10;
        }
        obj_clearFlags30(0x4040000);
        clear_player_status_flag(0, 0xA000000);
        break;
    case 4:
        this->m_b8 = 5;
        break;
    default:
        this->mode = 3;
        this->phase = 1;
        this->m_b8 = 2;
        obj_clearFlags30(0x4040000);
        clear_player_status_flag(0, 0xA000000);
        break;
    }
}

extern void *tl_04;

f32 get_collision_body_radius(void *, s32);
s32 check_path_obstructed(void *, void *);

extern u8 **TObjEneMerillLia__rock_stats_table;
extern u8 **merill_lia_rock_buffer;
extern u8 **merill_lia_rock_aux_buffer;
extern const f32 lbl_805DA33C;

extern s32 lbl_805D2A88;
extern const f32 lbl_805DA340;
extern const f32 lbl_805DA344;

#pragma defer_codegen on
void TObjEneMerillLia::load_entry_params(s32 i) {
    model = (void *)TObjEneMerillLia__entry_params_resource->models[i].model;
    texlist = TObjEneMerillLia__entry_params_resource->models[i].m_c;
}

TObjEneMerillLia::TObjEneMerillLia(TObject *parent, void *arg2) : TUnk_80493450(parent) {

    m_name = (const char *)lbl_805D2A88;
    apply_set_data(arg2);
    this->init_params_from_position();
    ((TObjPlayer *)this)->init_position_vectors();
    this->subtype = this->variant;
    this->clamp_and_apply_mode_param();
    this->load_entry_params(this->variant);
    action_table = lbl_80494570;
    this->set_field_d8((s32)(action_table));
    motion_list = TObjEneMerillLia__entry_params_resource->motions;
    this->m_b8 = 0;
    this->set_animation(this->m_b8);
    this->set_field_b8(this->m_b8);
    init_collision_body_parts(this, &lbl_804946A4[subtype], 1);
    this->bind_enemy_combat_stats(TObjEneMerillLia__rock_stats_table[subtype], merill_lia_rock_buffer[subtype], merill_lia_rock_aux_buffer[subtype]);
    movementParameters = &lbl_80494650[subtype];
    this->referenceHp = this->hp;
    this->update_prev_position();
    refresh_center_from_body();
    register_object_by_id();
    this->m_2ac = (s32)(lbl_805DA340 * (lbl_805DA344 * random_ratio()));
    this->resetTimer = 0xF;
    this->timer = this->resetTimer;
    this->phase = 0;
    this->m_374 = 0;
    this->m_376 = 0;
    this->m_378 = 0;
    this->m_37c = 0;
    this->add_flags_2e4(2);
    obj_setFlags30(this, 0x40000);
    this->unk_380 = TObjEneMerillLia__data_805DA300;
    this->m_398 = TObjEneMerillLia__rock_param_table[subtype]->distance;
    this->m_3a0 = TObjEneMerillLia__rock_param_table[subtype]->unknown_04;
    this->unk_39C = TObjEneMerillLia__rock_param_table[subtype]->unknown_08;
    this->unk_3A4 = TObjEneMerillLia__rock_param_table[subtype]->unknown_0c;
    this->backstep_distance = TObjEneMerillLia__rock_param_table[subtype]->backstep_distance;
    this->hurt_hp_fraction = TObjEneMerillLia__rock_param_table[subtype]->hurt_hp_percent / lbl_805DA338;
    this->m_390 = 1;
    this->mode = 0xD;
    this->m_b8 = 1;
    clear_lobby_object_state();
}

TObjEneMerillLia::~TObjEneMerillLia() {
    unlink_enemy_group_relations();
    free_collision_body_parts(this);
}

#pragma push
#pragma opt_loop_invariants off
void TObjEneMerillLia__sub_800D6D64(void) {
    s32 i;
    u8 *res;

    if (is_split_screen() != 0) {
        res = (u8 *)::operator new(0x440);
        if (res != NULL) {
            res = load_resource_from_descriptor(res, 1, &bm_ene_re8_merill_lia_low_resource_descriptor, 0, 0, 0);
        }
        TObjEneMerillLia__entry_params_resource = (BmlResource *)res;
    } else {
        res = (u8 *)::operator new(0x440);
        if (res != NULL) {
            res = load_resource_from_descriptor(res, 1, &bm_ene_re8_merill_lia_resource_descriptor, 0, 0, 0);
        }
        TObjEneMerillLia__entry_params_resource = (BmlResource *)res;
    }
    lbl_804946A4[0].radius = lbl_805DA2F8;
    lbl_804946A4[1].radius = lbl_805DA2F8;
    lbl_804946A4[2].radius = lbl_805DA33C;
    TObjEneMerillLia__rock_stats_table = (u8 **)mem_alloc(8);
    merill_lia_rock_buffer = (u8 **)mem_alloc(8);
    merill_lia_rock_aux_buffer = (u8 **)mem_alloc(8);
    TObjEneMerillLia__rock_param_table = (MerillLiaCombatParameters **)mem_alloc(8);
    TObjEneMerillLia__rock_stats_table[0] = (u8 *)TLobby::register_boss(75);
    TObjEneMerillLia__rock_stats_table[1] = (u8 *)TLobby::register_boss(76);
    merill_lia_rock_buffer[0] = (u8 *)TLobby::dispatch_shared_handler_b(78);
    merill_lia_rock_buffer[1] = (u8 *)TLobby::dispatch_shared_handler_b(79);
    merill_lia_rock_aux_buffer[0] = (u8 *)TLobby::register_object(74);
    merill_lia_rock_aux_buffer[1] = (u8 *)TLobby::register_object(75);
    TObjEneMerillLia__rock_param_table[0] = (MerillLiaCombatParameters *)TLobby::dispatch_shared_handler_a(74);
    TObjEneMerillLia__rock_param_table[1] = (MerillLiaCombatParameters *)TLobby::dispatch_shared_handler_a(75);
    {
        s16 ids[2] = {44, 46};
        NpcSpawnMotions motions = merill_lia_spawn_motions;
        motions.motions = TObjEneMerillLia__entry_params_resource->motions;
        for (i = 0; i < 2; i++) {
            TLobby::spawn_npc_enemy(ids[i], TObjEneMerillLia__entry_params_resource->models[i].model,
                TObjEneMerillLia__entry_params_resource->models[i].m_c, (s32)&motions,
                lbl_804946A4[i].radius, TObjEneMerillLia__data_805DA300);
        }
    }
}
#pragma pop

void TObjEneMerillLia::destroy_rocks() {
    if (TObjEneMerillLia__rock_stats_table != NULL) {
        mem_free(TObjEneMerillLia__rock_stats_table);
        TObjEneMerillLia__rock_stats_table = NULL;
    }
    if (merill_lia_rock_buffer != NULL) {
        mem_free(merill_lia_rock_buffer);
        merill_lia_rock_buffer = NULL;
    }
    if (merill_lia_rock_aux_buffer != NULL) {
        mem_free(merill_lia_rock_aux_buffer);
        merill_lia_rock_aux_buffer = NULL;
    }
    if (TObjEneMerillLia__rock_param_table != NULL) {
        mem_free(TObjEneMerillLia__rock_param_table);
        TObjEneMerillLia__rock_param_table = NULL;
    }
    if (TObjEneMerillLia__entry_params_resource != NULL) {
        TLobby__sub_8001FE7C(TObjEneMerillLia__entry_params_resource, 1);
        TObjEneMerillLia__entry_params_resource = NULL;
    }
}

void *TObjEneMerillLia__create(void *set_data) {
    TObjControl *control = new TObjControl((TObject *)tl_04);
    return new TObjEneMerillLia(control, set_data);
}

void TObjEneMerillLia::run_task() {
    s16 current_mode;
    if (TObjPlayer::check_demo_mode() == 1) {
        this->vfunc_101();
        return;
    }
    current_mode = this->mode;
    switch (current_mode) {
    case 0:
        this->vfunc_83();
        break;
    case 1:
        this->beast_idle_update();
        break;
    case 2:
        this->update_turn_toward_target();
        break;
    case 3:
        this->beast_update_approach();
        break;
    case 4:
        this->beast_update_group_chase();
        break;
    case 5:
        this->beast_update_attack();
        break;
    case 6:
        this->vfunc_89();
        break;
    case 7:
        this->beast_update_hurt();
        break;
    case 8:
        this->beast_update_dead();
        break;
    case 9:
        this->beast_retire_corpse();
        break;
    case 10:
        update_kafun_attack();
        break;
    case 11:
        update_emerge_state();
        break;
    case 12:
        search_target();
        break;
    case 13:
        this->sub_800D5570();
        break;
    }
    this->update_prev_position();
    refresh_center_from_body();
    submit_cursor_candidate((void *) this, -1);
    this->m_2b4 = (f32) ((this->m_2b4) + TObjEneMerillLia__data_805DA2F4);
}

void TObjEneMerillLia::select_action_by_distance() {
    if (random_ratio() <= this->melee_probability) {
        init_attack_state();
        return;
    }
    if (random_ratio() <= this->kafun_probability) {
        reset_action_state();
    }
}

#pragma push
#pragma opt_common_subs off
void TObjEneMerillLia::init_params_from_position() {
    this->chase_frames = (s16) ((s32) this->parameters[3] + 0x12C);
    this->melee_probability = (f32) (this->parameters[0] - lbl_805DA334);
    if (this->melee_probability < TObjEneMerillLia__data_805DA300) {
        this->melee_probability = (f32) TObjEneMerillLia__data_805DA300;
    }
    this->kafun_probability = (f32) (this->parameters[2] - lbl_805DA334);
    if (this->kafun_probability < TObjEneMerillLia__data_805DA300) {
        this->kafun_probability = (f32) TObjEneMerillLia__data_805DA300;
    }
    this->search_radius = (f32) (lbl_805DA338 + this->parameters[4]);
    if (this->search_radius < lbl_805DA2EC) {
        this->search_radius = (f32) lbl_805DA2EC;
    }
}
#pragma pop

void TObjEneMerillLia::render() {
    Vec render_offset;
    s32 draw_model;
    s16 current_mode;
    s32 view_detail;
    s32 fade_active;
    view_detail = classify_actor_view_detail(lbl_805DA324, lbl_805DA328, lbl_805DA314);
    if (view_detail != 0) {
        saved_model_render_flags = model_render_flags;
        select_actor_lighting((s32)this);
        TObjFish::set_global_param((int) texlist);
        push_matrix();
        translate_matrix(0, (f32) TObjEneMerillLia__data_805DA300, (f32) unk_380, (f32) TObjEneMerillLia__data_805DA300);
        post_translate_matrix(&position);
        rotate_matrix_y(0, (int) rotation_y);
        if (TObjPlayer::check_demo_mode() == 1) {
            draw_chunk_object(model);
        } else {
            TObjPlayer::toggle_particle_effect();
            draw_model = 1;
            fade_active = 0;
            if (((s16) mode) == 0xD) {
                fade_active = 1;
                draw_model = ((MaterialColorFade *)&fade)->has_visible_opacity();
            }
            if (fade_active != 0) {
                ((MaterialColorFade *)&fade)->set_flags_and_apply_damage_color();
                if (defer_render() != 0) {
                    draw_model = 0;
                }
            }
            if (draw_model != 0) {
                if (view_detail == 1) {
                    TObjPlayer::set_global_flag();
                    this->draw();
                    TObjPlayer::clear_global_state();
                } else {
                    TObjPlayer::set_global_flag();
                    this->render_world_model();
                    TObjPlayer::clear_global_state();
                }
            }
            TParticleCtrl::end_effect_render();
            if (fade_active != 0) {
                ((MaterialColorFade *)&fade)->clear_flag_and_notify();
            }
        }
        pop_matrix();
        restore_scene_lighting();
        current_mode = mode;
        if ((current_mode >= 0xA) || (current_mode < 8)) {
            render_offset.x = lbl_805DA32C;
            render_offset.y = TObjEneMerillLia__data_805DA2F4;
            render_offset.z = lbl_805DA330;
            this->render_with_position_override((u8 *)&render_offset.x, 0);
        }
    }
}

void TObjEneMerillLia::beast_update_approach() {
    Vec sp14;
    f32 r;
    switch (this->phase) {
    case 0:
        apply_actor_gravity(this, 0, TObjEneMerillLia__data_805DA300);
        advance_animation_playback(this);
        if (this->m_b4 != 0x20U) {
            this->phase = 1;
            this->m_b8 = 2;
        }
        break;
    default:

        spawn_ground_effect();
        if (target != NULL) {
            if (test_elt_flag(0, 0x300000) != 0) {
                if (this->m_38c++ < lbl_805DA31C) {
                    VecCopy((Vec *)&sp14, &this->home_position);
                } else {
                    VecCopy((Vec *)&sp14, (const Vec *)&((TObjChara *)target)->m_2fc);
                }
            } else {
                this->m_38c = 0U;
                VecCopy((Vec *)&sp14, (const Vec *)&((TObjChara *)target)->m_2fc);
            }
            this->update_target_near_flag();
            this->select_target_proximity_movement();
            advance_animation_playback(this);
            {
                Vec sp8 = sp14;
                enemy_move_toward(this, ((MerillLiaMovementParameters *)movementParameters)->turn_speed, &sp8, 0, unk_394);
            }
            if (this->targetId == 0xFFFF) {
                if (horizontal_distance_squared((u8 *)&this->position_29c, (u8 *)&this->position) < (r = unk_394 + bodies->radius) * r ||
                    lbl_805DA320 < (f32) (*(s32 *)&this->m_2ac)++) {
                    target = NULL;
                    *(s32 *)&this->m_2ac = 0;
                }
            }
        }
        break;
    }
    this->update_collisions();
    update_enemy_collision_flags();
    minimap_render_dot((u8 *)&this->position, -0x5DB4, 1, 0);
    this->obj_clearFlags30(0x200000);
}

void TObjEneMerillLia::vfunc_83() {
    switch (this->phase) {
    case 0:
    default:
        if (this->m_390 != 1) {
            this->phase = 2;
        } else {
            this->phase = 1;
            this->m_b8 = 0xB;
            this->set_indexed_flags(0, 0xA000000);
            obj_setFlags30(this, 0x4000000);
            this->vfunc_97();
        }
        break;
    case 1:

        spawn_ground_effect();
        if (objInBand((GameObj *)this, (f32)lbl_805DA304) != 0) {

            fn_800D501C();
        }
        if (this->m_b4 != 0x20) {
            this->phase = 2;
            this->m_390 = 0;
            this->m_b8 = 0;
            this->clear_player_status_flag(0, 0xA000000);
            this->obj_clearFlags30(0x4000000);
        }
        break;
    case 2:
        this->targetId = find_nearest_visible_player(this, 0, ((MerillLiaMovementParameters *)this->movementParameters)->range);
        this->mode = 1;
        break;
    }
    advance_animation_playback(this);
}

#pragma push
#pragma fp_contract on
void TObjEneMerillLia::beast_update_group_chase() {
    Vec save;
    Vec to;
    Vec d;
    f32 dist;
    advance_animation_playback(this);
    switch (this->phase) {
    case 0:
        this->phase = 1;
        this->vfunc_99();
        break;
    case 1:
        if (this->target != NULL) {
            spawn_ground_effect();
            save.x = this->position.x;
            save.y = this->position.y;
            save.z = this->position.z;
            if (this->backstep_distance <= TObjEneMerillLia__data_805DA300) {
                Vec a = *(Vec *)&((TObjChara *)this->target)->m_2fc;
                dist = enemy_backstep_from_point(this, &a, this->m_398);
            } else {
                Vec b = *(Vec *)&((TObjChara *)this->target)->m_2fc;
                dist = enemy_backstep_from_point(this, &b, this->backstep_distance);
            }
            this->turn_toward_direction(((MerillLiaMovementParameters *)this->movementParameters)->turn_speed, (Vec *)&this->x_speed);
            this->m_374--;
            if (dist < (this->m_398 + this->bodies->radius) * (this->m_398 + this->bodies->radius) || this->m_374 < 0) {
                this->phase = 2;
                this->m_374 = 0;
            }
            this->update_collisions();
            update_enemy_collision_flags();
            if (this->bodies->flags & 0x380000) {
                this->phase = 2;
                this->m_374 = 0;
                break;
            }
            d.x = this->position.x - save.x;
            d.y = this->position.y - save.y;
            d.z = this->position.z - save.z;
            normalize_vector(&d);
            to.x = lbl_805DA314 * d.x + this->position.x;
            to.y = lbl_805DA314 * d.y + this->position.y;
            to.z = lbl_805DA314 * d.z + this->position.z;
            if (csnVector(&save, &to, 0x88E0) != 0) {
                this->phase = 2;
                this->m_374 = 0;
            }
            break;
        }
        if (this->is_actor_cadence_frame(0x1E) != 0) {
            this->targetId = find_nearest_visible_player(this, 0, ((MerillLiaMovementParameters *)this->movementParameters)->range);
        }
        if (this->targetId < 0x1000) {
            TObjPlayer *p = (TObjPlayer *)get_player_by_client_id(this->targetId);
            if (p != NULL && p->get_field_3e4() == get_current_floor()) {
                this->target = (u8 *)p;
                break;
            }
            this->target = NULL;
            this->reset_state_clear_status();
            break;
        }
        this->target = NULL;
        this->reset_state_clear_status();
        break;
    case 2:
        this->obj_clearFlags30(0x1000);
        if (this->is_actor_cadence_frame(0x1E) != 0) {
            this->targetId = find_nearest_visible_player(this, 0, ((MerillLiaMovementParameters *)this->movementParameters)->range);
        }
        if (this->targetId < 0x1000) {
            TObjPlayer *p = (TObjPlayer *)get_player_by_client_id(this->targetId);
            if (p != NULL && p->get_field_3e4() == get_current_floor() &&
                xz_distance_squared(&p->position, &this->position) < lbl_805DA318) {
                this->mode = 1;
                this->phase = 0;
                this->m_b8 = 0xA;
                this->obj_clearFlags30(0x4040000);
                this->clear_player_status_flag(0, 0xA000000);
                break;
            }
            this->reset_state_clear_status();
        } else {
            this->reset_state_clear_status();
        }
        break;
    }
    this->update_collisions();
    update_enemy_collision_flags();
    minimap_render_dot(&this->position, -0x5DB4, 1, 0);
}
#pragma pop

#pragma push
#pragma opt_common_subs off
void TObjEneMerillLia::beast_idle_update() {
    this->update_target_near_flag();
    this->select_target_proximity_movement();
    advance_animation_playback(this);
    if (this->phase != 1) {
        this->phase = 1;
        this->link_into_group_chain();
        this->m_378 = this->has_group();
    }
    this->m_37c = this->countChildren();
    {
        TObjEneMerillLia *p = (TObjEneMerillLia *)this->next;
        if (p != NULL) {
            s32 diff = (s32)p->m_37c - (s32)this->m_37c;
            if (diff > 1) {
                this->link_last_group_child((TObjEnemy *)p, (TObjEnemy *)this);
                this->m_37c++;
                p->m_37c--;
            } else if (diff < -1) {
                this->link_last_group_child((TObjEnemy *)this, (TObjEnemy *)p);
                this->m_37c--;
                p->m_37c++;
            }
        }
    }
    {
        f32 dist = horizontal_distance_squared(&this->position, &this->home_position);
        f32 r = this->parameters[1] + (((MerillLiaMovementParameters *)this->movementParameters)->speed + this->bodies->radius);
        if (r * r < dist) {
            Vec *d;
            Vec *v;
            s32 ang;
            VecCopy((Vec *)&this->position_29c, (const Vec *)&this->home_position);
            VecCopy((Vec *)&this->position_290, (const Vec *)&this->m_2fc);
            VecCopy((Vec *)&this->prev_position, (const Vec *)&this->position);
            VecCopy((Vec *)&lbl_8050BEE0, (const Vec *)&this->home_position);
            subtract_vector(&lbl_8050BEE0, &this->position);
            d = &lbl_8050BEE0;
            ang = (s32)(10430.38043493439 * atan2_float(d->x, d->z));
            v = &lbl_8050BF00;
            v->x = v->y = TObjEneMerillLia__data_805DA300;
            v->z = this->unk_394;
            push_matrix_from(&identity_matrix);
            rotate_matrix_y(0, ang);
            rotate_vector_by_matrix(0, &lbl_8050BF00, &lbl_8050BF00);
            pop_matrices(1);
            vec3_add_to(&lbl_8050BF00, &this->position);
            if (project_actor_to_ground(this, &lbl_8050BF00, 0) == 1) {
                this->m_b8 = 2;
                VecCopy((Vec *)&this->position, (const Vec *)&lbl_8050BF00);
                this->rotation_y = approach_angle_limited(this->rotation_y, ang, ((MerillLiaMovementParameters *)this->movementParameters)->turn_speed);
            } else {
                f32 rr = fabs_float(d->z);
                if (fabs_float(lbl_8050BEE0.x) < rr) {
                    ang = (s32)(10430.38043493439 * atan2_float(lbl_8050BEE0.x, TObjEneMerillLia__data_805DA300));
                } else {
                    ang = (s32)(10430.38043493439 * atan2_float(TObjEneMerillLia__data_805DA300, d->z));
                }
                v->y = TObjEneMerillLia__data_805DA300;
                lbl_8050BF00.x = TObjEneMerillLia__data_805DA300;
                v->z = this->unk_394;
                push_matrix_from(&identity_matrix);
                rotate_matrix_y(0, ang);
                rotate_vector_by_matrix(0, &lbl_8050BF00, &lbl_8050BF00);
                pop_matrices(1);
                vec3_add_to(&lbl_8050BF00, &this->position);
                if (project_actor_to_ground(this, &lbl_8050BF00, 0) == 1) {
                    this->m_b8 = 2;
                    VecCopy((Vec *)&this->position, (const Vec *)&lbl_8050BF00);
                    this->rotation_y = approach_angle_limited(this->rotation_y, ang, ((MerillLiaMovementParameters *)this->movementParameters)->turn_speed);
                } else {
                    s32 ang2;
                    rr = fabs_float(d->z);
                    if (fabs_float(lbl_8050BEE0.x) < rr) {
                        ang2 = (s32)(10430.38043493439 * atan2_float(TObjEneMerillLia__data_805DA300, d->z));
                    } else {
                        ang2 = (s32)(10430.38043493439 * atan2_float(lbl_8050BEE0.x, TObjEneMerillLia__data_805DA300));
                    }
                    v->y = TObjEneMerillLia__data_805DA300;
                    lbl_8050BF00.x = TObjEneMerillLia__data_805DA300;
                    v->z = this->unk_394;
                    push_matrix_from(&identity_matrix);
                    rotate_matrix_y(0, ang2);
                    rotate_vector_by_matrix(0, &lbl_8050BF00, &lbl_8050BF00);
                    pop_matrices(1);
                    vec3_add_to(&lbl_8050BF00, &this->position);
                    if (project_actor_to_ground(this, &lbl_8050BF00, 0) == 1) {
                        this->m_b8 = 2;
                        VecCopy((Vec *)&this->position, (const Vec *)&lbl_8050BF00);
                        this->rotation_y = approach_angle_limited(this->rotation_y, ang2, ((MerillLiaMovementParameters *)this->movementParameters)->turn_speed);
                    } else {
                        this->m_b8 = 2;
                    }
                }
            }
        } else if ((s32)this->m_37c == 0 && TObjEneMerillLia__data_805DA300 < this->parameters[1]) {
            f32 w;
            this->m_b8 = 2;
            w = this->parameters[1];
            MerillLiaMovementParameters *movement = (MerillLiaMovementParameters *)this->movementParameters;
            f32 speed = movement->speed;
            s32 turn_speed = movement->turn_speed;
            this->enemy_wander_home(speed, w, w, turn_speed);
        } else {
            this->reset_state_clear_status();
        }
    }
    if (this->obj_testFlags30(0x800000) == 0) {
        apply_actor_gravity(this, 0, TObjEneMerillLia__data_805DA300);
    }
    this->refresh_collision_body_centers();
    minimap_render_dot(&this->position, -0x5DB4, 1, 0);
    this->obj_clearFlags30(0x04240000);
    this->clear_player_status_flag(0, 0x0A000000);
}
#pragma pop

void TObjEneMerillLia::beast_update_hurt() {
    Vec pos;

    advance_animation_playback(this);
    VecCopy((Vec *)&pos, (const Vec *)(&m_2fc));
    lbl_8050BEE0.y = TObjEneMerillLia__data_805DA300;
    lbl_8050BEE0.x = TObjEneMerillLia__data_805DA300;
    lbl_8050BEE0.z = get_collision_body_radius(this, 0);
    push_matrix_from(&identity_matrix);
    rotate_matrix_y(0, -this->rotation_y);
    rotate_vector_by_matrix(0, &lbl_8050BEE0, &lbl_8050BEE0);
    pop_matrix();
    vec3_add_to(&pos, &lbl_8050BEE0);
    pos.x = pos.x + this->x_speed;
    pos.z = pos.z + this->m_310;
    if (check_path_obstructed(this, &pos) == 0) {
        move_with_wall_slide((u8 *)this);
        this->x_speed = this->x_speed * TObjEneMerillLia__data_805DA308;
        this->m_310 = this->m_310 * TObjEneMerillLia__data_805DA308;
    } else {
        this->m_310 = TObjEneMerillLia__data_805DA300;
        this->x_speed = TObjEneMerillLia__data_805DA300;
    }
    this->update_collisions();
    update_enemy_collision_flags();
    if (objInBand((GameObj *)this, TObjEneMerillLia__data_805DA300) != 0) {
        this->vfunc_97();
    }
    if (this->m_b4 != 8) {
        this->obj_clearFlags30(0x600);
        this->clear_player_status_flag(0, 0x04000000);
        if ((f32)this->hp <= (f32)this->hpmax * this->hurt_hp_fraction) {
            this->select_action_by_distance();
        }
        this->referenceHp = this->hp;
    }
    minimap_render_dot(&position, -0x5DB4, 1, 0);
}

void TObjEneMerillLia::update_kafun_attack() {
    Vec sp14;
    advance_animation_playback(this);
    switch (this->phase) {
    default:
    case 0:
        this->phase = 1;
        this->m_b8 = 0xC;
        obj_setFlags30(this, 0x200000);
        this->obj_clearFlags30(0x04040000);
        this->clear_player_status_flag(0, 0x0A000000);
        break;
    case 1:
        if (objInBand((GameObj *)(this), (f32)lbl_805DA30C) != 0) {
            advance_animation_playback(this);
            push_matrix_from(&identity_matrix);
            post_translate_matrix(&position);
            rotate_matrix_y(0, this->rotation_y);
            this->render_anim_model(lbl_805DA30C);
            pop_matrix();
            push_matrix_from((void *)(anim_model_matrix_array + 0x450));
            {
                Vec sp8 = zero_offset;
                matrix_mult_vec(0, &sp8, &sp14);
            }
            pop_matrix();
            TTecKafun::create((s32)this, (s32)&sp14, 0xF, 0xD3, this->get_clamped_level(), TObjEneMerillLia__rock_param_table[subtype]->kafun_power, lbl_805DA310);

            fn_800D4EC8();
        }
        if ((u32) this->m_b4 != 4U) {
            this->phase = 2;
            this->m_b8 = 0;
            this->timer = 0xF;
        }
        break;
    case 2:
        (this->timer)--;
        if (this->timer < 0) {
            this->obj_clearFlags30(0x200000);
            this->timer = 0;
            if (random_ratio() <= this->melee_probability) {
                this->init_attack_state();
            } else {
                this->mode = 1;
                this->phase = 0;
                obj_setFlags30(this, 0x04040000);
                this->set_indexed_flags(0, 0x0A000000);
            }
        }
        break;
    }
    this->update_collisions();
    update_enemy_collision_flags();
    minimap_render_dot(&position, -0x5DB4, 1, 0);
}

void TObjEneMerillLia::update_emerge_state() {

    advance_animation_playback(this);
    switch (this->phase) {
    case 0:
    default:
        if ((s32) this->m_390 == 1) {
            this->phase = 2;
        } else {
            this->phase = 1;
            this->m_b8 = 0xD;
            this->set_indexed_flags(0, 0x0A000000);
            obj_setFlags30(this, 0x04000000);

            fn_800D501C();
        }
        break;
    case 1:

        spawn_ground_effect();
        if ((u32) this->m_b4 != 0x20U) {
            this->phase = 2;
            this->m_390 = 1;
            this->clear_player_status_flag(0, 0x0A000000);
            this->obj_clearFlags30(0x04040000);
        }
        break;
    case 2:
        this->mode = 0xC;
        this->m_b8 = 1;
        break;
    }
    this->update_collisions();
    update_enemy_collision_flags();
    minimap_render_dot(&position, -0x5DB4, 1, 0);
}

void TObjEneMerillLia::search_target() {
    TObjPlayer *p;
    s32 v;
    this->targetId = find_nearest_visible_player(this, 0, ((MerillLiaMovementParameters *)this->movementParameters)->range);
    if (this->targetId < 0x1000) {
        p = (TObjPlayer *)get_player_by_client_id(this->targetId);
        if (p != NULL) {
            s32 w;
            v = get_current_floor();
            w = p->get_field_3e4();
            if (w == v) {
                if (xz_distance_squared(&p->position, &this->position) < this->search_radius * this->search_radius) {
                    this->target = (u8 *)p;
                    this->mode = 0;
                    this->phase = 0;
                }
            }
        }
    }
    advance_animation_playback(this);
}

void TObjEneMerillLia::sub_800D5570() {
    switch (this->phase) {
    case 0:
    default:
        this->phase = 1;
        this->m_b8 = 1;
        TObjEneMe3SinowZoa__sub_800D758C(&fade);
        ((TBoss3Volopt *)&position)->play_area_sound_effect();
        break;
    case 1:

        spawn_ground_effect();
        if (((MaterialColorFade *)&fade)->advance_toward_max() != 0) {
            this->phase = 2;
        }
        break;
    case 2:
        this->mode = 12;
        break;
    }
    advance_animation_playback(this);
}

void TObjEneMerillLia::reset_action_state() {
    this->mode = 0xA;
    this->phase = 0;
    obj_setFlags30(this, 0x200000);
    obj_clearFlags30(0x04040000);
    clear_player_status_flag(0, 0x0A000000);
}

void TObjEneMerillLia::init_attack_state() {
    this->mode = 4;
    this->phase = 0;
    this->m_374 = (s16) this->chase_frames;
    obj_clearFlags30(0x04240000);
    clear_player_status_flag(0, 0x0A000000);
}

void TObjEneMerillLia::reset_state_clear_status() {
    this->mode = 0xB;
    this->phase = 0;
    this->target = 0;
    clear_player_status_flag(0, (s32)(0x0A000000U));
}

void TObjEneMerillLia::vfunc_58() {
    s32 current_mode;

    current_mode = this->mode;
    if (current_mode != 4) {
        if (current_mode < 4) {
            if (current_mode < 3) {
                if (current_mode >= 0) {
                    goto done;
                }
                goto reset_state;
            } else {
                goto reset_state;
            }
        } else if ((current_mode >= 0xE) || (current_mode < 0xB)) {
reset_state:
            if ((s32) this->m_390 != 0) {
                this->mode = 0;
            } else {
                this->mode = 1;
            }
            this->phase = 0;
            obj_setFlags30(this, 0x04040000);
            set_indexed_flags(0, 0x0A000000);
        }
    }
done:
    ;
}

void TObjEneMerillLia::vfunc_60() {
    switch (this->mode) {
    case 0:
    case 2:
    case 4:
    case 10:
    case 11:
    case 12:
    case 13:
        break;
    case 1:
        this->phase = 0;
        if (this->children == NULL) {
            this->mode = 3;
            this->m_b8 = 7;
        } else {
            this->mode = 2;
            this->m_b8 = 10;
        }
        obj_clearFlags30(0x4040000);
        clear_player_status_flag(0, 0xA000000);
        break;
    default:
        this->mode = 5;
        this->phase = 1;
        if (TObjEneMerillLia__data_805DA308 < random_ratio()) {
            this->m_b8 = 3;
        } else {
            this->m_b8 = 4;
        }
        obj_setFlags30(this, 0x200000);
        obj_clearFlags30(0x4040000);
        clear_player_status_flag(0, 0xA000000);
        break;
    }
}

}
