#include "types.h"
#include "pso/player/TechniqueCastState.h"

void TechniqueCastState::set_target_count(s16 arg1) {
    s16 var_r4;

    var_r4 = arg1;
    if ((var_r4 < 0) || (var_r4 > 0xA)) {
        var_r4 = 0;
    }
    *(s16 *)((char *)this + 6) = var_r4;
}
