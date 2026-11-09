#include "types.h"
#include "pso/misc/TLobby_8001D6A0.h"
#include "pso/misc/TWindowSubShortMail_80246CB8.h"
#include "pso/misc/TWindowSubStatusDisp_80228CC0.h"
#include "pso/misc/TWindowSubStatusDisp_80228F5C.h"
#include "pso/misc/TWindowSubStatusDisp_8025A9B4.h"
#include "pso/unk/text_80198A2C.h"
#include "pso/unk/text_8026CB5C.h"
#include "pso/misc/TWindowBase.h"
#include "pso/misc/TWindowTimer.h"
#include "pso/misc/TWindowDD.h"
#include "pso/misc/TWindowHelpItem.h"
#include "pso/misc/TWindowSubShortMail.h"
#include "pso/misc/TWindowSubSymbolChatPartsSet.h"

#pragma readonly_strings on

struct RecoveredGlobal_80287FBC_lbl_804D2E74 {
    s32 value;
    u8 remaining[0x10];
};

extern "C" {
s32 draw_visible_window_entries(void *, void *, int);
s32 draw_window_tab(void *, void *, int, f32);
extern const f32 lbl_805DD890;
extern RecoveredGlobal_80287FBC_lbl_804D2E74 window_timer_layout;
extern const char *TWindowTimer__name;
extern s32 lbl_805DD888;
extern s32 lbl_805DD88C;
s32 get_window_layout_position(s32);

void TWindowTimer::update_chat_parts() {
    u8 *arg0 = (u8 *)this;
    s32 window_layout_position;

    if (this->m_60 & 1) {
        window_layout_position = get_window_layout_position(0xA9);
    } else if ((TWindowSubShortMail::is_active() != 0) || (is_com_card_active() != 0) || (is_guild_card_receive_active() != 0)) {
        window_layout_position = get_window_layout_position(0xA8);
    } else {
        window_layout_position = get_window_layout_position(0x22);
    }
    ((TWindowSubSymbolChatPartsSet *)(arg0 + 0x30))->copy_vec2((void*)window_layout_position);
}

extern s32 lbl_805DD884;

void TWindowTimer::draw(s32 arg1, s32 arg2) {
    s32 array_entry;

    array_entry = (s32)get_array_entry(0);
    text_builder_reset();
    text_builder_append((u8 *)&lbl_805DD884);
    append_padded_number(arg1, 3);
    text_builder_append((u8 *)"\tC7:\tC3");
    append_padded_number(arg2, 3);
    set_text_entry_string((u8 *)array_entry, (u32)(get_shared_text_buffer()), 0x20);
    ((TWindowHelpItem *)array_entry)->reset_float_field();
}

void TWindowTimer::set_time(u32 secs) {
    s32 entry;
    u32 hours;
    u32 mins;
    entry = (s32)get_array_entry(0);
    text_builder_reset();
    hours = secs / 3600;
    secs %= 3600;
    if (hours > 9) {
        text_builder_append((u8 *)"9'59\"59");
    } else {
        append_padded_number((hours), 1);
        text_builder_append((u8 *)&lbl_805DD888);
        mins = secs / 60;
        secs %= 60;
        append_padded_number((mins), 2);
        text_builder_append((u8 *)&lbl_805DD88C);
        append_padded_number((secs), 2);
    }
    set_text_entry_string((u8 *)entry, (u32)(get_shared_text_buffer()), 0x20);
    ((TWindowHelpItem *)entry)->reset_float_field();
}

void TWindowTimer::draw_tab(s32 context) {
    draw_window_tab((void *)context, (void *)(context + 0x10), 3, (f32)lbl_805DD890);
}

s32 TWindowTimer::create() {
    TWindowTimer *window_timer = new TWindowTimer;
    init_timer_window_layout(window_timer);
    return (s32)window_timer;
}

s32 TWindowTimer::create_alt() {
    TWindowTimer *window_timer = new TWindowTimer;
    init_timer_window_layout_alt(window_timer);
    return (s32)window_timer;
}

void TWindowTimer::render() {
    s32 context = TWindowDD::draw_default_entry((s32)this);
    draw_tab(context);
    draw_visible_window_entries(this, &m_24, context);
}

void TWindowTimer::run_task() {
    if (m_60 & 1) {
        draw(get_timer_value(0), get_timer_value(1));
    }
    ((TWindowDD *)this)->initialize_subwindow();
    update_chat_parts();
    ease_window_timer_position();
    update_window_entry_list(&m_24);
}

TWindowTimer::~TWindowTimer() {}

typedef char RecoveredGlobal_80287FBC_lbl_804D2E74_size[sizeof(RecoveredGlobal_80287FBC_lbl_804D2E74) == 0x14 ? 1 : -1];

TWindowTimer::TWindowTimer()
    : TWindowBase((u8 *)&window_timer_layout, 4, (u8 *)get_zero_vec2()) {
    m_name = TWindowTimer__name;
    m_60 = 0;
    update_chat_parts();
    save_position();
}

}
