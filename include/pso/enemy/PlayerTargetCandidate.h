#ifndef PSO_ENEMY_PLAYERTARGETCANDIDATE_H
#define PSO_ENEMY_PLAYERTARGETCANDIDATE_H

#include "types.h"

struct PlayerTargetCandidate {
    u16 id;
    f32 distance_squared;
};

typedef char PlayerTargetCandidate_size[sizeof(PlayerTargetCandidate) == 8 ? 1 : -1];

#endif
