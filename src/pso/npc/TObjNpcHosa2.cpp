#include "pso/system/BmlResource.h"
#include "types.h"
#include "pso/system/BmlAccessors.h"
#include "pso/npc/TObjNpcHosa2.h"
#include "pso/npc/TUnk_804A9F50.h"

#include "pso/system/BmlResourceDescriptor.h"
#include "pso/npc/TObjNpcBase.h"
#include "pso/npc/TObjNpcLappy.h"
#include "pso/player/TObjPlayer.h"
#include "pso/ui/frontend/TAdSinglePlyChrSelectGC.h"

#pragma readonly_strings on

extern "C" {
extern const char *bm_npc_hosa2_motion_names[1];
__declspec(section ".data") const char *bm_npc_hosa2_model_names[2] = { "hosa_hone2_body.nj", NULL };
BmlResourceDescriptor npc_hosa2_resource_descriptor = { "bm_npc_hosa2.bml", bm_npc_hosa2_model_names, bm_npc_hosa2_motion_names, 1, 0 };

const char *bm_npc_hosa2_motion_names[1] = { NULL };
const char *TObjNpcHosa2__name = "TObjNpcHosa2";
u32 TObjNpcHosa2__shared_model_resource;
}

extern "C" {

extern u32 TObjNpcHosa2__shared_model_resource;
extern s32 __vt__12TObjNpcHosa2[];
extern const char *TObjNpcHosa2__name;

void TObjNpcHosa2::close_dialog_window() {
    if ((u32) TObjNpcHosa2__shared_model_resource != 0U) {
        delete (BmlResource *)TObjNpcHosa2__shared_model_resource;
        TObjNpcHosa2__shared_model_resource = 0U;
    }
}

void TObjNpcHosa2::load_shared_resource() {
    s32 var_r0;
    var_r0 = (long)new BmlResource(1, &npc_hosa2_resource_descriptor, 0, 0, NULL);
    (*(s32 *)&TObjNpcHosa2__shared_model_resource) = var_r0;
}

}
TObjNpcHosa2::~TObjNpcHosa2() {}

u8 *TObjNpcHosa2__ct(u8 *player, s32 arg1, s32 arg2) {
    ((TUnk_804A9F50 *)player)->construct_male_npc_base();
    *(s32 **)((s8 *)player + 0x18) = __vt__12TObjNpcHosa2;
    *(s32 *)((s8 *)player + 0) = (s32) TObjNpcHosa2__name;
    ((TObjNpcHosa2 *)(player))->apply_set_data((void *)arg2);
    ((TObjChara *)player)->initialize_position_copies();
    *(s32 *)((s8 *)player + 0x34) = (s32)get_bml_model((BmlResource *)((*(s32 *)&TObjNpcHosa2__shared_model_resource)), 0);
    ((TObjNpcHosa2 *)player)->texlist = (s32)get_bml_texlist((BmlResource *)((*(s32 *)&TObjNpcHosa2__shared_model_resource)), 0);
    ((TObjNpcBase *)player)->setup_common();
    return player;
}

