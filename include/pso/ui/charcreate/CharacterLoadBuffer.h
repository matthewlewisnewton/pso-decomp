#ifndef PSO_UI_CHARCREATE_CHARACTERLOADBUFFER_H
#define PSO_UI_CHARCREATE_CHARACTERLOADBUFFER_H

#include "types.h"

extern "C" {
u32 advance_character_load_buffer(s32 slot, s32 size);
void *get_character_load_buffer(s32 slot);
}

#endif
