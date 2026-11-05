#ifndef PSO_TITEMLIST_H
#define PSO_TITEMLIST_H
#include "pso/TObject.h"
#include "types.h"
#include <stddef.h>

struct TItem;

// Inventory slot. __ct__9TItemListFv writes __vt__9TItemList (0x18 bytes, the
// same four TObject virtuals) at 0x18 and the owned TItem at 0x1C, so this is
// a TObject plus one pointer. Children and siblings are TItemList nodes.
// Walks load those links with link_down / link_next.
class TItemList : public TObject {
public:
    // pickup_item stores the TItem here. get_owner_if_alive returns it while
    // that item is still live. Declared before the override so MWCC does not
    // insert another vptr ahead of it; the vptr stays TObject's at 0x18.
    TItem *item;
    virtual ~TItemList();
    // Inherited m_down / m_next are TObject *. Inventory children are
    // TItemList slots. Class-body inline: -inline noauto folds each call
    // to the lwz of that link. -inline off leaves a call.
    TItemList *link_down() { return static_cast<TItemList *>(m_down); }
    TItemList *link_next() { return static_cast<TItemList *>(m_next); }
    TItem *get_owner_if_alive();
    void set_field_1c(TItem *v);
    void count_owned_items();
    void collect_item_owners_recursive();
    void collect_alive_owners();
    void unequip_invalid_items_recursive();
    void count_items_recursive();
    TItemList *find_inventory_item_matching_data();
    TItemList *find_inventory_item_by_field_d8();
    void destroy_subobjects_recursive();
public:
    static s32 is_item_valid(TItemList *node);
    void reduce_owner_matched_items();
    void reduce_child_item_amounts();
    void collect_owner_fields_recursive();
    void *dt(s16 arg1);
    void *init_items();
    void *init_array();
    static void *create_node(void *arg0, void *arg1, void *arg2, s8 arg3);
    void *destroy(s16 arg1);
    int copy_item_data();
    void lookup_entry_by_count(s32 arg1);
    u8 get_item_count();
    void run_item_count_update();
public:
    u8 *ct_init_placement_ring(u8 *arg1, s32 arg2, u8 *arg3, u8 *arg4, s8 arg5);
};

typedef char TItemListItemAt1C[(offsetof(TItemList, item) == 0x1C) ? 1 : -1];
typedef char TItemListSize[(sizeof(TItemList) == 0x20) ? 1 : -1];

#endif
