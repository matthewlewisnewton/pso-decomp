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
}

#endif
