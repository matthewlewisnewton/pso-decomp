#include "types.h"
#include "pso/misc/TWindowSubComCard_8033BDB0.h"
#include "pso/misc/TWindowMessage.h"
#include "pso/misc/TWindowSubComCardList.h"
#include "pso/misc/TWindowMenu.h"

struct VBase { char pad[0x18]; };

struct VObj : VBase { virtual void m0(int); };

#include <stddef.h>
#include "pso/misc/TWindowSubComCard.h"
#include "pso/misc/TCheckMemoryCardState.h"
#include "pso/misc/TLobby.h"
#include "pso/misc/TQuestVmDownLoadServer.h"
#include "pso/misc/TWindowOptionCtrl.h"
extern "C" {
void TWindow__close(u8 *arg0);
u32 get_message_10__20TWindowSubStatusDispFl(s32);
s32 align_menu_entry_positions(u32);
int forward_trade_action_default__16TObjCityMainWarpFPviii(void *p, int a1, int a2, int a3);
s32 create_window_menu(s32 arg0, s32 arg1, s32 arg2);
u32 check_room_seq_4__16TAdChrSelASlotGCFl(const void *, s32);
u32 create_message_window__6TLobbyFllUls(const void *, const void *, s32, s32);
u32 update_window_mode_from_progress__6TLobbyFPv(const void *, const void *);
s32 get_selected_menu_value(void *);

void TCheckMemoryCard::create_message_and_menu(u32 arg1, s32 sel, u32 arg3, u32 arg4) {
    u32 msg;
    if (m_30 != NULL || m_34 != NULL) {
        return;
    }
    if ((s32)m_4c != 0) {
        m_30 = (void *)create_message_window__6TLobbyFllUls(&lbl_80477DB4, &lbl_80477DBC, 1, 4);
    } else {
        m_30 = (void *)update_window_mode_from_progress__6TLobbyFPv(&lbl_80477DB4, &lbl_80477DBC);
    }
    if (m_30 == NULL) {
        return;
    }
    if (m_30 != NULL && (s32)m_4c != 0) {
        ((TWindowSubComCard *)(m_30))->reparent_to_main_ctrl();
    }
    if (arg1 != 0U) {
        ((TLobby *)(m_30))->send_and_handle(arg1, 3);
    }
    ((TWindowMessage *)(m_30))->complete_reveal();
    if (sel == -1) {
        return;
    }
    if ((s32)m_4c != 0) {
        m_34 = (void *)create_window_menu((s32)&lbl_804EF8D8, 2, 4);
    } else {
        m_34 = (void *)check_room_seq_4__16TAdChrSelASlotGCFl(&lbl_804EF8D8, 2);
    }
    if (m_30 == NULL) {
        return;
    }
    if (m_34 != NULL && (s32)m_4c != 0) {
        ((TWindowSubComCard *)(m_34))->reparent_to_main_ctrl();
    }
    msg = arg3;
    if (arg3 == 0U) {
        msg = get_message_10__20TWindowSubStatusDispFl(0x5B);
    }
    forward_trade_action_default__16TObjCityMainWarpFPviii((void *)(m_34), (int)msg, 5, 0);
    if (sel != -2) {
        msg = arg4;
        if (arg4 == 0U) {
            msg = get_message_10__20TWindowSubStatusDispFl(0x5C);
        }
        forward_trade_action_default__16TObjCityMainWarpFPviii((void *)(m_34), (int)msg, 5, 1);
    }
    ((TWindowSubComCardList *)(m_34))->update_layout_height(lbl_805D6D98);
    align_menu_entry_positions((u32)m_34);
    if (sel != -2) {
        ((TWindowSubComCardList *)(m_34))->set_selected_index(sel);
    } else {
        ((TWindowSubComCardList *)(m_34))->set_selected_index(0);
    }
    ((TWindowOptionCtrl *)(m_34))->clear_flag70_bit4();
}

#pragma push
#pragma fp_contract on
void TCheckMemoryCard::close_windows() {
    u8 *temp_r3;
    u8 *temp_r3_2;
    temp_r3 = (u8 *)m_30;
    if (temp_r3 != NULL) {
        if ((s32) m_4c != 0) {
            if (temp_r3 != NULL) {
                ((VObj *)temp_r3)->m0(1);
            }
        } else {
            TWindow__close(temp_r3);
        }
        m_30 = NULL;
        m_38 = 7;
    }
    temp_r3_2 = (u8 *)m_34;
    if (temp_r3_2 != NULL) {
        TWindow__close(temp_r3_2);
        m_34 = NULL;
        m_38 = 7;
    }
}
#pragma pop

void TCheckMemoryCard::set_state(s32 next_state) {
    // Preserve the original conditional transition. The constructor's first
    // read of m_20 remains an explicit unresolved lifecycle finding.
    if ((s32)m_20 != next_state) {
        m_20 = next_state;
        CheckMemoryCardAction action = lbl_804EF940[m_20].enter;
        if (action != 0) {
            (this->*action)();
        }
    }
}

void TCheckMemoryCard::reset() {
    m_30 = 0;
    m_34 = 0;
    m_38 = 0;
    m_2c = 0;
    m_24 = 0;
    m_28 = sub_8033BB14();
    m_3c = 0;
    m_40 = 0;
    m_44 = 0;
    set_state(0);
}

void TCheckMemoryCard::poll_card_status() {
    m_3c = 0;
    if ((s32) m_38 <= 0) {
        m_2c = 0;
        m_28 = sub_8033BB14();
        if ((s32) m_28 != 0) {
            set_state(1);
            return;
        }
        m_3c = 1;
    }
}

void TCheckMemoryCard::fn_8033C178() { close_windows(); }
void TCheckMemoryCard::fn_8033C198() { }
void TCheckMemoryCard::fn_8033C19C() { update_card_display(0, -1, -1, -1); }
void TCheckMemoryCard::handle_menu_selection() {
    if (m_34 == 0 || ((TWindowMenu *)(m_34))->is_visible() == 0) {
        return;
    }
    switch (get_selected_menu_value(m_34)) {
    case 0:
        m_44 = 1;
        break;
    }
}

}
