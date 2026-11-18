#ifndef PSO_NETWORK_NETWORK_TIMER_H
#define PSO_NETWORK_NETWORK_TIMER_H

#include "types.h"

// Timer records store a callback invoked without arguments by the timer loop.
typedef void (*NetTimerCallback)(void);

extern "C" {
s32 NetRegisterTimer(s32 period, s16 locked, NetTimerCallback fn);
s32 NetUnregisterTimer(NetTimerCallback fn);
}

#endif
