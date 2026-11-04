#ifndef PSO_TPLYITEM_H
#define PSO_TPLYITEM_H

#include "pso/TObject.h"
#include "types.h"
#include <stddef.h>

class TItemList;
struct TObjPlayer;

// Inventory object stored at TObjPlayer::inventory_objects (0xD00).
// TPlyItem__ct clears the count at +0x1C. create_inventory stores the
// item-slot list at +0x1C4 and a child TObject at +0x1C8.
class TPlyItem : public TObject {
public:
    virtual ~TPlyItem();
    s16 item_count;
    u16 unk_1E;
    u8 pad_20[0x1C4 - 0x20];
    TItemList *item_list;
    TObject *unk_1C8;

    void reduce_item_amount(TObjPlayer *player, TItemList *slot, s32 amount);
    s32 use_item(TObjPlayer *player, s32 item_id, s32 amount);
    void set_globals_and_update(int player, int kind);
};

typedef char TPlyItemCountAt1C[(offsetof(TPlyItem, item_count) == 0x1C) ? 1 : -1];
typedef char TPlyItemListAt1C4[(offsetof(TPlyItem, item_list) == 0x1C4) ? 1 : -1];
typedef char TPlyItemChildAt1C8[(offsetof(TPlyItem, unk_1C8) == 0x1C8) ? 1 : -1];

#endif
