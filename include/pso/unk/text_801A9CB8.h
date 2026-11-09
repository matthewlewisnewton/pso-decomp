#ifndef PSO_UNK_TEXT_801A9CB8_H
#define PSO_UNK_TEXT_801A9CB8_H

#include "types.h"

class TObjChara;

extern "C" {
TObjChara *find_entity_by_id(u16 identity);
s32 get_current_floor();
s32 is_split_screen();
u16 get_entity_id(void *object);
s32 get_photon_blast_chain(void *output, s32 player);
// Address 0x801A9E10, inside text_801A9CB8's unit. Not yet a recovered method.
s32 TObjPlayer__sub_801A9E10(void *obj, int id, void *slots, void *counts, int animated, int delay);
}

#endif
