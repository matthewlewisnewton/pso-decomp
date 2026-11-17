#include "pso/ui/PlayerWindowDispatch.h"
#include "types.h"
#include "pso/misc/TWindowCtrl_8024ADAC.h"
#include "pso/misc/TWindowCtrl.h"

extern void *TWindowCtrl__active_window;

void TWindowCtrl::set_flag_bit2() {
    if ((void *) TWindowCtrl__active_window != NULL) {
        *(u16 *)((s8 *)TWindowCtrl__active_window + 0x1C) = (u16) (*(u16 *)((s8 *)TWindowCtrl__active_window + 0x1C) | 4);
    }
}

void TWindowCtrl::clear_flag_bit2() {
    if ((void *) TWindowCtrl__active_window != NULL) {
        *(u16 *)((s8 *)TWindowCtrl__active_window + 0x1C) = (u16) (*(u16 *)((s8 *)TWindowCtrl__active_window + 0x1C) & 0xFFFFFFFB);
    }
}

#include <stddef.h>

extern "C" {
extern PlayerWindowCommand lbl_804CEA1C;
extern PlayerWindowCommand lbl_804CEA10;
void TWindowCtrl__sub_8024ADAC(s32 arg0) {
    PlayerWindowCommand callback = lbl_804CEA1C;
    dispatch_player_window_command(arg0, callback);
}
void TWindowCtrl__sub_8024ADF0(s32 arg0) {
    PlayerWindowCommand callback = lbl_804CEA10;
    dispatch_player_window_command(arg0, callback);
}

}
