#define TOBJECT_OUT_OF_LINE_HELPERS
#include "types.h"
#include "pso/object/TObject_80019A50.h"
#include "pso/player/TObjPlayer_801D4CB8.h"
#include "pso/player/TObjPlayer.h"
#include "pso/TItemList.h"
#include "pso/TPlyItem.h"
#include "pso/item/TItem.h"
#include "pso/item/TItemData.h"

    extern s32 inventory_walk_visit_count;
    extern void *player_owner_collect_cursor;
int TPlyItem::count_matching_items(void *out) { player_owner_collect_cursor = out; inventory_walk_visit_count = 0; item_list->collect_item_owners_recursive(); return inventory_walk_visit_count; }

int TPlyItem::apply_shop_judgment(void *out) { player_owner_collect_cursor = out; inventory_walk_visit_count = 0; item_list->collect_alive_owners(); return inventory_walk_visit_count; }

    extern void *item_reduce_target_player;
void TPlyItem::set_flag_and_update(void *a1) { item_reduce_target_player = a1; item_list->unequip_invalid_items_recursive(); }

extern "C" {

s32 all_parents_unqueued_for_destruction__7TObjectFv();

extern void *inventory_search_item_data;

s32 TPlyItem::count_items_by_id(void *data) {
    TItem *owner;
    TItemList *slot;

    if (TItemData::lookup_item_def(data) != 0) {
        slot = set_mode_and_refresh_object(data);
        if (slot != NULL) {
            owner = slot->get_owner_if_alive();
            if ((owner != NULL) && (owner->all_parents_unqueued_for_destruction() != 0)) {
                return owner->get_amount();
            }
        }
        return 0;
    }
    inventory_search_item_data = data;
    inventory_walk_visit_count = 0;
    item_list->count_items_recursive();
    return inventory_walk_visit_count;
}

}

struct VB_801D4E94 { u8 pad[0x18]; };

struct V_801D4E94 : VB_801D4E94 {
    virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3();
    virtual void m4(); virtual void m5(); virtual void m6(); virtual void m7();
    virtual void m8(); virtual void m9(); virtual void m10(); virtual void m11();
    virtual void m12(); virtual void m13(); virtual void m14(); virtual void m15();
    virtual void m16(); virtual void m17(); virtual void m18(); virtual void m19();
    virtual void m20(); virtual void m21(); virtual void m22(); virtual void m23();
    virtual void m24(); virtual void m25(); virtual void m26(); virtual void m27();
};

extern "C" {
TItemList *find_matching_inventory_item_node(TItemList *);

TItemList *TPlyItem::find_first_inventory_entry(void *a1) { inventory_search_item_data = a1; return item_list->find_inventory_item_matching_data(); }

TItemList *TPlyItem::set_mode_and_refresh_object(void *a1) { inventory_search_item_data = a1; return find_matching_inventory_item_node(item_list); }

    extern s32 inventory_walk_progress_count;
void TPlyItem::destroy_subobjects(void *a1) { item_reduce_target_player = a1; inventory_walk_progress_count = 0; item_list->destroy_subobjects_recursive(); item_list->queue_destruction(); unk_1C8->run_tasks(); unk_1C8->run_tasks(); unk_1C8->queue_destruction(); }

    extern s32 inventory_update_field_d8_key;

void TItemList::destroy_subobjects_recursive() {
    TItemList *p;
    V_801D4E94 *o;
    p = link_down();
    while (p != NULL) {
        if (TItemList::is_item_valid(p) != 0) {
            o = (V_801D4E94 *)p->get_owner_if_alive();
            if (o != NULL && all_parents_unqueued_for_destruction__7TObjectFv() != 0) {
                o->m27();
            }
        }
        p->destroy_subobjects_recursive();
        p = p->link_next();
    }
}

TItemList *TPlyItem::start_inventory_update(int a1) {
    inventory_update_field_d8_key = a1;
    inventory_walk_progress_count = 0;
    return item_list->find_inventory_item_by_field_d8();
}

}
