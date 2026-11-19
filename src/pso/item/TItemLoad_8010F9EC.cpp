#include "pso/item/TUnk_8049F42C.h"
#include "types.h"
#include "pso/system/data/FlagWord.h"
#include "pso/item/TItemLoad.h"
#include "pso/ui/frontend/TAdRicoRing.h"
#include "pso/player/TObjPlayer.h"

extern "C" {

s32 test_flags_any(s32 *flags, s32 mask);

extern s32 item_load_work_buffer_busy;

void TUnk_8049F42C::reset_ring_state() {
    u8 *arg0 = (u8 *)this;
    if (test_flags_any((s32 *)(arg0 + 0x1C), 4) != 0) {
        item_load_work_buffer_busy = 0;
        ((FlagWord *)(arg0 + 0x1C))->clear(4);
    }
    *(s32 *)((s8 *)arg0 + 0x18) = 0;
    ((FlagWord *)(arg0 + 0x1C))->reset();
}

void TUnk_8049F42C::update_state() {

    switch (*(s32 *)((s8 *)this + 0x18)) {
    case 1:
        advance_load_state();
        return;
    case 2:
        update_ring();
        return;
    case 4:
        vfunc_3();
    case 3:
        return;
    }
}

}
