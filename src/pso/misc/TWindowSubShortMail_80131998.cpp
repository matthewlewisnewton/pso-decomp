#include "types.h"
#include "pso/misc/TKeyBoardControl.h"
#include "pso/misc/TWindowBase.h"
#include "pso/misc/TWindowKeyBoardHard.h"
#include "pso/misc/TWindowSubComCard_80244774.h"

void TKeyBoardControl::set_flag1c_bit4() {
    u16 flags = m_1c;
    if (!(flags & 4)) {
        m_1c = (u16)(flags | 4);
        if (m_24 != 0U) {
            ((TWindowKeyBoardHard *)m_24)->set_flag60_bit200();
        }
        if (m_28 != 0U) {
            ((TWindowBase *)m_28)->request_close();
        }
    }
}

void TKeyBoardControl::clear_flag1c_bit4() {
    u16 flags = m_1c;
    if (flags & 4) {
        m_1c = (u16)(flags & 0xFFFFFFFB);
        if (m_24 != 0U) {
            ((TWindowKeyBoardHard *)m_24)->clear_flag60_bit200();
        }
        if (!(m_1c & 1) && m_28 != 0U) {
            window_request_show((void *)m_28);
        }
    }
}
