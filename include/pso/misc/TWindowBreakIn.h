#ifndef PSO_MISC_TWINDOWBREAKIN_H
#define PSO_MISC_TWINDOWBREAKIN_H

#include "types.h"
#include "pso/misc/TWindowBase.h"

struct TWindowBreakIn : public TWindowBase {
    TWindowBreakIn();
    virtual ~TWindowBreakIn();
    virtual void render();
    virtual void run_task();
};

typedef char TWindowBreakIn_size[sizeof(TWindowBreakIn) == 0x60 ? 1 : -1];

#endif
