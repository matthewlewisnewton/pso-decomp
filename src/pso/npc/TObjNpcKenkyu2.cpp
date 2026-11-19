#include "pso/system/BmlResource.h"
#include "types.h"
#include "pso/system/BmlAccessors.h"
#include "pso/npc/TObjNpcKenkyu2.h"
#include "pso/npc/TObjNpcKenkyu2_802FEA38.h"
#include "pso/npc/TObjNpcHosa2.h"
#include "pso/npc/TUnk_804A9F50.h"
#include "pso/system/BmlResourceDescriptor.h"
#include "pso/npc/TObjNpcBase.h"
#include "pso/npc/TObjNpcLappy.h"
#include "pso/player/TObjPlayer.h"
#include "pso/ui/frontend/TAdSinglePlyChrSelectGC.h"
#pragma readonly_strings on

extern "C" {

void *__ct__11TObjControlFP7TObject(void *, void *);
void *__nw__7TObjectFUl(int);

extern void *tl_04;

void * TObjNpcKenkyu2__create(void *arg0) {
    void *o;
    void *o2;
    o = __nw__7TObjectFUl(0x20);
    if (o != NULL) {
        o = __ct__11TObjControlFP7TObject(o, tl_04);
    }
    o2 = __nw__7TObjectFUl(0x3B8);
    if (o2 != NULL) {
        o2 = TObjNpcKenkyu2__ct((u8 *)o2, (s32)o, (s32)arg0);
    }
    return o2;
}

}

extern const char *bm_npc_kenkyu2_model_names[2];
extern BmlResourceDescriptor TObjNpcKenkyu2__resource_descriptor;
extern const char *bm_npc_kenkyu2_motion_names[1];

extern "C" {
extern u32 TObjNpcKenkyu2__shared_model_resource;
extern s32 __vt__14TObjNpcKenkyu2[];
extern const char *TObjNpcKenkyu2__name;

void TObjNpcKenkyu2::free_static_model() {
    if ((u32) TObjNpcKenkyu2__shared_model_resource != 0U) {
        delete (BmlResource *)TObjNpcKenkyu2__shared_model_resource;
        TObjNpcKenkyu2__shared_model_resource = 0U;
    }
}

void TObjNpcKenkyu2::load_shared_resource() {
    s32 var_r0;
    var_r0 = (long)new BmlResource(1, &TObjNpcKenkyu2__resource_descriptor, 0, 0, NULL);
    (*(s32 *)&TObjNpcKenkyu2__shared_model_resource) = var_r0;
}

}
TObjNpcKenkyu2::~TObjNpcKenkyu2() {}
extern "C" {


u8 *TObjNpcKenkyu2__ct(u8 *player, s32 arg1, s32 arg2) {
    ((TUnk_804A9F50 *)player)->construct_male_npc_base();
    *(s32 **)((s8 *)player + 0x18) = __vt__14TObjNpcKenkyu2;
    *(s32 *)((s8 *)player + 0) = (s32) TObjNpcKenkyu2__name;
    ((TObjNpcKenkyu2 *)(player))->apply_set_data((void *)arg2);
    ((TObjChara *)player)->initialize_position_copies();
    *(s32 *)((s8 *)player + 0x34) = (s32)get_bml_model((BmlResource *)((*(s32 *)&TObjNpcKenkyu2__shared_model_resource)), 0);
    ((TObjNpcKenkyu2 *)player)->texlist = (s32)get_bml_texlist((BmlResource *)((*(s32 *)&TObjNpcKenkyu2__shared_model_resource)), 0);
    ((TObjNpcBase *)player)->setup_common();
    return player;
}

void * TObjNpcHosa2__create(void *arg0) {
    void *o;
    void *o2;
    o = __nw__7TObjectFUl(0x20);
    if (o != NULL) {
        o = __ct__11TObjControlFP7TObject(o, tl_04);
    }
    o2 = __nw__7TObjectFUl(0x3B8);
    if (o2 != NULL) {
        o2 = TObjNpcHosa2__ct((u8 *)o2, (s32)o, (s32)arg0);
    }
    return o2;
}

__declspec(section ".data") const char *bm_npc_kenkyu2_model_names[2] = { "kenkyu2_body.nj", NULL };
BmlResourceDescriptor TObjNpcKenkyu2__resource_descriptor = { "bm_npc_kenkyu2.bml", bm_npc_kenkyu2_model_names, bm_npc_kenkyu2_motion_names, 1, 0 };
__declspec(section ".sdata") const char *bm_npc_kenkyu2_motion_names[1] = { NULL };

const char *TObjNpcKenkyu2__name = "TObjNpcKenkyu2";
u32 TObjNpcKenkyu2__shared_model_resource;
}
