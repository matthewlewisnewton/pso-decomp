#include "types.h"
#include "pso/misc/TWindowCtrl_8026AD44.h"
#include "pso/misc/TWindowCtrl.h"

extern void *TWindowCtrl__active_window;

s32 TWindowCtrl::get_field44() {
    if ((void *) TWindowCtrl__active_window == NULL) {
        return 0;
    }
    return *(s32 *)((s8 *)TWindowCtrl__active_window + 0x44);
}

void TWindowCtrl__sub_8026AD60(void) {
    if ((void *) TWindowCtrl__active_window != NULL) {
        *(s32 *)((s8 *)TWindowCtrl__active_window + 0x44) = 0;
    }
}

void TWindowCtrl__sub_8026AD78(TWindowMessageLog *arg0) {
    if ((void *) TWindowCtrl__active_window != NULL) {
        *(TWindowMessageLog **)((s8 *)TWindowCtrl__active_window + 0x44) = arg0;
    }
}
