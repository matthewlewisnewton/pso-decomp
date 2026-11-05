#ifndef PSO_BOSS_TBOSS1DRAGONEFFTAIL_H
#define PSO_BOSS_TBOSS1DRAGONEFFTAIL_H

#include "types.h"
#include "pso/player/TUnk_804928CC.h"

struct TBoss1DragonEffTail : public TUnk_804928CC {
    virtual ~TBoss1DragonEffTail();
    virtual void apply_hit_if_active(void *, f32 *);
    virtual void run_task();
    u32 m_b0;
    u32 m_b4;
    u32 m_b8;
    u32 m_bc;
    void* m_c0;
    virtual void render();
    void enable();
    void disable();
    int is_visible();
    u8 unk_C4[0x4];
    f32 m_c8;
};

typedef char TBoss1DragonEffTail_size[sizeof(TBoss1DragonEffTail) == 0xCC ? 1 : -1];

extern "C" {
void TBoss1DragonEffTail__vt18(s32 arg0, s32 arg1);
void apply_hit_if_active__19TBoss1DragonEffTailFPvPf(TBoss1DragonEffTail *arg0, u8 *arg1);
void *__dt__19TBoss1DragonEffTailFv(void *arg0, s16 arg1);
void run_task__19TBoss1DragonEffTailFv(u8 *arg0);
}

#endif
