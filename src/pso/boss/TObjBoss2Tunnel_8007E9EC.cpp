#include "types.h"
#include "pso/math/VectorNormalize.h"
#include <dolphin/mtx.h>

extern "C" {

s32 TCameraCtrl__sub_8006B370(f32);
f32 vec_squared_length(const Vec *);
f32 normalize_vector(void *);

extern f32 TObjBoss2Tunnel__data_805D9234;

f32 normalize_vector_checked(Vec *vector) {
    f32 var_f31;
    f32 temp_f0;

    var_f31 = TObjBoss2Tunnel__data_805D9234;
    if (TObjBoss2Tunnel__data_805D9234 != vec_squared_length(vector)) {
        var_f31 = normalize_vector(vector);
        if (TCameraCtrl__sub_8006B370(var_f31) != 0) {
            vector->x = var_f31 = TObjBoss2Tunnel__data_805D9234;
            vector->y = var_f31;
            vector->z = var_f31;
        }
    } else {
        temp_f0 = TObjBoss2Tunnel__data_805D9234;
        vector->x = temp_f0;
        vector->y = temp_f0;
        vector->z = temp_f0;
    }
    return var_f31;
}

}
