#include "types.h"
#include "pso/items/TItemWeapon.h"
#include "pso/player/TObjPlayer.h"

void*TObjPlayer::get_state_ptr() { return (char*)this + 0x30; }
