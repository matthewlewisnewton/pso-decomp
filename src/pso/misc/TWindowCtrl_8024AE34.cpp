#include "pso/ui/PlayerWindowDispatch.h"
#include "types.h"
#include "pso/misc/TWindowCtrl.h"

void TWindowCtrl::init_all_slots() {
    s32 var_r31;

    var_r31 = 0;
    do {
        suppress_player_window(var_r31);
        var_r31 += 1;
    } while (var_r31 < 0xC);
}

void TWindowCtrl::init_all_slots2() {
    s32 var_r31;

    var_r31 = 0;
    do {
        unsuppress_player_window(var_r31);
        var_r31 += 1;
    } while (var_r31 < 0xC);
}
