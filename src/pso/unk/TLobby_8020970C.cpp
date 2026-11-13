#include "types.h"
#include "pso/system/byteswap.h"
#include "pso/unk/TLobby.h"
#include "pso/unk/ChallengeEvent.h"

extern u32 challenge_action_buffer;
extern s32 challenge_action_size;

void TLobby::append_swapped_u32(s32 *arg0) {
    s32 sp8;

    if ((u32) challenge_action_buffer != 0U) {
        sp8 = *arg0;
        bswap_32((u32 *)&sp8);
        ((TLobby *)(challenge_action_buffer + challenge_action_size))->move_data(&sp8, 4);
        challenge_action_size += 4;
    }
}

void ChallengeEventCommand::append() const {
    s32 arg0 = (s32)this;
    if ((u32) challenge_action_buffer != 0U) {
        ((TLobby *)(challenge_action_buffer + challenge_action_size))->move_data((s32 *)arg0, 1);
        challenge_action_size += 1;
    }
}
