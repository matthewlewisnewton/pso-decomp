#include "types.h"
#include "pso/system/BmlResourceClass.h"
#include "pso/npc/TObjNpcHosa2.h"
#include "pso/unk/text_8014B8A4.h"
#include "pso/npc/TUnk_804A9F50.h"
#include "pso/system/BmlResourceDescriptor.h"
#include "pso/npc/TObjNpcKenkyu2.h"
#include "pso/npc/TObjNpcBase.h"
#include "pso/npc/TObjNpcLappy.h"
#include "pso/player/TObjPlayer.h"
#include "pso/ui/TAdSinglePlyChrSelectGC.h"

#pragma readonly_strings on

extern const char *bm_npc_kenkyu2_model_names[2];
extern BmlResourceDescriptor TObjNpcKenkyu2__resource_descriptor;
extern const char *bm_npc_kenkyu2_motion_names[1];

struct RecoveredGlobal_802FEAD8_lbl_804E6248 { s32 value; u8 remaining[0xC]; };
typedef char RecoveredGlobal_802FEAD8_lbl_804E6248_size[sizeof(RecoveredGlobal_802FEAD8_lbl_804E6248) == 0x10 ? 1 : -1];

struct RecoveredGlobal_802FEB80___vt__14TObjNpcKenkyu2 {
    s32 value;
    u8 remaining[0x174];
};

extern "C" {
extern u32 TObjNpcKenkyu2__shared_model_resource;
s32 TObjFish__sub_8001EDB0(int, int);
s32 get_bml_model(int, int);
extern s32 __vt__14TObjNpcKenkyu2[];
extern const char *TObjNpcKenkyu2__name;
void *__ct__11TObjControlFP7TObject(void *, void *);
void __dl__7TObjectFPv(void *);
void *__nw__7TObjectFUl(int);

void TObjNpcKenkyu2::free_static_model() {
    if ((u32) TObjNpcKenkyu2__shared_model_resource != 0U) {
        delete (BmlResource *)((void*)TObjNpcKenkyu2__shared_model_resource);
        TObjNpcKenkyu2__shared_model_resource = 0U;
    }
}

void TObjNpcKenkyu2::load_shared_resource() {
    s32 temp_r3;
    s32 var_r0;
    temp_r3 = (int)new BmlResource(1, (BmlResourceDescriptor *)(&TObjNpcKenkyu2__resource_descriptor), 0, 0, (void *)(0));
    var_r0 = temp_r3;
    (*(s32 *)&TObjNpcKenkyu2__shared_model_resource) = var_r0;
}

void *__dt__14TObjNpcKenkyu2Fv(void *arg0, s16 arg1) {
    if (arg0 != NULL) {
        *(s32 **)((s8 *)arg0 + 0x18) = __vt__14TObjNpcKenkyu2;
        ((TUnk_804A9F50 *)arg0)->destroy_npc_lappy_base(0);
        if (arg1 > 0) {
            __dl__7TObjectFPv(arg0);
        }
    }
    return arg0;
}

extern void *tl_04;

typedef char RecoveredGlobal_802FEB80___vt__14TObjNpcKenkyu2_size[sizeof(RecoveredGlobal_802FEB80___vt__14TObjNpcKenkyu2) == 0x178 ? 1 : -1];
u8 *TObjNpcKenkyu2__ct(u8 *player, s32 arg1, s32 arg2) {
    construct_male_npc_base((player));
    *(s32 **)((s8 *)player + 0x18) = &(*(RecoveredGlobal_802FEB80___vt__14TObjNpcKenkyu2 *)&__vt__14TObjNpcKenkyu2).value;
    *(s32 *)((s8 *)player + 0) = (s32) TObjNpcKenkyu2__name;
    ((TObjNpcKenkyu2 *)(player))->apply_set_data((void *)arg2);
    ((TObjChara *)player)->initialize_position_copies();
    *(s32 *)((s8 *)player + 0x34) = get_bml_model((int) ((*(s32 *)&TObjNpcKenkyu2__shared_model_resource)), 0);
    ((TObjNpcKenkyu2 *)player)->texlist = TObjFish__sub_8001EDB0((int) ((*(s32 *)&TObjNpcKenkyu2__shared_model_resource)), 0);
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
