#ifndef PSO_ENEMY_TOBJENEME1GIGUE_H
#define PSO_ENEMY_TOBJENEME1GIGUE_H

#include "types.h"
#include "pso/enemy/TObjEnemyCustom.h"
#include "pso/misc/MaterialOpacityFade.h"
#include "pso/misc/RenderFadeState.h"

struct BmlResource;

struct TObjEneMe1GiGue : public TObjEnemyCustom {
    TObjEneMe1GiGue(TObject *parent, void *set_data);
    virtual ~TObjEneMe1GiGue();
    virtual void run_task();
    virtual void render();
    virtual f32 receive_physical_attack(void *, f32);
    virtual f32 receive_direct_attack(void *, DirectAttackPayload, void *, s32, s32);
    virtual f32 receive_weapon_special_attack(void *, void *);
    virtual s32 update_action_hold_status();
    virtual void vfunc_58();
    virtual void vfunc_59();
    virtual void vfunc_60();
    virtual void vfunc_61();
    virtual void vfunc_62();
    virtual void vfunc_63();

    void reset_spawn_after_hold();
    void update_idle();
    void select_next_action();
    void init_move();
    void update_direction();
    void load_params();
    s32 get_int_parameter(s32 index);
    f32 get_float_parameter(s32 index);
    u16 m_38c;
    Vec move_destination;
    Vec missile_origin;
    Vec needle_origin;
    Vec barrier_origin;
    s32 target_count;
    u16 target_ids[12];
    s32 search_turn;
    f32 wander_distance;
    f32 movement_speed;
    f32 model_y_offset;
    f32 flight_height;
    u32 m_3f0;
    s32 shake_timer;
    s32 attack_count;
    MaterialOpacityFade spawn_fade;
    RenderFadeState camera_fade;
    s32 attack_angle;
    f32 attack_range;
    f32 initial_height;
    f32 barrier_probability;
    f32 technique_probability;
    s32 volley_count;
    s32 barrier_duration;
    s32 attack_duration;
    s32 rush_timer;
    void find_open_direction(Vec *direction);
    void update_animation_nodes();
    s32 collect_targets();
    void add_target_in_cone(TObjChara *target);
    void update_spawn();
    void update_landing();
    void spawn_needle(s32 index);
    void move_around_center(Vec *center, f32 radius);
    void update_rush_attack();
    void update_barrier();
    void update_techniques();
    void update_needle_attack();
    void update_missile_attack();
    void update_search();
    void fn_802CD054();
    void fn_802CDAE8();
    void dispatch_state();
    static void *create(void *arg0);
    static void delete_barrier();
    static void load_resources();
    void load_params_from_table(s32 i);
    static BmlResource *get_resources();
    void clear_barrier_active();
    void set_barrier_active();
    s32 should_end_barrier();
    s32 get_barrier_duration();
    s32 get_barrier_rotation();
    Vec *update_barrier_origin();
    void apply_hit_shake(u32 arg1);
    s32 check_vector_bit(Vec *point);
    s32 remap_sound_id(s32 id);
    void break_apart();
    void update_hit_reaction();
};

typedef char TObjEneMe1GiGue_size[sizeof(TObjEneMe1GiGue) == 0x458 ? 1 : -1];
#endif
