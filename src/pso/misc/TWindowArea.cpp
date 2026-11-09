#include "pso/misc/TWindowArea.h"
#include "pso/misc/TWindowDD.h"

extern "C" {
u8 *get_window_layout_position(s32);
void copy_vec2__28TWindowSubSymbolChatPartsSetFPv(f32 *destination, const void *source);
extern const char *lbl_805D3880;
extern const f32 lbl_805DCAC4;
}

void TWindowArea::run_task() {
    ((TWindowDD *)this)->initialize_subwindow();
    update_window_entry_list(&m_24);
}

TWindowArea::~TWindowArea() {}

TWindowArea::TWindowArea() : TWindowRoom(NULL) {
    m_name = lbl_805D3880;
    // Existing two-float ABI; its historical class attribution remains provisional.
    const void *position = get_window_layout_position(0x25);
    copy_vec2__28TWindowSubSymbolChatPartsSetFPv(&m_40, position);
    tabParameter = lbl_805DCAC4;
}
