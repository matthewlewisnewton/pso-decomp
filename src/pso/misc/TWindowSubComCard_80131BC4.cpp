#include "pso/system/ArrayAllocation.h"
#include "types.h"
#include "pso/misc/TKeyBoardControl.h"
#include "pso/misc/TWindowSubComCard.h"
#include "pso/misc/TWindowKeyBoardSoft.h"
#include "pso/misc/TWindowMakeTeam.h"

extern "C" {

s32 export_keyboard_text(s32, s32);


s32 TWindowSubComCard::realloc_buffer() {
    s32 out;

    out = (s32)::operator new[](((TWindowKeyBoardSoft *)(this->m_20))->measure_text_overflow());
    export_keyboard_text(this->m_20, out);
    return out;
}

int TWindowSubComCard::is_keyboard_active() { return ((TKeyBoardControl *)(this->m_20))->is_active(); }
int TWindowSubComCard::update_keyboard() { return ((TKeyBoardControl *)(this->m_20))->is_key_active(); }

}
