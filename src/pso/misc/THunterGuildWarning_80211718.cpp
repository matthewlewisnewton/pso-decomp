#include "pso/THunterGuildWarning.h"
#include "pso/misc/TCameraCtrl.h"
#include "pso/misc/TLobby.h"
#include "pso/misc/TLobby_8030A6A8.h"
#include "pso/misc/TWindowMessage.h"
#include "pso/player/TObjPlayer_801AF2F0.h"
#include "pso/ui/TObjBagWarnWin_8006EF24.h"

// lbl_8044BC7C is two floats. lbl_8044BC84 is that pair plus 4 unused bytes.
// Neither symbol names this type.
struct Pair_8044BC7C {
    f32 x;
    f32 y;
};

extern "C" {
extern const Pair_8044BC7C lbl_8044BC7C;
struct Data_8044BC84 { Pair_8044BC7C value; u8 padding[4]; };
extern const Data_8044BC84 lbl_8044BC84;
extern const f32 lbl_805DC640;
const Pair_8044BC7C *get_window_layout_position(s32);
void TWindow__close(TWindowMessage *window);
}

void THunterGuildWarning::close_windows() {
    s32 i = 0;
    do {
        if (m_windows[i] != NULL) {
            TWindow__close(m_windows[i]);
            m_windows[i] = NULL;
        }
        i++;
    } while (i < 4);
}

void THunterGuildWarning::sub_80211774(s32) {
    Pair_8044BC7C size = lbl_8044BC7C;
    Pair_8044BC7C position = lbl_8044BC84.value;
    if (TCameraCtrl::get_instance() > 2) {
        position.x = lbl_805DC640;
        position.y = lbl_805DC640;
    }
    switch (m_warning_type) {
    case 0: {
        u16 id = TCameraCtrl::get_nth_view_player_id(0);
        if (get_player_by_client_id(id)) {
            m_windows[id] = TLobby::create_message_window(get_window_layout_position(0x31), &size, 1, id);
        }
        if (m_windows[id]) {
            s32 text = 0x63;
            m_windows[id]->send_and_handle(TQuestVmDownLoadServer__sub_8006EF6C(text), 0x81);
            m_windows[id]->set_position_xy(position.x, position.y);
        }
        break;
    }
    case 1: {
        u16 id = TCameraCtrl::get_nth_view_player_id(0);
        if (get_player_by_client_id(id)) {
            m_windows[id] = TLobby::create_message_window(get_window_layout_position(0x31), &size, 1, id);
        }
        if (m_windows[id]) {
            s32 text = 0x68;
            m_windows[id]->send_and_handle(TQuestVmDownLoadServer__sub_8006EF6C(text), 0x81);
            m_windows[id]->set_position_xy(position.x, position.y);
        }
        break;
    }
    case 2: {
        s32 text = 0x64;
        if (get_game_play_mode() == 2) text = 0x6a;
        u16 local = TCameraCtrl::get_nth_view_player_id(0);
        const s32 message = text;
        for (s32 i = 0; i < 4; i++) {
            if (local != i) {
                if (get_player_by_client_id(i)) {
                    m_windows[i] = TLobby::create_message_window(get_window_layout_position(0x31), &size, 1, i);
                }
                if (m_windows[i]) {
                    m_windows[i]->send_and_handle(TQuestVmDownLoadServer__sub_8006EF6C(message), 0x81);
                    m_windows[i]->set_position_xy(position.x, position.y);
                }
            }
        }
        break;
    }
    }
}

void THunterGuildWarning::sub_802119CC() {
    for (s32 i = 0; i < 4; i++) m_windows[i] = NULL;
}
