#include "pso/system/ArrayAllocation.h"
#include "types.h"
#include "pso/TItemList.h"
#include "pso/item/TItem.h"
#include "pso/item/TItemData.h"
#include <stddef.h>
#include "pso/misc/TKeyBoardControl_8000F764.h"
#include "pso/misc/TLobby_8030A6A8.h"
#include "pso/ui/TAdSinglePlyChrSelectGC_801FBF54.h"
#include "pso/unk/text_801D40D4.h"
#include "pso/system/memory.h"
#include "pso/player/TObjPlayer.h"
#include "pso/TPlyItem.h"
#include "pso/TPlyInventory.h"
#include "pso/item/TItemProShield.h"
#include "pso/ui/TAdSinglePlyChrSelectGC.h"
#include "pso/misc/TCameraCtrl.h"
#include "pso/TTecCtrl.h"
#include "pso/misc/TWindowActionPalette_801C1890.h"
#include <string.h>

typedef struct Ent_801D41B4 {
    u8 pad0[8];
    u8 sub[0xC];
    s32 id;
    u8 pad18[4];
} Ent_801D41B4;

// Sort record: owner key and item. new[] builds the array with this
// constructor and no destructor (__construct_new_array gets a null dtor),
// which is also why delete[] frees from the 0x10-byte array cookie.
struct Ent_801D4744 {
    u32 key;
    TItem *val;
    Ent_801D4744();
    // Non-const source: the original reloads other.val after storing key.
    Ent_801D4744 &operator=(Ent_801D4744 &other);
};

// The 8-byte list TObjPlayer__sub_801D4368 allocates with new and frees with
// delete (the destructor's s16 argument is MWCC's delete flag).
struct List_801D4744 {
    s32 count;
    Ent_801D4744 *items;
    List_801D4744(s32 n);
    ~List_801D4744();
    // Bubble-sorts records by key.
    void sort_by_key();
};

