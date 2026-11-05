#include "pso/ui/MenuText.h"
#include "types.h"
#include "pso/TAdTitleTexGC.h"
#include "pso/TObjWarpString.h"

extern const f32 lbl_805DDF80;
extern const f32 lbl_805DDF84;

#pragma push
#pragma opt_common_subs off
void TAdTitleTexGC::sub_802A4D74(s32 arg1, u8 *arg2, u8 *arg3) {
    u8 *arg0 = (u8 *)this;
    draw_menu_text(lbl_805DDF80 + *(f32 *)((s8 *)arg0 + 0x1C), lbl_805DDF84 + *(f32 *)((s8 *)arg0 + 0x20), (const char *)arg2, arg1);
    draw_menu_text(lbl_805DDF80 + *(f32 *)((s8 *)arg0 + 0x3C), lbl_805DDF84 + *(f32 *)((s8 *)arg0 + 0x40), (const char *)arg3, arg1);
}

#pragma pop
