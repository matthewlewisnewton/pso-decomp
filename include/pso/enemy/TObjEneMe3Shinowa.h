#ifndef PSO_ENEMY_TOBJENEME3SHINOWA_H
#define PSO_ENEMY_TOBJENEME3SHINOWA_H

#include "types.h"
#include "pso/enemy/TObjEneDD_ST.h"
#include "pso/enemy/TUnk_80494938.h"

struct TObjEneMe3Shinowa : public TObjEneDD_ST {
    virtual ~TObjEneMe3Shinowa();
    virtual void run_task();
    virtual void dispatch_action(u32, s32);
    virtual void vfunc_104(f32);
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
    virtual void vfunc_115(s32);
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
    u32 m_374;
    u8 unk_378[0x14];
    u16 m_38c;
    u8 unk_38e[2];
    u32 m_390;
    u8 unk_394[8];
    u32 m_39c;
    u32 m_3a0;
    u8 unk_3a4[0x1c];
    s32 m_3c0;
    u32 state_flags;
    f32 initial_y;
    f32 render_y_offset;
    u32 effect_color;
    s32 m_3d4;
    s32 m_3d8;
    s16 m_3dc;
    u8 unk_3de[2];
    TObject *effect_3e0;
    TObject *effect_3e4;
    TUnk_80494938 fade;
    s32 m_404;
    s32 m_408;
    s32 m_40c;
    f32 m_410;
    f32 m_414;
    f32 m_418;
    f32 m_41c;
    f32 m_420;
    TObject *effect_424;
    TObject *effect_428;
    void copy_position_vector();
};

typedef char ShinowaFadeOffset[offsetof(TObjEneMe3Shinowa, fade) == 0x3e8 ? 1 : -1];
typedef char ShinowaEffectsOffset[offsetof(TObjEneMe3Shinowa, effect_424) == 0x424 ? 1 : -1];
typedef char ShinowaBaseSize[sizeof(TObjEneMe3Shinowa) == 0x42c ? 1 : -1];

#endif
