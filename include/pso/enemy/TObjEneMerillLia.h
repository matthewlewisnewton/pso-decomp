#ifndef PSO_ENEMY_TOBJENEMERILLLIA_H
#define PSO_ENEMY_TOBJENEMERILLLIA_H

#include "types.h"
#include <stddef.h>
#include "pso/enemy/TUnk_80493450.h"
#include "pso/misc/MaterialOpacityFade.h"

struct MerillLiaMovementParameters {
    f32 range;
    f32 speed;
    s32 turn_speed;
    s32 unknown_0c;
    s32 unknown_10;
    s32 unknown_14;
    s32 unknown_18;
};

struct MerillLiaCombatParameters {
    f32 distance;
    f32 unknown_04;
    f32 unknown_08;
    f32 unknown_0c;
    f32 kafun_power;
    f32 backstep_distance;
    s32 hurt_hp_percent;
};

struct MerillLiaAttackParameters {
    u32 unknown_00[4];
    f32 field_10;
    u32 unknown_14;
    s32 technique_level;
};

struct TObjEneMerillLia : public TUnk_80493450 {
    TObjEneMerillLia(TObject *parent, void *set_data);
    virtual ~TObjEneMerillLia();
    virtual void beast_idle_update();
    virtual void beast_update_hurt();
    virtual void run_task();
    virtual void render();
    virtual void beast_update_approach();
    virtual void beast_update_group_chase();
    virtual void vfunc_93();
    virtual void vfunc_94();
    virtual void vfunc_96();
    virtual void vfunc_97();
    virtual void vfunc_98();
    virtual void vfunc_99();
    virtual void vfunc_101();
    void update_fade_transition();
    void spawn_ground_effect();
    void play_kafun_attack_sound();
    void fn_800D501C();
    virtual void vfunc_83();
    virtual void vfunc_60();
    virtual void vfunc_59();
    virtual void vfunc_58();
    s32 get_clamped_level();
    void clamp_and_apply_mode_param();
    void reset_state_clear_status();
    void init_attack_state();
    void reset_action_state();
    void search_target();
    void update_emerge_state();
    void update_kafun_attack();
    void init_params_from_position();
    void select_action_by_distance();
    static void destroy_rocks();
    void load_entry_params(s32 i);
    MaterialOpacityFade fade;
    f32 melee_probability;
    f32 kafun_probability;
    f32 hurt_hp_fraction;
    f32 search_radius;
    f32 backstep_distance;
    s16 chase_frames;
    u8 unk_3DA[0x2];
};

typedef char TObjEneMerillLia_size[sizeof(TObjEneMerillLia) == 0x3DC ? 1 : -1];

typedef char MerillLia_fade_offset[offsetof(TObjEneMerillLia, fade) == 0x3A8 ? 1 : -1];
typedef char MerillLia_melee_probability_offset[offsetof(TObjEneMerillLia, melee_probability) == 0x3C4 ? 1 : -1];
typedef char MerillLia_kafun_probability_offset[offsetof(TObjEneMerillLia, kafun_probability) == 0x3C8 ? 1 : -1];
typedef char MerillLia_hurt_hp_fraction_offset[offsetof(TObjEneMerillLia, hurt_hp_fraction) == 0x3CC ? 1 : -1];
typedef char MerillLia_search_radius_offset[offsetof(TObjEneMerillLia, search_radius) == 0x3D0 ? 1 : -1];
typedef char MerillLia_backstep_distance_offset[offsetof(TObjEneMerillLia, backstep_distance) == 0x3D4 ? 1 : -1];
typedef char MerillLia_chase_frames_offset[offsetof(TObjEneMerillLia, chase_frames) == 0x3D8 ? 1 : -1];

extern "C" void *TObjEneMerillLia__create(void *set_data);

#endif
