#include "types.h"
#include "pso/misc/TWindowSubComCard.h"
#include "pso/misc/TWindowSubStatusDisp.h"

extern "C" {
f64 floor(f64);
__declspec(section ".sdata2") extern const f32 lbl_805E0DE0;
f64 ceil(f64);
__declspec(section ".sdata2") extern const f32 lbl_805E0DE8;
#pragma push
#pragma scheduling off
f32 TWindowSubComCard::trunc_float(f32 farg0) {
    if (farg0 < lbl_805E0DE0) {
        return -(f32) floor(-farg0);
    }
    return (f32) floor((f64) farg0);
}
#pragma pop

#pragma push
#pragma scheduling off
f32 TWindowSubStatusDisp::round_away_from_zero(f32 farg0) {
    if (farg0 < lbl_805E0DE8) {
        return -(f32) ceil(-farg0);
    }
    return (f32) ceil((f64) farg0);
}
#pragma pop

// sin_cos_table[angle & 0xFFFF] is the {sin, cos} pair init_sin_cos_table writes.
// Both lookups are lis/addi/lwz of that pointer, then add + lfs. A direct
// .sine load is lfsx at displacement 0; the member pointer keeps add + lfs.
struct SinCosPair {
    f32 sine;
    f32 cosine;
};
extern SinCosPair *sin_cos_table;

f32 sin_table_lookup(s32 angle) {
    f32 SinCosPair::*member = &SinCosPair::sine;
    return sin_cos_table[(u16)angle].*member;
}

f32 cos_table_lookup(s32 angle) {
    f32 SinCosPair::*member = &SinCosPair::cosine;
    return sin_cos_table[(u16)angle].*member;
}

}
