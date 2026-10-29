#ifndef PSO_ENEMY_TOBJENEPANARMS_H
#define PSO_ENEMY_TOBJENEPANARMS_H

#include "types.h"
#include "pso/enemy/TObjEnemy.h"
#include "pso/misc/RenderFadeState.h"
#include <stddef.h>

class TObjEnePanBARA;

struct TObjEnePanarms : public TObjEnemy {
    TObjEnePanarms(TObject *parent, void *set_data);
    virtual ~TObjEnePanarms();
    virtual void run_task();
    virtual void render();
    s32 sub_800DE390();
    void vfunc_63();
    void vfunc_62();
    void vfunc_61();
    u8 unk_374[0x4];
    s32 m_378;
    u8 unk_37C[0x4];
    s32 m_380;
    u8 unk_384[0x4];
    s32 m_388;
    u32 m_38c;
    u32 m_390;
    u8 unk_394[0x4];
    s32 m_398;
    u32 m_39c;
    void* m_3a0;
    u8 unk_3A4[0x4];
    f32 m_3a8;
    u8 unk_3AC[0x4];
    f32 m_3b0;
    s32 action_timer;
    u8 unk_3B8[0x4];
    s32 m_3bc;
    u8 unk_3C0[0x4];
    s32 m_3c4;
    u8 unk_3C8[0x4];
    s32 m_3cc;
    u8 unk_3D0[0x4];
    s32 m_3d4;
    u8 unk_3D8[0x4];
    void* m_3dc;
    u8 unk_3E0[0x4];
    u32 m_3e4;
    u32 m_3e8;
    u32 m_3ec;
    u8 _pad3F0[0x4];
    u32 m_3f4;
    u32 m_3f8;
    u32 m_3fc;
    RenderFadeState camera_fades[4];
    u8 unk_470[0x4];
    u32 m_474;
    u32 m_478;
    int find_nearest_enemy_with_flag(s32 arg1, f32 farg0);
    static void spawn_npc_pair();
    static TObjEnePanBARA *create_bara(void *set_data, s32 part);
    static s32 create(s32 arg0);
    void init(void* a1);
    void copy_target_state(void* a1);
    void fn_800DE2B0();
    void fn_800DE124();
    void fn_800DDED8();
    void fn_800DDC30();
    void fn_800DDAD8();
    void fn_800DD9A0();
    void fn_800DD7F4();
    void fn_800DD5C8();
    void fn_800DD488();
    void fn_800DD368();
    void fn_800DCFE0();
    void init_state();
    typedef void (TObjEnePanarms::*Action)();
    struct ActionPair { Action enter; Action update; };
    void update_spin();
    void enter_down_state();
    void update_state_effect();
    void update_timed_action();
    void merge_halves();
    void update_separated_parts();
    void update_hit_effect();
    void update_wait_then_set_state();
    void update_particle_emitters();
    void set_flags_and_field_b8();
    void update_destroy_child();
    void update_particle_emitters_set2();
    void set_state_flags_6();
    void update_fall();
    void set_hidden_flags();
    void try_activate();
    static s32 find_combine_position(void *p);
    void turn_toward_target(s32 arg1);
    u16 turn_to_nearest_player(s32 arg1, s32 arg2);
    void snap_to_ground();
    void set_state(s32 arg1);
    void draw_shadow();
    void destroy_handles();
    static void free_data();
    static void load_and_spawn_npc();
};

typedef char PanarmsSize[sizeof(TObjEnePanarms) == 0x47C ? 1 : -1];
typedef char PanarmsFadeOffset[offsetof(TObjEnePanarms, camera_fades) == 0x400 ? 1 : -1];

#endif
