#ifndef PSO_UI_WINDOW_TWINDOWBREAKIN_H
#define PSO_UI_WINDOW_TWINDOWBREAKIN_H

#include "types.h"
#include "pso/ui/window/TWindowBase.h"

struct TWindowBreakIn : public TWindowBase {
    virtual ~TWindowBreakIn();
    virtual void render();
    virtual void run_task();
    u8 unknown_30[0x30];
};

typedef char TWindowBreakIn_size[sizeof(TWindowBreakIn) == 0x60 ? 1 : -1];

extern "C" {
u8 *TWindowBreakIn__ct(u8 *arg0);
}

// --- C functions defined in TWindowBreakIn.cpp ---
extern "C" {
u8 *TWindowBreakIn__ct(u8 *window_dd);
}
// --- end of C functions

#endif
