#include "pso/system/CurrentTextureList.h"
#include "types.h"
#include "pso/system/GinjaMaterial.h"
#include "pso/unk/text_803D96A8.h"
#include "pso/TObjBoss5FloorGrass.h"
#include "pso/object/TObjFish.h"
#include "pso/player/TObjPlayer.h"

extern "C" {

s32 push_matrix();

extern void *lbl_805D4DD8;
extern s32 boss5_common_texture_list;

void TObjBoss5FloorGrass::render() {
    if (TObjPlayer::is_any_teammate_in_state() == 0) {
        push_matrix();
        set_current_texture_list((GinjaTextureList *)(boss5_common_texture_list));
        draw_ginja_object((void *)(*(s32 *)((s8 *)(*(void **)((s8 *)lbl_805D4DD8 + 0x42C)) + 0x78)));
        pop_matrix();
    }
}

void TObjBoss5FloorGrass::run_task() {  }

}
