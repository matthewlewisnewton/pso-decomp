#include "types.h"
#include "pso/system/vector.h"

#pragma fp_contract on

extern "C" {

int TCameraCtrl__sub_8006B370(f32 farg0);
f32 newton_sqrtf(f32);

extern const f32 TObjBoss2Tunnel__data_805D9234;
extern const f32 lbl_805D923C;

}

f32 normalize_vector_xz(Vec *vector) {
    f32 temp_f31;
    f32 temp_f30;
    f32 temp_f29;
    f32 temp_f28;

    temp_f30 = vector->z;
    temp_f31 = vector->x;
    temp_f29 = (temp_f31 * temp_f31) + (temp_f30 * temp_f30);
    if (TObjBoss2Tunnel__data_805D9234 != temp_f29) {
        temp_f28 = lbl_805D923C / newton_sqrtf(temp_f29);
        if (TCameraCtrl__sub_8006B370(temp_f28) != 0) {
            vector->x = (f32) TObjBoss2Tunnel__data_805D9234;
            vector->z = (f32) TObjBoss2Tunnel__data_805D9234;
            return TObjBoss2Tunnel__data_805D9234;
        }
        vector->x = (f32) (temp_f31 * temp_f28);
        vector->z = (f32) (temp_f30 * temp_f28);
        return temp_f29 * temp_f28;
    }
    vector->x = (f32) TObjBoss2Tunnel__data_805D9234;
    vector->z = (f32) TObjBoss2Tunnel__data_805D9234;
    return TObjBoss2Tunnel__data_805D9234;
}
