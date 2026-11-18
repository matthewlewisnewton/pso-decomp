#include "types.h"
#include "pso/misc/TWindowKeyBoardBase.h"
#include "pso/misc/TWindowChat.h"
#include "pso/misc/TWindowKeyBoardSoft.h"

int TWindowKeyBoardBase::sub_8025CB10() {
    if ((u32) this->m_7c != 0U) {
        return 1;
    }
    return this->m_94 != 0 ? 1 : 0;
}

void TWindowChat::flush_if_flagged() { if (get_flag() != 0) { reset_input(); } }
