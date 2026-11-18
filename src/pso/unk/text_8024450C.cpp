#include "types.h"
#include "pso/misc/TWindowArea.h"
#include "pso/misc/TWindowSubComCard.h"
#include "pso/misc/TWindowSubComCard_80244774.h"
#include "pso/misc/TWindowSubStatusDisp_80144B14.h"
#include "pso/object/TObjResultWin.h"
#include "pso/unk/text_8024450C.h"
#include "pso/misc/TWindowSubStatusDisp.h"

extern "C" {
extern const f32 lbl_805DCABC;
extern const f32 lbl_805DCAC0;
void fn_8024450C(s32 arg0) {
    s32 var_r30;
    s32 var_r31;
    s32 var_r3;
    s32 var_r5;
    var_r30 = arg0;
    var_r31 = TObjNewFloorWin__sub_8007410C();
    var_r3 = var_r30;
    var_r5 = TWindowSubComCard__sub_80244774();
    ((TWindowSubStatusDisp *)var_r3)->set_count_ratio_text(var_r31, var_r5);
}
#pragma push
#pragma fp_contract on
s32 create_area_window(s32 arg0) {
    TWindowArea *object;
    u8 *temp_r31;
    object = new TWindowArea;
    ((TWindowSubStatusDisp *)object)->set_entry_display_value(arg0);
    fn_802449E0((u8 *)object);
    temp_r31 = (u8 *)(object->get_title_entry());
    *(f32 *)((s8 *)temp_r31 + 8) = (f32) -((lbl_805DCAC0 * (f32) calc_text_width((char *)(arg0))) - lbl_805DCABC);
    return (s32)object;
}
}
#pragma pop

#pragma push
#pragma fp_contract on
s32 create_window_area(void) {
    TWindowArea *object;
    u8 *temp_r31;
    object = new TWindowArea;
    fn_802449E0((u8 *)object);
    fn_8024450C((s32)object);
    temp_r31 = (u8 *)object->get_title_entry();
    *(f32 *)((s8 *)temp_r31 + 8) = (f32) -((lbl_805DCAC0 * (f32) calc_text_width((char *)(((TWindowSubComCard *)temp_r31)->get_field_20()))) - lbl_805DCABC);
    return (s32)object;
}
#pragma pop
