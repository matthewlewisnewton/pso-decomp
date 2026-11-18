#ifndef PSO_UI_WINDOW_TWINDOWAREA_H
#define PSO_UI_WINDOW_TWINDOWAREA_H

#include "pso/ui/window/TWindowRoom.h"

struct TWindowArea : public TWindowRoom {
    TWindowArea();
    virtual ~TWindowArea();
    virtual void run_task();
};

typedef char TWindowAreaSize[sizeof(TWindowArea) == 0x64 ? 1 : -1];

#endif
