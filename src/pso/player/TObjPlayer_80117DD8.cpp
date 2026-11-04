#include "types.h"
#include "pso/item/TItem.h"
#include "pso/player/TObjPlayer.h"
#include "pso/item/TItemData.h"
#include "pso/item/TItemProShield.h"

struct Pl_80117F14 { u8 pad0[0x38]; f32 pos[3]; };

extern "C" {
f32 horizontal_distance_squared(void *, void *);
void *get_player_by_client_id(s32 i);
extern const f64 lbl_8043E648[];
extern const f64 lbl_8043E650[];

// Another client on the same floor, within lbl_8043E648, whose class_flags
// low bit is the opposite of ours (1 male, 2 female).
s32 TObjPlayer__sub_80117E50(u16 id) {
    s32 result;
    TObjPlayer *me;
    u32 mask;
    s32 key;
    u16 i;
    TObjPlayer *other;

    result = 0;
    me = (TObjPlayer *)get_player_by_client_id(id);
    if (me != NULL) {
        mask = (me->class_flags & 1) != 0 ? 2 : 1;
        key = me->get_floor();
        for (i = 0; i != 4; i++) {
            if (i != id) {
                other = (TObjPlayer *)get_player_by_client_id(i);
                if (other != NULL && (other->class_flags & mask) != 0 &&
                    key == other->get_floor() &&
                    horizontal_distance_squared(&me->position, &other->position) < lbl_8043E648[0]) {
                    result = 1;
                    break;
                }
            }
        }
    }
    return result;
}

s32 TObjPlayer::count_nearby_players_with_shield(u16 idx, u8 *item) {
    s32 key;
    Pl_80117F14 *me;
    s32 count;
    u16 i;
    Pl_80117F14 *other;
    void *it;
    count = 0;
    me = (Pl_80117F14 *)get_player_by_client_id(idx);
    if (me != NULL && item != NULL) {
        key = ((TObjPlayer *)me)->get_floor();
        for (i = 0; i != 4; i++) {
            if (i != idx) {
                other = (Pl_80117F14 *)get_player_by_client_id(i);
                if (other != NULL && key == ((TObjPlayer *)other)->get_floor() &&
                    horizontal_distance_squared(me->pos, other->pos) < lbl_8043E650[0] &&
                    (it = (void *)((TItemData *)other)->test_flag3()) != NULL &&
                    item[2] == ((TItem *)it)->get_item_index()) {
                    count++;
                }
            }
        }
    }
    return count;
}

}
