#include "types.h"
#include "pso/system/BmlResourceClass.h"
#include "pso/player/TObjPlayer.h"

extern "C" {

extern u32 lobby_pigeon_bml_archive;

void TObjPlayer::free_static_instance() {
    if ((u32) lobby_pigeon_bml_archive != 0U) {
        delete (BmlResource *)((void*)lobby_pigeon_bml_archive);
        lobby_pigeon_bml_archive = 0U;
    }
}

}
