#ifndef PSO_MISC_TWINDOWPARTYSTATUS_H
#define PSO_MISC_TWINDOWPARTYSTATUS_H

#include "types.h"
#include "pso/misc/TWindowSimpleStatus.h"

struct TWindowPartyStatus : public TWindowSimpleStatus {
    TWindowPartyStatus(s32 slot, u8 *descriptor);
    virtual ~TWindowPartyStatus();
    virtual void render();
    void draw();
    void draw_background(u8 *arg1);
    virtual void run_task();
};

typedef char TWindowPartyStatus_size[sizeof(TWindowPartyStatus) == 0x78 ? 1 : -1];
#endif
