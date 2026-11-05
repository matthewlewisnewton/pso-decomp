#include "types.h"
#include "pso/unk/text_803D853C.h"
#include "pso/unk/text_803D96A8.h"
#include "pso/boss/TObjBoss2Tunnel.h"
#include "pso/player/TObjPlayer.h"

extern "C" {

int push_matrix(void*);

void TObjBoss2Tunnel::render(void* a1) { push_matrix(this); TObjPlayer::invert_matrix_in_place((u32)((void*)0)); get_current_matrix(a1); pop_matrix(); }

}
