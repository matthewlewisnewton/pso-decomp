#include "types.h"
#include <stddef.h>
#include "pso/misc/TWindowCtrl_8024C6CC.h"
#include "pso/misc/TWindowCtrl.h"
#include "pso/misc/TRaderMapCore.h"
#include "pso/misc/TUnk_804CF0B8.h"
#include "pso/misc/TWindowSimpleStatus.h"

typedef char WindowCtrl_flags_offset[offsetof(TWindowCtrl, m_1c) == 0x1C ? 1 : -1];
typedef char WindowCtrl_child_offset[offsetof(TWindowCtrl, m_3c) == 0x3C ? 1 : -1];
typedef char WindowBase_width_offset[offsetof(TWindowBase, m_20) == 0x20 ? 1 : -1];

// Full-width complements retain the native rotate-and-mask instructions.
void TWindowCtrl__sub_8024C6CC(TWindowCtrl *window) {
    window->m_1c |= 0x40;
}
void TWindowCtrl__sub_8024C6DC(TWindowCtrl *window) {
    window->m_1c &= ~0x40;
}
void TWindowCtrl__sub_8024C6EC(TWindowCtrl *window) {
    window->m_1c |= 0x2;
}
void TWindowCtrl__sub_8024C6FC(TWindowCtrl *window) {
    window->m_1c &= ~0x2;
}
void TWindowCtrl__sub_8024C70C(TWindowCtrl *window) {
    window->m_1c |= 0x4;
}
void TWindowCtrl__sub_8024C71C(TWindowCtrl *window) {
    window->m_1c &= ~0x4;
}
void TWindowCtrl__sub_8024C72C(TWindowCtrl *window) {
    window->m_1c |= 0x8;
}
void TWindowCtrl__sub_8024C73C(TWindowCtrl *window) {
    window->m_1c &= ~0x8;
}
void TWindowCtrl__sub_8024C74C(TWindowCtrl *window) {
    window->m_1c |= 0x10;
}
void TWindowCtrl__sub_8024C75C(TWindowCtrl *window) {
    window->m_1c &= ~0x10;
}
void TWindowCtrl::set_radar_dirty_flag() {
    this->m_1c = (u16) (this->m_1c | 1);
    TRaderMapCore::hide_radar();
}
void TWindowCtrl::clear_flag_bit0() {
    this->m_1c = (u16) (this->m_1c & 0xFFFE);
    TRaderMapCore::show_radar();
}

s32 TWindowCtrl__sub_8024C7C4(const TWindowCtrl *window) {
    // Integer arms avoid C++ bool-to-int narrowing in the GC 2.0 compiler.
    return window->m_3c != 0 ? 1 : 0;
}

int TWindowCtrl__sub_8024C7D4(const TWindowCtrl *window) {
    return (window->m_1c >> 1) & 1;
}
int TWindowCtrl__sub_8024C7E0(const TWindowCtrl *window) {
    return (window->m_1c >> 2) & 1;
}
int TWindowCtrl::is_enabled() { return (this->m_1c >> 3) & 0x1; }
int TWindowCtrl__sub_8024C7F8(const TWindowCtrl *window) {
    return (window->m_1c >> 4) & 1;
}
int TWindowCtrl::is_visible() { return this->m_1c & 0x1; }
s16 TUnk_804CF0B8::get_field_20() { return m_20; }
s16 TWindowSimpleStatus::get_width() { return m_20; }
