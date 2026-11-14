#ifndef PSO_MISC_TWINDOWMESSAGESCROLL_H
#define PSO_MISC_TWINDOWMESSAGESCROLL_H

#include "types.h"
#include <stddef.h>
#include "pso/misc/TWindowMessageQuest.h"

struct TWindowMessageScroll : public TWindowMessageQuest {
    TWindowMessageScroll(s32 layout, s32 *completion);
    virtual ~TWindowMessageScroll();
    void run_task();
    f32 m_94;
    s32 * m_98;
};

typedef char TWindowMessageScroll_size[sizeof(TWindowMessageScroll) == 0x9C ? 1 : -1];

extern "C" {
void *__dt__20TWindowMessageScrollFv(void *arg0, s16 arg1);
}

// --- C functions defined in TWindowMessageScroll.cpp ---
extern "C" {
}
// --- end of C functions

typedef char TWindowMessageScroll_owned_field_offset[offsetof(TWindowMessageScroll, m_94) == 0x94 ? 1 : -1];

#endif
