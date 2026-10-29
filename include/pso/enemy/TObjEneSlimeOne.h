#ifndef PSO_ENEMY_TOBJENESLIMEONE_H
#define PSO_ENEMY_TOBJENESLIMEONE_H

#include "types.h"
#include "pso/enemy/SlimeAnimationState.h"
#include "pso/enemy/TObjEnemy.h"
#include "dolphin/mtx.h"

struct TObjEneSlime;

struct TObjEneSlimeOne : public TObjEnemy {
    TObjEneSlimeOne(TObject *parent, TObjEneSlime *owner, void *set_data, const Vec *velocity);
    TObjEneSlimeOne(TObject *parent, TObjEneSlime *owner, void *set_data);
    virtual ~TObjEneSlimeOne();
    void initialize_slime_instance_state();
    void init_state();
    void update_wait_search();
    void reset_display();
    void fn_800EA820();
    void init_slime_display();
    void fn_800EA678();
    void fn_800EA56C();
    void fn_800EA364();
    void enter_slime_state();
    void update_slime_timer();
    void enter_appear_state();
    void update_dive_timer();
    void fn_800EA120();
    void fn_800E9EFC();
    void init_slime_state();
    void fn_800E9DC8();
    void fn_800E9D7C();
    void fn_800E9BCC();
    void begin_appear();
    void update_water_bomb_timer();
    void start_tail_attack();
    void tick_timer();
    void reset_display_state();
    void update_tick();
    void init_split_effect();
    void fn_800E969C();
    void fn_800E95F4();
    void update_effect_fade_lifetime();
    void fn_800E9538();
    void fn_800E92D8();

    void sub_800E9090();
    virtual void vfunc_63();
    virtual void vfunc_62();
    virtual void vfunc_61();
    virtual f32 receive_direct_attack(void *, DirectAttackPayload, void *, s32, s32);
    virtual void render();
    virtual void run_task();
    Vec trail_position;
    u8 * m_380;
    s32 m_384;
    SlimeAnimationState *animation;
    CollisionBody *collision_body;
    s32 m_390;
    s32 state_timer;
    f32 m_398;
    s32 motion_phase;
    f32 m_3a0;
    f32 vertical_offset;
    Vec render_scale;
    f32 movement_speed;
    Vec movement_direction;
    s32 turn_step;
    s32 m_3c8;
    s32 m_3cc;
    Vec attack_position;
    Vec m_3dc;
    void * m_3e8;
    s32 m_3ec;
    u32 m_3f0;
    s32 variant;
    s32 get_attack_target();
    s32 is_in_water_bomb_states();
    static int get_instance();
    int is_timer_active();
    int find_nearest_enemy_with_flag(s32 arg1, f32 farg0);
    int check_player_field_7cc();
    void copy_position();
    void set_random_timer_15();
    void set_random_timer(s32 minimum, s32 range);
    void set_display_mode(s32 mode);
    s32 project_to_ground();
    void clear_child_flag();
    void set_target_flag_bit0();
    static s32 create(s32 arg0, s32 arg1, s32 arg2);
    static s32 create(s32 arg0, s32 arg1);
    void set_state(s32 arg1);
    s32 try_spawn_child(void *arg1);
};

typedef char TObjEneSlimeOne_size[sizeof(TObjEneSlimeOne) == 0x3F8 ? 1 : -1];
#endif
