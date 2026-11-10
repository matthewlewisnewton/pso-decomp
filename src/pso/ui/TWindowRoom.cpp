#include "pso/misc/TWindowBase.h"
#include "types.h"
#include "pso/misc/TWindowSubStatusDisp_8025A9B4.h"
#include "pso/misc/TWindowSubStatusDisp_80287570.h"
#include "pso/ui/TWindowRoom.h"
#include "pso/misc/TWindowSubStatusDisp.h"
#include "pso/misc/TWindowDD.h"

struct RecoveredGlobal_8026D674_lbl_804D08DC {
    s32 value;
    u8 remaining[0x10];
};

struct Pos_8026D740 { f32 x; f32 y; };

struct RoomTitleEntry {
    u8 unknown00[8];
    f32 positionX;
    u8 unknown0C[4];
    f32 width;
};

extern "C" {
int get_array_entry__11TWindowBaseFi(void*, int);
void refresh_status_display__9TWindowDDFv(void *);
s32 get_window_layout_position(int);
extern RecoveredGlobal_8026D674_lbl_804D08DC room_window_base_parameters;
extern const char *TWindowRoom__class_name;
extern const f32 lbl_805DD2F0;
extern const f32 lbl_805DD2F4;
extern const f32 lbl_805DD2F8;
s32 clamp_list_scroll_offset(struct Pos_8026D740 *a, struct Pos_8026D740 *b, struct Pos_8026D740 *c);
s32 draw_visible_window_entries(void *, void *, s32);
s32 draw_window_tab(s32, s32, s32, f32);

}

void *TWindowRoom::get_title_entry() {
    return get_array_entry(0);
}

void TWindowSubStatusDisp::set_entry_display_value(s32 arg1) {
    set_text_entry_string((u8 *)(get_array_entry__11TWindowBaseFi(this, 0)), arg1, 0x60);
}

void TWindowRoom::draw_tab(void *context) {
    draw_window_tab((s32)context, (s32)((u8 *)context + 0x10), 3, tabParameter);
}

void TWindowRoom::render() {
    s32 context = TWindowDD::draw_default_entry((s32)this);
    draw_tab((void *)context);
    draw_visible_window_entries(this, &m_24, context);
}

void TWindowRoom::run_task() {
    ((TWindowDD *)this)->initialize_subwindow();
    update_window_entry_list(&m_24);
}

TWindowRoom::~TWindowRoom() {}

typedef char RecoveredGlobal_8026D674_lbl_804D08DC_size[sizeof(RecoveredGlobal_8026D674_lbl_804D08DC) == 0x14 ? 1 : -1];

TWindowRoom::TWindowRoom(char *title)
    : TWindowBase((u8 *)&room_window_base_parameters, 4, (u8 *)get_window_layout_position(0xAF)) {
    RoomTitleEntry *entry;
    m_name = TWindowRoom__class_name;
    entry = (RoomTitleEntry *)get_array_entry(0);
    set_text_entry_string((u8 *)entry, (u32)title, 0x60);
    refresh_status_display__9TWindowDDFv(entry);
    m_38 = lbl_805DD2F0 + (entry->positionX + entry->width);
    m_30 -= m_38;
    save_position();
    tabParameter = TWindowSubStatusDisp__sub_802877A4(m_48 - lbl_805DD2F4);
}

s32 clamp_list_scroll_offset(struct Pos_8026D740 *a, struct Pos_8026D740 *b, struct Pos_8026D740 *c) {
    f32 room;
    if (a->y < c->y || b->y < lbl_805DD2F8) {
        b->y = lbl_805DD2F8;
        return 1;
    }
    room = a->y - c->y;
    if (b->y > room) {
        b->y = room;
        return 1;
    }
    return 0;
}
