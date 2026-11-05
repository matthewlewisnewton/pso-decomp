#include "types.h"
#include "pso/enemy/TObjEneDD.h"
#pragma fp_contract on

extern "C" {

f32 random_ratio__9TObjCharaFv();

f32 TObjEneDD::rand_range(f32 farg0, f32 farg1) {
    return ((farg1 - farg0) * random_ratio__9TObjCharaFv()) + farg0;
}

}
