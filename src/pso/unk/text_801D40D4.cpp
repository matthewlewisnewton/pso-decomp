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
#include "pso/item/TItemProShield.h"
#include "pso/ui/TAdSinglePlyChrSelectGC.h"

// 0x1C inventory record: mode, flags, then the item data. Byte 0 of the
// item data is the type fn_801D40D4 tests.
struct Rec_801D40D4 {
    s8 mode;
    u8 pad1[3];
    s32 flags;
    union {
        u8 type;
        TItemData data;
    } item;
};
typedef char Rec_801D40D4_size[(sizeof(Rec_801D40D4) == 0x1C) ? 1 : -1];
typedef char Rec_801D40D4_flags[(offsetof(Rec_801D40D4, flags) == 4) ? 1 : -1];
typedef char Rec_801D40D4_item[(offsetof(Rec_801D40D4, item) == 8) ? 1 : -1];

typedef struct Ent_801D41B4 {
    u8 pad0[8];
    u8 sub[0xC];
    s32 id;
    u8 pad18[4];
} Ent_801D41B4;

typedef struct Ent_801D4744 {
    u32 key;
    TItem *val;
} Ent_801D4744;

typedef struct List_801D4744 {
    s32 count;
    Ent_801D4744 *items;
    // Bubble-sorts records by key. `this` is the 8-byte list, not a TObjPlayer.
    void sort_by_key();
    List_801D4744 *sub_801D46D4(s32 arg1);
    List_801D4744 *sub_801D4678(s16 arg1);
} List_801D4744;

// TPlyItem from TObjPlayer::create_inventory (0x1CC bytes). TPlyItem__ct
// stores the owner count at +0x1C; create_inventory stores the item list at
// +0x1C4. pickup_item parents a 0x20 TItemList (the item slot) under that list.
struct PlyItem_801D4368 {
    u8 pad0[0x1C];
    s16 item_count;
    u8 pad_1E[0x1C4 - 0x1E];
    TItemList *item_list;
};

typedef char PlyItem_801D4368_count[(offsetof(PlyItem_801D4368, item_count) == 0x1C) ? 1 : -1];
typedef char PlyItem_801D4368_list[(offsetof(PlyItem_801D4368, item_list) == 0x1C4) ? 1 : -1];

