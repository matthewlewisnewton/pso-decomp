#include "types.h"
#include "pso/player/TObjPlayer.h"
#include "pso/TItemList.h"
#include "pso/TObject.h"
#include <stddef.h>
#include "pso/item/TItem.h"
#include "pso/misc/TOSwitchItem.h"

extern "C" {
s32 item_identity_matches(void *arg0, void *arg1);
extern u8 *inventory_search_item_data;
TItemList *find_matching_inventory_item_node(TItemList *root);
s32 is_at_tekker__5TItemFv();
extern s32 inventory_walk_visit_count;
extern TItem **player_owner_collect_cursor;
s32 is_item_equipped();
extern u8 *player_item_collect_cursor;
void TObjPlayer__sub_801D52A8(TItemList *arg0);
void unequip_item__10TObjPlayerFiPv(s32 arg0, void *arg1);
s32 get_slot_value__10TObjPlayerFPvi(s32 *arg0, s32 arg1);
}
extern s32 item_reduce_target_player;
s32 compare_item_data_masked(void *arg0, void *arg1, s32 arg2);
extern s32 inventory_update_field_d8_key;
extern s32 inventory_walk_progress_count;
extern "C" {

extern u8 *owned_item_export_cursor;

void TItemList::count_owned_items() {
    TItemList *down;
    TItem *temp;

    down = m_down;
    while (down != NULL) {
        if ((TItemList::is_item_valid(down) != 0) && ((temp = down->get_owner_if_alive()) != NULL) && (temp->export_inventory_entry(owned_item_export_cursor) != 0)) {
            owned_item_export_cursor += 0x1C;
            inventory_walk_visit_count += 1;
        }
        down->count_owned_items();
        down = down->m_next;
    }
}

void TObjPlayer__sub_801D52A8(TItemList *arg0) {
    TItemList *n;
    TItem *o;
    for (n = arg0->m_down; n != NULL; n = n->m_next) {
        if (TItemList::is_item_valid(n) != 0) {
            o = n->get_owner_if_alive();
            if ((o != NULL) && (is_item_equipped() != 0) && (o->get_item_type() == 0)) {
                o->copy_to_item_data((TItemData *)(player_item_collect_cursor + 8));
                *(s32 *)(player_item_collect_cursor + 4) = o->get_item_id();
                player_item_collect_cursor += 0x1C;
                inventory_walk_visit_count += 1;
            }
        }
        TObjPlayer__sub_801D52A8(n);
    }
}

void TItemList::collect_item_owners_recursive() {
    TItemList *n;
    TItem *o;
    for (n = m_down; n != NULL; n = n->m_next) {
        if (TItemList::is_item_valid(n) != 0) {
            o = n->get_owner_if_alive();
            if ((o != NULL) && (is_at_tekker__5TItemFv() == 0)) {
                *player_owner_collect_cursor = o;
                player_owner_collect_cursor += 1;
                inventory_walk_visit_count += 1;
            }
        }
        n->collect_item_owners_recursive();
    }
}

void TItemList::collect_alive_owners() {
    TItem *temp_r3;
    TItemList *down;

    down = m_down;
    while (down != NULL) {
        if (TItemList::is_item_valid(down) != 0) {
            temp_r3 = down->get_owner_if_alive();
            if (temp_r3 != NULL) {
                *player_owner_collect_cursor = temp_r3;
                player_owner_collect_cursor += 1;
                inventory_walk_visit_count += 1;
            }
        }
        down->collect_alive_owners();
        down = down->m_next;
    }
}

void TItemList::unequip_invalid_items_recursive() {
    TItemList *n;
    TItem *o;
    for (n = m_down; n != NULL; n = n->m_next) {
        if (TItemList::is_item_valid(n) != 0) {
            o = n->get_owner_if_alive();
            if ((o != NULL) && (is_item_equipped() != 0) && (o->is_unit() == 0) &&
                (get_slot_value__10TObjPlayerFPvi((s32 *)(item_reduce_target_player + 0xD04), o->get_attach_slot()) != 0U)) {
                unequip_item__10TObjPlayerFiPv(item_reduce_target_player, o);
            }
        }
        n->unequip_invalid_items_recursive();
    }
}

void TItemList::count_items_recursive() {
    s32 sp8[7];
    TItemList *down;
    TItem *temp;

    down = m_down;
    while (down != NULL) {
        if ((TItemList::is_item_valid(down) != 0) && ((temp = down->get_owner_if_alive()) != NULL)) {
            temp->copy_to_item_data((TItemData *)&sp8[0]);
            if (item_identity_matches(&sp8[0], inventory_search_item_data) != 0) {
                inventory_walk_visit_count += 1;
            }
        }
        down->count_items_recursive();
        down = down->m_next;
    }
}

TItemList *TItemList::find_inventory_item_matching_data() {
    s32 data[8];
    TItemList *node;
    TItemList *found;
    TItem *owner;
    for (node = m_down; node != NULL; node = node->m_next) {
        if (TItemList::is_item_valid(node) != 0) {
            owner = node->get_owner_if_alive();
            if (owner != NULL) {
                owner->copy_to_item_data((TItemData *)data);
                if (compare_item_data_masked(data, inventory_search_item_data, 0) != 0) {
                    return node;
                }
            }
        }
        found = node->find_inventory_item_matching_data();
        if (found != NULL) {
            return found;
        }
    }
    return NULL;
}

TItemList *find_matching_inventory_item_node(TItemList *root) {
    s32 data[8];
    TItemList *node;
    TItemList *found;
    TItem *owner;
    for (node = root->m_down; node != NULL; node = node->m_next) {
        if (TItemList::is_item_valid(node) != 0) {
            owner = node->get_owner_if_alive();
            if (owner != NULL) {
                owner->copy_to_item_data((TItemData *)data);
                if (item_identity_matches(data, inventory_search_item_data) != 0) {
                    return node;
                }
            }
        }
        found = find_matching_inventory_item_node(node);
        if (found != NULL) {
            return found;
        }
    }
    return NULL;
}

TItemList *TItemList::find_inventory_item_by_field_d8() {
    TItemList *node;
    TItemList *found;
    TItem *owner;
    for (node = m_down; node != NULL; node = node->m_next) {
        if (TItemList::is_item_valid(node) != 0) {
            owner = node->get_owner_if_alive();
            if (owner != NULL) {
                if (inventory_update_field_d8_key == owner->get_item_id()) {
                    return node;
                }
                inventory_walk_progress_count += 1;
            }
        }
        found = node->find_inventory_item_by_field_d8();
        if (found != NULL) {
            return found;
        }
    }
    return NULL;
}

typedef char TItemList_next_at_c[(offsetof(TItemList, m_next) == 0xC) ? 1 : -1];
typedef char TItemList_down_at_14[(offsetof(TItemList, m_down) == 0x14) ? 1 : -1];
typedef char TItemList_item_at_1c[(offsetof(TItemList, item) == 0x1C) ? 1 : -1];

TItem *TItemList::get_owner_if_alive() {
    if (item->all_parents_unqueued_for_destruction() != 0) {
        return item;
    }
    return NULL;
}
void TItemList::set_field_1c(TItem *v) { item = v; }
}
