#include "types.h"
#include "pso/player/TObjPlayer.h"

void TObjPlayer::set_tech_level(s16 arg1) {
    s16 var_r4;

    var_r4 = arg1;
    if ((var_r4 < 0) || (var_r4 > 0xA)) {
        var_r4 = 0;
    }
    this->m_id = var_r4;
}
