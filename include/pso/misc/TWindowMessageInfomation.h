#ifndef PSO_MISC_TWINDOWMESSAGEINFOMATION_H
#define PSO_MISC_TWINDOWMESSAGEINFOMATION_H

#include "types.h"
#include "pso/misc/TWindowMessage.h"

struct TWindowMessageInfomation : public TWindowMessage {
    TWindowMessageInfomation(s32 arg1, s32 arg2);
    virtual ~TWindowMessageInfomation();
    void render();
};

typedef char TWindowMessageInfomation_size[sizeof(TWindowMessageInfomation) == 0x90 ? 1 : -1];
#endif
