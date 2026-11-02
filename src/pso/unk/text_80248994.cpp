#include "types.h"
#include "pso/misc/TUnk_804CE018.h"
#include "pso/misc/TWindowSubItem.h"
#include "pso/misc/TWindowSubStatusDisp.h"

struct Obj_80248994 { u8 pad[0x76]; s16 count; };

extern "C" void fn_80248994(TUnk_804CE018 *list, u32 color, s32 pos);

void fn_80248994(TUnk_804CE018 *list, u32 color, s32 pos) {
    s32 i;
    s32 e;
    for (i = 0; i < ((Obj_80248994 *)list)->count; i++) {
        e = (s32)list->get_array_entry(i);
        if (e != 0 && ((TWindowSubStatusDisp *)e)->is_flag_4_set() != 0 && pos == ((TWindowSubItem *)e)->get_cursor_pos()) {
            ((TWindowSubItem *)e)->m_2c = color;
            ((TWindowSubItem *)e)->m_30 = color;
        }
    }
}
