#include "pso/misc/WindowConstructorAbi.h"
#include "types.h"
#include "pso/misc/TWindowFukidasi_80252B74.h"
extern "C" {
void *sub_80251DF0__13TUnk_804CF0B8Fslsf(void *, s32, s32, s32, f32);
s32 get_zero_vec2();
extern u8 window_fukidasi_addition_params[];
extern u8 lbl_804CF0B8[];
u8 *TWindowFukidasi__sub_80252B74(u8 *arg0, s32 arg1, s32 str, s32 arg3, f32 farg0) {
    __ct__15TWindowAdditionFPUcsPUc((TWindowAddition *)(arg0), (u8 *)(window_fukidasi_addition_params), (s16)(arg3), (u8 *)(get_zero_vec2()));
    *(void **)(arg0 + 0x18) = lbl_804CF0B8;
    sub_80251DF0__13TUnk_804CF0B8Fslsf(arg0, arg1, str, arg3, farg0);
    return arg0;
}

}
