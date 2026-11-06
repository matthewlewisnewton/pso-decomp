#include "types.h"
#include "pso/player/TObjPlayer_801BF8EC.h"
#include "pso/misc/TMainCursor.h"
#include "pso/misc/TWindowSubStatusDisp.h"
#include "pso/player/TObjPlayer.h"

void set_equip_slot_entry(s32 arg0, s32 arg1, s32 arg2) {
    *(s32 *)((s8 *)arg0 + (arg1 * 4)) = arg2;
}

void TObjPlayer__sub_801BF8F8(s32 *p) {
    s32 i;
    for (i = 0; i < 13; i++) {
        *p++ = 0;
    }
}

void TObjPlayer__sub_801BF914(void) {  }