extern "C" {
u8 *get_ptr_4__10TObjPlayerFv();
void fn_801C1BA8(void *, void *);
s32 is_both_confirmed__23TAdSinglePlyChrSelectGCFv(void *);

// Byte 0 of the item data is the item type.
s32 fn_801D40D4(s32 arg0, TPlyInventoryItem *arg1, TPlyInventoryItem *arg2) {
    s32 i;
    for (i = 0; i < arg0; i++) {
        if (arg1->m_flags & 8) {
            if (arg1->m_data.data1.data_u8[0] == 0) {
                fn_801C1BA8(arg2, arg1);
            }
            if (arg1->m_data.data1.data_u8[0] == 2) {
                fn_801C1BA8(arg2 + 1, arg1);
            }
        }
        arg1++;
    }
    return 1;
}

s32 check_player_action_allowed(void) {
    if ((get_main_phase() == 0xE) || (TTecCtrl::is_technique_ready() != 0) || ((is_quest_active() == 1) && (get_game_play_mode() == 1))) {
        return 0;
    }
    return TAdSinglePlyChrSelectGC::get_game_mode();
}

void remove_list_entry_by_id(s32 arg0) {
    u8 *cnt;
    s32 i;
    s32 n;
    Ent_801D41B4 *p;
    s32 rem;
    cnt = ((u8 *)get_char_index__23TAdSinglePlyChrSelectGCFUi(0xFFFF));
    if (cnt != NULL) {
        p = ((Ent_801D41B4 *)get_ptr_4__10TObjPlayerFv());
        n = *cnt;
        for (i = 0; i < n; p++, i++) {
            if (p->id == arg0) {
                if (is_both_confirmed__23TAdSinglePlyChrSelectGCFv(p->sub) != 0) {
                    TAdSinglePlyChrSelectGC::remove_matching_entries((s32)cnt);
                }
                rem = n - i;
                *cnt -= 1;
                if (rem <= 0) {
                    reset(p);
                    return;
                }
                memcpy(p, p + 1, rem * 0x1C);
                return;
            }
        }
    }
}

s32 fn_801D4270(s32 arg0) {
    s32 i;
    u8 *p;
    if ((u32)get_char_index__23TAdSinglePlyChrSelectGCFUi(0xFFFF) == 0) {
        return 0;
    }
    p = get_ptr_4__10TObjPlayerFv();
    for (i = 0; i < 30; i++, p += 0x1C) {
        if (*(s32 *)(p + 0x14) == arg0) {
            return 1;
        }
    }
    return 0;
}

void *reset(void *p) { return memset(p, 0, 28); }

s32 TItem::export_inventory_entry(TPlyInventoryItem *dest) {
    if (copy_to_item_data(&dest->m_data) != 0) {
        dest->m_present[0] = get_mode();
        dest->m_flags = get_item_flags();
        return 1;
    }
    return 0;
}

// Reassigns each owned item's owner id from a key-sorted copy of the list.
// Each loop keeps its own cursor: CodeWarrior assigns those registers from
// this declaration order.
s32 TObjPlayer__sub_801D4368(TPlyItem *ply) {
    List_801D4744 *recs;
    s32 filled;
    Ent_801D4744 *rec;
    s32 counted;
    TItemList *node_assigned;
    TItem *owner;
    Ent_801D4744 *rec_checked;
    Ent_801D4744 *rec_assigned;
    TItemList *node_checked;
    TItemList *node_filled;
    TItemList *node;
    s32 checked;

    if (ply->item_list == NULL) {
        return 0;
    }
    if (TItemList::is_item_valid(ply->item_list) == 0) {
        return 0;
    }
    if (ply->item_count > 30 || ply->item_count < 1) {
        return 0;
    }
    recs = new List_801D4744(ply->item_count);
    if (recs == NULL) {
        return 0;
    }
    if (recs->items == NULL) {
        delete recs;
        return 0;
    }
    counted = 0;
    node = ply->item_list->link_down();
    while (node != NULL) {
        if (TItemList::is_item_valid(node) != 0 && node->get_owner_if_alive() != NULL) {
            counted++;
        }
        node = node->link_next();
    }
    if (counted != ply->item_count) {
        delete recs;
        return 0;
    }
    filled = 0;
    rec = recs->items;
    node_filled = ply->item_list->link_down();
    while (node_filled != NULL) {
        if (TItemList::is_item_valid(node_filled) != 0 && (owner = node_filled->get_owner_if_alive()) != NULL) {
            rec->val = owner;
            TObjPlayer__sub_801D45B0(&rec->key, owner);
            rec++;
            filled++;
        }
        node_filled = node_filled->link_next();
    }
    recs->sort_by_key();
    checked = 0;
    rec_checked = recs->items;
    node_checked = ply->item_list->link_down();
    while (node_checked != NULL) {
        if (TItemList::is_item_valid(node_checked) != 0 && node_checked->get_owner_if_alive() != NULL && rec_checked->val != NULL) {
            rec_checked++;
            checked++;
        }
        node_checked = node_checked->link_next();
    }
    if (filled != checked) {
        delete recs;
        return 0;
    }
    rec_assigned = recs->items;
    node_assigned = ply->item_list->link_down();
    while (node_assigned != NULL) {
        if (TItemList::is_item_valid(node_assigned) != 0 && node_assigned->get_owner_if_alive() != NULL) {
            if (rec_assigned->val != NULL) {
                node_assigned->set_field_1c(rec_assigned->val);
                rec_assigned++;
            }
        }
        node_assigned = node_assigned->link_next();
    }
    delete recs;
    return 1;
}

void TObjPlayer__sub_801D45B0(u32 *arg0, TItem *arg1) {
    *arg0 = 0;
    *arg0 |= arg1->get_item_type() << 0x19;
    if (arg1->get_item_type() == 1) {
        *arg0 |= (arg1->get_item_group() << 0x11) & 0x01FE0000;
    } else {
        *arg0 |= (arg1->get_item_group() << 8) & 0xFF00;
    }
    *arg0 |= arg1->get_item_index();
    if (is_item_equipped(arg1) == 0) {
        *arg0 |= 0x10000;
    }
}

List_801D4744::~List_801D4744() {
    if (items != NULL) {
        delete[] items;
    }
}

List_801D4744::List_801D4744(s32 n) {
    count = n;
    items = new Ent_801D4744[count];
}

Ent_801D4744::Ent_801D4744() {
    key = -1;
    val = NULL;
}

void List_801D4744::sort_by_key() {
    Ent_801D4744 t;
    s32 n;
    s32 j;
    Ent_801D4744 *p;
    Ent_801D4744 *q;
    n = count;
    while (--n > 0) {
        p = items;
        for (j = 0; j < n; p++, j++) {
            q = p + 1;
            if (p->key > q->key) {
                t = *p;
                *p = *q;
                *q = t;
            }
        }
    }
}

Ent_801D4744 &Ent_801D4744::operator=(Ent_801D4744 &other) {
    key = other.key;
    val = other.val;
    return *this;
}
s32 TObjPlayer__sub_801D47EC(TPlyItem *arg0, s32 arg1, s32 arg2) {
    TItemList *temp_r3;
    TItemList *temp_r3_2;
    TItem *temp_r3_3;
    TItem *temp_r3_4;
    temp_r3 = arg0->start_inventory_update(arg1);
    if (temp_r3 == NULL) {
        return 0;
    }
    temp_r3_2 = arg0->start_inventory_update(arg2);
    if (temp_r3_2 == NULL) {
        return 0;
    }
    temp_r3_3 = temp_r3->get_owner_if_alive();
    if (temp_r3_3 == NULL) {
        return 0;
    }
    temp_r3_4 = temp_r3_2->get_owner_if_alive();
    if (temp_r3_4 == NULL) {
        return 0;
    }
    temp_r3->set_field_1c(temp_r3_4);
    temp_r3_2->set_field_1c(temp_r3_3);
    return 1;
}

}
