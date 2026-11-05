#define TOBJECT_OUT_OF_LINE_HELPERS
#include "types.h"
#include "pso/TPlyItem.h"
#include "pso/misc/TLobby.h"
#include "pso/player/TObjPlayer.h"
#include "pso/TItemList.h"
#include "pso/item/TItem.h"

extern "C" {

void TLobby__sub_801D4C28(TPlyItem *a0, void *a1, int a2, int a3);
s32 try_spend_actor_meseta(TObjPlayer *player, s32 amount);
s32 is_item_equipped(void *);
int TObjPlayer__sub_801D52A8(void*);

void TPlyItem::reduce_item_amount(TObjPlayer *arg1, TItemList *slot, s32 arg3) {
    s16 temp_r4;
    TItem *item;

    item = slot->get_owner_if_alive();
    if ((item != NULL) && (arg3 >= 0)) {
        if ((item->get_amount() - arg3) > 0) {
            item->remove_amount(arg3);
            return;
        }
        if (is_item_equipped(item) != 0) {
            arg1->unequip_item(item);
        }
        temp_r4 = item_count;
        item_count = temp_r4 - 1;
        item->destroy();
        slot->queue_destruction();
    }
}

s32 TPlyItem::use_item(TObjPlayer *player, s32 arg2, s32 arg3) {
    TItemList *temp_r3;

    if (arg2 == -1) {
        try_spend_actor_meseta(player, arg3);
        return 1;
    }
    temp_r3 = start_inventory_update(arg2);
    if (temp_r3 == NULL) {
        return 0;
    }
    reduce_item_amount(player, temp_r3, arg3);
    return 1;
}

    extern void *item_reduce_target_player;
    extern unsigned char item_reduce_owner_match_field_ec;
    extern unsigned char reduce_owner_match_id;
void TLobby__sub_801D4C28(TPlyItem *a0, void *a1, int a2, int a3) { item_reduce_target_player = a1; item_reduce_owner_match_field_ec = a2; reduce_owner_match_id = a3; a0->item_list->reduce_owner_matched_items(); }

void TPlyItem::set_globals_and_update(void *a1, int a2) { item_reduce_target_player = a1; item_reduce_owner_match_field_ec = a2; item_list->reduce_child_item_amounts(); }

    extern int player_item_collect_cursor;
    extern int inventory_walk_visit_count;
int TLobby::set_globals_and_notify(int a1, int a2) { player_item_collect_cursor = a2; inventory_walk_visit_count = 0; TObjPlayer__sub_801D52A8((void*)(*(int*)((char*)this + 0x1c4))); return inventory_walk_visit_count; }

}
