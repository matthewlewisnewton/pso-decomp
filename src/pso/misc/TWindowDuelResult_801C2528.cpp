#include "types.h"
#include "pso/misc/TPlayerBattleCtrl4P_8031012C.h"
#include "pso/misc/TWindowDuelResult_801C2528.h"
#include "pso/unk/TUnk_804C3E60.h"
#include "pso/misc/TLobby.h"
#include "pso/misc/TRaderMapCore.h"

struct RecoveredGlobal_801C257C_TLobby__data_80511C80 {
    s32 value;
    u8 remaining[0x1C];
};

extern "C" {
extern RecoveredGlobal_801C257C_TLobby__data_80511C80 TLobby__duel_result_table;
TUnk_804C3E60::TUnk_804C3E60(TObject *parent, s32 gain, s32 duration)
    : TObject(parent) {
    countdown = duration;
    gain_offset = gain;
    TLobby::set_and_notify(gain);
}
typedef char RecoveredGlobal_801C257C_TLobby__data_80511C80_size[sizeof(RecoveredGlobal_801C257C_TLobby__data_80511C80) == 0x20 ? 1 : -1];
s32 *TWindowDuelResult__sub_801C257C(void) {
    if (TRaderMapCore::is_not_split_screen() == 1) {
        return (long *) (get_split_screen_battle_rankings());
    }
    return &TLobby__duel_result_table.value;
}

}
