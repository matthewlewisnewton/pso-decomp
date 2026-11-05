#ifndef PSO_MISC_TWINDOWDEPOSIT_H
#define PSO_MISC_TWINDOWDEPOSIT_H

#include "types.h"
#include "pso/misc/TUnk_804CE018.h"

struct TWindowDeposit : public TUnk_804CE018 {
    virtual ~TWindowDeposit();
    virtual void render();
    f32 m_60;
    void* m_64;
    void render_status(s32 arg1);
    virtual void run_task();
    u8 unk_68[0x4];
};

typedef char TWindowDeposit_size[sizeof(TWindowDeposit) == 0x6C ? 1 : -1];

extern "C" {
u8 *TWindowDeposit__ct(u8 *arg0, s32 arg1);
void *__dt__14TWindowDepositFv(void *arg0, s16 arg1);
void render__14TWindowDepositFv(s32 arg0);
}

// --- C functions defined in TWindowDeposit.cpp ---
extern "C" {
u8 *TWindowDeposit__ct(u8 *arg0, s32 arg1);
void *__dt__14TWindowDepositFv(void *arg0, s16 arg1);
void render__14TWindowDepositFv(s32 arg0);
}
// --- end of C functions

#endif
