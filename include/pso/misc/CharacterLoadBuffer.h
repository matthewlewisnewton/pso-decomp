#ifndef PSO_MISC_CHARACTERLOADBUFFER_H
#define PSO_MISC_CHARACTERLOADBUFFER_H

#include "types.h"

// Native slot cursors use 32-bit address words. These helpers preserve the
// existing arithmetic and validation; the first argument is a numeric slot.
extern "C" {
extern u32 chr_select_load_buffer_base;
extern u32 chr_select_load_buffer;
u32 advance_character_load_buffer(s32 slot, s32 size);
void *get_character_load_buffer(s32 slot);
}

#endif
