#include "pso/misc/WindowLayoutDescriptor.h"
#include "types.h"
#include "pso/misc/TWindowCtrlMain_8024674C.h"
#include "pso/misc/TWindowBase.h"
#include "pso/misc/TWindowBreakIn.h"
#include "pso/misc/TWindowDD.h"

#pragma push
#pragma readonly_strings on
const char *lbl_805D3890 = "TWindowBreakIn";
#pragma pop

extern "C" {
u8 * get_window_layout_position(s32);
extern u8 lbl_804CE030[];
WindowLayoutDescriptor window_break_in_layout = {
    {112.0f, 30.0f}, 50000.0f, lbl_804CE030, 0x823
};
s32 draw_visible_window_entries(s32, s32, s32);
int initialize_subwindow__9TWindowDDFv(void*);

void TWindowBreakIn::render() {
    s32 context = TWindowDD::draw_default_entry((s32)this);
    draw_visible_window_entries((s32)this, (s32)&m_24, context);
}

void TWindowBreakIn::run_task() { update_entry_visibility__20TWindowSubStatusDispFv((s32)this); initialize_subwindow__9TWindowDDFv(this); update_window_entry_list((char*)this + 0x24); }

TWindowBreakIn::~TWindowBreakIn() {}

TWindowBreakIn::TWindowBreakIn()
    : TWindowBase((u8 *)&window_break_in_layout, 4, get_window_layout_position(0xAA)) {
    m_name = lbl_805D3890;
}

}
