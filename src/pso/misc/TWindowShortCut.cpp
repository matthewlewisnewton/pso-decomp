#include "pso/misc/WindowLayoutDescriptor.h"
#include "types.h"
#include "pso/misc/TWindowShortCut.h"
#include "pso/misc/TWindowChatSymbol.h"
#include "pso/misc/TWindowDD.h"
#include "pso/misc/TWindowSubStatusDisp.h"

extern "C" {
s32 draw_visible_window_entries(void *, void *, s32);
s32 forward_render__20TWindowSubStatusDispFv(void *, s32);
void *construct_type1_heading__20TWindowSubStatusDispFll(void *storage, s32 text, s32 client);
extern u8 lbl_804D0968[];
WindowLayoutDescriptor window_short_cut_layout = {
    {405.0f, 188.0f}, 50100.0f, lbl_804D0968, 0x63
};
extern const char *TWindowShortCut__name;
s32 initialize_subwindow__9TWindowDDFv(void *);

void TWindowShortCut::render() {
    s32 context;
    context = TWindowDD::draw_default_entry((s32)this);
    draw_window_frame((void *)context);
    draw_visible_window_entries(this, (u8 *)this + 0x24, context);
    forward_render__20TWindowSubStatusDispFv(m_60, context);
}

void TWindowShortCut::run_task() {
    ((TWindowSubStatusDisp *)m_60)->update_subwindow();
    initialize_subwindow__9TWindowDDFv(this);
    update_fade();
    update_window_entry_list((u8 *)this + 0x24);
}

TWindowShortCut::~TWindowShortCut() {
    if (m_68 != NULL) {
        m_68->close();
        m_68 = NULL;
    }
    if (m_64 != NULL) {
        m_64->close();
        m_64 = NULL;
    }
    TWindowSubStatusDisp::destroy_status_display((s32)m_60, 1);
}

TWindowShortCut::TWindowShortCut(void *position, s32 index, void *shortcut)
    : TWindowBase((u8 *)&window_short_cut_layout, 4, (u8 *)position) {
    void *heading;
    m_name = TWindowShortCut__name;
    heading = ::operator new(0x24);
    if (heading != NULL) {
        heading = construct_type1_heading__20TWindowSubStatusDispFll(
            heading, (s32)TWindowSubStatusDisp::get_message_10(0x35), m_20);
    }
    m_60 = heading;
    m_64 = NULL;
    m_68 = NULL;
    m_6c = index;
    m_70 = shortcut;
    initialize_preview(index, (s32 *)shortcut);
}

}
