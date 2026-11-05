#ifndef PSO_MISC_RADARCOMPASS_H
#define PSO_MISC_RADARCOMPASS_H

#include "types.h"
#include "pso/system/CurrentTextureList.h"

extern "C" {
// Existing four-byte BSS slot; its texture list remains owned by the loader.
extern GinjaTextureList *TRaderMapCore__data_805D5F4C;
// The original caller passes its field at 0x90; this helper does not read it.
s32 apply_compass_param__13TRaderMapCoreFv(const s32 *ignored);
}

#endif
