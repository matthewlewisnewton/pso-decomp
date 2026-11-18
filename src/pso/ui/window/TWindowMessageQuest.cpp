#include "pso/ui/window/TWindowDrawContext.h"
#include "types.h"
#include "pso/ui/window/TWindowMessageQuest.h"
#include "pso/ui/window/TWindowBase.h"
#include "pso/unk/TLobby_8026B06C.h"
#include "pso/network/client_id.h"
#include <dolphin/mtx/GeoTypes.h>

#pragma readonly_strings on

const char *TWindowMessageQuest__name = "TWindowMessageQuest";

// create_quest_message_window_at's second argument (384 x 80: the window's size, inferred)
static const Vec lbl_8044F464 = {384.0f, 80.0f, 0.0f};

extern "C" {
s32 get_window_layout_position(int);
void draw_visible_window_entries(void *, void *, void *);
extern s32 __vt__19TWindowMessageQuest[];
u8 *TWindowMessage__ct(u8 *arg0, s32 arg1, u32 arg2, s32 arg3);

void create_quest_message_window(void) {
    create_quest_message_window_at((get_window_layout_position(0xAD)), (s32)&lbl_8044F464);
}
void TWindowMessageQuest::render() {
    TWindowDrawContext *c = setup_content_draw_context();
    switch (frame_mode) {
    case 0:
        if (c->open_tick < 0) {
            c->scale[0] = (f32)open_tick / 7.5f;
            c->scale[1] = c->scale[0];
        }
        this->draw_quest_message_frame(c);
        break;
    case 1:
        draw_window_frame(c);
        break;
    case 2:
        break;
    }
    draw_visible_window_entries(this, &entry_list, c);
}

}

TWindowMessageQuest::~TWindowMessageQuest() {

}


u8 *TWindowMessageQuest__ct(u8 *arg0, s32 arg1) {
    TWindowMessage__ct((arg0), (arg1), 1, (local_client_id));
    *(s32 **)((s8 *)arg0 + 0x18) = __vt__19TWindowMessageQuest;
    *(s32 *)((s8 *)arg0 + 0) = (s32)TWindowMessageQuest__name;
    ((TWindowMessageQuest *)arg0)->frame_mode = 0;
    return arg0;
}

