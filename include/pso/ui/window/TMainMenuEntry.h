#ifndef PSO_UI_WINDOW_TMAINMENUENTRY_H
#define PSO_UI_WINDOW_TMAINMENUENTRY_H

#include "types.h"

struct TMainMenuRow;

struct TMainMenuEntry {
    int is_item_active();
    void set_symbol_chat_parts(TMainMenuRow *row);
    void update_item_tween();
    void init_color();
};

#endif
