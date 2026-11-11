#include "pso/misc/WordSelectMessage.h"
#include "pso/misc/PageIndicator.h"
#include "pso/misc/TWindowDrawContext.h"
#include "types.h"
#include "pso/unk/text_80076BC4.h"
#include "pso/misc/TWindowBase.h"
#include "pso/misc/TWindowMenuIconLine.h"
#include "pso/misc/TWindowSubShortCutList.h"
#include "pso/misc/TWindowChat.h"
#include "pso/misc/TWindowShortListCtrl.h"
#include "pso/misc/TWindowSubStatusDisp.h"
#include "pso/misc/TWindowSubSymbolChat.h"

extern "C" {
void TShopJudgmentItemWindow__sub_80267F9C(void *, int);
extern s32 lbl_8044FAA8[];
extern const char *TWindowSubShortCutList__class_name;
extern s32 local_client_id;
s32 get_shared_text_buffer();
s32 clamp_selection_to_valid_entry__20TShopArmorListWindowFv(void *);
s32 save_cursor_selection__20TShopArmorListWindowFv();
s32 reset_list__19TWindowMenuIconLineFv(void *);
s32 draw_visible_window_entries(void *, void *, s32);
s32 forward_render__20TWindowSubStatusDispFv(s32, s32);

void TWindowSubShortCutList::refresh_entries() {
    s32 *chat_shortcut;
    s32 temp_r0;
    s32 var_r30;
    s32 var_r29;
    save_cursor_selection__20TShopArmorListWindowFv();
    reset_list__19TWindowMenuIconLineFv(this);
    var_r29 = ((PageIndicator *)this->m_88)->get_type();
    var_r30 = 0;
    var_r29 *= 4;
    do {
        chat_shortcut = (s32 *)get_chat_shortcut(var_r29);
        switch (*chat_shortcut) {
        case 0:
            draw_entry(var_r29, 0x33, 0, var_r29);
            break;
        case 1:
            temp_r0 = (s32)fn_80076BC4(chat_shortcut + 1);
            draw_entry(var_r29, 0x12, temp_r0, var_r29);
            break;
        case 2:
            format_word_select_message((WordSelectMessage *)(chat_shortcut + 1), (char *)get_shared_text_buffer(), (u16) local_client_id);
            draw_entry(var_r29, 0x10, get_shared_text_buffer(), var_r29);
            break;
        case 3: {
            u8 *preset = TWindowChat::open_symbol_chat(chat_shortcut + 1);
            u8 *name = reinterpret_cast<TWindowSubSymbolChat *>(preset)->get_symbol_chat_data();
            draw_entry(var_r29, 0x11, (s32)name, var_r29);
            break;
        }
        }
        var_r30 += 1;
        var_r29 += 1;
    } while (var_r30 < 4);
    clamp_selection_to_valid_entry__20TShopArmorListWindowFv(this);
}

TWindowSubShortCutList *TWindowSubShortCutList::create(void *position, s32 selection) {
    TShopJudgmentItemWindow__sub_80267F9C(lbl_8044FAA8, 4);
    return new TWindowSubShortCutList(position, selection);
}

void TWindowSubShortCutList::render() {
    s32 temp_r3;

    temp_r3 = (s32)get_draw_context__11TWindowBaseFPv(this);
    this->draw_window_frame((void *)temp_r3);
    draw_visible_window_entries(this, (u8 *)this + 0x24, temp_r3);
    this->draw_selected_list_entry(temp_r3);
    if ((u32) *(u32 *)((s8 *)this + 0x80) != 0U) {
        forward_render__20TWindowSubStatusDispFv(*(u32 *)((s8 *)this + 0x80), temp_r3);
    }
    if ((u32) this->m_88 != 0U) {
        draw_list_page_indicator((PageIndicator *)(this->m_88), (TWindowDrawContext *)(temp_r3));
    }
}

void TWindowSubShortCutList::run_task() {
    TWindowMenuIconLine::run_task();
    if ((is_decided() == 0) && (handle_list_page_flip_input((PageIndicator *)(this->m_88)) != 0)) {
        refresh_entries();
    }
}

TWindowSubShortCutList::~TWindowSubShortCutList() {
    delete_if_allocated((void *)m_88, 1);
}

TWindowSubShortCutList::TWindowSubShortCutList(void *position, s32 selection)
    : TWindowMenuIconLine((u8 *)position, 4, (s16)local_client_id) {
    s32 row;
    s32 col;
    m_name = TWindowSubShortCutList__class_name;
    row = selection / 4;
    col = selection % 4;
    ensure_status_display((s32)TWindowSubStatusDisp::get_message_10(0x2D));
    m_88 = (u32)new PageIndicator((s8)row, 5, local_client_id);
    set_flag70_bit10();
    refresh_entries();
    set_cursor_index((s16)col);
}

}
