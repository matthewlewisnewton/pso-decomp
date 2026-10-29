#ifndef PSO_ENEMY_TOBJENEPANBARA_H
#define PSO_ENEMY_TOBJENEPANBARA_H

#include "pso/enemy/TObjEnemy.h"
#include "pso/misc/RenderFadeState.h"
#include <stddef.h>

struct TObjEnePanarms;
struct PanarmsDrawCallbacks;

class TObjEnePanBARA : public TObjEnemy {
public:
    TObjEnePanBARA(TObject *parent, void *set_data, s32 part);
    virtual ~TObjEnePanBARA();
    virtual void run_task();
    virtual void render();
    virtual void vfunc_61();
    virtual void vfunc_62();
    virtual void vfunc_63();
    void calc_part_position(u8 *, s32 *);

    s32 fn_800DFB44();
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
    static int do_action_2(void* p);
    void init_state();
    void update_linked_effect();
    void draw();
    void draw_with_fade();
    void set_random_action_timer(int minimum, int range);
    int find_nearest_enemy_with_flag_alt_target(s32 arg1, f32 farg0);

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
    PanarmsDrawCallbacks *draw_callbacks;
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
