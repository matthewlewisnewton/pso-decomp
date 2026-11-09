#include "types.h"
#include "pso/misc/TWindowSubStatusDisp.h"
#include "pso/math/AngleLookup.h"

// sin_table_lookup.inc addresses sin_cos_table@ha. Kept in this file: other
// units already declare that symbol with their own types.
struct SinCosPair {
    f32 sin;
    f32 cos;
};

extern "C" {
extern SinCosPair *sin_cos_table;
f64 ceil(f64);
extern const f32 lbl_805E0DE8;
#pragma push
#pragma scheduling off
f32 TWindowSubStatusDisp::round_away_from_zero(f32 farg0) {
    if (farg0 < lbl_805E0DE8) {
        return -(f32) ceil(-farg0);
    }
    return (f32) ceil((f64) farg0);
}
#pragma pop

}

asm f32 sin_table_lookup(s32 angle) {
#include "orig_asm/pso/unk/text_803D647C/sin_table_lookup.inc"
}

asm f32 cos_table_lookup(s32 angle) {
#include "orig_asm/pso/unk/text_803D647C/cos_table_lookup.inc"
}
