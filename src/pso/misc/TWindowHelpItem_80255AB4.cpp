#include "pso/misc/PageIndicator_8026CB44.h"
#include "pso/misc/WindowLayoutDescriptor.h"
#include "types.h"
#include "pso/unk/text_80263A20.h"
#include "pso/misc/TWindowHelpItem_80255AB4.h"
#include "pso/misc/TWindowBase.h"
#include "pso/misc/TWindowHelpItem.h"
#include "pso/misc/TWindowDD.h"
#include "pso/misc/TWindowSubComCard.h"
#include "pso/misc/TWindowSubMag.h"
#include "pso/misc/TWindowSubStatusDisp.h"
#include "pso/misc/TWindowSubSymbolChatPartsSet.h"
#include "pso/ui/TWindowInputNumber.h"

#pragma inline_depth(1)
#pragma auto_inline off
#pragma dont_inline off

extern "C" {
extern u8 *text_language_group_table;
extern WindowLayoutDescriptor window_help_item_parameters;
extern const char *window_help_item_class_name;
extern TWindowHelpItem::CallbackWords __ptmf_null;
extern const f32 lbl_805DCE10;
void call_if_split_screen(void *self, s32 idx);
// Existing two-float copy entry; target is the position prefix, not a PartsSet.
void copy_vec2__28TWindowSubSymbolChatPartsSetFPv(void *destination, void *source);

s32 draw_visible_window_entries(void *, void *, int);

void TWindowHelpItem::update_cursor_selection() {
    this->m_60 = (u8) (this->m_60 | 1);
    if ((s32) this->m_a4 != -1) {
        this->m_68 = (s32) this->m_70;
        this->m_9c = (s32) this->m_a4;
        return;
    }
    if ((s32) this->m_a0 != -1) {
        this->m_68 = (s32) this->m_6c;
        this->m_9c = (s32) this->m_a0;
        return;
    }
    this->m_60 = (u8) (this->m_60 & 0xFE);
    this->m_68 = 0;
    this->m_9c = -1;
}

void TWindowHelpItem::render() {
    s32 context = setup_window_draw_context((s32)&m_a8);
    draw_window_frame((void *)context);
    draw_visible_window_entries(this, (u8 *)this + 0x24, context);
    if ((m_60 & 1) && (m_60 & 2)) {
        draw_list_page_indicator(m_64, (TWindowDrawContext *)context);
    }
}

void TWindowHelpItem::run_task() {
    u8 *arg0 = (u8 *)this;
    if (!(this->m_2c & 2)) {
        this->m_5c = 0x01000000;
    }
    if ((this->m_60 & 1) && (((TWindowBase *)arg0)->sub_80244994() != 0) && !(this->m_2c & 4)) {
        if (!(this->m_60 & 4)) {
            if (handle_list_page_flip_input((PageIndicator_8026CB44 *)(this->m_64)) != 0) {
                ((TWindowHelpItem *)arg0)->dispatch_item_help();
            }
        } else {
            decay_page_arrow_offset((PageIndicator_8026CB44 *)(this->m_64));
        }
        ((TWindowHelpItem *)arg0)->invoke_callback_pmf();
    }
    ((TWindowDD *)arg0)->initialize_subwindow();
    ((TWindowBase *)arg0)->update_fade();
    ((TWindowBase *)arg0)->update_window_entry_list((u8 *)&this->m_24);
    if (!(this->m_60 & 8)) {
        toggle_help_window_on_button((u32)arg0, this->m_20);
    }
}

TWindowHelpItem::~TWindowHelpItem() {
    delete_if_allocated(m_64, 1);
}

}
TWindowHelpItem::TWindowHelpItem(void *pos, u16 idx)
    : TWindowBase((u8 *)&window_help_item_parameters, (s16)idx, (u8 *)pos) {
    m_name = window_help_item_class_name;
    copy_vec2__28TWindowSubSymbolChatPartsSetFPv(&m_30, pos);
    save_position();
    m_60 = 0;
    m_64 = new PageIndicator_8026CB44(0, 3, m_20);
    m_68 = 0;
    m_6c = 0;
    m_70 = 0;
    m_9c = -1;
    m_a0 = -1;
    m_a4 = -1;
    m_callback = __ptmf_null;
    m_a8 = lbl_805DCE10;
    m_ac = lbl_805DCE10;
    dispatch_item_help();
    call_if_split_screen(this, m_20);
}

s32 get_help_text_string(s32 arg0) {
    return *(s32 *)((s8 *)(*(s32 *)((s8 *)text_language_group_table + 0x18)) + (arg0 * 4));
}

s32 TWindowHelpItem__sub_80255DDC(void* p) { return *(s32*)((char*)p + 0x1c); }
void TWindowHelpItem::set_flag0_bit20() { *(u16*)((char*)this + 0x0) |= 0x20; }
