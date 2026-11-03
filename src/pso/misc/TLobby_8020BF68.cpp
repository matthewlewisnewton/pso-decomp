#include "types.h"
#include "pso/misc/TLobby.h"

extern "C" {

void TLobby__sub_8020B47C(void*);

void TLobby::sync_game_state() { TLobby__sub_8020B47C(this); }

}
