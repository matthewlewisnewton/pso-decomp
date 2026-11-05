#include "types.h"
#include "pso/unk/text_802789E0.h"
#include "pso/item/TItem.h"
#include "pso/misc/TShopJudgmentItemWindow.h"
#include "pso/misc/TWindowSubStatusDisp.h"
#include "pso/player/TObjPlayer.h"
#include "pso/player/TObjPlayer_801AF2F0.h"
#include "pso/TPlyItem.h"
extern "C" {
void calc_list_content_extent(void *);
void fn_802789E0(u8 *arg0) {
    s32 ids[32];
    TObjPlayer *pl;
    u32 n;
    void *item;
    u32 i;
    pl = get_player_by_client_id(*(s16 *)(arg0 + 0x20));
    if (pl != NULL) {
        n = pl->inventory_objects->run_and_get_result(ids);
        for (i = 0; i < n; i++) {
            item = find_item_by_id(ids[i]);
            if (item != NULL && ((TItem *)item)->get_usable_action_flags(2, 0) != 0 && ((TItem *)item)->get_usable_action_flags(1, 0) == 0) {
                ((TShopJudgmentItemWindow *)arg0)->add_list_entry((s32)item, ids[i]);
            }
        }
        if (*(s16 *)(arg0 + 0x72) <= 0) {
            ((TWindowSubStatusDisp *)arg0)->add_list_entry(-1);
        }
        calc_list_content_extent(arg0);
    }
}

}
