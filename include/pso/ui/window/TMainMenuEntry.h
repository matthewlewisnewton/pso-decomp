#ifndef PSO_UI_WINDOW_TMAINMENUENTRY_H
#define PSO_UI_WINDOW_TMAINMENUENTRY_H

#include "types.h"
#include <stddef.h>

struct TMainMenuRow;

struct TMainMenuEntry {
    f32 x;
    f32 y;
    f32 cur_x;
    f32 cur_y;
    s8 fade;
    s8 icon;
    s8 kind;
    u8 flags;
    s8 tween;
    u8 b5;
    u8 b6;
    u8 b7;
    int is_item_active();
    void set_symbol_chat_parts(TMainMenuRow *row);
    void update_item_tween();
    void init_color();
};

typedef char TMainMenuEntry_size[sizeof(TMainMenuEntry) == 0x18 ? 1 : -1];
typedef char TMainMenuEntry_flags[offsetof(TMainMenuEntry, flags) == 0x13 ? 1 : -1];

#endif
