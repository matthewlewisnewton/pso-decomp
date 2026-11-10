#include "pso/misc/TWindowChat.h"
#include "pso/misc/TWindowKeyBoardBase.h"
#include "types.h"
#include "pso/misc/TWindowSubShortCut.h"

extern "C" {

s32 open_next_input_window__11TWindowChatFv(void *);
s32 close_all_children__11TWindowChatFv();

void TWindowSubShortCut::close_and_clear_flag() {
    close_all_children__11TWindowChatFv();
    this->m_1e = (u16) (this->m_1e & 0xFFFFFFFD);
    open_next_input_window__11TWindowChatFv(this);
}

void TWindowChat::set_keyboard_flag62_bit4() { TWindowKeyBoardBase *keyboard = (TWindowKeyBoardBase *)composer; if (keyboard) keyboard->set_flag62_bit4(); }

}
