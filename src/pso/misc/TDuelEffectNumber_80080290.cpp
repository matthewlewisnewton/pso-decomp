#include "types.h"
#include "pso/TDuelEffectNumber.h"
#include "pso/misc/TCameraCtrl.h"
#include "pso/misc/TWindowSubStatusDisp_803DEE6C.h"

struct RecoveredGlobal_80080438_lbl_80438DD4 {
    s32 value;
    u8 remaining[0x14];
};

struct Entry_800803D4 { u8 data[0x18]; };

extern "C" {
void TDuelEffectNumber__sub_800802F8(void *, const void *, f32);
f32 get_scale__15TWindowCtrlMainFv(s32);
extern RecoveredGlobal_80080438_lbl_80438DD4 duel_number_default_layout;
extern Entry_800803D4 duel_number_pair_layout[];
}

extern void *TDuelEffectNumber__class_name;
TDuelEffectNumber::TDuelEffectNumber(TObject *object, void *arg2, void *arg3) : TObject(object) {
    *(void * *)&this->m_name = TDuelEffectNumber__class_name;
    *(f32 *)((s8 *)this + 0x1C) = *(f32 *)((s8 *)arg2 + 0x0);
    *(f32 *)((s8 *)this + 0x20) = *(f32 *)((s8 *)arg2 + 0x4);
    *(void **)((s8 *)this + 0x24) = arg3;
    *(u32 *)((s8 *)this + 0x28) = 0;
}

// The six-float layout holds x/y, width/height and atlas coordinates.
// The shared window declaration omits the camera selector used by this ABI.
#pragma push
#pragma fp_contract on
void TDuelEffectNumber__sub_800802F8(void *object, const void *layout, f32 scale) {
    f32 depth;
    f32 quad[8];
    const f32 *src = (const f32 *)layout;
    f32 *position = (f32 *)((u8 *)object + 0x1C);
    depth = -1.0f / get_scale__15TWindowCtrlMainFv(TCameraCtrl::get_camera_no());

    quad[0] = src[0] * scale + position[0];
    quad[1] = src[1] * scale + position[1];
    quad[2] = scale * (src[0] + src[2]) + position[0];
    quad[3] = scale * (src[1] + src[3]) + position[1];
    quad[4] = src[4];
    quad[5] = src[5];
    quad[6] = src[4] + src[2];
    quad[7] = src[5] + src[3];
    quad[4] *= 0.00390625f;
    quad[5] *= 0.00390625f;
    quad[6] *= 0.00390625f;
    quad[7] *= 0.00390625f;
    draw_textured_quad_at_depth(quad, depth);
}
#pragma pop

typedef char RecoveredGlobal_80080438_lbl_80438DD4_size[sizeof(RecoveredGlobal_80080438_lbl_80438DD4) == 0x18 ? 1 : -1];

void TDuelEffectNumber::render_pair(f32 f) {
    s32 i;
    for (i = 0; i < 2; i++) {
        TDuelEffectNumber__sub_800802F8(this, &duel_number_pair_layout[i], f);
    }
}

void TDuelEffectNumber::render_number_default(f32 farg0) {
    u8 *arg0 = (u8 *)this;
    TDuelEffectNumber__sub_800802F8(arg0, &duel_number_default_layout.value, farg0);
}
