#ifndef PSO_BOSS_TBOSS4DARKFALZSTATE_H
#define PSO_BOSS_TBOSS4DARKFALZSTATE_H

#include "pso/boss/TBoss4DarkFalz.h"
#include <stddef.h>

// All four callbacks receive the same Dark Falz controller object.
typedef void (TBoss4DarkFalz::*DarkFalzStateAction)();
struct DarkFalzState {
    const char *name;
    DarkFalzStateAction enter;
    DarkFalzStateAction leave;
    DarkFalzStateAction tick;
    DarkFalzStateAction update;
};
typedef char DarkFalzStateAction_size[sizeof(DarkFalzStateAction) == 12 ? 1 : -1];
typedef char DarkFalzState_size[sizeof(DarkFalzState) == 0x34 ? 1 : -1];
typedef char DarkFalzState_name_offset[offsetof(DarkFalzState, name) == 0 ? 1 : -1];
typedef char DarkFalzState_enter_offset[offsetof(DarkFalzState, enter) == 4 ? 1 : -1];
typedef char DarkFalzState_leave_offset[offsetof(DarkFalzState, leave) == 0x10 ? 1 : -1];
typedef char DarkFalzState_tick_offset[offsetof(DarkFalzState, tick) == 0x1C ? 1 : -1];
typedef char DarkFalzState_update_offset[offsetof(DarkFalzState, update) == 0x28 ? 1 : -1];

extern "C" DarkFalzState TBoss4DarkFalz__data_80485108[16];

#endif
