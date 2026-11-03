#include "types.h"
#include "pso/misc/TWindowSubStatusDisp.h"
#include "pso/player/TObjPlayer.h"
#include "pso/player/TObjPlayer_801AF2F0.h"
#include "pso/misc/TWindowSubEquipList.h"
#include "pso/item/TItem.h"
#include "pso/item/TItemData.h"
#include <stddef.h>

// Row initializers still use legacy owner names elsewhere; their receiver is a
// row returned by the list, not a TWindowSubStatusDisp object.
struct EquipListRow {
    u8 unknown_00[8];
    f32 height;
    u8 unknown_0c[0x20];
    u32 color;
};
typedef char EquipListRowHeightOffset[offsetof(EquipListRow, height) == 8 ? 1 : -1];
typedef char EquipListRowColorOffset[offsetof(EquipListRow, color) == 0x2c ? 1 : -1];

extern "C" {
void init_status_entry__20TWindowSubStatusDispFPvcUii(EquipListRow *, u8, u32, s32);
void init_item_row__20TWindowSubStatusDispFPvl(EquipListRow *, TItem *, s32);
extern const f32 lbl_805DD620;
}

void TWindowSubEquipList::add_status_line(u8 icon, TItem *item, s32 slot) {
    EquipListRow *row = (EquipListRow *)get_array_entry(entry_count);
    if (item == NULL) {
        init_status_entry__20TWindowSubStatusDispFPvcUii(row, icon, 0, slot);
        row->height += lbl_805DD620;
        row->color = 0xFFAAAAAA;
    } else {
        init_item_row__20TWindowSubStatusDispFPvl(row, item, slot);
    }
    if (icon == 4) {
        row->height += lbl_805DD620;
    }
    entry_count++;
}

u8 get_class_weapon_icon_index(void *self, u8 *player);

void TWindowSubEquipList::build_equipment_list() {
    // This declaration order preserves CodeWarrior's register allocation.
    TItem *item;
    s32 count;
    s32 i;
    TObjPlayer *player;
    u8 icon;

    player = get_player_by_client_id(m_20);
    if (player != NULL) {
        icon = get_class_weapon_icon_index(this, (u8 *)player);
        item = (TItem *)TObjPlayer::get_slot_value(player->equipped_items, 6);
        add_status_line(icon, item, 6);
        item = (TItem *)TObjPlayer::get_slot_value(player->equipped_items, 2);
        add_status_line(0x0b, item, 2);
        if (item != NULL) {
            TItemData data;
            item->copy_to_item_data(&data);
            count = (s8)data.data1.data_u8[5];
            for (i = 0; i < count; i++) {
                item = (TItem *)TObjPlayer::get_slot_value(player->equipped_items, i + 9);
                add_status_line(4, item, i + 9);
            }
        }
        item = (TItem *)TObjPlayer::get_slot_value(player->equipped_items, 3);
        add_status_line(0x0a, item, 3);
        item = (TItem *)TObjPlayer::get_slot_value(player->equipped_items, 1);
        add_status_line(3, item, 1);
    }
}
