#include "pso/ui/keyboard/TKeyBoardControl.h"
#include "pso/ui/window/TWindowKeyBoardBase.h"
#include "pso/ui/window/TWindowKeyBoardHard.h"
#include "pso/ui/window/TWindowKeyBoardSoft.h"
#include "pso/ui/window/TWindowMakeTeam.h"

void TKeyBoardControl::set_position(void *position) {
    ((TWindowKeyBoardBase *)m_20)->target_position[0] = ((f32 *)position)[0] - 4.0f;
    ((TWindowKeyBoardBase *)m_20)->target_position[1] = ((f32 *)position)[1] - 10.0f;
    ((TWindowKeyBoardBase *)m_20)->tween_ticks = 3;
}

void TKeyBoardControl::set_soft_keyboard_position(u8 *position) {
    ((TWindowKeyBoardSoft *)m_28)->target_position[0] = ((f32 *)position)[0];
    ((TWindowKeyBoardSoft *)m_28)->target_position[1] = ((f32 *)position)[1];
    ((TWindowKeyBoardSoft *)m_28)->save_position();
}

void TKeyBoardControl::set_hard_keyboard_position(u8 *position) {
    ((TWindowKeyBoardHard *)m_24)->target_position[0] = ((f32 *)position)[0];
    ((TWindowKeyBoardHard *)m_24)->target_position[1] = ((f32 *)position)[1];
    ((TWindowKeyBoardHard *)m_24)->save_position();
}

void TKeyBoardControl::set_composer_position(u8 *position) {
    ((TWindowKeyBoardBase *)m_20)->target_position[0] = ((f32 *)position)[0] - 4.0f;
    ((TWindowKeyBoardBase *)m_20)->target_position[1] = ((f32 *)position)[1] - 10.0f;
    ((TWindowKeyBoardBase *)m_20)->save_position();
}

extern "C" {
int TWindowMakeTeam::get_keyboard_field_6c() { return ((TWindowKeyBoardSoft *)(this->m_20))->get_field_6c(); }

}
