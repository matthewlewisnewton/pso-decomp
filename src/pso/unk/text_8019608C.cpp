#include "types.h"
#include "pso/unk/text_8019608C.h"
#include "pso/misc/TNpcPlayer.h"

struct RecoveredGlobal_8019608C_lbl_8050DD08 {
    s32 value;
    u8 remaining[0xC];
};

extern RecoveredGlobal_8019608C_lbl_8050DD08 quest_col_apc_warp_target_pos;
extern s32 quest_collision_warp_pending;
typedef char RecoveredGlobal_8019608C_lbl_8050DD08_size[sizeof(RecoveredGlobal_8019608C_lbl_8050DD08) == 0x10 ? 1 : -1];
void fn_8019608C(void) {
    if ((s32) quest_collision_warp_pending != 0) {
        TNpcPlayer::send_warp_toward_player((u16)1U, (f32 *)&quest_col_apc_warp_target_pos.value);
    }
}
