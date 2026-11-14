#include "pso/ui/PlayerWindowDispatch.h"
#include "types.h"
#include "pso/misc/TWindowCtrl_8024AEAC.h"

#include <stddef.h>
#include "pso/misc/TWindowCtrl.h"

extern "C" {
extern PlayerWindowQuery lbl_804CE9D4;
extern PlayerWindowQuery window_ctrl_apply_default_vec_callback_entry;
extern PlayerWindowQuery TWindowCtrl__player_menu_query_cb;
extern PlayerWindowCommand TWindowCtrl__unsuppress_slot_cb;
extern PlayerWindowCommand TWindowCtrl__suppress_slot_cb;

void suppress_player_window(s32 arg0) {
    PlayerWindowCommand callback = TWindowCtrl__suppress_slot_cb;
    dispatch_player_window_command(arg0, callback);
}

void unsuppress_player_window(s32 arg0) {
    PlayerWindowCommand callback = TWindowCtrl__unsuppress_slot_cb;
    dispatch_player_window_command(arg0, callback);
}

void dispatch_player_window_command(s32 client_id, PlayerWindowCommand pmf) {
    TWindowCtrl *w = (TWindowCtrl *)TWindowCtrl::get_window(client_id);
    if (w != NULL) {
        (w->*pmf)();
    }
}

s32 has_player_active_menu(s32 arg0) {
    PlayerWindowQuery callback = TWindowCtrl__player_menu_query_cb;
    return dispatch_player_window_query(arg0, callback);
}

void TWindowCtrl::apply_default_vec(s32 arg0, s32 arg1) {
    PlayerWindowQuery callback = window_ctrl_apply_default_vec_callback_entry;
    dispatch_player_window_query(arg1, callback);
}

void TWindowCtrl__sub_8024B000(s32 arg0, s32 arg1) {
    PlayerWindowQuery callback = lbl_804CE9D4;
    dispatch_player_window_query(arg1, callback);
}

}
