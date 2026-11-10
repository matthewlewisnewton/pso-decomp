#include "pso/map/ChallengeEnemySet.h"
#include "pso/system/byteswap.h"
#include "pso/misc/TLobby.h"

void TLobby::append_swapped_u32(s32 *arg0) {
    s32 sp8;

    if (challenge_action_buffer != NULL) {
        sp8 = *arg0;
        bswap_32((u32 *)&sp8);
        move_data(challenge_action_buffer + challenge_action_size, &sp8, 4);
        challenge_action_size += 4;
    }
}

void ChallengeEventCommand::append() const {
    if (challenge_action_buffer != NULL) {
        move_data(challenge_action_buffer + challenge_action_size, &opcode, 1);
        challenge_action_size += 1;
    }
}
