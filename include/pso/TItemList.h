#ifndef PSO_TITEMLIST_H
#define PSO_TITEMLIST_H
#include "pso/TObject.h"
#include "types.h"

struct TItem;

// Same 0x20-byte TObject prefix as an inventory slot (__ct__9TItemListFv), but
// the sibling and child links are TItemList so a walk does not downcast.
// The vptr stays at 0x18, where that constructor writes __vt__9TItemList.
class TItemList {
public:
    const char *m_name;
    u16 m_flags;
    u16 m_id;
    TItemList *m_prev;
    TItemList *m_next;
    TItemList *m_up;
    TItemList *m_down;
    virtual ~TItemList();
    // pickup_item stores the TItem here. get_owner_if_alive returns it while
    // that item is still live.
    TItem *item;
    TItem *get_owner_if_alive();
    void set_field_1c(TItem *v);
    void count_owned_items();
    void collect_item_owners_recursive();
    void collect_alive_owners();
    void unequip_invalid_items_recursive();
    void count_items_recursive();
    TItemList *find_inventory_item_matching_data();
    TItemList *find_inventory_item_by_field_d8();
public:
    static s32 is_item_valid(s32 arg0);
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

#endif
