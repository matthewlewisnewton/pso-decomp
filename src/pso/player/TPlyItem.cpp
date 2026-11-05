#include "pso/TPlyItem.h"
#include "pso/item/TItemList.h"
#include "pso/item/TItem.h"
#include "pso/TItemList.h"
#include "pso/player/TObjPlayer.h"

#include "types.h"

extern "C" {
extern TObjPlayer *item_reduce_target_player;
}

TPlyItem::~TPlyItem() {
    TItemList__sub_801D5B10(item_pool, -1);
}

#include "pso/misc/TLobby.h"
#include "pso/player/TObjPlayer.h"
#include "pso/TItemList.h"
#include "pso/misc/TOSwitchItem.h"

extern void *TPlyItem_name_ref;

TPlyItem::TPlyItem(TObject *parent) : TObject(parent) {
    ((TItemList *)item_pool)->init_items();
    *(void **)&m_name = TPlyItem_name_ref;
    item_count = 0;
    unk_1E = 0;
}

void TItemList::reduce_owner_matched_items() {
    TItem *owner;
    TItemList *it;
    TObjPlayer *player;
    for (it = link_down(); it != NULL; it = it->link_next()) {
        if (TItemList::is_item_valid(it) != 0) {
            owner = it->get_owner_if_alive();
            if (owner != NULL && item_reduce_owner_match_field_ec == owner->get_item_type() &&
                reduce_owner_match_id == owner->get_item_group()) {
                if (item_reduce_owner_match_field_ec == 3) {
                    player = item_reduce_target_player;
                    player->inventory_objects->reduce_item_amount(player, it, owner->get_amount());
                } else {
                    item_reduce_target_player->inventory_objects->reduce_item_amount(item_reduce_target_player, it, 1);
                }
            }
        }
        it->reduce_child_item_amounts();
    }
}
void TItemList::reduce_child_item_amounts() {
    TItem *owner;
    TItemList *it;
    TObjPlayer *player;
    for (it = link_down(); it != NULL; it = it->link_next()) {
        if (TItemList::is_item_valid(it) != 0) {
            owner = it->get_owner_if_alive();
            if (owner != NULL && item_reduce_owner_match_field_ec == owner->get_item_type()) {
                if (item_reduce_owner_match_field_ec == 3) {
                    player = item_reduce_target_player;
                    player->inventory_objects->reduce_item_amount(player, it, owner->get_amount());
                } else {
                    item_reduce_target_player->inventory_objects->reduce_item_amount(item_reduce_target_player, it, 1);
                }
            }
        }
        it->reduce_child_item_amounts();
    }
}
void TItemList::collect_owner_fields_recursive() {
    TItemList *it;
    TItem *owner;
    for (it = link_down(); it != NULL; it = it->link_next()) {
        if (TItemList::is_item_valid(it) != 0 && (owner = it->get_owner_if_alive()) != NULL) {
            *TObjPlayer__owner_field_write_cursor++ = owner->get_item_id();
            inventory_walk_visit_count++;
        }
        it->collect_owner_fields_recursive();
    }
}
