#include "types.h"
#include "pso/ui/window/TWindowBase.h"
#include "pso/ui/window/TWindowMenuIconLine.h"
#include "pso/ui/window/TWindowSubEquipKind.h"
#include "pso/ui/window/TWindowSubStatusDisp.h"

extern "C" {
extern const char *TWindowSubEquipKind__class_name;
void *get_draw_context__11TWindowBaseFPv(void *window);
s32 draw_visible_window_entries(void *, void *, s32);
s32 draw_window_scrollbar(s32, s32, void *);
s32 forward_render__20TWindowSubStatusDispFv(s32, s32);

void TWindowSubEquipKind::render() {
    s32 context = (s32)get_draw_context__11TWindowBaseFPv(this);
    draw_window_frame((void *)context);
    draw_visible_window_entries(this, (u8 *)this + 0x24, context);
    draw_selected_list_entry(context);
    if (m_88 != 4) {
        draw_tab_label((void *)context);
    }
    if (status_display != NULL) {
        forward_render__20TWindowSubStatusDispFv((s32)status_display, context);
    }
    if (unk_84 != NULL) {
        draw_window_scrollbar((s32)unk_84, context, &m_68);
    }
}

void TWindowSubEquipKind::run_task() {
    int temp_r3;

    TWindowMenuIconLine::run_task();
    temp_r3 = this->m_8a;
    if (temp_r3 != 0) {
        this->m_8a = (temp_r3 - 1);
    }
}

TWindowSubEquipKind::~TWindowSubEquipKind() {}

TWindowSubEquipKind::TWindowSubEquipKind(void *position, s32 client)
    : TWindowMenuIconLine((u8 *)position, 0x1F, (s16)client) {
    m_name = TWindowSubEquipKind__class_name;
    create_menu_scroll_bar();
    m_88 = 4;
    m_8a = 0;
}

}
