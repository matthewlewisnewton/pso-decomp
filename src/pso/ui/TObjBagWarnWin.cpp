#ifdef __MWERKS__
#pragma dont_inline off
#pragma inline_depth(2)
#endif
#include "pso/ui/WarningWindowUpdate.h"
#include "pso/TObjBagWarnWin.h"
#include "pso/misc/TWindowBase.h"
#include "pso/ui/TObjBagWarnWin_8006EF24.h"
#include "pso/unk/text_8006EF80.h"
#include "pso/misc/TCameraCtrl.h"
#include "pso/misc/TWindowAddition.h"
#include "pso/map/FloorArea.h"

#include "types.h"
#include "pso/misc/TLobby.h"
#include "pso/map/FloorArea.h"

struct Sub_8006EC20 {
    u8 pad[0x1C];
    s16 v1C;
};

struct Ctrl_8006EC20 {
    u8 pad0[0x38];
    f32 f38;
    u8 pad3C[4];
    f32 f40;
    u8 pad44[0xD00 - 0x44];
    Sub_8006EC20 *pD00;
};

extern "C" {
s32 TWindowCtrlMain__sub_8024CE58();
void *get_player_by_client_id(s32 i);
s32 TLobby__sub_80211C3C();
extern s32 local_client_id;
extern const f32 lbl_805D90B8;
extern const f32 lbl_805D90BC;
extern const f32 lbl_805D90C0;
extern const f32 lbl_805D90C4;
s32 append_line__14TWindowMessageFii(u32, void *, s32);
u32 create__14TWindowMessageFPvll(s32, void *, s32);
s32 get_window_layout_position(s32);
s32 strncpy(void *, s32, s32);
extern u8 TObjBagWarnWin__message_window_size[];
extern const f32 lbl_805D90C8;
extern const f32 lbl_805D90CC;

s32 TObjBagWarnWin::should_show_warning(void *arg0) {
    Ctrl_8006EC20 *ctrl;
    if (TLobby__sub_80211C3C() != 3) {
        return 0;
    }
    if (fn_8006EF80() != 0) {
        return 0;
    }
    ctrl = (Ctrl_8006EC20 *)get_player_by_client_id(local_client_id);
    if (ctrl == NULL) {
        return 0;
    }
    switch (get_current_floor_area()) {
    case AREA_PIONEER2_EP1:
        if (ctrl->f38 <= lbl_805D90B8 || ctrl->f38 >= lbl_805D90BC) {
            return 0;
        }
        break;
    case AREA_PIONEER2_EP2:
        if (ctrl->f38 <= lbl_805D90C0 || ctrl->f40 <= lbl_805D90C4) {
            return 0;
        }
        break;
    }
    ctrl = (Ctrl_8006EC20 *)get_player_by_client_id(local_client_id);
    if (ctrl == NULL || ctrl->pD00->v1C < 30) {
        return 0;
    }
    return 1;
}

struct TObjBagWarnWinPolicy {
    static s32 should_show(TObjBagWarnWin *self) { return TObjBagWarnWin::should_show_warning(self); }
    static void open(TObjBagWarnWin *self) { self->open_message_window(); }
};

void TObjBagWarnWin::run_task() {
    update_warning_window<TObjBagWarnWin, TObjBagWarnWinPolicy>(this);
}

void TObjBagWarnWin::open_message_window() {
    warning.window = (TWindowBase *)create__14TWindowMessageFPvll(get_window_layout_position(0x38), TObjBagWarnWin__message_window_size, 1);
    if (warning.window != NULL) {
        ((TWindowBase *)(warning.window))->set_depth(lbl_805D90C8);
        if (TCameraCtrl::get_camera_id() == 4) {
            ((TWindowAddition *)(warning.window))->set_position_xy(lbl_805D90CC, lbl_805D90CC);
        }
        strncpy(warning.text, TQuestVmDownLoadServer__sub_8006EF6C(0x59), 0x7F);
        warning.text[0x7F] = 0;
        append_line__14TWindowMessageFii((u32)warning.window, warning.text, 0);
    }
}
TObjBagWarnWin::~TObjBagWarnWin() {}

}
