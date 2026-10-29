#ifndef PSO_ENEMY_TOBJENEBALCLAWCLAW_H
#define PSO_ENEMY_TOBJENEBALCLAWCLAW_H

#include "types.h"
#include "pso/enemy/TObjEneBalClaw.h"

struct TObjEneBalClawClaw : public TObjEneBalClaw {
    virtual ~TObjEneBalClawClaw();
    virtual void run_task();
    virtual void render();
    void update_attack_distance_state();
    void sub_80090D3C();
    void sub_80090798();
    virtual void vfunc_58();
    void update_state();
    void *create(void *arg1, void *arg2, void *arg3, void *arg4, void *arg5);
    void *create();
    static void spawn_child_enemy();
    u8 unk_3C0[0x6];
    s16 m_3c6;
    u8 unk_3C8[0x60];
    void set_claw_flags();
    void clear_flag();
    void enter_hit_state(s16 arg1);
    s32 check_active();
    void update_chase_state();
    void run_active_state();
};

typedef char TObjEneBalClawClaw_size[sizeof(TObjEneBalClawClaw) == 0x428 ? 1 : -1];

extern "C" {
s32 TObjEneBalClawClaw__ct(void *arg0);
void TObjEneBalClawClaw__sub_80090824(void);
void TObjEneBalClawClaw__sub_80090A10(u8 *arg0, u8 *arg1, s32 arg2, s16 arg3);
void TObjEneBalClawClaw__sub_800914A4(void);
void run_task__18TObjEneBalClawClawFv(u8 *arg0);
u8 *TObjEneBalClawClaw__sub_80091B98(u8 *arg0, s32 arg1, u8 *arg2, s32 arg3, s32 arg4, u8 *arg5, s32 arg6, s32 _w7);
u8 *TObjEneBalClawClaw__sub_80091C58(u8 *arg0, s32 arg1, u8 *arg1_arg);
void action__18TObjEneBalClawClawFPv(u8 *arg0);
void *deleting_dtor__18TObjEneBalClawClawFPvs(void *arg0, s16 arg1);
void render__18TObjEneBalClawClawFv(u8 *arg0);
int reset_active_state__18TObjEneBalClawClawFPv(void *p);
void run_active_state__18TObjEneBalClawClawFv(u8 *arg0);
void spawn_lobby_npc_enemy(void);
void update_chase_state__18TObjEneBalClawClawFv(u8 *arg0);
}

#endif
