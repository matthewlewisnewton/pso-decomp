#include "pso/THunterGuildWarning.h"
#include "pso/misc/TCameraCtrl.h"
#include "pso/misc/TWindowMessage.h"
#include "pso/misc/TWindowSubComCard_80244774.h"

struct WarningWindowPair {
    f32 x;
    f32 y;
};

extern "C" {
extern const WarningWindowPair lbl_8044BC7C;
struct WarningPositionData { WarningWindowPair value; u8 padding[4]; };
extern const WarningPositionData lbl_8044BC84;
extern const f32 lbl_805DC640;
void *get_player_by_client_id(s32);
const WarningWindowPair *get_window_layout_position(s32);
TWindowMessage *create_message_window__6TLobbyFllUls(const WarningWindowPair *, const WarningWindowPair *, u32, s32);
s32 TQuestVmDownLoadServer__sub_8006EF6C(s32);
s32 send_and_handle__6TLobbyFii(TWindowMessage *, s32, s32);
s32 get_game_play_mode();
}

void THunterGuildWarning::close_windows() {
    s32 i = 0;
    do {
        if (m_windows[i] != NULL) {
            TWindow__close((u8 *)m_windows[i]);
            m_windows[i] = NULL;
        }
        i++;
    } while (i < 4);
}

extern "C" void THunterGuildWarning__sub_80211774(THunterGuildWarning *self, s32) {
    WarningWindowPair size = lbl_8044BC7C;
    WarningWindowPair position = lbl_8044BC84.value;
    if (TCameraCtrl::get_instance() > 2) {
        position.x = lbl_805DC640;
        position.y = lbl_805DC640;
    }
    switch (self->m_warning_type) {
    case 0: {
        u16 id = TCameraCtrl::get_nth_view_player_id(0);
        if (get_player_by_client_id(id)) {
            self->m_windows[id] = create_message_window__6TLobbyFllUls(get_window_layout_position(0x31), &size, 1, id);
        }
        if (self->m_windows[id]) {
            s32 text = 0x63;
            send_and_handle__6TLobbyFii(self->m_windows[id], TQuestVmDownLoadServer__sub_8006EF6C(text), 0x81);
            self->m_windows[id]->set_position_xy(position.x, position.y);
        }
        break;
    }
    case 1: {
        u16 id = TCameraCtrl::get_nth_view_player_id(0);
        if (get_player_by_client_id(id)) {
            self->m_windows[id] = create_message_window__6TLobbyFllUls(get_window_layout_position(0x31), &size, 1, id);
        }
        if (self->m_windows[id]) {
            s32 text = 0x68;
            send_and_handle__6TLobbyFii(self->m_windows[id], TQuestVmDownLoadServer__sub_8006EF6C(text), 0x81);
            self->m_windows[id]->set_position_xy(position.x, position.y);
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
                    self->m_windows[i] = create_message_window__6TLobbyFllUls(get_window_layout_position(0x31), &size, 1, i);
                }
                if (self->m_windows[i]) {
                    send_and_handle__6TLobbyFii(self->m_windows[i], TQuestVmDownLoadServer__sub_8006EF6C(message), 0x81);
                    self->m_windows[i]->set_position_xy(position.x, position.y);
                }
            }
        }
        break;
    }
    }
}

extern "C" void THunterGuildWarning__sub_802119CC(THunterGuildWarning *self) {
    for (s32 i = 0; i < 4; i++) self->m_windows[i] = NULL;
}
