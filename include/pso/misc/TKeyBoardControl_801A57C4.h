#ifndef PSO_MISC_TKEYBOARDCONTROL_801A57C4_H
#define PSO_MISC_TKEYBOARDCONTROL_801A57C4_H

#include "types.h"
#include "pso/misc/KeyboardInputQueries.h"

extern "C" {
s32 TKeyBoardControl__sub_801A58D8(void);
}
void init_stick_escape_detector(void *arg0, void *arg1);
extern "C" {
void update_state_from_input__16TKeyBoardControlFPv(void *arg0);
}

// --- C functions defined in TKeyBoardControl_801A57C4.cpp ---
extern "C" {
s32 TKeyBoardControl__sub_801A58D8(void);
void update_state_from_input__16TKeyBoardControlFPv(void *arg0);
}
// --- end of C functions

#endif
