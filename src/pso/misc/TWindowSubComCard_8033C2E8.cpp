#include "types.h"
#include "pso/misc/TWindowSubComCard.h"
#include "pso/TAdPlayerLoadGC.h"
#include "pso/misc/TCheckMemoryCard.h"
#include "pso/misc/TQuestVmDownLoadServer.h"

void TCheckMemoryCard::update_display_state() {
    s32 temp_r4;

    temp_r4 = this->m_28;
    if (!(temp_r4 & 2)) {
        if (temp_r4 & 1) {
            if ((u32) this->m_30 == 0U) {
                update_card_display(0, -1, -1, -1);
            }
        } else {
            if (temp_r4 & 4) {
                if ((s32) this->m_40 != 0) {
                    set_state(3);
                    return;
                }
                set_state(1);
                return;
            }
            if (temp_r4 & 8) {
                if ((s32) this->m_40 != 0) {
                    set_state(3);
                    return;
                }
                set_state(1);
                return;
            }
            if (temp_r4 & 0x10) {
                if ((s32) this->m_40 != 0) {
                    set_state(3);
                    return;
                }
                set_state(1);
                return;
            }
            if (temp_r4 == 0) {
                set_state(2);
            }
        }
    }
}

void TCheckMemoryCard::close_and_update_display() {
    close_windows();
    if (this->m_28 & 1) {
        update_card_display(0, -1, -1, -1);
    }
}
