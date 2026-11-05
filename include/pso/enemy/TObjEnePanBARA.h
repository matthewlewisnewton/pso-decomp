#ifndef PSO_ENEMY_TOBJENEPANBARA_H
#define PSO_ENEMY_TOBJENEPANBARA_H

#include "pso/enemy/TObjEnemy.h"
#include "pso/misc/RenderFadeState.h"
#include <stddef.h>

struct TObjEnePanarms;
struct ModelNodePositionCapture;

class TObjEnePanBARA : public TObjEnemy {
public:
    TObjEnePanBARA(TObject *parent, void *set_data, s32 part);
    virtual ~TObjEnePanBARA();
    virtual void run_task();
    virtual void render();
    virtual void vfunc_61();
    virtual void vfunc_62();
    virtual void vfunc_63();
    void calc_part_position(Vec *, s32 *);
    s32 try_move_with_detour(Vec *);

    s32 is_in_state_7_or_8();
    int get_state_flag();
    int is_state_4_timer_expired();
    int is_in_state_11();
    int is_in_state_8();
    void bind_parts(TObjEnePanarms *body, TObjEnePanBARA *half);
    void fn_800E1D38();
    void fn_800E1D94();
    void start_split_at_body();
    void update_action_timer();
    void init_attack_state();
    void init_open_state();
    void update_move_timer();
    void start_phase3_timer12();
    void start_phase2_timer150();
    void update_attack();
    void init_attack_state2();
    void init_action();
    void update_chase_target();
    void init_state_2();
    void apply_effect_if_flagged();
    void update_hit_state();
    void restore_from_linked_object();
    void init_state_16();
    void update_move_to_target();
    void init_state_1();
    void start_action();
    void handle_split_flag();
    void init_split();
    void snap_to_parent_position();
    void reset_state();
    void spawn_periodic_particle();
    void attack_target_player(s32 arg1);
    void update_offset_from_parent();
    void reset_split();
    void do_action_2();
    void init_state();
    void update_linked_effect();
    void draw();
    void set_random_action_timer(int minimum, int range);
    int find_nearest_enemy_with_flag_alt_target(Vec *direction, f32 radius);

    void fn_800DFE08();
    void fn_800E0048();
    void fn_800E0214();
    void fn_800E0344();
    void fn_800E055C();
    void fn_800E092C();
    void fn_800E0930();
    void fn_800E0950();
    void fn_800E0A44();
    void fn_800E0B9C();
    void fn_800E0D1C();
    void fn_800E10D0();
    s32 acquire_target_in_front();
    void set_state(s32 state);
    s32 is_phase_12();
    s32 check_can_attack();
    s32 is_in_state_13();
    s32 is_in_state_14();
    s32 is_below_half_hp();
    s32 is_in_state_9_or_11();
    void calc_default_part_position();

    typedef void (TObjEnePanBARA::*Action)();
    struct ActionPair { Action enter; Action update; };

    s32 previous_state;
    s32 state;
    CollisionBody *collision_body;
    s32 part_index;
    s32 visible;
    s32 collision_active;
    Vec split_position;
    s32 m_398;
    TObjEnePanarms *combined_body;
    TObjEnePanBARA *other_half;
    Vec effect_position;
    f32 movement_speed;
    s32 action_timer;
    s32 target_id;
    s32 initial_hp;
    s32 m_3c0;
    s32 m_3c4;
    Vec other_half_direction;
    s32 other_half_angle;
    f32 other_half_distance;
    ModelNodePositionCapture *draw_callbacks;
    Vec draw_callback_position;
    RenderFadeState camera_fades[4];
    s32 frame_counter;
    f32 m_460;
    f32 attack_power;
    f32 jellen_probability;
    f32 zalure_probability;
};

typedef char PanBaraSize[sizeof(TObjEnePanBARA) == 0x470 ? 1 : -1];
typedef char PanBaraBodyOffset[offsetof(TObjEnePanBARA, combined_body) == 0x39C ? 1 : -1];
typedef char PanBaraHalfOffset[offsetof(TObjEnePanBARA, other_half) == 0x3A0 ? 1 : -1];
typedef char PanBaraTargetOffset[offsetof(TObjEnePanBARA, target_id) == 0x3B8 ? 1 : -1];
typedef char PanBaraFadeOffset[offsetof(TObjEnePanBARA, camera_fades) == 0x3EC ? 1 : -1];
typedef char PanBaraCounterOffset[offsetof(TObjEnePanBARA, frame_counter) == 0x45C ? 1 : -1];

#endif
