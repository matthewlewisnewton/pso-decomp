#include <stddef.h>
#include "types.h"

#include <stddef.h>
#include "pso/TChCrTagPlGraphic.h"
#include "pso/misc/TWindowSubSymbolChatPartsSet.h"
struct Stack_802A3138 {
    f32 sp8;
    f32 spC;
    s32 sp10;
    f32 sp14;
};

struct RecoveredFields_802A3138_arg0 {
    u8 unknown_0[0x20];
    s32 field_20;
    u8 unknown_24[0x18];
    f32 field_3C;
    f32 field_40;
    f32 field_44;
};

extern "C" {
s32 draw_ui_sprite_shaded(f32, f32, f32, void *, void *, void *);
extern const f32 lbl_805DDF18;
extern const f32 lbl_805DDF1C;
#pragma push
#pragma opt_common_subs off
#pragma fp_contract on
typedef char RecoveredFields_802A3138_arg0_20_offset[offsetof(RecoveredFields_802A3138_arg0, field_20) == 0x20 ? 1 : -1];
typedef char RecoveredFields_802A3138_arg0_3C_offset[offsetof(RecoveredFields_802A3138_arg0, field_3C) == 0x3C ? 1 : -1];
typedef char RecoveredFields_802A3138_arg0_40_offset[offsetof(RecoveredFields_802A3138_arg0, field_40) == 0x40 ? 1 : -1];
typedef char RecoveredFields_802A3138_arg0_44_offset[offsetof(RecoveredFields_802A3138_arg0, field_44) == 0x44 ? 1 : -1];
void TChCrTagPlGraphic::draw_class_illustration() {
    u8 *arg0 = (u8 *)this;
    typedef char sp8_offset[(offsetof(Stack_802A3138, sp8) == 0x0) ? 1 : -1];
    typedef char spC_offset[(offsetof(Stack_802A3138, spC) == 0x4) ? 1 : -1];
    typedef char sp10_offset[(offsetof(Stack_802A3138, sp10) == 0x8) ? 1 : -1];
    typedef char sp14_offset[(offsetof(Stack_802A3138, sp14) == 0xC) ? 1 : -1];
    Stack_802A3138 stack;
    f32 temp_f0;
    f32 scale;
    s32 depth;
    if (!(((RecoveredFields_802A3138_arg0 *)arg0)->field_3C <= lbl_805DDF18)) {
        ((TWindowSubSymbolChatPartsSet *)(&stack.sp10))->copy_vec2(arg0 + 0x48);
        temp_f0 = ((RecoveredFields_802A3138_arg0 *)arg0)->field_44;
        stack.spC = temp_f0;
        stack.sp8 = temp_f0;
        scale = ((RecoveredFields_802A3138_arg0 *)arg0)->field_3C;
        depth = (((RecoveredFields_802A3138_arg0 *)arg0)->field_20 * 2) + 0x66;
        draw_ui_sprite_shaded((f32) (((RecoveredFields_802A3138_arg0 *)arg0)->field_40), (f32)scale, (f32)scale, (void *)depth, &stack.sp10, &stack.sp8);
        stack.sp14 += lbl_805DDF1C * ((RecoveredFields_802A3138_arg0 *)arg0)->field_44;
        draw_ui_sprite_shaded((f32) (((RecoveredFields_802A3138_arg0 *)arg0)->field_40), scale, scale, (void *)(depth + 1), (void *)&stack.sp10, (void *)&stack.sp8);
    }
}
#pragma pop

}
