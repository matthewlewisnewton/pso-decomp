#ifndef PSO_SYSTEM_RANDOMRATIO_H
#define PSO_SYSTEM_RANDOMRATIO_H

#include "types.h"

// The caller supplies a subtractive-generator state, including embedded states.
// Its complete layout is still represented locally by the generator provider.
extern "C" f32 calc_random_ratio__10TObjPlayerFv(void *state);

#endif
