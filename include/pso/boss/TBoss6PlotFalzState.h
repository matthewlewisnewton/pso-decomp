#ifndef PSO_BOSS_TBOSS6PLOTFALZSTATE_H
#define PSO_BOSS_TBOSS6PLOTFALZSTATE_H

#include "pso/boss/TBoss6PlotFalz.h"
#include <stddef.h>

// The Falz plot demo-script state table: nine 0x34-byte records.
// set_state calls leave (+0x10) on the outgoing state, stores m_378, then
// calls enter (+0x4). run_task (0x802AC788) calls tick (+0x1C) through
// call_state_action only while the word at +0x374 is 0, then always calls
// update (+0x28) through run_phase_action. Same slots as DarkFalzState.
typedef void (TBoss6PlotFalz::*TBoss6PlotFalzAction)();
struct TBoss6PlotFalzScriptState {
    const char *name;
    TBoss6PlotFalzAction enter;
    TBoss6PlotFalzAction leave;
    TBoss6PlotFalzAction tick;
    TBoss6PlotFalzAction update;
};
typedef char TBoss6PlotFalzAction_size[sizeof(TBoss6PlotFalzAction) == 12 ? 1 : -1];
typedef char TBoss6PlotFalzScriptState_size[sizeof(TBoss6PlotFalzScriptState) == 0x34 ? 1 : -1];
typedef char TBoss6PlotFalzScriptState_name_offset[offsetof(TBoss6PlotFalzScriptState, name) == 0 ? 1 : -1];
typedef char TBoss6PlotFalzScriptState_enter_offset[offsetof(TBoss6PlotFalzScriptState, enter) == 4 ? 1 : -1];
typedef char TBoss6PlotFalzScriptState_leave_offset[offsetof(TBoss6PlotFalzScriptState, leave) == 0x10 ? 1 : -1];
typedef char TBoss6PlotFalzScriptState_tick_offset[offsetof(TBoss6PlotFalzScriptState, tick) == 0x1C ? 1 : -1];
typedef char TBoss6PlotFalzScriptState_update_offset[offsetof(TBoss6PlotFalzScriptState, update) == 0x28 ? 1 : -1];

extern "C" TBoss6PlotFalzScriptState TBoss6PlotFalz__data_804DE66C[9];

#endif
