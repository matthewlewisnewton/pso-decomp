#include "pso/enemy/TObjEnePanarms.h"
#include "pso/enemy/TObjEnePanBARA.h"

extern "C" {
int fn_800660B8(void *);
int apply_animation_transition(void *, void *);
void sub_8002AE64();
}

void TObjEnePanarms::init(void *animation) {
    fn_800660B8(this);
    apply_animation_transition(this, animation);
    sub_8002AE64();
}

s32 TObjEnePanBARA::fn_800DFB44() {
    return state == 7 || state == 8;
}

int TObjEnePanBARA::get_state_flag() {
    return (actorFlags >> 4) & 1;
}
