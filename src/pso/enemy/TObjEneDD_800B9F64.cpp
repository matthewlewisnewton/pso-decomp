#include "types.h"
#include "pso/enemy/TObjEneDD.h"

extern "C" {


extern f32 lbl_805D9E94;

s32 TObjEneDD::get_random_scaled() {
    return (s32) (lbl_805D9E94 * random_ratio());
}

}
