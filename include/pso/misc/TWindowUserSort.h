#ifndef PSO_MISC_TWINDOWUSERSORT_H
#define PSO_MISC_TWINDOWUSERSORT_H

#include "types.h"
#include "pso/misc/TUnk_804CE018.h"
#include "pso/misc/TWindowBase.h"

struct TWindowUserSort : public TUnk_804CE018 {
    virtual ~TWindowUserSort();
    virtual void render();
    u32 m_60;
    virtual void run_task();
};

typedef char TWindowUserSort_size[sizeof(TWindowUserSort) == 0x64 ? 1 : -1];
#endif
