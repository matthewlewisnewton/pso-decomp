#ifndef PSO_ENEMY_TOBJENEGIBBLES_H
#define PSO_ENEMY_TOBJENEGIBBLES_H
#include "types.h"
#include <stddef.h>
#include "pso/enemy/TObjEnemy.h"
#include "pso/enemy/TUnk_80494938.h"
#include "pso/misc/RenderFadeState.h"
#include "pso/system/BmlResource.h"

struct GibblesAiParameters {
    s32 unknown_0;
    f32 combo_wait;
    f32 pursuit_step;
    f32 jump_animation_speed;
    s32 unknown_10;
    s32 unknown_14;
    s32 jump_wait_frames;
};

struct GibblesResourceBinding {
    BmlMotionEntry *motions;
    s32 unknown_4;
    s32 unknown_8;
    s32 unknown_c;
};

struct GibblesMovementParameters {
    f32 target_range;
    f32 speed;
    s32 turn_speed;
    s32 unknown_c;
    s32 unknown_10;
    s32 unknown_14;
    s32 unknown_18;
};

struct TObjEneGibbles : public TObjEnemy {
    TObjEneGibbles(TObject *parent, void *set_data);
    virtual ~TObjEneGibbles();
    virtual void run_task();
    virtual void render();
    virtual void *get_center();
    virtual void vfunc_28();
    virtual s32 is_target_in_attack_range();
    virtual int test_flag_256();
    virtual s32 update_action_hold_status();
    virtual s32 update_movement_status();
    virtual void vfunc_58();
    virtual void vfunc_59();
    virtual void vfunc_60();
    virtual void vfunc_61();
    virtual void vfunc_62();
    virtual void vfunc_63();

    void sub_802DBC94(s32);
    void update_wander();
    void sub_802DA7A4();
    void sub_802DA0BC();
    void sub_802D8984();
    void sub_802D8140();
    u32 resolve_sound_id(u32 sound_id);
    void set_min_clamped_entry_value(s32 index, f32 value);
    s32 spawn_ground_impact_effects(const Vec *pos, f32 farg0);
    void play_distance_sound();
    void update_shadow_height();
    void update_position();
    void sync_state();
    void update_move_state();
    void update_action_state();
    void update_death_sequence();
    void update_spawn_state();
    void init_state();
    void clamp_angle(s32 arg1);
    void init_params();
    static void *create(void *arg0);
    static void free_static();
    static void load_resources();
    f32 get_pos_x();
    void turn_toward_target();
    void slam_damage_players(s32 arg1);
    void fn_802D7A54();
    s32 fn_802D7BE0();
    void fn_802D7DAC();
    void fn_802D7E3C();
    void fn_802D8034();
    void fn_802D8580();
    void fn_802D8E8C();
    void fn_802D9110();
    s32 fn_802D9A04();
    void render_and_get_joint_pos(Vec *result, s32 joint);
    bool fn_802D9644(s32, f32);
    bool fn_802D9824(s32, f32);

    s32 flags;
    u32 target_class_mask;
    s16 attack_index;
    s16 attack_count;
    s32 state_code;
    s32 last_state_code;
    s16 m_388;
    s16 reference_388;
    f32 height_offset;
    f32 vertical_step;
    f32 jump_probability;
    f32 recoil_jump_probability;
    s32 target_class_index;
    f32 state_distance;
    s32 phase_frames;
    s32 wait_frames;
    s32 unknown_3ac;
    u8 *m_3b0;
    TObjCollidable *attack_body;
    TObjCollidable *m_3b8;
    s32 render_angle;
    TUnk_80494938 material_fade;
    RenderFadeState camera_fades[4];
};
typedef char GibblesAiParameters_size[sizeof(GibblesAiParameters) == 0x1C ? 1 : -1];
typedef char GibblesMovementParameters_size[sizeof(GibblesMovementParameters) == 0x1C ? 1 : -1];
typedef char GibblesResourceBinding_size[sizeof(GibblesResourceBinding) == 0x10 ? 1 : -1];
typedef char TObjEneGibbles_size[sizeof(TObjEneGibbles) == 0x44C ? 1 : -1];
typedef char GibblesFlags_offset[offsetof(TObjEneGibbles, flags) == 0x374 ? 1 : -1];
typedef char GibblesAttackBody_offset[offsetof(TObjEneGibbles, attack_body) == 0x3B4 ? 1 : -1];
typedef char GibblesMaterialFade_offset[offsetof(TObjEneGibbles, material_fade) == 0x3C0 ? 1 : -1];
typedef char GibblesCameraFades_offset[offsetof(TObjEneGibbles, camera_fades) == 0x3DC ? 1 : -1];

void gibbles_render_node_callback(void);

#endif
