#include "pso/item/TItemDrop_80105D0C.h"
#include "pso/misc/TLobby.h"

extern "C" s32 item_drop_rng;

u32 TLobby::clamp_min_drop(u32 minimum, u32 limit) {
    u32 value = item_drop_rng_below(item_drop_rng, limit);
    if (value < minimum) {
        value = minimum;
    }
    return value;
}
