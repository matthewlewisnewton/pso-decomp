#include "types.h"
#include "pso/unk/text_80121180.h"

struct RecoveredGlobal_80121198_lbl_804C43CC {
    s32 value;
    u8 remaining[0x8];
};

struct RecoveredGlobal_80121198_lbl_804C43D8 {
    s32 value;
    u8 remaining[0xC];
};

struct RecoveredGlobal_80121180_lbl_804C43C0 {
    s32 value;
    u8 remaining[0x8];
};

extern "C" {
s16 get_validated_attack_stage();
extern RecoveredGlobal_80121198_lbl_804C43CC attack_type_accuracy_scales;
extern RecoveredGlobal_80121198_lbl_804C43D8 attack_combo_accuracy_multipliers;
extern RecoveredGlobal_80121180_lbl_804C43C0 attack_damage_scale_table;
typedef char RecoveredGlobal_80121198_lbl_804C43CC_size[sizeof(RecoveredGlobal_80121198_lbl_804C43CC) == 0xC ? 1 : -1];
typedef char RecoveredGlobal_80121198_lbl_804C43D8_size[sizeof(RecoveredGlobal_80121198_lbl_804C43D8) == 0x10 ? 1 : -1];

typedef char RecoveredGlobal_80121180_lbl_804C43C0_size[sizeof(RecoveredGlobal_80121180_lbl_804C43C0) == 0xC ? 1 : -1];
f32 get_attack_damage_scale(s16 *arg0) {
    return *(f32 *)((s8 *)((u8 *)&attack_damage_scale_table.value + (*(s16 *)((s8 *)arg0 + 0) * 4)) + 0);
}

f32 get_attack_accuracy_scale(s16 *arg0) {
    return *(f32 *)((s8 *)((u8 *)&attack_type_accuracy_scales.value + (*(s16 *)((s8 *)arg0 + 0) * 4)) + 0) * *(f32 *)((s8 *)((u8 *)&attack_combo_accuracy_multipliers.value + (get_validated_attack_stage() * 4)) + 0);
}

}
