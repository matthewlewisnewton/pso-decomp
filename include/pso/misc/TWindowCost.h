#ifndef PSO_MISC_TWINDOWCOST_H
#define PSO_MISC_TWINDOWCOST_H

#include "types.h"
#include "pso/misc/TWindowMeseta.h"

struct TWindowCost : public TWindowMeseta {
    TWindowCost(void *position, s32 client, s32 text);
    virtual ~TWindowCost();
    virtual void run_task();
};

typedef char TWindowCost_size[sizeof(TWindowCost) == 0x74 ? 1 : -1];
extern "C" {
TWindowCost *create_cost_window(s32 client);
void fn_803094E8(TWindowCost *window, s32 value);
}

#endif
