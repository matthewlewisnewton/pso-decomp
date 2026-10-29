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
    u8 unk_394[0x4];
    f32 m_398;
    u8 unk_39C[0x4];
    f32 m_3a0;
    u8 unk_3A4[0x4];
    void* m_3a8;
    u8 unk_3AC[0x4];
    f32 m_3b0;
    u8 unk_3B4[0x4];
    f32 m_3b8;
    u8 unk_3BC[0x4];
    f32 m_3c0;
    u8 unk_3C4[0x4];
    s32 m_3c8;
    s32 m_3cc;
    u8 unk_3D0[0xC];
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
    void clear_child_flag();
    void set_target_flag_bit0();
    static s32 create(s32 arg0, s32 arg1, s32 arg2);
    static s32 create(s32 arg0, s32 arg1);
    void set_state(s32 arg1);
    s32 try_spawn_child(void *arg1);
};

typedef char TObjEneSlimeOne_size[sizeof(TObjEneSlimeOne) == 0x3F8 ? 1 : -1];
#endif
