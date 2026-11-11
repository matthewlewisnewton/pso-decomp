#include "types.h"
#include "pso/player/TObjPlayer.h"

extern "C" {

void __dt__11BmlResourceFv(void*, int);

extern u32 lobby_pigeon_bml_archive;

void TObjPlayer::free_static_instance() {
    if ((u32) lobby_pigeon_bml_archive != 0U) {
        __dt__11BmlResourceFv((void*)lobby_pigeon_bml_archive, 1);
        lobby_pigeon_bml_archive = 0U;
    }
}

}
