#ifndef PSO_ITEM_ITEMCREATEFUNCTION_H
#define PSO_ITEM_ITEMCREATEFUNCTION_H

#include "types.h"

struct TItem;
struct TItemData;

// Item factory tables pass the beginning of a complete item-data record.
typedef TItem *(*ItemCreateFunction)(u8 *item);

extern "C" {
ItemCreateFunction get_weapon_factory_for_item(u8 *item);
ItemCreateFunction TLobby__sub_8010440C(u8 *item);
TItem *create_weapon_for_item(u8 *item);
TItem *TLobby__sub_801054E0(u8 *item);
}

#ifndef __MWERKS__
// Only entry 4 has a TItemData* parameter in the original table. Converting
// its stored pointer back to the declared function type makes the port call
// well-defined, rather than relying on the native byte-pointer callback ABI.
inline TItem *invoke_item_factory(ItemCreateFunction factory, u8 *item, u8 type) {
    if (type == 4) {
        typedef TItem *(*MoneyCreateFunction)(TItemData *);
        return reinterpret_cast<MoneyCreateFunction>(factory)(
            reinterpret_cast<TItemData *>(item));
    }
    return factory(item);
}
#endif

#endif
