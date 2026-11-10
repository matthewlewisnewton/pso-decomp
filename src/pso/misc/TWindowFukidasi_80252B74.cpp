#include "types.h"
#include "pso/misc/TUnk_804CF0B8.h"

extern "C" {
s32 get_zero_vec2();
extern u8 window_fukidasi_addition_params[];
// Existing word-valued ABI view; the recovered short-form method remains held.
void sub_80251DF0__13TUnk_804CF0B8Fslsf(void *, s32, s32, s32, f32);
}

TUnk_804CF0B8::TUnk_804CF0B8(s32 speaker, s32 text, s32 client, f32 scale)
    : TWindowAddition(window_fukidasi_addition_params, (s16)client, (u8 *)get_zero_vec2()) {
    sub_80251DF0__13TUnk_804CF0B8Fslsf(this, speaker, text, client, scale);
}
