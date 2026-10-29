#ifndef PSO_ENEMY_TOBJENEBALCLAWBODY_H
#define PSO_ENEMY_TOBJENEBALCLAWBODY_H

#include "types.h"
#include "pso/enemy/TObjEneBalClaw.h"

struct TObjEneBalClawBody : public TObjEneBalClaw {
    virtual ~TObjEneBalClawBody();
    void sub_8008FC10();
    virtual void render();
    void sub_8008FF50();
    void update_dragon_boss_state();
    virtual void vfunc_58();
    u32 m_3c0;
    s32 claw_ids[5];
    s16 m_3d8;
    u8 unk_3da[2];
    TObject *effects[4];
    u8 unk_3ec[0x18];
    static void *create(void *arg0);
};

typedef char TObjEneBalClawBody_size[sizeof(TObjEneBalClawBody) == 0x404 ? 1 : -1];
#endif
