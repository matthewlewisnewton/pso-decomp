#include "pso/misc/TWindowDrawContext.h"
#include "types.h"
#include "pso/misc/TWindowBase.h"
#include "pso/misc/TWindowMenuIconLine.h"
#include "pso/misc/TWindowSubEquipList.h"
#include "pso/misc/TWindowSubStatusDisp.h"

#pragma readonly_strings on

extern "C" {
const char *TWindowSubEquipList__class_name = "TWindowSubEquipList";
}


extern "C" {
s32 draw_visible_window_entries(void *, void *, int);
s32 forward_render__20TWindowSubStatusDispFv(void *, int);
s32 TShopJudgmentItemWindow__sub_80267F9C(void *, int);
extern const char *TWindowSubEquipList__class_name;

u8 *create_equip_list_window(s32 arg0, s32 arg1, s32 arg2) {
    TShopJudgmentItemWindow__sub_80267F9C((void *)arg1, 8);
    return (u8 *)new TWindowSubEquipList((void *)arg0, arg2);
}

#pragma push
#pragma fp_contract on
void TWindowSubEquipList::render() {
    s32 temp_r3;
    temp_r3 = (s32)get_draw_context__11TWindowBaseFPv(this);
    draw_window_frame((void *)temp_r3);
    draw_visible_window_entries(this, (void *) (((u8 *)this) + 0x24), temp_r3);
    draw_selected_list_entry(temp_r3);
    if ((u32) this->status_display != 0U) {
        forward_render__20TWindowSubStatusDispFv(this->status_display, temp_r3);
    }
}
#pragma pop

void TWindowSubEquipList::run_task() {
    TWindowMenuIconLine::run_task();
}

TWindowSubEquipList::~TWindowSubEquipList() {}

TWindowSubEquipList::TWindowSubEquipList(void *position, s32 client)
    : TWindowMenuIconLine((u8 *)position, 8, (s16)client) {
    m_name = TWindowSubEquipList__class_name;
    ensure_status_display((s32)TWindowSubStatusDisp::get_message_10(0x25));
}

}
