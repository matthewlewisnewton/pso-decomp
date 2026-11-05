#include "types.h"
#include "pso/unk/text_803E1FC8.h"
#include "pso/unk/text_803E2008.h"
#include "pso/unk/text_803E2070.h"
#include "pso/player/TObjPlayer.h"
extern const f32 lbl_805E1050;
extern const f32 lbl_805E1054;
#pragma push
#pragma scheduling off
void reset_scene_fog(void) {
    fn_803E1FC8(0xFFFFFFFF);
    set_scene_fog_distances(lbl_805E1050, lbl_805E1054);
    set_scene_fog_type(2);
    TObjPlayer::set_effect_active();
    apply_scene_fog();
}
#pragma pop
