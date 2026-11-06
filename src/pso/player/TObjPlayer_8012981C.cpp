#include "types.h"
#include "pso/player/TObjPlayer_8012981C.h"
#include "pso/player/TObjPlayer.h"

extern "C" {

s32 rotate_matrix_z(s32, s32);
}

void s_rank_shot_turn_barrels(void *arg0) {
    if (TObjPlayer::get_player_list() == 1) {
        rotate_matrix_z(0, *(s32 *)((s8 *)arg0 + 0x200));
    }
    if (TObjPlayer::get_player_list() == 4) {
        rotate_matrix_z(0, -*(s32 *)((s8 *)arg0 + 0x200));
    }
}
