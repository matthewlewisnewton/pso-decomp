#ifndef PSO_MISC_TWINDOWDEPOSIT_H
#define PSO_MISC_TWINDOWDEPOSIT_H

#include "types.h"
#include "pso/misc/TWindowBase.h"

struct TWindowDeposit : public TWindowBase {
    TWindowDeposit(s16 arg1);
    virtual ~TWindowDeposit();
    virtual void render();
    f32 m_60;
    void* m_64;
    void render_status(s32 arg1);
    virtual void run_task();
    u8 unk_68[0x4];
};

typedef char TWindowDeposit_size[sizeof(TWindowDeposit) == 0x6C ? 1 : -1];

#endif
