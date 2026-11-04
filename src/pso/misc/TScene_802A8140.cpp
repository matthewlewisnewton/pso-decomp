#include "types.h"
#include "pso/misc/TScene_802A8140.h"
#include "pso/player/TObjPlayer_803DC834.h"
#include "pso/misc/TScene.h"
#include "pso/player/TObjPlayer.h"

extern "C" {

s32 GXSetNumIndStages(s32);
s32 GXSetTevDirect(s32);
void __dl__7TObjectFPv(void *);
void __dt__7TObjectFv(void *, int);

void TScene::set_indirect_tev(s32 ignored, s32 arg1) {
    if (arg1 != 0) {
        GXSetTevDirect(1);
    } else {
        GXSetTevDirect(0);
    }
    GXSetNumIndStages(0);
    set_ginja_post_texgen_count(0);
}

void TScene::draw_field_1c(s32 sampler, s32 arg2, s32 arg3) {
    TObjPlayer::play_particle_at_active_slot(*(u8 *)((s8 *)this + 0x1C), sampler, arg2, 0, arg3, 0);
}

extern s32 lbl_804DDF04[];

void *__dt__13TUnk_804DDF04Fv(void *arg0, s16 arg1) {
    if (arg0 != NULL) {
        *(s32 **)((s8 *)arg0 + 0x18) = lbl_804DDF04;
        __dt__7TObjectFv(arg0, 0);
        if (arg1 > 0) {
            __dl__7TObjectFPv(arg0);
        }
    }
    return arg0;
}

}
