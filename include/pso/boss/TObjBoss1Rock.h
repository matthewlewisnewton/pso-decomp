#ifndef PSO_BOSS_TOBJBOSS1ROCK_H
#define PSO_BOSS_TOBJBOSS1ROCK_H

#include "types.h"
#include "pso/TObject.h"

struct TObjBoss1Rock : public TObject {
    TObjBoss1Rock(TObject *arg1, void *arg2, void *arg3);
    virtual ~TObjBoss1Rock();
    void sub_8002E1CC(u8 *, u8 *, s32);
    void* m_1c;
    u8 _pad20[0x8];
    void* m_28;
    u8 unk_2C[0x4];
    f32 m_30;
    u32 m_34;
    u32 m_38;
    u32 m_3c;
    u8 unk_40[0x4];
    f32 m_44;
    u8 unk_48[0x4];
    f32 m_4c;
    u32 m_50;
    virtual void render();
    virtual void run_task();
    void *construct(void *arg1, void *arg2, void *arg3, void *arg4);
};

typedef char TObjBoss1Rock_size[sizeof(TObjBoss1Rock) == 0x54 ? 1 : -1];
#endif
