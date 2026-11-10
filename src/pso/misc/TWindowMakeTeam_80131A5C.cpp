#include "types.h"
#include "pso/misc/TKeyBoardControl.h"
#include "pso/misc/TWindowKeyBoardBase.h"

void TKeyBoardControl::set_keyboard_flag62_bit2() {
    ((TWindowKeyBoardBase *)m_20)->set_flag62_bit2();
}

void TKeyBoardControl::set_keyboard_depth(f32 depth) {
    ((TWindowKeyBoardBase *)m_20)->set_depth(depth);
}
