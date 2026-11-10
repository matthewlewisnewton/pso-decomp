#include "types.h"
#include "pso/misc/TKeyBoardControl.h"
#include "pso/misc/TWindowKeyBoardBase.h"
#include "pso/misc/TWindowMakeTeam.h"
#include "pso/misc/TWindowSubTradeMain.h"

extern "C" {

int set_depth__11TWindowBaseFf(void*);

void TKeyBoardControl::set_keyboard_flag62_bit2() { ((TWindowKeyBoardBase *)m_20)->set_flag62_bit2(); }

int TWindowMakeTeam::get_lobby_field_20() { return set_depth__11TWindowBaseFf(*(void* *)&this->m_20); }

}
