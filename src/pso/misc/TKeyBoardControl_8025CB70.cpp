#include "types.h"
#include "pso/misc/TKeyBoardControl_8025CB70.h"
#include "pso/misc/TWindowChat.h"
#include "pso/misc/TWindowKeyBoardBase.h"
#include "pso/misc/TWindowKeyBoardHard.h"
#include "pso/misc/TWindowKeyBoardSoft.h"
#include "pso/ui/Language.h"


void TWindowChat::reset_input() {
    u8 *arg0 = (u8 *)this;
    ((TWindowKeyBoardSoft *)(arg0 + 0x6C))->reset_state();
    ((TWindowKeyBoardSoft *)(arg0 + 0x84))->reset_state();
    *(s32 *)((s8 *)arg0 + 0x68) = (s32)(arg0 + 0x6C);
    *(s16 *)((s8 *)arg0 + 0x60) = 0;
    *(s32 *)((s8 *)arg0 + 0xA0) = 0;
    *(s32 *)((s8 *)arg0 + 0xA4) = 0;
}

void TWindowKeyBoardBase::set_input_flags_212() { m_b4 = 0x212; }

void TWindowKeyBoardBase::set_input_flags_112() {
    set_input_flags_12();
    m_b4 |= 0x100;
}

void TWindowKeyBoardBase::set_input_flags_92() {
    set_input_flags_12();
    m_b4 |= 0x80;
}

void TWindowKeyBoardBase::set_input_flags_12() { m_b4 = 0x12; }
void TWindowKeyBoardHard__sub_8025CC48(void *arg0) {
    switch (current_language) {
    case LANGUAGE_JAPANESE:
        *(s32 *)((s8 *)arg0 + 0xB4) = 0;
        if (((TWindowKeyBoardHard *)(*(s16 *)((s8 *)arg0 + 0x20)))->test_card_flag_16() != 0) {
            *(s32 *)((s8 *)arg0 + 0xB4) = (s32) (*(s32 *)((s8 *)arg0 + 0xB4) | 1);
        }
        if (((TWindowKeyBoardHard *)(*(s16 *)((s8 *)arg0 + 0x20)))->call_1A529C_with_32() != 0) {
            *(s32 *)((s8 *)arg0 + 0xB4) = (s32) (*(s32 *)((s8 *)arg0 + 0xB4) | 2);
        }
        if (((TWindowKeyBoardHard *)(*(s16 *)((s8 *)arg0 + 0x20)))->test_card_flag_64() != 0) {
            *(s32 *)((s8 *)arg0 + 0xB4) = (s32) (*(s32 *)((s8 *)arg0 + 0xB4) | 4);
        }
        if (((TWindowKeyBoardHard *)(*(s16 *)((s8 *)arg0 + 0x20)))->test_card_flag_0x80() != 0) {
            *(s32 *)((s8 *)arg0 + 0xB4) = (s32) (*(s32 *)((s8 *)arg0 + 0xB4) | 8);
        }
        break;
    case LANGUAGE_ENGLISH:
    case LANGUAGE_GERMAN:
    case LANGUAGE_FRENCH:
    case LANGUAGE_SPANISH:
        *(s32 *)((s8 *)arg0 + 0xB4) = 6;
        break;
    }
}
