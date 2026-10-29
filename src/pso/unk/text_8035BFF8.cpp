#include "pso/system/vector.h"
#include <dolphin/mtx.h>
#include "pso/unk/text_8035BFF8.h"
#include "types.h"
#include "pso/boss/TObjBoss2Tunnel.h"

extern "C" {
s32 VecCopy__FP3VecPC3Vec(void *);
extern const f32 lbl_805E0168;
s32 fn_8035BFF8(void) {
    Vec position;
    VecCopy__FP3VecPC3Vec(&position.x);
    return normalize_vector_xz((Vec *)(&position.x)) > lbl_805E0168;
}

}
