#include "types.h"
#include "pso/misc/TWindowSubSymbolChat_802838C4.h"
#include "pso/misc/TWindowSubSymbolChatPartsSet.h"
#include "pso/misc/TWindowSubSymbolChat.h"
#include "pso/misc/TWindowSubSymbolChatHelp.h"


extern "C" {
void TWindowSubSymbolChat::set_flag_bit2(s32 *arg0) {
    *arg0 |= 2;
}

void TWindowSubSymbolChat::clear_flag_bit2(s32 *arg0) {
    *arg0 &= 0xFFFFFFFD;
}

s16 TWindowSubSymbolChat::get_cursor_pos() {
    return *(s16 *)((s8 *)this + 0x6C);
}

s16 TWindowSubSymbolChat::get_cursor_x() {
    return *(s16 *)((s8 *)this + 0x6A);
}

s32 TWindowSubSymbolChatPartsSet::is_active() {
    return this->m_68 & 1;
}

s32 TWindowSubSymbolChat__sub_80283900(void *arg0) {
    return *(u8 *)((s8 *)arg0 + 0x68) & 2;
}

void TWindowSubSymbolChatHelp::clear_flag60_bit2() {
    m_60 = (u8)(m_60 & ~2);
}

void TWindowSubSymbolChatHelp::clear_flag60_bit4() {
    m_60 = (u8)(m_60 & ~4);
}

void TWindowSubSymbolChatHelp::sub_8028392C(s32 *first, s32 *second) {
    m_6c = first;
    m_70 = second;
    m_60 = (u8)(m_60 | 4);
}
void fn_80283944(TWindowSubSymbolChatHelp *window) {
    window->m_60 &= ~1;
}

}
