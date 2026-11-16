#ifndef PSO_ENEMY_TOBJENEDARKGUNCENTER_H
#define PSO_ENEMY_TOBJENEDARKGUNCENTER_H

#include "types.h"
#include <stddef.h>
#include "pso/enemy/TObjEnemy.h"

struct TObjEneDarkGunCenter : public TObjEnemy {
    virtual ~TObjEneDarkGunCenter();
    virtual void run_task();
    virtual void render();
    void sub_800A0994();
    u32 state;
    s32 state_timer;
    s32 linked_enemy_count;
    u32 m_380;
    u16 linked_enemy_ids[16];
    s32 empty_group_timer;
    static void *create(void *arg0);
    void hide_linked_enemies();
};

typedef char DarkGunCenter_state_offset[offsetof(TObjEneDarkGunCenter, state) == 0x374 ? 1 : -1];
typedef char DarkGunCenter_timer_offset[offsetof(TObjEneDarkGunCenter, state_timer) == 0x378 ? 1 : -1];
typedef char DarkGunCenter_count_offset[offsetof(TObjEneDarkGunCenter, linked_enemy_count) == 0x37C ? 1 : -1];
typedef char DarkGunCenter_ids_offset[offsetof(TObjEneDarkGunCenter, linked_enemy_ids) == 0x384 ? 1 : -1];
typedef char DarkGunCenter_empty_timer_offset[offsetof(TObjEneDarkGunCenter, empty_group_timer) == 0x3A4 ? 1 : -1];
typedef char TObjEneDarkGunCenter_size[sizeof(TObjEneDarkGunCenter) == 0x3A8 ? 1 : -1];

extern "C" {
void TObjEneDarkGunCenter__sub_800A0B18(void *);
void TObjEneDarkGunCenter__sub_800A0E7C(void);
void TObjEneDarkGunCenter__sub_800A0E80(void);
}

#endif
