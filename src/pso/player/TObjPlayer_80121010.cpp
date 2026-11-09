#include "types.h"
#include "pso/player/TObjPlayer_80121010.h"

extern "C" {

TItem *create_weapon_for_item(u8 *item) {
    if (item != 0) {
        ItemCreateFunction factory = get_weapon_factory_for_item(item);
        return factory(item);
    }
    return 0;
}

}
