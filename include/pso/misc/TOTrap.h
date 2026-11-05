#ifndef PSO_MISC_TOTRAP_H
#define PSO_MISC_TOTRAP_H

#include "types.h"
#include "pso/player/TObjChara.h"

struct TOTrap : public TObjChara {
    virtual ~TOTrap();
    virtual void find_target_player();
    virtual void submit_cursor_and_notify();
    virtual void vfunc_81();
    virtual void vfunc_82();
    virtual s32 is_any_player_matching_stat();
    virtual void vfunc_84();
    virtual void play_sounds();
    virtual void vfunc_86();
    virtual f32 vfunc_87(f32);
    virtual void vfunc_88();
    virtual void vfunc_89();
    virtual f32 receive_physical_attack(void *, f32);
    virtual s32 try_start_action(s32, s32);
    virtual void vfunc_6(s16 *, s32);
    virtual void apply_knockback_from_attacker(u8 *, f32);
    virtual void run_task();
    f32 range;
    f32 dist;
    u16 player;
    u8 _pad33E[0x2];
    s32 m_340;
    virtual void render();
    virtual s32 select_melee_contact_body(void *source, f32) { return source != target; }
    virtual int calc_distance_accuracy_penalty(void *source, void *, void *, f32) { return source != target; }
    virtual f32 receive_direct_attack(void *source, DirectAttackPayload, void *, s32, s32) {
        if (source != target) {
            receive_physical_attack(NULL, 1.0f);
        }
        return 0.0f;
    }
    virtual f32 receive_weapon_special_attack(void *source, void *) {
        if (source != target) {
            receive_physical_attack(NULL, 1.0f);
        }
        return 0.0f;
    }
    virtual s32 roll_physical_accuracy(void *, s32, f32);
};

typedef char TOTrap_size[sizeof(TOTrap) == 0x344 ? 1 : -1];
#endif
