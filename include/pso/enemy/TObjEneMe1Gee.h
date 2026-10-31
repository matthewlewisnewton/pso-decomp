#ifndef PSO_ENEMY_TOBJENEME1GEE_H
#define PSO_ENEMY_TOBJENEME1GEE_H

#include "types.h"
#include "pso/system/NinjaTypes.h"
#include "pso/enemy/TObjEneDD_ST.h"
#include "pso/misc/MaterialOpacityFade.h"

struct BmlResource;

struct GeeParameters {
    f32 chase_speed;
    f32 needle_parameter;
    u32 unknown08[4];
    s32 needle_charge_frames;
    u32 unknown1C;
    s32 needle_recovery_frames;
    s32 needle_count;
    s32 hit_recovery_frames;
    s32 swarm_group_divisor;
};

struct TObjEneMe1Gee : public TObjEneDD_ST {
    enum GeeFlags {
        IN_FIGHTER = 0x100,
        OUT_FIGHTER = 0x200,
        LOW_APPEARANCE = 0x02000000,
        HIGH_APPEARANCE = 0x04000000,
    };
    TObjEneMe1Gee(TObject *parent, TObjEneMe1Gee *leader,
        const Vec *initial_position, u16 child_id, s32 child_index);
    TObjEneMe1Gee(TObject *parent, void *set_data, s32 actor_role);
    virtual ~TObjEneMe1Gee();
    static TObjEneMe1Gee *create_child(TObjEneMe1Gee *leader,
        const Vec *initial_position, u16 child_id, s32 child_index);
    void init_state();
    virtual void dispatch_action(u32 state, s32 reason);
    void state_despawn(s32 reason);
    void state_hit_recovery(s32 reason);
    void fn_800C9964(s32 reason);
    void fn_800C9A94(s32 reason);
    void fn_800C9DF8(s32 reason);
    void fn_800CA454(s32 reason);
    void fn_800CB4DC();
    void activate_immediately();
    void *get_committed_target();
    s32 has_gee_flags(u32 flags);
    int has_materialized();
    s32 fn_800CBA80();
    void disable_attack_body();
    void enable_attack_body();
    static void random_child_position(TObjEneMe1Gee *actor, Vec *result);
    virtual void vfunc_88();
    virtual u8 *vfunc_101(u8 *);
    virtual s32 vfunc_104(f32 distance);
    virtual void vfunc_89();
    virtual void vfunc_105();
    virtual void vfunc_106();
    virtual void vfunc_107();
    virtual s32 vfunc_108();
    virtual int vfunc_109();
    virtual void vfunc_110(s32);
    virtual void vfunc_111(s32);
    virtual void vfunc_112(s32);
    virtual void vfunc_113();
    virtual void vfunc_114();
    virtual void vfunc_115();
    virtual int vfunc_116(void *target);
    virtual void remove_child(TObjEneMe1Gee *child);
    virtual void vfunc_28();
    virtual void vfunc_63();
    virtual void vfunc_62();
    virtual void vfunc_61();
    void sync_body_position();
    void apply_behavior_parameters();
    void sub_800CBF58(f32);
    void fn_800CBE6C(f32 target_height);
    void fn_800CBDBC(f32 target_height);
    void approach_world_height(f32 target_height);
    void update_hover_height();
    void update_animation_frame();
    void update_fade_sequence();
    void update_packed_color();
    void set_color(const NJS_ARGB *source);
    void set_low_appearance();
    void set_high_appearance();
    void set_in_fighter();
    void set_out_fighter();
    void set_flag3c8_bit2();
    void state_attack_loop(s32);
    void render();
    void run_task();
    TObjEneMe1Gee *leader;
    s32 role;
    u32 gee_flags;
    MaterialOpacityFade fade;
    f32 attack_height;
    f32 hover_height;
    f32 alternate_height;
    f32 model_height;
    f32 world_height;
    f32 needle_speed;
    f32 height_step;
    s32 activation_delay;
    s32 attack_count;
    s32 field_40C;
    s32 alternate_model_index;
    Vec node_positions[2];
    GeeParameters *gee_parameters;
    s32 attack_cycle;
    s32 state_step;
    s32 state_timer;
    s32 state_count;
    s32 field_440;
    s32 rotation_step;
    f32 field_448;
    f32 field_44C;
    f32 field_450;
    Vec attack_destination;
    TObject *effect_460;
    TObject *effect_464;
    NJS_ARGB color;
    u32 packed_color;
    s32 color_sequence;
    s32 color_script;
    s32 color_timer;
    s32 color_cursor;
    u16 leader_id;
    u8 pad_48E[2];
    static BmlResource *get_resources();
    static void load_resources();
    static void cache_result_805D6660();
    static void queue_debug_text(s32 arg0, char *arg1);
    static void advance_camera_ctrl_step();
    void state_orbit(s32 arg1);
    void handle_event(s32 arg1);
    void state_return_home(s32 arg1);
    void state_attack(s32 arg1);
    void state_hover(s32 arg1);
    void state_move(s32 arg1);
    void fn_800CAFD8(s32 reason);
    void fn_800CB968();
    void set_flag3c8_bit40();
    void set_flag3c8_bit8();
    void update_photon_target();
    s32 remap_gee_sound(s32 sound);
    s32 return_home_if_target_lost();
    s32 check_can_attack();
    void update_angle();
    void update_from_float_sum();
    void set_move_speed_x();
    static void free_globals();
    static void *create(void *arg0);
    void set_flag3c8_bit4();
    void activate_with_target(void *target, s32 delay);
    void start_color_sequence(s32 sequence);
    void update();
};

typedef char GeeParametersChargeOffset[offsetof(GeeParameters, needle_charge_frames) == 0x18 ? 1 : -1];
typedef char GeeParametersRecoveryOffset[offsetof(GeeParameters, needle_recovery_frames) == 0x20 ? 1 : -1];
typedef char GeeParametersCountOffset[offsetof(GeeParameters, needle_count) == 0x24 ? 1 : -1];
typedef char GeeParametersHitRecoveryOffset[offsetof(GeeParameters, hit_recovery_frames) == 0x28 ? 1 : -1];
typedef char GeeParametersSwarmDivisorOffset[offsetof(GeeParameters, swarm_group_divisor) == 0x2C ? 1 : -1];
typedef char GeeParametersSize[sizeof(GeeParameters) == 0x30 ? 1 : -1];

typedef char GeeLeaderOffset[offsetof(TObjEneMe1Gee, leader) == 0x3C0 ? 1 : -1];
typedef char GeeFlagsOffset[offsetof(TObjEneMe1Gee, gee_flags) == 0x3C8 ? 1 : -1];
typedef char GeeFadeOffset[offsetof(TObjEneMe1Gee, fade) == 0x3CC ? 1 : -1];
typedef char GeeWorldHeightOffset[offsetof(TObjEneMe1Gee, world_height) == 0x3F8 ? 1 : -1];
typedef char GeeNodePositionsOffset[offsetof(TObjEneMe1Gee, node_positions) == 0x414 ? 1 : -1];
typedef char GeeStateStepOffset[offsetof(TObjEneMe1Gee, state_step) == 0x434 ? 1 : -1];
typedef char GeeColorOffset[offsetof(TObjEneMe1Gee, color) == 0x468 ? 1 : -1];
typedef char GeeLeaderIdOffset[offsetof(TObjEneMe1Gee, leader_id) == 0x48C ? 1 : -1];
typedef char TObjEneMe1Gee_size[sizeof(TObjEneMe1Gee) == 0x490 ? 1 : -1];
#endif
