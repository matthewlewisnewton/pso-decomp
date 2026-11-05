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
    void set_globals_and_update(void *player, int kind);
    // Collects the inventory items into out; player is unused.
    int set_globals_and_notify(TObjPlayer *player, void *out);
    // First argument of the old free function is this inventory object.
    void remove_equipped_item(TObjPlayer *player, TItemList *slot);
    // Both store the matching TItem pointers into out and return the count.
    int count_matching_items(void *out);
    int apply_shop_judgment(void *out);
    void set_flag_and_update(void *player);
    s32 count_items_by_id(void *data);
    TItemList *find_first_inventory_entry(void *a1);
    TItemList *set_mode_and_refresh_object(void *a1);
    void destroy_subobjects(void *player);
    TItemList *start_inventory_update(int a1);
    // Stores the inventory items' ids into out and returns the count.
    int run_and_get_result(s32 *out);
    int run_state_query(void *a1);
    // Drops amount of the item with item_id at pos on floor.
    s32 update_inventory_item(TObjPlayer *player, s32 item_id, f32 *pos, s32 amount, s32 floor);
};

typedef char TPlyItemCountAt1C[(offsetof(TPlyItem, item_count) == 0x1C) ? 1 : -1];
typedef char TPlyItemListAt1C4[(offsetof(TPlyItem, item_list) == 0x1C4) ? 1 : -1];
typedef char TPlyItemChildAt1C8[(offsetof(TPlyItem, unk_1C8) == 0x1C8) ? 1 : -1];

// State the TPlyItem entry points set up for the TItemList walks.
extern s32 inventory_walk_visit_count;
extern s32 inventory_walk_progress_count;
extern s32 inventory_update_field_d8_key;
extern u8 item_reduce_owner_match_field_ec;
extern u8 reduce_owner_match_id;
extern s32 *TObjPlayer__owner_field_write_cursor;

#endif
