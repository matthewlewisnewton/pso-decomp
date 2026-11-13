#ifndef PSO_ENEMY_GIGUE_TOBJENEME1GIGUE_H
#define PSO_ENEMY_GIGUE_TOBJENEME1GIGUE_H

#include "types.h"
#include "pso/enemy/TObjEnemyCustom.h"

struct TObjEneMe1GiGue : public TObjEnemyCustom {
    virtual ~TObjEneMe1GiGue();
    void reset_spawn_after_hold();
    virtual void run_task();
    void update_idle();
    void select_next_action();
    void init_move();
    void clear_barrier_active();
    void update_direction();
    void load_params();
    s32 get_int_parameter(s32 index);
    f32 get_float_parameter(s32 index);
    virtual void vfunc_62();
    virtual void vfunc_63();
    virtual s32 update_action_hold_status();
    virtual f32 receive_physical_attack(void *, f32);
    virtual f32 receive_weapon_special_attack(void *, void *);
    virtual void vfunc_61();
    virtual void vfunc_59();
    virtual void vfunc_60();
    virtual void vfunc_58();
    u16 m_38c;
    u8 _pad38E[0x2];
    void* m_390;
    u8 unk_394[0x30];
    s32 m_3c4;
    u8 unk_3C8[0x1C];
    f32 m_3e4;
    u8 unk_3E8[0x4];
    f32 m_3ec;
    u8 unk_3F0[0x4];
    u32 m_3f4;
    u32 m_3f8;
    void* m_3fc;
    u8 _pad400[0x18];
    void* m_418;
    u8 unk_41C[0x18];
    s32 m_434;
    u8 unk_438[0x4];
    f32 m_43c;
    u8 unk_440[0x4];
    f32 m_444;
    u32 m_448;
    void dispatch_state();
    static void *create(void *arg0);
    static void delete_barrier();
    static void load_resources();
    void load_params_from_table(s32 i);
    u8 unk_44C[0xC];
    static int get_resources();
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
