#ifndef PSO_BOSS_TBOSS8DRAGONEFFBULLET_H
#define PSO_BOSS_TBOSS8DRAGONEFFBULLET_H

#include "types.h"
#include "pso/TObject.h"

struct TBoss8DragonEffBullet : public TObject {
    virtual ~TBoss8DragonEffBullet();
    void* m_1c;
    u8 _pad20[0x8];
    void* m_28;
    u8 _pad2C[0x8];
    u32 m_34;
    u32 m_38;
    u8 unk_3C[0x4];
    f32 m_40;
    u32 m_44;
    u16 m_48;
    u8 _pad4A[0x2];
    u32 m_4c;
    u32 m_50;
    u32 m_54;
    virtual void render();
    virtual void run_task();
};

typedef char TBoss8DragonEffBullet_size[sizeof(TBoss8DragonEffBullet) == 0x58 ? 1 : -1];

extern "C" {
u8 *TBoss8DragonEffBullet__ct(u8 *storage, void *parent, const void *source, const void *target, s32 mode, u16 owner);
void *__dt__21TBoss8DragonEffBulletFv(void *arg0, s16 arg1);
}

// --- C functions defined in TBoss8DragonEffBullet.cpp ---
extern "C" {
u8 *TBoss8DragonEffBullet__ct(u8 *storage, void *parent, const void *source, const void *target, s32 mode, u16 owner);
}
// --- end of C functions

#endif
