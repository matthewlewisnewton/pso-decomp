#include "pso/ui/PlayerWindowDispatch.h"
#include "types.h"
#include "pso/unk/text_8024ACEC.h"

#include <stddef.h>

extern "C" {
extern PlayerWindowCommand player_keyboard_hold_cb;
void begin_player_keyboard_hold(s32 arg0) {
    PlayerWindowCommand callback = player_keyboard_hold_cb;
    dispatch_player_window_command(arg0, callback);
}

}
