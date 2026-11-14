#include "pso/ui/PlayerWindowDispatch.h"
#include "types.h"
#include "pso/unk/text_8024AD30.h"

#include <stddef.h>

extern "C" {
extern PlayerWindowCommand window_ctrl_end_keyboard_hold_callback_entry;
void end_player_keyboard_hold(s32 arg0) {
    PlayerWindowCommand callback = window_ctrl_end_keyboard_hold_callback_entry;
    dispatch_player_window_command(arg0, callback);
}

}