extern "C" {
u8 get_item_type__5TItemFv(void *, int);
s32 is_item_equipped(void *, int);
u8 *get_ptr_4__10TObjPlayerFv();
s32 __construct_new_array(void *, void *, int, int, int);
void fn_801C1BA8(void *, void *);
s32 fn_801D40D4(s32 arg0, Rec_801D40D4 *arg1, u8 *arg2);
s32 is_both_confirmed__23TAdSinglePlyChrSelectGCFv(void *);
void memcpy(void *, void *, s32);
s32 is_quest_active();
s32 is_technique_ready__8TTecCtrlFv();
int memset(void*, int, int);

s32 fn_801D40D4(s32 arg0, Rec_801D40D4 *arg1, u8 *arg2) {
    s32 i;
    for (i = 0; i < arg0; i++) {
        if (arg1->flags & 8) {
            if (arg1->item.type == 0) {
                fn_801C1BA8(arg2, arg1);
            }
            if (arg1->item.type == 2) {
                fn_801C1BA8(arg2 + 0x1C, arg1);
            }
        }
        arg1++;
    }
    return 1;
}

s32 check_player_action_allowed(void) {
    if ((get_main_phase() == 0xE) || (is_technique_ready__8TTecCtrlFv() != 0) || ((is_quest_active() == 1) && (get_game_play_mode() == 1))) {
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

int reset(void* p) { return memset(p, 0, 28); }

s32 TItem::export_inventory_entry(void *dest) {
    Rec_801D40D4 *rec = (Rec_801D40D4 *)dest;
    if (copy_to_item_data(&rec->item.data) != 0) {
        rec->mode = get_mode();
        rec->flags = get_item_flags();
        return 1;
    }
    return 0;
}

// Reassigns each owned item's owner id from a key-sorted copy of the list.
// Each loop keeps its own cursor: CodeWarrior assigns those registers from
// this declaration order.
s32 TObjPlayer__sub_801D4368(PlyItem_801D4368 *ply) {
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
    recs = (List_801D4744 *)::operator new(8);
    if (recs != NULL) {
        recs = recs->sub_801D46D4(ply->item_count);
    }
    if (recs == NULL) {
        return 0;
    }
    if (recs->items == NULL) {
        recs->sub_801D4678(1);
        return 0;
    }
    counted = 0;
    node = (TItemList *)ply->item_list->m_down;
    while (node != NULL) {
        if (TItemList::is_item_valid(node) != 0 && node->get_owner_if_alive() != NULL) {
            counted++;
        }
        node = (TItemList *)node->m_next;
    }
    if (counted != ply->item_count) {
        recs->sub_801D4678(1);
        return 0;
    }
    filled = 0;
    rec = recs->items;
    node_filled = (TItemList *)ply->item_list->m_down;
    while (node_filled != NULL) {
        if (TItemList::is_item_valid(node_filled) != 0 && (owner = node_filled->get_owner_if_alive()) != NULL) {
            rec->val = owner;
            TObjPlayer__sub_801D45B0((s32 *)rec, owner);
            rec++;
            filled++;
        }
        node_filled = (TItemList *)node_filled->m_next;
    }
    recs->sort_by_key();
    checked = 0;
    rec_checked = recs->items;
    node_checked = (TItemList *)ply->item_list->m_down;
    while (node_checked != NULL) {
        if (TItemList::is_item_valid(node_checked) != 0 && node_checked->get_owner_if_alive() != NULL && rec_checked->val != NULL) {
            rec_checked++;
            checked++;
        }
        node_checked = (TItemList *)node_checked->m_next;
    }
    if (filled != checked) {
        recs->sub_801D4678(1);
        return 0;
    }
    rec_assigned = recs->items;
    node_assigned = (TItemList *)ply->item_list->m_down;
    while (node_assigned != NULL) {
        if (TItemList::is_item_valid(node_assigned) != 0 && node_assigned->get_owner_if_alive() != NULL) {
            if (rec_assigned->val != NULL) {
                node_assigned->set_field_1c(rec_assigned->val);
                rec_assigned++;
            }
        }
        node_assigned = (TItemList *)node_assigned->m_next;
    }
    recs->sub_801D4678(1);
    return 1;
}

void TObjPlayer__sub_801D45B0(s32 *arg0, TItem *arg1) {
    s32 temp_r4;
    u8 player;
    *arg0 = 0;
    temp_r4 = get_item_type__5TItemFv(arg1, (int)arg1) << 0x19;
    *arg0 |= temp_r4;
    if (get_item_type__5TItemFv(arg1, (int)temp_r4) == 1) {
        *arg0 |= (arg1->get_item_group() << 0x11) & 0x01FE0000;
    } else {
        *arg0 |= (arg1->get_item_group() << 8) & 0xFF00;
    }
    player = arg1->get_item_index();
    *arg0 |= player;
    if (is_item_equipped(arg1, (int)player) == 0) {
        *arg0 |= 0x10000;
    }
}

List_801D4744 *List_801D4744::sub_801D4678(s16 arg1) {
    Ent_801D4744 *q;
    if (this != NULL) {
        q = items;
        if (q != NULL) {
            if (q != NULL) {
                // sub_801D46D4 allocates n * 8 + 0x10. __construct_new_array
                // returns the element pointer, and __dla__FPv does not subtract
                // the 0x10-byte MWCC array cookie in front of it. delete[] of
                // Ent_801D4744 does not match: the record has no destructor, so
                // MWCC frees the element pointer. A destructor makes delete[]
                // call __destroy_new_array instead (see attempts log).
                ::operator delete[]((u8 *)q - 0x10);
            }
        }
        if (arg1 > 0) {
            ::operator delete(this);
        }
    }
    return this;
}

List_801D4744 *List_801D4744::sub_801D46D4(s32 arg1) {
    s32 n;
    count = arg1;
    n = count;
    items = (Ent_801D4744 *)__construct_new_array(::operator new[]((n * 8 + 0x10)), TObjPlayer__sub_801D4730, 0, 8, n);
    return this;
}

void TObjPlayer__sub_801D4730(void* p) { *(s32*)((char*)p + 0x0) = -1; *(s32*)((char*)p + 0x4) = 0; }

void List_801D4744::sort_by_key() {
    Ent_801D4744 t;
    s32 n;
    s32 j;
    Ent_801D4744 *p;
    Ent_801D4744 *q;
    TObjPlayer__sub_801D4730(&t);
    n = count;
    while (--n > 0) {
        p = items;
        for (j = 0; j < n; p++, j++) {
            q = p + 1;
            if (p->key > q->key) {
                TObjPlayer__sub_801D47D8(&t, p);
                TObjPlayer__sub_801D47D8(p, q);
                TObjPlayer__sub_801D47D8(q, &t);
            }
        }
    }
}

void TObjPlayer__sub_801D47D8(void* p, void* q) { *(u32*)((char*)p + 0x0) = *(u32*)((char*)q + 0x0); *(u32*)((char*)p + 0x4) = *(u32*)((char*)q + 0x4); }
s32 TObjPlayer__sub_801D47EC(TObjPlayer *arg0, s32 arg1, s32 arg2) {
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
