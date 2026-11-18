#include "pso/misc/TWindowCost.h"
#include "pso/misc/TWindowSubComCard_80269064.h"

extern "C" {
int initialize_subwindow__9TWindowDDFv(void *);

void fn_803094E8(TWindowCost *window, s32 value) {
    fn_80269078((u8 *)window, value);
}

void TWindowCost::run_task() {
    initialize_subwindow__9TWindowDDFv(this);
    update_window_entry_list((char *)this + 0x24);
}
}
