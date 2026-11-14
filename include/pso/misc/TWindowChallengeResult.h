#ifndef PSO_MISC_TWINDOWCHALLENGERESULT_H
#define PSO_MISC_TWINDOWCHALLENGERESULT_H

#include "types.h"
#include "pso/misc/TWindowBase.h"

struct TWindowChallengeResult : public TWindowBase {
    virtual ~TWindowChallengeResult();
    virtual void render();

    f32 scale_x;
    f32 scale_y;
};

typedef char TWindowChallengeResult_size[sizeof(TWindowChallengeResult) == 0x68 ? 1 : -1];

typedef char ChallengeResult_scale_x[offsetof(TWindowChallengeResult, scale_x) == 0x60 ? 1 : -1];
typedef char ChallengeResult_scale_y[offsetof(TWindowChallengeResult, scale_y) == 0x64 ? 1 : -1];

extern "C" {
void *dt__22TWindowChallengeResultFPvs(void *arg0, s16 arg1);
void init_subwindow__22TWindowChallengeResultFPv(void *p);
}

// --- C functions defined in TWindowChallengeResult.cpp ---
extern "C" {
void *dt__22TWindowChallengeResultFPvs(void *arg0, s16 arg1);
void init_subwindow__22TWindowChallengeResultFPv(void *p);
}
// --- end of C functions

#endif
