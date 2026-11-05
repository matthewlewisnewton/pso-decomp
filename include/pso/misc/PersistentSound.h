#ifndef PSO_MISC_PERSISTENTSOUND_H
#define PSO_MISC_PERSISTENTSOUND_H

#include "types.h"
struct Vec;

extern "C" {
s32 play_persistent_sound(s32 id, const void *identity, const Vec *position, s32 adjustment, s32 flags);
}

#endif
