#include "types.h"
#include "pso/unk/text_802A8210.h"
#include "pso/unk/text_803281B8.h"
#include "pso/misc/TUnk_804ED5B0.h"

struct RecoveredGlobal_803281B8_lbl_804ED5B0 {
    s32 value;
    u8 remaining[0x14];
};

extern "C" {
void __ct__7TObjectFP7TObject(void *, void *);
}
extern RecoveredGlobal_803281B8_lbl_804ED5B0 lbl_804ED5B0;
typedef char RecoveredGlobal_803281B8_lbl_804ED5B0_size[sizeof(RecoveredGlobal_803281B8_lbl_804ED5B0) == 0x18 ? 1 : -1];
u8 *construct_indirect_effect_task(u8 *arg0, s32 kind, s32 arg2, u8 *arg3) {
    __ct__7TObjectFP7TObject(arg0, arg3);
    *(s32 **)((s8 *)arg0 + 0x18) = &lbl_804ED5B0.value;
    *(s8 *)&((TUnk_804ED5B0 *)arg0)->unk_1C = kind;
    ((TUnk_804ED5B0 *)arg0)->m_1d = arg2;
    register_indirect_effect_ctrl((s32) kind);
    return arg0;
}
