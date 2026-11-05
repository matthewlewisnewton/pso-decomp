#include "types.h"
#include "pso/player/TObjPlayer.h"

extern "C" {

int scale_current_matrix(void*);
int get_player_list__10TObjPlayerFv(void*);

void TObjPlayer::update_effect_if_state1() { if (get_player_list__10TObjPlayerFv(this) == 1) { scale_current_matrix((char*)this + 0x1f8); } }

}
