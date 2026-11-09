#include "pso/misc/TWindowDrawContext.h"
#include "types.h"
#include "pso/misc/TWindowBase.h"
#include "pso/misc/TWindowMenuIconLine.h"
#include "pso/misc/TWindowSubEquipKind.h"
#include "pso/misc/TWindowSubStatusDisp.h"

extern "C" {
extern const char *TWindowSubEquipKind__class_name;
s32 draw_visible_window_entries(void *, void *, s32);
s32 draw_window_scrollbar(s32, s32, void *);
s32 forward_render__20TWindowSubStatusDispFv(s32, s32);

void TWindowSubEquipKind::render() {
    s32 temp_r3;

    temp_r3 = (s32)get_draw_context__11TWindowBaseFPv(this);
    this->draw_window_frame((void *)temp_r3);
    draw_visible_window_entries(this, (u8 *)this + 0x24, temp_r3);
    this->draw_selected_list_entry(temp_r3);
    if ((s16) this->m_88 != 4) {
        this->draw_tab_label((void *)temp_r3);
    }
    if ((u32) *(u32 *)((s8 *)this + 0x80) != 0U) {
        forward_render__20TWindowSubStatusDispFv(*(u32 *)((s8 *)this + 0x80), temp_r3);
    }
    if ((u32) *(u32 *)((s8 *)this + 0x84) != 0U) {
        draw_window_scrollbar(*(u32 *)((s8 *)this + 0x84), temp_r3, (u8 *)this + 0x68);
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
