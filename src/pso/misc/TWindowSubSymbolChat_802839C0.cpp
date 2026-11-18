#include "pso/system/SoundEffect.h"
#include "types.h"
#include "pso/misc/TWindowSubSymbolChatFaceType.h"
#include "pso/misc/TWindowSubStatusDisp.h"

extern "C" {



void TWindowSubSymbolChatFaceType::close_when_chat_closed() {
    if (is_open() == 0) {
        play_sound_effect(0x52F16, 0, 0, 0);
        this->m_60 = (u8) (this->m_60 | 2);
    }
}

void TWindowSubSymbolChatFaceType::confirm_selection() {
    play_sound_effect(0x52D01, 0, 0, 0);
    this->m_60 = (u8) (this->m_60 | 1);
    ((TWindowSubStatusDisp *)(this->m_68))->set_entry_state(2);
}

}
