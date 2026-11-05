#include "types.h"
#include "pso/misc/TWindowSubItem.h"
#include "pso/misc/TWindowSubStatusDisp.h"

void TWindowSubItem::clear_selected_and_update_entry() {
    *(u16 *)((s8 *)this + 0x70) = (u16) (*(u16 *)((s8 *)this + 0x70) & 0xFFFFFFFD);
    if ((u32) *(u32 *)((s8 *)this + 0x80) != 0U) {
        ((TWindowSubStatusDisp *)(*(s32 *)((s8 *)this + 0x80)))->set_entry_state(1);
    }
}
