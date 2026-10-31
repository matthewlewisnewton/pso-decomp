#ifndef PSO_ENEMY_TOBJENEMORFOS_H
#define PSO_ENEMY_TOBJENEMORFOS_H

#include "types.h"
#include <stddef.h>
#include "pso/enemy/TObjEneDD_ST.h"
#include "pso/player/TUnk_80490470.h"
#include "pso/misc/MaterialOpacityFade.h"
#include "pso/misc/RenderFadeState.h"

class TParticleCtrl;
struct MorfosParameters;
struct BmlResource;

struct TObjEneMorfos : public TObjEneDD_ST {
    TObjEneMorfos(TObject *parent, void *set_data);
    virtual ~TObjEneMorfos();
    virtual void dispatch_action(u32 state, s32 reason);
    virtual f32 receive_physical_attack(void *attacker, f32 scale);
    s32 render_reflection();
    virtual void vfunc_28();
    virtual void vfunc_63();
    virtual void vfunc_62();
    virtual void vfunc_61();
    virtual void vfunc_88();
    virtual void update_demo();
    virtual void render_demo();
    virtual void render();
    virtual void run_task();
    u32 flags;
    u32 ground_flags;
    Vec ground_position;
    s32 texture_offset;
    f32 movement_speed;
    f32 movement_interval;
    f32 guard_probability;
    f32 burst_probability;
    s32 ground_movement;
    TUnk_80490470 damage_fade;
    MaterialOpacityFade body_fade;
    RenderFadeState camera_fade[4];
    TParticleCtrl *charge_effect;
    enum ModelNodePosition { PROJECTILE_POSITION, ARM_POSITION, MODEL_NODE_POSITION_COUNT };
    Vec model_node_positions[MODEL_NODE_POSITION_COUNT];
    s32 action_phase;
    s32 phase_counter;
    s32 burst_timer;
    s32 target_angle;
    s32 burst_start_angle;
    f32 action_progress;
    f32 m_4c8;
    Vec movement_direction;
    static BmlResource *get_resources();
    void draw_guard_wall();
    static void record_model_node_position();
    void state_death(s32 reason);
    void state_patrol(s32 reason);
    void state_appear(s32 reason);
    void handle_event_transition(s32 ev);
    void play_frame_sounds();
    void initialize_behavior_parameters();
    void update_body_center();
    s32 turn_toward_angle(s32 target_heading, s32 max_step);
    s32 try_enter_low_hp_state();
    s32 check_low_hp_trigger();
    void init_instance();
    static void unload_static_data();
    static void load_resources();
    static void *create(void *set_data);
    void update_ground_probe();
    s32 crosses_heading(s32 start, s32 end, s32 heading);
    Vec *get_arm_position();
    s32 get_heading();
    void state_damaged(s32 reason);
    void state_melee_attack(s32 reason);
    void state_projectile_attack(s32 reason);
    void state_move(s32 reason);
    void state_disappear(s32 reason);
    void state_hidden(s32 reason);
    void state_fade_in(s32 reason);
    void render_with_camera_fade(s32 idx, s32 mode);
    void state_rotating_projectile_burst(s32 reason);
    s32 select_target_in_view();
    s32 fn_803344F0();
    MorfosParameters *get_parameters();
};

typedef char TObjEneMorfos_size[sizeof(TObjEneMorfos) == 0x4D8 ? 1 : -1];
typedef char Morfos_target_offset[offsetof(TObjEneMorfos, target) == 0x390 ? 1 : -1];
typedef char Morfos_flags_offset[offsetof(TObjEneMorfos, flags) == 0x3C0 ? 1 : -1];
typedef char Morfos_damage_fade_offset[offsetof(TObjEneMorfos, damage_fade) == 0x3EC ? 1 : -1];
typedef char Morfos_body_fade_offset[offsetof(TObjEneMorfos, body_fade) == 0x408 ? 1 : -1];
typedef char Morfos_camera_fade_offset[offsetof(TObjEneMorfos, camera_fade) == 0x424 ? 1 : -1];
typedef char Morfos_projectile_position_offset[offsetof(TObjEneMorfos, model_node_positions) == 0x498 ? 1 : -1];
typedef char Morfos_arm_position_offset[offsetof(TObjEneMorfos, model_node_positions) + sizeof(Vec) == 0x4A4 ? 1 : -1];
typedef char Morfos_movement_direction_offset[offsetof(TObjEneMorfos, movement_direction) == 0x4CC ? 1 : -1];

#endif
