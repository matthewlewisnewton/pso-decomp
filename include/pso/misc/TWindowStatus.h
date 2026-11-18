#ifndef PSO_MISC_TWINDOWSTATUS_H
#define PSO_MISC_TWINDOWSTATUS_H

#include "types.h"
#include "pso/misc/TWindowSimpleStatus.h"

struct TWindowStatus : public TWindowSimpleStatus {
    TWindowStatus(void *position, s32 client, u8 *descriptor);
    virtual ~TWindowStatus();
    virtual void render();
    virtual void run_task();
    void draw_background(u8 *arg1);
};

typedef char TWindowStatus_size[sizeof(TWindowStatus) == 0x78 ? 1 : -1];
#endif
