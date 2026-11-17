#include "types.h"
#include "pso/system/BmlResourceClass.h"
#include "pso/npc/TObjNpcFemaleChild.h"
#include "pso/npc/TUnk_804A8640.h"
#include "pso/npc/TObjNpcFemaleDwarf.h"
#include "pso/npc/TObjNpcBase.h"
#include "pso/npc/TObjNpcFemaleBase.h"
#include "pso/player/TObjPlayer.h"
#include "pso/ui/TAdSinglePlyChrSelectGC.h"

struct RecoveredGlobal_80149FB8_lbl_804A8950 { s32 value; u8 remaining[0xC]; };
typedef char RecoveredGlobal_80149FB8_lbl_804A8950_size[sizeof(RecoveredGlobal_80149FB8_lbl_804A8950) == 0x10 ? 1 : -1];

struct RecoveredGlobal_8014A060___vt__18TObjNpcFemaleChild {
    s32 value;
    u8 remaining[0x174];
};

extern "C" {
extern const char lbl_8043F868[] = "n_ecw_i_body.nj";
extern const char lbl_8043F878[] = "bm_n_ecw_i_body.bml";
extern const char lbl_8043F88C[] = "TObjNpcFemaleChild";
extern RecoveredGlobal_80149FB8_lbl_804A8950 bm_n_ecw_i_body_resource_descriptor;
extern s32 __vt__18TObjNpcFemaleChild[];
extern s32 TObjNpcFemaleChild__name;
void *__ct__11TObjControlFP7TObject(void *, void *);
void __dl__7TObjectFPv(void *);
void *__nw__7TObjectFUl(int);

void TObjNpcFemaleChild::release_static_instance() {
    if ((u32) TObjNpcFemaleChild__static_instance != 0U) {
        delete (BmlResource *)((void*)TObjNpcFemaleChild__static_instance);
        TObjNpcFemaleChild__static_instance = 0U;
    }
}
void TObjNpcFemaleChild::load_shared_resource() {
    BmlResource *temp_r3;
    BmlResource *var_r0;
    temp_r3 = new BmlResource(1, (BmlResourceDescriptor *)(&bm_n_ecw_i_body_resource_descriptor.value), 0, 0, (void *)(0));
    var_r0 = temp_r3;
    TObjNpcFemaleChild__static_instance = var_r0;
}

void *__dt__18TObjNpcFemaleChildFv(void *arg0, s16 arg1) {
    if (arg0 != NULL) {
        *(s32 **)((s8 *)arg0 + 0x18) = __vt__18TObjNpcFemaleChild;
        ((TUnk_804A8640 *)arg0)->destroy_npc_female_base(0);
        if (arg1 > 0) {
            __dl__7TObjectFPv(arg0);
        }
    }
    return arg0;
}

extern void *tl_04;

typedef char RecoveredGlobal_8014A060___vt__18TObjNpcFemaleChild_size[sizeof(RecoveredGlobal_8014A060___vt__18TObjNpcFemaleChild) == 0x178 ? 1 : -1];
u8 *TObjNpcFemaleChild__ct(u8 *arg0, s32 arg1, s32 arg2) {
    ((TUnk_804A8640 *)arg0)->construct_female_base();
    *(s32 **)((s8 *)arg0 + 0x18) = &(*(RecoveredGlobal_8014A060___vt__18TObjNpcFemaleChild *)&__vt__18TObjNpcFemaleChild).value;
    *(s32 *)((s8 *)arg0 + 0) = (s32) TObjNpcFemaleChild__name;
    ((TObjNpcFemaleChild *)(arg0))->apply_set_data((void *)arg2);
    ((TObjChara *)arg0)->initialize_position_copies();
    *(s32 *)((s8 *)arg0 + 0x34) = (s32) *(s32 *)((s8 *)(*(u8 **)((s8 *)TObjNpcFemaleChild__static_instance + 0x42C)) + 8);
    ((TObjNpcFemaleChild *)arg0)->texlist = (s32) *(s32 *)((s8 *)(*(u8 **)((s8 *)TObjNpcFemaleChild__static_instance + 0x42C)) + 0xC);
    ((TObjNpcBase *)arg0)->setup_common();
    return arg0;
}

void * TObjNpcFemaleDwarf__create(void *arg0) {
    void *o;
    void *o2;
    o = __nw__7TObjectFUl(0x20);
    if (o != NULL) {
        o = __ct__11TObjControlFP7TObject(o, tl_04);
    }
    o2 = __nw__7TObjectFUl(0x3B8);
    if (o2 != NULL) {
        o2 = TObjNpcFemaleDwarf__ct((u8 *)o2, (s32)o, (s32)arg0);
    }
    return o2;
}

}
