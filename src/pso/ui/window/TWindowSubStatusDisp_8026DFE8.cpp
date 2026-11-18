#include "types.h"
#include "pso/ui/window/TWindowBase.h"
#include "pso/ui/window/TWindowMenuIconLine.h"
#include "pso/ui/window/TUnk_804D0948.h"
#include "pso/ui/window/TWindowSubStatusDisp.h"

extern "C" {
s32 draw_visible_window_entries(void *, void *, int);
s32 draw_item_list_capacity(void *, int, int, int);
s32 draw_window_scrollbar(void *, int, void *);
s32 forward_render__20TWindowSubStatusDispFv(void *, int);
extern s32 local_client_id;
u8 * get_window_layout_position(s32);

#pragma push
#pragma fp_contract on
void TUnk_804D0948::render() {
    u8 *arg0 = (u8 *)this;
    s32 temp_r3;
    s32 n;
    void *p;
    temp_r3 = (s32)setup_content_draw_context();
    ((TWindowBase *)arg0)->draw_window_frame((void *)temp_r3);
    draw_visible_window_entries(arg0, arg0 + 0x24, temp_r3);
    if (!(this->state_flags & 0x80)) {
        ((TWindowMenuIconLine *)arg0)->draw_selected_list_entry(temp_r3);
    }
    n = capacity;
    if (n > 0) {
        draw_item_list_capacity(arg0, temp_r3, this->entry_count, n);
    }
    p = this->status_display;
    if (p != NULL) {
        forward_render__20TWindowSubStatusDispFv(p, temp_r3);
    }
    p = this->unk_84;
    if (p != NULL) {
        draw_window_scrollbar(p, temp_r3, (u8 *)&this->scroll_offset[0]);
    }
}
#pragma pop

void TUnk_804D0948::run_task() {
    TWindowMenuIconLine::run_task();
}

TUnk_804D0948::~TUnk_804D0948() {}

TUnk_804D0948::TUnk_804D0948(void *position, s32 heading, u32 count, u8 *descriptor)
    : TWindowMenuIconLine((u8 *)position, count, (s16)local_client_id, descriptor) {
    sub_8026DE94(heading);
}

TUnk_804D0948::TUnk_804D0948(s32 heading, u32 count, s32 client)
    : TWindowMenuIconLine(get_window_layout_position(0x26), count, (s16)client) {
    sub_8026DE94(heading);
}
}
