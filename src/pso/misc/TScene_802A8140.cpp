#include "types.h"
#include "pso/misc/TScene_802A8140.h"
#include "pso/player/TObjPlayer_803DC834.h"
#include "pso/misc/TScene.h"
#include "pso/player/TObjPlayer.h"

extern "C" {

s32 GXSetNumIndStages(s32);
s32 GXSetTevDirect(s32);

void TScene::set_indirect_tev(s32 ignored, s32 arg1) {
    if (arg1 != 0) {
        GXSetTevDirect(1);
    } else {
        GXSetTevDirect(0);
    }
    GXSetNumIndStages(0);
    set_ginja_post_texgen_count(0);
}

void draw_field_1c__6TSceneFlll(TUnk_804DDF04 *manager, s32 sampler, s32 arg2, s32 arg3) {
    TObjPlayer::play_particle_at_active_slot(manager->kind, sampler, arg2, 0, arg3, 0);
}

}
