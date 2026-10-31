#ifndef PSO_ENEMY_TOBJENEME3SHINOWA_H
#define PSO_ENEMY_TOBJENEME3SHINOWA_H

#include "types.h"
#include "pso/enemy/TObjEneDD_ST.h"

struct TObjEneMe3Shinowa : public TObjEneDD_ST {
    virtual ~TObjEneMe3Shinowa();
    virtual void run_task();
    virtual void vfunc_88();
    virtual void vfunc_89();
    virtual void vfunc_105();
    virtual u8 can_hit_same_target();
    virtual void vfunc_107();
    virtual void update_player_state_default();
    virtual s32 update_effect();
    virtual void dispatch_if_active();
    virtual void vfunc_111();
    virtual void apply_effect_pair();
    virtual void action(s32);
    virtual void vfunc_114(s32);
    virtual void vfunc_115();
    virtual void vfunc_116(s32);
    virtual void update_mirage();
    virtual void vfunc_118();
    void init_enemy();
    f32 get_node_world_y();
    u8 check_body_collision_at(s32, f32);
    s32 sub_800E701C();
    s32 sub_800E6FE0();
    void sub_800E6F64();
    void sub_800E6BB8(s32);
    void vfunc_63();
    void vfunc_62();
    void vfunc_61();
    void vfunc_28();
    u8 unk_3C0[0xC];
    void* m_3e8;
    void copy_position_vector();
};

#endif
