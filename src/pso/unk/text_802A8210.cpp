#include "pso/player/demo_mode.h"
#include "types.h"
#include "pso/effect/TEffIndirectCtrl.h"
#include "pso/unk/text_802A8210.h"
#include "pso/player/TObjPlayer.h"

struct RecoveredGlobal_802A8210_lbl_804DDF04 {
    s32 value;
    u8 remaining[0x14];
};

extern "C" {
void __ct__7TObjectFP7TObject(void *, void *);
extern RecoveredGlobal_802A8210_lbl_804DDF04 lbl_804DDF04;
u8 *__nw__7TObjectFUl(u32);
u8 *TEffIndirectCtrl__ct(u8 *, s32, s32);
extern u8 *indirect_effect_ctrl_table[];
extern s32 tl_01;
extern u8 indirect_effect_ctrl_count;
typedef char RecoveredGlobal_802A8210_lbl_804DDF04_size[sizeof(RecoveredGlobal_802A8210_lbl_804DDF04) == 0x18 ? 1 : -1];
u8 *fn_802A8210(u8 *object, s32 kind, u8 *arg2) {
    __ct__7TObjectFP7TObject(object, arg2);
    *(s32 **)((s8 *)object + 0x18) = &lbl_804DDF04.value;
    *(s8 *)((s8 *)object + 0x1C) = kind;
    register_indirect_effect_ctrl((s32)((s32) kind));
    return object;
}
void register_indirect_effect_ctrl(s32 kind) {
    u8 *p;
    if (((s8 (*)(s32))find_indirect_effect_ctrl)(kind) < 0 && indirect_effect_ctrl_count < 6) {
        p = __nw__7TObjectFUl(0x54);
        if (p != NULL) {
            p = TEffIndirectCtrl__ct(p, kind, tl_01);
        }
        indirect_effect_ctrl_table[indirect_effect_ctrl_count] = p;
        indirect_effect_ctrl_count++;
    }
}
s8 find_indirect_effect_ctrl(u8 arg0) {
    s32 i;
    for (i = 0; i < indirect_effect_ctrl_count; i++) {
        if (indirect_effect_ctrl_table[i] != 0) {
            u8 id = TEffIndirectCtrl__sub_802A9554(indirect_effect_ctrl_table[i]);
            if (id == arg0) {
                if (check_demo_mode() == 0) {
                    TEffIndirectCtrl__sub_802A9548(indirect_effect_ctrl_table[i]);
                }
                return i;
            }
        }
    }
    return -1;
}

}
