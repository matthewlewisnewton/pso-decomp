#include "types.h"
#include "pso/player/TObjPlayer.h"

s32 TObjPlayer::get_tp() { return this->m_1c0; }
void TObjPlayer::set_effect_state(s32 v) { *(s32 *)&this->unk_1C4 = v; }
