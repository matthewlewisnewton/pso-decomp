#include "pso/misc/TWindowChat.h"
#include "pso/misc/TWindowKeyBoardBase.h"
#include "types.h"

void TWindowChat::close_and_clear_flag() {
    close_all_children();
    flags = (u16)(flags & 0xFFFFFFFD);
    open_next_input_window();
}

void TWindowChat::set_keyboard_flag62_bit4() { TWindowKeyBoardBase *keyboard = (TWindowKeyBoardBase *)composer; if (keyboard) keyboard->set_flag62_bit4(); }
