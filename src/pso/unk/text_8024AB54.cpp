#include "pso/ui/PlayerWindowDispatch.h"
#include "types.h"
#include "pso/unk/text_8024AB54.h"

#include <stddef.h>

extern "C" {
extern PlayerWindowCommand window_ctrl_init_params;
void fn_8024AB54(s32 arg0) {
    PlayerWindowCommand callback = window_ctrl_init_params;
    dispatch_player_window_command(arg0, callback);
}

}
