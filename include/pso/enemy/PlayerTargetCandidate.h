#ifndef PSO_ENEMY_PLAYERTARGETCANDIDATE_H
#define PSO_ENEMY_PLAYERTARGETCANDIDATE_H

#include "types.h"

struct TObjEneDD;

struct PlayerTargetCandidate {
    u16 id;
    f32 distance_squared;
};

typedef char PlayerTargetCandidate_size[sizeof(PlayerTargetCandidate) == 8 ? 1 : -1];

extern "C" {
s32 collect_enemy_target_candidates(const TObjEneDD *enemy, PlayerTargetCandidate *out, f32 squared_range);
extern PlayerTargetCandidate enemy_target_candidate_table[4];
}

#endif
