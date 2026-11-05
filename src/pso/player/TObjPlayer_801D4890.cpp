#define TOBJECT_OUT_OF_LINE_HELPERS
#include "types.h"
#include "pso/object/TObjMotion.h"
#include "pso/player/TObjPlayer.h"
#include "pso/TItemList.h"
#include "pso/TPlyItem.h"
#include "pso/item/TItem.h"
#include "pso/misc/TWindowActionPalette_801C1890.h"

extern "C" {
s32 TObjPlayer__sub_801D49F4(TPlyItem *player, TObjPlayer *arg1, s32 *arg2, s32 arg3);

    extern void *TObjPlayer__owner_field_write_cursor;
    extern int inventory_walk_visit_count;
int TPlyItem::run_and_get_result(void *a1) { TObjPlayer__owner_field_write_cursor = a1; inventory_walk_visit_count = 0; item_list->collect_owner_fields_recursive(); return inventory_walk_visit_count; }

    extern void *owned_item_export_cursor;
int TPlyItem::run_state_query(void *a1) { owned_item_export_cursor = a1; inventory_walk_visit_count = 0; item_list->count_owned_items(); return inventory_walk_visit_count; }

s32 TPlyItem::update_inventory_item(TObjPlayer *player, s32 item_id, f32 *pos, s32 amount, s32 floor) {
    s16 temp_r4;
    TItem *temp_r3_2;
    TItemList *temp_r3;

    if (amount < 0) {
        return 0;
    }
    temp_r3 = start_inventory_update(item_id);
    if (temp_r3 == NULL) {
        return 0;
    }
    temp_r3_2 = temp_r3->get_owner_if_alive();
    if (temp_r3_2 == NULL) {
        return 0;
    }
    if ((temp_r3_2->get_amount() - amount) > 0) {
        temp_r3_2->remove_amount(amount);
        return 1;
    }
    if (is_item_equipped(temp_r3_2) != 0) {
        player->unequip_item(temp_r3_2);
    }
    temp_r3_2->room = player->get_room();
    temp_r3_2->place_on_ground(floor, pos, 0);
    temp_r4 = item_count;
    item_count = temp_r4 - 1;
    temp_r3->queue_destruction();
    return 1;
}
s32 TObjPlayer__sub_801D49F4(TPlyItem *player, TObjPlayer *arg1, s32 *arg2, s32 arg3) {
    s32 i;
    TItemList *r;
    for (i = 0; i < arg3; arg2++, i++) {
        r = player->start_inventory_update(*arg2);
        if (r == NULL) {
            return 0;
        }
        player->remove_equipped_item(arg1, r);
    }
    return 1;
}

}

struct Base_801D4A6C { char pad[0x18]; };
struct VObj_801D4A6C : Base_801D4A6C {
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual void m3();
    virtual void m4();
    virtual void m5();
    virtual void m6();
    virtual void m7();
    virtual void m8();
    virtual void m9();
    virtual void m10();
    virtual void m11();
    virtual void m12();
    virtual void m13();
    virtual void m14();
    virtual void m15();
    virtual void m16();
    virtual void m17();
    virtual void m18();
    virtual void m19();
    virtual void m20();
    virtual void m21();
    virtual void m22();
    virtual void m23();
    virtual void m24();
    virtual void m25();
    virtual void m26();
    virtual void m27(s16);
};

void TPlyItem::remove_equipped_item(TObjPlayer *arg1, TItemList *arg2) {
    s16 temp_r4;
    TItem *temp_r3;

    temp_r3 = arg2->get_owner_if_alive();
    if (temp_r3 != NULL) {
        if (((s32 (*)()) is_item_equipped)() != 0) {
            arg1->unequip_item(temp_r3);
        }
        temp_r4 = item_count;
        item_count = temp_r4 - 1;
        ((VObj_801D4A6C *)temp_r3)->m27(temp_r4);
        arg2->queue_destruction();
    }
}
