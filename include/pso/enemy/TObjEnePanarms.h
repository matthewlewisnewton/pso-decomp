#ifndef PSO_ENEMY_TOBJENEPANARMS_H
#define PSO_ENEMY_TOBJENEPANARMS_H

#include "types.h"
#include "pso/enemy/TObjEnemy.h"
#include "pso/misc/RenderFadeState.h"
#include <stddef.h>

class TObjEnePanBARA;
struct PanarmsDrawCallbacks;

struct TObjEnePanarms : public TObjEnemy {
    TObjEnePanarms(TObject *parent, void *set_data);
    virtual ~TObjEnePanarms();
    virtual void run_task();
    virtual void render();
    s32 sub_800DE390();
    void vfunc_63();
    void vfunc_62();
    void vfunc_61();
    s32 state;
    Vec velocity;
    f32 ground_height;
    s32 state_timer;
    s32 m_38c;
    CollisionBody *collision_body;
    void *particle_emitters[2];
    PanarmsDrawCallbacks *draw_callbacks;
    Vec draw_positions[5];
    s32 visible;
    s32 shadow_enabled;
    TObjEnePanBARA *m_3e4;
    TObjEnePanBARA *m_3e8;
    s32 m_3ec;
    s32 m_3f0;
    s32 initial_hp;
    s32 m_3f8;
    s32 m_3fc;
    RenderFadeState camera_fades[4];
    f32 m_470;
    s32 m_474;
    s32 m_478;
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
    s32 find_combine_position();
    s32 try_warp_to_position(Vec *position);
    s32 check_ground_along_path(Vec *start, Vec *end, f32 step, f32 dy);
    s32 fn_800DE528(Vec *position);
    s32 fn_800DE494();
    void fn_800DE430(s32 first, s32 second);
    void fn_800DEEF8();
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
