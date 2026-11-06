#include "types.h"
#include "pso/player/TObjPlayer_80121010.h"

extern "C" {

s32 (*get_weapon_factory_for_item())(s32);

s32 create_weapon_for_item(s32 arg0) {
    if (arg0 != 0) {
        s32 (*fp)(s32) = get_weapon_factory_for_item();
        return fp(arg0);
    }
    return 0;
}

}
