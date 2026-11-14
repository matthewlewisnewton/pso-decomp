#include "types.h"
#include "pso/misc/TWindowSnapShot.h"
#include "pso/misc/TWindowSoundBalance.h"
#include "pso/misc/TWindowOptionCtrl.h"

extern "C" {

s32 __nw__7TObjectFUl(s32);
s32 get_option_entry__17TWindowOptionCtrlFi(s32);

s32 TWindowOptionCtrl::create_snap_shot_window() {
    return (s32)new TWindowSnapShot((void *)get_option_entry__17TWindowOptionCtrlFi(0xCF));
}

s32 TWindowOptionCtrl::create_sound_balance_window() {
    return (s32)new TWindowSoundBalance((void *)get_option_entry__17TWindowOptionCtrlFi(0xCF));
}

}
