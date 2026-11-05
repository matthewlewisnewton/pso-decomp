#include "types.h"
#include "pso/player/TObjPlayer.h"
#include "pso/TItemList.h"
#include "pso/TObject.h"
#include <stddef.h>
#include "pso/item/TItem.h"
#include "pso/misc/TOSwitchItem.h"
#include "pso/misc/TWindowActionPalette_801C1890.h"
#include "pso/player/TObjPlayer_801D5220.h"

extern "C" {
s32 item_identity_matches(void *arg0, void *arg1);
extern u8 *inventory_search_item_data;
extern s32 inventory_walk_visit_count;
extern TItem **player_owner_collect_cursor;
}
extern TObjPlayer *item_reduce_target_player;

struct Collected_801D52A8 {
    s8 mode;
    u8 pad[3];
    s32 id;
    TItemData data;
};
extern Collected_801D52A8 *player_item_collect_cursor;
s32 compare_item_data_masked(void *arg0, void *arg1, s32 arg2);
extern s32 inventory_update_field_d8_key;
extern s32 inventory_walk_progress_count;
extern "C" {

extern u8 *owned_item_export_cursor;

void TItemList::count_owned_items() {
    TItemList *down;
    TItem *temp;

    down = link_down();
    while (down != NULL) {
        if ((TItemList::is_item_valid(down) != 0) && ((temp = down->get_owner_if_alive()) != NULL) && (temp->export_inventory_entry(owned_item_export_cursor) != 0)) {
            owned_item_export_cursor += 0x1C;
            inventory_walk_visit_count += 1;
        }
        down->count_owned_items();
        down = down->link_next();
    }
}

void TObjPlayer__sub_801D52A8(TItemList *arg0) {
    TItemList *n;
    TItem *o;
    for (n = arg0->link_down(); n != NULL; n = n->link_next()) {
        if (TItemList::is_item_valid(n) != 0) {
            o = n->get_owner_if_alive();
            if ((o != NULL) && (is_item_equipped(o) != 0) && (o->get_item_type() == 0)) {
                o->copy_to_item_data(&player_item_collect_cursor->data);
                player_item_collect_cursor->id = o->get_item_id();
                player_item_collect_cursor += 1;
                inventory_walk_visit_count += 1;
            }
        }
        TObjPlayer__sub_801D52A8(n);
    }
}

void TItemList::collect_item_owners_recursive() {
    TItemList *n;
    TItem *o;
    for (n = link_down(); n != NULL; n = n->link_next()) {
        if (TItemList::is_item_valid(n) != 0) {
            o = n->get_owner_if_alive();
            if ((o != NULL) && (o->is_at_tekker() == 0)) {
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

    down = link_down();
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
        down = down->link_next();
    }
}

void TItemList::unequip_invalid_items_recursive() {
    TItemList *n;
    TItem *o;
    for (n = link_down(); n != NULL; n = n->link_next()) {
        if (TItemList::is_item_valid(n) != 0) {
            o = n->get_owner_if_alive();
            if ((o != NULL) && (is_item_equipped(o) != 0) && (o->is_unit() == 0) &&
                (TObjPlayer::get_slot_value(item_reduce_target_player->equipped_items, o->get_attach_slot()) != 0U)) {
                item_reduce_target_player->unequip_item(o);
            }
        }
        n->unequip_invalid_items_recursive();
    }
}

void TItemList::count_items_recursive() {
    TItemData sp8;
    TItemList *down;
    TItem *temp;

    down = link_down();
    while (down != NULL) {
        if ((TItemList::is_item_valid(down) != 0) && ((temp = down->get_owner_if_alive()) != NULL)) {
            temp->copy_to_item_data(&sp8);
            if (item_identity_matches(&sp8, inventory_search_item_data) != 0) {
                inventory_walk_visit_count += 1;
            }
        }
        down->count_items_recursive();
        down = down->link_next();
    }
}

TItemList *TItemList::find_inventory_item_matching_data() {
    TItemData data;
    TItemList *node;
    TItemList *found;
    TItem *owner;
    for (node = link_down(); node != NULL; node = node->link_next()) {
        if (TItemList::is_item_valid(node) != 0) {
            owner = node->get_owner_if_alive();
            if (owner != NULL) {
                owner->copy_to_item_data(&data);
                if (compare_item_data_masked(&data, inventory_search_item_data, 0) != 0) {
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
    TItemData data;
    TItemList *node;
    TItemList *found;
    TItem *owner;
    for (node = root->link_down(); node != NULL; node = node->link_next()) {
        if (TItemList::is_item_valid(node) != 0) {
            owner = node->get_owner_if_alive();
            if (owner != NULL) {
                owner->copy_to_item_data(&data);
                if (item_identity_matches(&data, inventory_search_item_data) != 0) {
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
    for (node = link_down(); node != NULL; node = node->link_next()) {
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
