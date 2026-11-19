#include "pso/system/BmlResource.h"
#include "types.h"
#include "pso/system/BmlAccessors.h"
#include "pso/npc/TObjNpcKenkyu.h"
#include "pso/npc/TObjNpcSoutokufu.h"
#include "pso/npc/TUnk_804A9F50.h"

#include "pso/npc/TObjNpcBase.h"
#include "pso/npc/TObjNpcLappy.h"
#include "pso/player/TObjPlayer.h"
#include "pso/ui/frontend/TAdSinglePlyChrSelectGC.h"
#include "pso/system/BmlResourceDescriptor.h"
#include "pso/system/task/TObject.h"

#pragma readonly_strings on

extern "C" {
extern const char *bm_npc_kenkyu_motion_names[1];
extern const char *bm_npc_kenkyu_model_names[2];
const char *bm_npc_kenkyu_motion_names[1] = { NULL };
__declspec(section ".data") const char *bm_npc_kenkyu_model_names[2] = { "kenkyu_body.nj", NULL };
BmlResourceDescriptor bm_npc_kenkyu_resource_descriptor = { "bm_npc_kenkyu.bml", bm_npc_kenkyu_model_names, bm_npc_kenkyu_motion_names, 1, 0 };
const char *TObjNpcKenkyu__name = "TObjNpcKenkyu";
u32 TObjNpcKenkyu__static_model;
}

extern "C" {
extern s32 __vt__13TObjNpcKenkyu[];
void *__ct__11TObjControlFP7TObject(void *, void *);

void TObjNpcKenkyu::free_static_model() {
    if ((u32) TObjNpcKenkyu__static_model != 0U) {
        delete (BmlResource *)TObjNpcKenkyu__static_model;
        TObjNpcKenkyu__static_model = 0U;
    }
}

void TObjNpcKenkyu::load_shared_resource() {
    s32 var_r0;
    var_r0 = (long)new BmlResource(1, &bm_npc_kenkyu_resource_descriptor, 0, 0, NULL);
    (*(s32 *)&TObjNpcKenkyu__static_model) = var_r0;
}

}
TObjNpcKenkyu::~TObjNpcKenkyu() {}


extern void *tl_04;

u8 *TObjNpcKenkyu__ct(u8 *player, s32 arg1, s32 arg2) {
    ((TUnk_804A9F50 *)player)->construct_male_npc_base();
    *(s32 **)((s8 *)player + 0x18) = __vt__13TObjNpcKenkyu;
    *(s32 *)((s8 *)player + 0) = (s32) TObjNpcKenkyu__name;
    ((TObjNpcKenkyu *)(player))->apply_set_data((void *)arg2);
    ((TObjChara *)player)->initialize_position_copies();
    *(s32 *)((s8 *)player + 0x34) = (s32)get_bml_model((BmlResource *)((*(s32 *)&TObjNpcKenkyu__static_model)), 0);
    ((TObjNpcKenkyu *)player)->texlist = (s32)get_bml_texlist((BmlResource *)((*(s32 *)&TObjNpcKenkyu__static_model)), 0);
    ((TObjNpcBase *)player)->setup_common();
    return player;
}

void * TObjNpcSoutokufu__create(void *arg0) {
    void *o;
    void *o2;
    o = TObject::operator new(0x20);
    if (o != NULL) {
        o = __ct__11TObjControlFP7TObject(o, tl_04);
    }
    o2 = TObject::operator new(0x3B8);
    if (o2 != NULL) {
        o2 = TObjNpcSoutokufu__ct((u8 *)o2, (s32)o, (s32)arg0);
    }
    return o2;
}

