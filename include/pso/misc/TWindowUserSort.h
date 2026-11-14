#ifndef PSO_MISC_TWINDOWUSERSORT_H
#define PSO_MISC_TWINDOWUSERSORT_H

#include "types.h"
#include "pso/misc/TWindowBase.h"

struct TWindowUserSort : public TWindowBase {
    TWindowUserSort(void *position, s32 value);
    virtual ~TWindowUserSort();
    virtual void render();
    u32 m_60;
    virtual void run_task();
};

typedef char TWindowUserSort_size[sizeof(TWindowUserSort) == 0x64 ? 1 : -1];
typedef char TWindowUserSort_m60[offsetof(TWindowUserSort, m_60) == 0x60 ? 1 : -1];
#endif
