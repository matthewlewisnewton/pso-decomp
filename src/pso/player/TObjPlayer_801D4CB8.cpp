#define TOBJECT_OUT_OF_LINE_HELPERS
#include "types.h"
#include "pso/object/TObject_80019A50.h"
#include "pso/player/TObjPlayer_801D4CB8.h"
#include "pso/player/TObjPlayer.h"
#include "pso/TItemList.h"
#include "pso/TPlyItem.h"

    extern s32 inventory_walk_visit_count;
    extern s32 player_owner_collect_cursor;
int TPlyItem::count_matching_items(int a1) { player_owner_collect_cursor = a1; inventory_walk_visit_count = 0; item_list->collect_item_owners_recursive(); return inventory_walk_visit_count; }

int TPlyItem::apply_shop_judgment(int a1) { player_owner_collect_cursor = a1; inventory_walk_visit_count = 0; item_list->collect_alive_owners(); return inventory_walk_visit_count; }

    extern void *item_reduce_target_player;
void TPlyItem::set_flag_and_update(void *a1) { item_reduce_target_player = a1; item_list->unequip_invalid_items_recursive(); }

struct Base_801D4D48 { char pad[0x18]; };
struct VObj_801D4D48 : Base_801D4D48 {
#define V8(b) virtual void b##0(); virtual void b##1(); virtual void b##2(); virtual void b##3(); virtual void b##4(); virtual void b##5(); virtual void b##6(); virtual void b##7();
    V8(a) V8(b) V8(c) V8(d)
    virtual void p32(); virtual void p33();
    virtual s32 m34();
};

extern "C" {

s32 lookup_item_def__9TItemDataFPv(s32);
s32 all_parents_unqueued_for_destruction__7TObjectFv();

extern s32 inventory_search_item_data;

s32 TPlyItem::count_items_by_id(s32 arg1) {
    void *temp_r3;
    TItemList *slot;

    if (lookup_item_def__9TItemDataFPv(arg1) != 0) {
        slot = set_mode_and_refresh_object((void *)arg1);
        if (slot != NULL) {
            temp_r3 = slot->get_owner_if_alive();
            if ((temp_r3 != NULL) && (all_parents_unqueued_for_destruction__7TObjectFv() != 0)) {
                return ((VObj_801D4D48 *)temp_r3)->m34();
            }
        }
        return 0;
    }
    inventory_search_item_data = arg1;
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

TItemList *TPlyItem::find_first_inventory_entry(void *a1) { inventory_search_item_data = (s32)a1; return item_list->find_inventory_item_matching_data(); }

TItemList *TPlyItem::set_mode_and_refresh_object(void *a1) { inventory_search_item_data = (s32)a1; return find_matching_inventory_item_node(item_list); }

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
