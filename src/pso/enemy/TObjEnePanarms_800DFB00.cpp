#include "pso/enemy/TObjEnePanarms.h"
#include "pso/enemy/TObjEnePanBARA.h"

extern "C" {
int fn_800660B8(void *);
void sub_8002AE64();
}

void TObjEnePanarms::init(s16 animation) {
    fn_800660B8(this);
    change_action(animation);
    sub_8002AE64();
}

s32 TObjEnePanBARA::is_in_state_7_or_8() {
    return state == 7 || state == 8;
}

int TObjEnePanBARA::get_state_flag() {
    return (actorFlags >> 4) & 1;
}
