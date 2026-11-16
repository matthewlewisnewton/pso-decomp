#ifndef PSO_UI_WARNING_WINDOW_STATE_H
#define PSO_UI_WARNING_WINDOW_STATE_H
#include "types.h"
#include <stddef.h>
class TWindowBase;

struct WarningWindowState {
    TWindowBase *window;
    char text[0x80];
    s32 countdown;
};
typedef char WarningWindowStateSize[sizeof(WarningWindowState) == 0x88 ? 1 : -1];
typedef char WarningWindowTextOffset[offsetof(WarningWindowState, text) == 4 ? 1 : -1];
typedef char WarningWindowCountdownOffset[offsetof(WarningWindowState, countdown) == 0x84 ? 1 : -1];
#endif
