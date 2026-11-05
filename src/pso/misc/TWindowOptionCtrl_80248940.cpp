#include "types.h"
#include "pso/misc/TWindowOptionCtrl.h"

extern "C" {

s32 get_cursor_pos__14TWindowSubItemFv();
s32 get_array_entry__13TUnk_804CE018Fi(void *, s16);

void TWindowOptionCtrl::update_selected_item() {
    get_array_entry__13TUnk_804CE018Fi(this, *(s16 *)((s8 *)this + 0x88));
    get_cursor_pos__14TWindowSubItemFv();
}

}
