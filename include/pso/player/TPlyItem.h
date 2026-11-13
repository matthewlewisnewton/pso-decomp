#ifndef PSO_PLAYER_TPLYITEM_H
#define PSO_PLAYER_TPLYITEM_H

#include "pso/system/task/TObject.h"
#include "pso/item/TItemData.h"
#include "types.h"
#include <stddef.h>

class TItemList;
struct TObjPlayer;

// 0x1C record of an item dropped on death; set_globals_and_notify fills
// source_id and item.
struct DeathDropRecord {
    s32 state;
    s32 source_id;
    TItemData item;
};

// Inventory object stored at TObjPlayer 0xD00.
class TPlyItem : public TObject {
public:
    virtual ~TPlyItem();
    s16 item_count;
    u16 unk_1E;
    u8 item_pool[0x1C4 - 0x20];
    TItemList *item_list;
    TObject *unk_1C8;

    void reduce_item_amount(TObjPlayer *player, TItemList *slot, s32 amount);
    s32 use_item(TObjPlayer *player, s32 item_id, s32 amount);
    void set_globals_and_update(void *player, int kind);
    int set_globals_and_notify(TObjPlayer *player, DeathDropRecord *out);
    int count_matching_items(void *out);
    int apply_shop_judgment(void *out);
    void set_flag_and_update(void *player);
    s32 count_items_by_id(void *data);
    void find_first_inventory_entry(void *a1);
    void destroy_subobjects(void *player);
    TItemList *start_inventory_update(int a1);
    int run_state_query(void *a1);
    s32 update_inventory_item(TObjPlayer *player, s32 item_id, f32 *pos, s32 amount, s32 floor);
};

#endif
