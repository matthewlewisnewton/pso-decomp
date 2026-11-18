#include "types.h"
#include "pso/misc/TUnk_804CF0B8.h"

extern "C" {
s32 get_zero_vec2();
extern u8 window_fukidasi_addition_params[];
}

TUnk_804CF0B8::TUnk_804CF0B8(u16 speaker, s32 text, s32 client, f32 scale)
    : TWindowAddition(window_fukidasi_addition_params, (s16)client, (u8 *)get_zero_vec2()) {
    sub_80251DF0(speaker, text, client, scale);
}
