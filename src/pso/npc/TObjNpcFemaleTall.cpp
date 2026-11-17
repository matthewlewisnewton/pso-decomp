#include "types.h"
#include "pso/system/BmlResourceClass.h"
#include "pso/npc/TObjNpcFemaleTall.h"
#include "pso/npc/TUnk_804A92A8.h"
#include "pso/npc/TUnk_804A8640.h"
#include "pso/npc/TObjNpcBase.h"
#include "pso/npc/TObjNpcFemaleBase.h"
#include "pso/player/TObjPlayer.h"

struct RecoveredGlobal_8014A8F0_lbl_804A9120 { s32 value; u8 remaining[0xC]; };
typedef char RecoveredGlobal_8014A8F0_lbl_804A9120_size[sizeof(RecoveredGlobal_8014A8F0_lbl_804A9120) == 0x10 ? 1 : -1];

struct RecoveredGlobal_8014A998___vt__17TObjNpcFemaleTall {
    s32 value;
    u8 remaining[0x174];
};

extern "C" {
extern const char lbl_8043F990[] = "n_etw_i_body.nj";
extern const char lbl_8043F9A0[] = "bm_n_etw_i_body.bml";
extern const char lbl_8043F9B4[] = "TObjNpcFemaleTall";
extern RecoveredGlobal_8014A8F0_lbl_804A9120 bm_n_etw_i_body_resource_descriptor;
extern s32 __vt__17TObjNpcFemaleTall[];
extern s32 TObjNpcFemaleTall__name;
void __dl__7TObjectFPv(void *);

void TObjNpcFemaleTall::destroy_instance() {
    if ((u32) TObjNpcFemaleTall__instance != 0U) {
        delete (BmlResource *)((void*)TObjNpcFemaleTall__instance);
        TObjNpcFemaleTall__instance = 0U;
    }
}
void TObjNpcFemaleTall::load_resource_instance() {
    BmlResource *temp_r3;
    BmlResource *var_r0;
    temp_r3 = new BmlResource(1, (BmlResourceDescriptor *)(&bm_n_etw_i_body_resource_descriptor.value), 0, 0, (void *)(0));
    var_r0 = temp_r3;
    TObjNpcFemaleTall__instance = var_r0;
}

void *__dt__17TObjNpcFemaleTallFv(void *arg0, s16 arg1) {
    if (arg0 != NULL) {
        *(s32 **)((s8 *)arg0 + 0x18) = __vt__17TObjNpcFemaleTall;
        ((TUnk_804A8640 *)arg0)->destroy_npc_female_base(0);
        if (arg1 > 0) {
            __dl__7TObjectFPv(arg0);
        }
    }
    return arg0;
}

typedef char RecoveredGlobal_8014A998___vt__17TObjNpcFemaleTall_size[sizeof(RecoveredGlobal_8014A998___vt__17TObjNpcFemaleTall) == 0x178 ? 1 : -1];
u8 *TObjNpcFemaleTall__ct(u8 *arg0, s32 arg1, s32 arg2) {
    ((TUnk_804A8640 *)arg0)->construct_female_base();
    *(s32 **)((s8 *)arg0 + 0x18) = &(*(RecoveredGlobal_8014A998___vt__17TObjNpcFemaleTall *)&__vt__17TObjNpcFemaleTall).value;
    *(s32 *)((s8 *)arg0 + 0) = (s32) TObjNpcFemaleTall__name;
    ((TObjNpcFemaleTall *)(arg0))->apply_set_data((void *)arg2);
    ((TObjChara *)arg0)->initialize_position_copies();
    *(s32 *)((s8 *)arg0 + 0x34) = (s32) *(s32 *)((s8 *)(*(u8 **)((s8 *)TObjNpcFemaleTall__instance + 0x42C)) + 8);
    ((TObjNpcFemaleTall *)arg0)->texlist = (s32) *(s32 *)((s8 *)(*(u8 **)((s8 *)TObjNpcFemaleTall__instance + 0x42C)) + 0xC);
    ((TObjNpcBase *)arg0)->setup_common();
    return arg0;
}

void TObjNpcFemaleTall__sub_8014AA28(void *arg0, s32 arg1) {
    if (arg1 != 1) {
        ((TUnk_804A92A8 *)arg0)->requested_action = 0;
        return;
    }
    ((TUnk_804A92A8 *)arg0)->requested_action = 1;
}

}
