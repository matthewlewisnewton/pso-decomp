#include "types.h"
#include "pso/player/TObjPlayer_8012BDA8.h"

void psycho_wand_equip(void* p) { *(s16*)((char*)p + 0x1f8) = -1; }
void psycho_wand_unequip(void* p) { *(s16*)((char*)p + 0x1f8) = -1; }
