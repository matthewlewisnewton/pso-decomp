#include "types.h"
#include "pso/enemy/TObjEneRecon.h"

extern "C" {

f32 fabs_float(f32);

extern const f32 lbl_805DF3B8;
extern const f32 TObjEneRecon__data_805DF3D0;
extern const f32 lbl_805DF3E8;
extern const f32 lbl_805DF424;

f32 TObjEneRecon::approach_value(f32 farg0, f32 farg1) {
    f32 temp_f31;
    f32 var_f1;

    temp_f31 = farg1 - farg0;
    if (fabs_float(temp_f31) < lbl_805DF3E8) {
        return farg1;
    }
    var_f1 = TObjEneRecon__data_805DF3D0;
    var_f1 = temp_f31 * var_f1;
    if (var_f1 > lbl_805DF3B8) {
        var_f1 = lbl_805DF3B8;
    } else if (var_f1 < lbl_805DF424) {
        var_f1 = lbl_805DF424;
    }
    return farg0 + var_f1;
}

}
