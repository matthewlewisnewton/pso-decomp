#include "types.h"
#include "pso/npc/TObjNpcEnemy.h"

extern "C" {
extern s32 debug_text_global_count;
void TObjNpcEnemy::set_global_count(s32 arg0) {
    debug_text_global_count = arg0;
}
}
