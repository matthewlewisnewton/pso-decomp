#ifndef PSO_PLAYER_TOBJPLAYER_802D5B78_H
#define PSO_PLAYER_TOBJPLAYER_802D5B78_H

#include "types.h"

struct Vec_802D5B78 {
    f32 x;
    f32 y;
    f32 z;
};

extern "C" {
// Copies the incoming vector, normalizes the copy in place, and subtracts the
// scaled copy from the battle-parameter hit offsets into the output vector.
void TObjPlayer__sub_802D5B78(void *arg0, void *arg1, const Vec_802D5B78 *arg2);
}

#endif
