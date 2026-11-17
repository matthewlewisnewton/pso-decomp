#include "types.h"
#include "pso/system/BmlResourceClass.h"
#include "pso/npc/TObjNpcFemaleMacho.h"
#include "pso/npc/TUnk_804A8640.h"
#include "pso/npc/TObjNpcFemaleOld.h"
#include "pso/npc/TObjNpcBase.h"
#include "pso/npc/TObjNpcFemaleBase.h"
#include "pso/player/TObjPlayer.h"
#include "pso/ui/TAdSinglePlyChrSelectGC.h"

struct RecoveredGlobal_8014A540_lbl_804A8E00 { s32 value; u8 remaining[0xC]; };
typedef char RecoveredGlobal_8014A540_lbl_804A8E00_size[sizeof(RecoveredGlobal_8014A540_lbl_804A8E00) == 0x10 ? 1 : -1];

struct RecoveredGlobal_8014A5E8___vt__18TObjNpcFemaleMacho {
    s32 value;
    u8 remaining[0x174];
};

extern "C" {
extern const char lbl_8043F918[] = "n_emw_i_body.nj";
extern const char lbl_8043F928[] = "bm_n_emw_i_body.bml";
extern const char lbl_8043F93C[] = "TObjNpcFemaleMacho";
extern RecoveredGlobal_8014A540_lbl_804A8E00 bm_n_emw_i_body_resource_descriptor;
extern s32 __vt__18TObjNpcFemaleMacho[];
extern s32 TObjNpcFemaleMacho__name;
void *__ct__11TObjControlFP7TObject(void *, void *);
void __dl__7TObjectFPv(void *);
void *__nw__7TObjectFUl(int);

void TObjNpcFemaleMacho::close_dialog_window() {
    if ((u32) TObjNpcFemaleMacho__lobby_resource != 0U) {
        delete (BmlResource *)((void*)TObjNpcFemaleMacho__lobby_resource);
        TObjNpcFemaleMacho__lobby_resource = 0U;
    }
}
void TObjNpcFemaleMacho::load_resources() {
    BmlResource *temp_r3;
    BmlResource *var_r0;
    temp_r3 = new BmlResource(1, (BmlResourceDescriptor *)(&bm_n_emw_i_body_resource_descriptor.value), 0, 0, (void *)(0));
    var_r0 = temp_r3;
    TObjNpcFemaleMacho__lobby_resource = var_r0;
}

void *__dt__18TObjNpcFemaleMachoFv(void *arg0, s16 arg1) {
    if (arg0 != NULL) {
        *(s32 **)((s8 *)arg0 + 0x18) = __vt__18TObjNpcFemaleMacho;
        ((TUnk_804A8640 *)arg0)->destroy_npc_female_base(0);
        if (arg1 > 0) {
            __dl__7TObjectFPv(arg0);
        }
    }
    return arg0;
}

extern void *tl_04;

typedef char RecoveredGlobal_8014A5E8___vt__18TObjNpcFemaleMacho_size[sizeof(RecoveredGlobal_8014A5E8___vt__18TObjNpcFemaleMacho) == 0x178 ? 1 : -1];
u8 *TObjNpcFemaleMacho__ct(u8 *arg0, s32 arg1, s32 arg2) {
    ((TUnk_804A8640 *)arg0)->construct_female_base();
    *(s32 **)((s8 *)arg0 + 0x18) = &(*(RecoveredGlobal_8014A5E8___vt__18TObjNpcFemaleMacho *)&__vt__18TObjNpcFemaleMacho).value;
    *(s32 *)((s8 *)arg0 + 0) = (s32) TObjNpcFemaleMacho__name;
    ((TObjNpcFemaleMacho *)(arg0))->apply_set_data((void *)arg2);
    ((TObjChara *)arg0)->initialize_position_copies();
    *(s32 *)((s8 *)arg0 + 0x34) = (s32) *(s32 *)((s8 *)(*(u8 **)((s8 *)TObjNpcFemaleMacho__lobby_resource + 0x42C)) + 8);
    ((TObjNpcFemaleMacho *)arg0)->texlist = (s32) *(s32 *)((s8 *)(*(u8 **)((s8 *)TObjNpcFemaleMacho__lobby_resource + 0x42C)) + 0xC);
    ((TObjNpcBase *)arg0)->setup_common();
    return arg0;
}

void * TObjNpcFemaleOld__create(void *arg0) {
    void *o;
    void *o2;
    o = __nw__7TObjectFUl(0x20);
    if (o != NULL) {
        o = __ct__11TObjControlFP7TObject(o, tl_04);
    }
    o2 = __nw__7TObjectFUl(0x3B8);
    if (o2 != NULL) {
        o2 = TObjNpcFemaleOld__ct((u8 *)o2, (s32)o, (s32)arg0);
    }
    return o2;
}

}
