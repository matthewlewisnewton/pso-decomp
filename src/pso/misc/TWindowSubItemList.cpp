#include "pso/misc/TWindowDrawContext.h"
#include "types.h"
#include "pso/misc/TWindowBase.h"
#include "pso/misc/TWindowMenuIconLine.h"
#include "pso/misc/TWindowSubItemList.h"
#include "pso/misc/TWindowSubItem.h"
#include "pso/misc/TWindowSubStatusDisp.h"

#pragma readonly_strings on

extern "C" {
const char *TWindowSubItemList__class_name = "TWindowSubItemList";
}


extern "C" {
s32 draw_visible_window_entries(void *, void *, int);
s32 draw_item_list_capacity(void *, int, int, int);
s32 draw_window_scrollbar(void *, int, void *);
s32 forward_render__20TWindowSubStatusDispFv(void *, int);
s32 TShopJudgmentItemWindow__sub_80267F9C(void *, int);
extern const char *TWindowSubItemList__class_name;

TWindowSubItemList *create_sub_item_list_window(void *position, void *extent, s32 client) {
    TShopJudgmentItemWindow__sub_80267F9C(extent, 0x24);
    return new TWindowSubItemList(position, client);
}

#pragma push
#pragma fp_contract on
void TWindowSubItemList::render() {
    u8 *arg0 = (u8 *)this;
    s32 window_key_board_soft;
    window_key_board_soft = (s32)get_draw_context__11TWindowBaseFPv(this);
    ((TWindowBase *)arg0)->draw_window_frame((void *)window_key_board_soft);
    draw_visible_window_entries(arg0, arg0 + 0x24, window_key_board_soft);
    ((TWindowMenuIconLine *)arg0)->draw_selected_list_entry(window_key_board_soft);
    ((TWindowSubItemList *)arg0)->sub_8027ACF8((u8 *)window_key_board_soft);
    draw_item_list_capacity(arg0, window_key_board_soft, this->m_8c, 0x1E);
    if ((u32) *(u32 *)&this->status_display != 0U) {
        forward_render__20TWindowSubStatusDispFv(this->status_display, window_key_board_soft);
    }
    if ((u32) *(u32 *)&this->unk_84 != 0U) {
        draw_window_scrollbar(*(void * *)&this->unk_84, window_key_board_soft, (u8 *)&this->m_68);
    }
}
#pragma pop

void TWindowSubItemList::run_task() {
    TWindowMenuIconLine::run_task();
}

TWindowSubItemList::~TWindowSubItemList() {}

TWindowSubItemList::TWindowSubItemList(void *position, s32 client)
    : TWindowMenuIconLine((u8 *)position, 0x24, (s16)client) {
    m_name = TWindowSubItemList__class_name;
    ensure_status_display((s32)TWindowSubStatusDisp::get_message_10(0x24));
    create_menu_scroll_bar();
    reset_selected();
    m_8c = 0;
}

}
