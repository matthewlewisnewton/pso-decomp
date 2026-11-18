#include "pso/ui/PlayerWindowDispatch.h"
#include "types.h"

#include <stddef.h>
#include "pso/misc/TWindowCtrl.h"

extern "C" {
extern PlayerWindowQuery window_ctrl_is_visible_callback_entry;
s32 is_player_window_visible(s32 arg0) {
    PlayerWindowQuery callback = window_ctrl_is_visible_callback_entry;
    return dispatch_player_window_query(arg0, callback);
}

s32 dispatch_player_window_query(s32 client_id, PlayerWindowQuery pmf) {
    TWindowCtrl *w = (TWindowCtrl *)TWindowCtrl::get_window(client_id);
    if (w == NULL) {
        return 0;
    }
    return (w->*pmf)();
}

}
