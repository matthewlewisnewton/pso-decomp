#ifndef PSO_BOSS_TBOSS6PLOTFALZSTATE_H
#define PSO_BOSS_TBOSS6PLOTFALZSTATE_H

#include "pso/boss/TBoss6PlotFalz.h"
#include <stddef.h>

// The Falz plot demo-script state table: nine 0x34-byte records
// {name, enter, idle, update, advance} consumed by
// TBoss6PlotFalz::run_phase_action (+0x28), call_state_action (+0x1C)
// and set_state (+0x10/+0x4).
typedef void (TBoss6PlotFalz::*TBoss6PlotFalzAction)();
struct TBoss6PlotFalzScriptState {
    const char *name;
    TBoss6PlotFalzAction enter;
    TBoss6PlotFalzAction idle;
    TBoss6PlotFalzAction update;
    TBoss6PlotFalzAction advance;
};
typedef char TBoss6PlotFalzAction_size[sizeof(TBoss6PlotFalzAction) == 12 ? 1 : -1];
typedef char TBoss6PlotFalzScriptState_size[sizeof(TBoss6PlotFalzScriptState) == 0x34 ? 1 : -1];
typedef char TBoss6PlotFalzScriptState_name_offset[offsetof(TBoss6PlotFalzScriptState, name) == 0 ? 1 : -1];
typedef char TBoss6PlotFalzScriptState_enter_offset[offsetof(TBoss6PlotFalzScriptState, enter) == 4 ? 1 : -1];
typedef char TBoss6PlotFalzScriptState_idle_offset[offsetof(TBoss6PlotFalzScriptState, idle) == 0x10 ? 1 : -1];
typedef char TBoss6PlotFalzScriptState_update_offset[offsetof(TBoss6PlotFalzScriptState, update) == 0x1C ? 1 : -1];
typedef char TBoss6PlotFalzScriptState_advance_offset[offsetof(TBoss6PlotFalzScriptState, advance) == 0x28 ? 1 : -1];

extern "C" TBoss6PlotFalzScriptState TBoss6PlotFalz__data_804DE66C[9];

#endif
