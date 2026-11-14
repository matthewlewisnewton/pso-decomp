#include "pso/ui/PlayerWindowDispatch.h"
#include "types.h"
#include "pso/unk/text_8024AC64.h"

#include <stddef.h>

extern "C" {
extern PlayerWindowCommand lbl_804CEA4C;
void fn_8024AC64(s32 arg0) {
    PlayerWindowCommand callback = lbl_804CEA4C;
    dispatch_player_window_command(arg0, callback);
}

}
