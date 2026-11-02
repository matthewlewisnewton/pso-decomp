#include "types.h"
#include "pso/misc/TWindowSubComCard.h"
#include "pso/misc/TWindowSubStatusDisp.h"

struct SinCos_803D64C0 { f32 c; f32 s; };

extern "C" {
extern SinCos_803D64C0 *sin_cos_table;
f64 floor(f64);
extern const f32 lbl_805E0DE0;
f64 ceil(f64);
extern const f32 lbl_805E0DE8;
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

// Recovered source. MWCC 2.6 emits an indexed lfsx for these lookups; the
// original keeps the table pointer and byte offset in r6/r7 and loads with
// add-plus-displacement, which the available MWCC builds do not produce from C,
// so objdiff reports both functions unmatched.
f32 sin_table_lookup(s32 angle) {
    return sin_cos_table[(u16) angle].c;
}

f32 cos_table_lookup(s32 angle) {
    return sin_cos_table[(u16) angle].s;
}

}
