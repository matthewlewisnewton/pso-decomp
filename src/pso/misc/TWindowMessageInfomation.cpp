#include "pso/misc/TWindowDrawContext.h"
#include "types.h"
#include "pso/misc/TWindowMessageInfomation.h"

#pragma readonly_strings on

extern "C" {
const char *lbl_805D3988 = "TWindowMessageInfomation";
}



struct RecoveredGlobal_8026A100___vt__24TWindowMessageInfomation {
    s32 value;
    u8 remaining[0x14];
};

extern "C" {
extern s32 __vt__24TWindowMessageInfomation[];
extern const char *lbl_805D3988;
s32 draw_visible_window_entries(s32, s32, s32);

void TWindowMessageInfomation::render() {
    s32 arg0 = (s32)this;
    s8 *tmp = (s8 *)get_draw_context__11TWindowBaseFPv(this);
    draw_visible_window_entries(arg0, arg0 + 0x24, (s32)tmp);
}

}
TWindowMessageInfomation::~TWindowMessageInfomation() {

}

typedef char RecoveredGlobal_8026A100___vt__24TWindowMessageInfomation_size[sizeof(RecoveredGlobal_8026A100___vt__24TWindowMessageInfomation) == 0x18 ? 1 : -1];
TWindowMessageInfomation::TWindowMessageInfomation(s32 arg1, s32 arg2)
    : TWindowMessage(arg1, 0x10U, arg2) {
    *(s32 *)((s8 *)((u8 *)this) + 0) = (s32) ((s32)lbl_805D3988);

}

