#include "types.h"

struct RecoveredGlobal_801D94C8_lbl_804C4A20 {
    s32 value;
    u8 remaining[0x2C];
};

extern "C" {
s8 TObjPlayer__sub_801AFDBC(s8);
extern RecoveredGlobal_801D94C8_lbl_804C4A20 class_technique_boost_table;
f32 get_class_technique_boost(s8 arg0, s16 arg1);
typedef char RecoveredGlobal_801D94C8_lbl_804C4A20_size[sizeof(RecoveredGlobal_801D94C8_lbl_804C4A20) == 0x30 ? 1 : -1];
f32 get_class_technique_boost(s8 arg0, s16 arg1) {
    s32 *var_r3;
    s16 var_r31;
    s32 var_r4;
    var_r31 = arg1;
    var_r3 = (s32 *)&class_technique_boost_table.value;
    var_r4 = TObjPlayer__sub_801AFDBC(arg0) * 4;
    var_r3 = (s32 *)&class_technique_boost_table.value;
    var_r3 = (s32 *)(*(s32 **)((s8 *)((u8 *)&class_technique_boost_table.value + var_r4) + 0));
    return *(f32 *)((s8 *)((u8 *)var_r3 + (var_r31 * 4)) + 0);
}

}
