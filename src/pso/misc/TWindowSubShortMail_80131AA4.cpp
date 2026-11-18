#include "types.h"
#include "pso/misc/TKeyBoardControl.h"
#include "pso/misc/TWindowKeyBoardBase.h"
#include "pso/misc/TWindowBase.h"

void TKeyBoardControl::set_position(void *position) {
    ((TWindowKeyBoardBase *)m_20)->m_30 = *(f32 *)position - 4.0f;
    ((TWindowKeyBoardBase *)m_20)->m_34f = *(f32 *)((u8 *)position + 4) - 10.0f;
    ((TWindowKeyBoardBase *)m_20)->m_50 = 3;
}

void TKeyBoardControl::set_soft_keyboard_position(u8 *position) {
    ((TWindowBase *)m_28)->m_30 = *(f32 *)position;
    ((TWindowBase *)m_28)->m_34f = *(f32 *)(position + 4);
    ((TWindowBase *)m_28)->save_position();
}

void TKeyBoardControl::set_hard_keyboard_position(u8 *position) {
    ((TWindowBase *)m_24)->m_30 = *(f32 *)position;
    ((TWindowBase *)m_24)->m_34f = *(f32 *)(position + 4);
    ((TWindowBase *)m_24)->save_position();
}

void TKeyBoardControl::set_composer_position(u8 *position) {
    ((TWindowKeyBoardBase *)m_20)->m_30 = *(f32 *)position - 4.0f;
    ((TWindowKeyBoardBase *)m_20)->m_34f = *(f32 *)(position + 4) - 10.0f;
    ((TWindowKeyBoardBase *)m_20)->save_position();
}

void TKeyBoardControl::set_text(char *text) { ((TWindowKeyBoardBase *)m_20)->set_text(text); }
