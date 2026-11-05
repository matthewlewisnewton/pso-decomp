#include "types.h"
#include "pso/player/TObjPlayer.h"

void TechniqueCastState::set_target_count(s16 count) {
    s16 var_r4;

    var_r4 = count;
    if ((var_r4 < 0) || (var_r4 > 0xA)) {
        var_r4 = 0;
    }
    this->target_count = var_r4;
}
