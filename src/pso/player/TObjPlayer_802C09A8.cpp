#include "types.h"
#include "pso/player/TObjPlayer.h"
#include "pso/system/BmlResourceClass.h"
#include "pso/system/BmlResourceDescriptor.h"

extern "C" {


extern u32 lobby_pigeon_bml_archive;

void TObjPlayer::free_static_instance() {
    if ((u32) lobby_pigeon_bml_archive != 0U) {
        delete (BmlResource *)(lobby_pigeon_bml_archive);
        lobby_pigeon_bml_archive = 0U;
    }
}

}
