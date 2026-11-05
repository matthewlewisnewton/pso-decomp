#include "types.h"
#include "pso/enemy/TObjEnePanarms_800DFB74.h"
#include "pso/enemy/TObjEnemy.h"
#include "pso/enemy/TObjEnePanarms.h"
#include "pso/enemy/TObjEnePanBARA.h"

int TObjEnePanBARA::is_state_4_timer_expired() {
    u8 result = 0;
    if (state == 4 && action_timer < 0) {
        result = 1;
    }
    return result;
}

int TObjEnePanBARA::is_in_state_11() { return (u8)(state == 11); }

int TObjEnePanBARA::is_in_state_8() { return (u8)(state == 8); }

int TObjEnePanarms__sub_800DFBC4(void* p) { return (*(u32*)((char*)p + 0x30) >> 4) & 0x1; }
