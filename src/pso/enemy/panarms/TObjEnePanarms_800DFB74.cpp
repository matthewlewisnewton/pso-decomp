#include "types.h"
#include "pso/enemy/panarms/TObjEnePanarms_800DFB74.h"
#include "pso/enemy/TObjEnemy.h"
#include "pso/enemy/panarms/TObjEnePanarms.h"

int is_state_4_timer_expired__14TObjEnePanBARAFv(u8 *arg0) {
    u8 var_r4;
    var_r4 = 0;
    if (((s32) *(s32 *)((s8 *)arg0 + 0x378) == 4) && ((s32) *(s32 *)((s8 *)arg0 + 0x3B4) < 0)) {
        var_r4 = 1;
    }
    return var_r4;
}

u8 is_in_state_11__14TObjEnePanBARAFv(u8 *arg0) {
    return (u8) (*(s32 *)((s8 *)arg0 + 0x378) == 0xB);
}

u8 is_in_state_8__14TObjEnePanBARAFv(u8 *arg0) {
    return (u8) (*(s32 *)((s8 *)arg0 + 0x378) == 8);
}

int TObjEnePanarms__sub_800DFBC4(void* p) { return (*(u32*)((char*)p + 0x30) >> 4) & 0x1; }
