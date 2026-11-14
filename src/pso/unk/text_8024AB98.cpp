#include "pso/ui/PlayerWindowDispatch.h"
#include "types.h"
#include "pso/unk/text_8024AB98.h"

#include <stddef.h>

extern "C" {
extern PlayerWindowCommand TWindowSubComCard__window_ctrl_callback_pmf;
extern PlayerWindowCommand lbl_804CEA64;
extern PlayerWindowCommand lbl_804CEA58;
void TWindowSubComCard__sub_8024AB98(s32 arg0) {
    PlayerWindowCommand callback = TWindowSubComCard__window_ctrl_callback_pmf;
    dispatch_player_window_command(arg0, callback);
}
void disable_player_main_menu(s32 arg0) {
    PlayerWindowCommand callback = lbl_804CEA64;
    dispatch_player_window_command(arg0, callback);
}
void enable_player_main_menu(s32 arg0) {
    PlayerWindowCommand callback = lbl_804CEA58;
    dispatch_player_window_command(arg0, callback);
}

}
