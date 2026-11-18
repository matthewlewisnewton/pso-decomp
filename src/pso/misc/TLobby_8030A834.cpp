#include "types.h"
#include "pso/misc/TLobby_8030A834.h"
#include "pso/misc/TLobby.h"
#include "pso/TBoss4ZakoDraw.h"
#include "pso/TParticleCtrl.h"
#include "pso/player/TObjPlayer.h"

extern "C" {
    extern int lobby_online_ready_flag;
int TLobby::get_online_ready_flag() {  return lobby_online_ready_flag; }

void *fn_8030A83C(void *parent) {
    return new TBoss4ZakoDraw((TObject *)parent);
}

}
