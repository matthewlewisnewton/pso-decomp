#include "types.h"
#include "pso/boss/TBoss6PlotFalzState.h"
#include "pso/render/render_util.h"
#include "pso/unk/text_802B0A44.h"

#include "pso/misc/TWindowCtrlMain.h"

#include <stddef.h>
struct Stack_802B0DCC {
    s32 * sp8;
    s32 * spC;
    s32 sp10;
    s32 sp14;
};

extern s32 empty_warp_overlay_zero_vec[];
extern s32 empty_warp_overlay_vertices[];
extern const f32 lbl_805DE228;
void draw_empty_warp_overlay(void) {
    typedef char sp8_offset[(offsetof(Stack_802B0DCC, sp8) == 0x0) ? 1 : -1];
    typedef char spC_offset[(offsetof(Stack_802B0DCC, spC) == 0x4) ? 1 : -1];
    typedef char sp10_offset[(offsetof(Stack_802B0DCC, sp10) == 0x8) ? 1 : -1];
    typedef char sp14_offset[(offsetof(Stack_802B0DCC, sp14) == 0xC) ? 1 : -1];
    Stack_802B0DCC stack;
    stack.spC = empty_warp_overlay_zero_vec;
    stack.sp10 = 0;
    stack.sp14 = 4;
    stack.sp8 = empty_warp_overlay_vertices;
    set_depth_buffer_settings_1();
    ((TWindowCtrlMain *)(&stack.sp8))->draw_strip_swap_color(4, 2, lbl_805DE228);
    restore_saved_depth_alpha_state();
}

// --- __sinit_text_802B0A44_cpp: boot-seed ctor for the Falz plot demo state
// table --- File-scope array of 9 script states {name, 4x member-action
// slots}, typed by pso/boss/TBoss6PlotFalzState.h and consumed through that
// shared type by TBoss6PlotFalz::run_phase_action, call_state_action and
// set_state. The null PMF slots force runtime init: MWCC gathers the 25
// constant member pointers into a .data template (lbl_804DE540, 0x12C) and
// synthesizes __sinit_text_802B0A44_cpp (registered in .ctors at 0x80433FC4)
// that copies the template over the instance TBoss6PlotFalz__data_804DE66C
// (0x1D4) and writes __ptmf_null into the empty action slots.

extern "C" {
extern const char lbl_80470920[];  // "FALL_ELEV"
extern const char lbl_8047092C[];  // "DEMO_START"
extern const char lbl_80470938[];  // "VS_TYPE1"
extern const char lbl_80470944[];  // "DEMO_DED_T1"
extern const char lbl_80470950[];  // "DEMO_WAIT_T2"
extern const char lbl_80470960[];  // "DEMO_APP_T2"
extern const char lbl_8047096C[];  // "VS_TYPE2"
extern const char lbl_80470978[];  // "DEMO_END"
extern const char lbl_80470984[];  // "OL_ENDING"
}

// Ten of the table's twenty-five action slots target free functions: the era
// symbols (TBoss6PlotFalz__sub_802B0A34, init_proto1_adx__FPv,
// stop_adx_audio__FPv and their siblings, defined in the TPlayerFootStamp
// units) fix them as free functions that take the controller as void*. MWCC
// cannot form a member-pointer constant from a free function, so these slots
// are declared through this provisional shim, which gives them the same
// {0, -1, target} member-pointer form as the genuine members. The shim is
// never instantiated and its members are never defined; it exists only for
// these ten table entries.
class FalzPlotActionShim : public TBoss6PlotFalz {
public:
    void sub_802B0A34();
    void init_proto1_adx();
    void sub_802B08F0();
    void sub_802B0808();
    void sub_802B06D0();
    void init_hall_boss_scene();
    void stop_adx_audio();
    void sub_802B0448();
    void sub_802B03F4();
    void sub_802B0228();
};
typedef void (FalzPlotActionShim::*FalzPlotActionShimAction)();

extern "C" {
TBoss6PlotFalzScriptState TBoss6PlotFalz__data_804DE66C[9] = {
    { lbl_80470920, (TBoss6PlotFalzAction)(FalzPlotActionShimAction)&FalzPlotActionShim::sub_802B0A34, 0,
      &TBoss6PlotFalz::advance_if_ready, &TBoss6PlotFalz::advance_intro_timer },
    { lbl_8047092C, (TBoss6PlotFalzAction)(FalzPlotActionShimAction)&FalzPlotActionShim::init_proto1_adx, 0,
      (TBoss6PlotFalzAction)(FalzPlotActionShimAction)&FalzPlotActionShim::sub_802B08F0, &TBoss6PlotFalz::tick_timeout },
    { lbl_80470938, &TBoss6PlotFalz::enter_active_state, 0,
      &TBoss6PlotFalz::update_phase, (TBoss6PlotFalzAction)(FalzPlotActionShimAction)&FalzPlotActionShim::sub_802B0808 },
    { lbl_80470944, &TBoss6PlotFalz::reset_and_recreate, 0,
      &TBoss6PlotFalz::set_state4_if_ready, (TBoss6PlotFalzAction)(FalzPlotActionShimAction)&FalzPlotActionShim::sub_802B06D0 },
    { lbl_80470950, (TBoss6PlotFalzAction)(FalzPlotActionShimAction)&FalzPlotActionShim::init_hall_boss_scene, 0,
      &TBoss6PlotFalz::check_and_advance_state, &TBoss6PlotFalz::update_cutscene_fade },
    { lbl_80470960, (TBoss6PlotFalzAction)(FalzPlotActionShimAction)&FalzPlotActionShim::stop_adx_audio, 0,
      &TBoss6PlotFalz::advance_phase_if_ready, &TBoss6PlotFalz::advance_timer },
    { lbl_8047096C, (TBoss6PlotFalzAction)(FalzPlotActionShimAction)&FalzPlotActionShim::sub_802B0448, 0,
      &TBoss6PlotFalz::check_action_7, (TBoss6PlotFalzAction)(FalzPlotActionShimAction)&FalzPlotActionShim::sub_802B03F4 },
    { lbl_80470978, &TBoss6PlotFalz::finish_and_dispatch_next_phase, 0, 0,
      &TBoss6PlotFalz::update_plot_timer },
    { lbl_80470984, &TBoss6PlotFalz::reset_ending_state, 0, 0,
      (TBoss6PlotFalzAction)(FalzPlotActionShimAction)&FalzPlotActionShim::sub_802B0228 },
};
}
