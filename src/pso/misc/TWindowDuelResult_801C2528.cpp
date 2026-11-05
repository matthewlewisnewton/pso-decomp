#include "types.h"
#include "pso/misc/TPlayerBattleCtrl4P_8031012C.h"
#include "pso/misc/TWindowDuelResult_801C2528.h"
#include "pso/misc/TWindowDuelResult.h"
#include "pso/misc/TLobby.h"
#include "pso/misc/TRaderMapCore.h"

struct RecoveredGlobal_801C257C_TLobby__data_80511C80 {
    s32 value;
    u8 remaining[0x1C];
};

extern "C" {
extern RecoveredGlobal_801C257C_TLobby__data_80511C80 TLobby__duel_result_table;
void __ct__7TObjectFP7TObject(void *);

extern s32 duel_result_window_dispatch_table[];

void *TWindowDuelResult::init(void *arg1, void *arg2, void *arg3) {
    __ct__7TObjectFP7TObject(this);
    *(s32 **)((s8 *)this + 0x18) = duel_result_window_dispatch_table;
    *(void * *)&this->frame_pad_1c = arg3;
    *(void **)((s8 *)this + 0x20) = arg2;
    TLobby::set_and_notify((int)arg2);
    return this;
}
typedef char RecoveredGlobal_801C257C_TLobby__data_80511C80_size[sizeof(RecoveredGlobal_801C257C_TLobby__data_80511C80) == 0x20 ? 1 : -1];
s32 *TWindowDuelResult__sub_801C257C(void) {
    if (TRaderMapCore::is_not_split_screen() == 1) {
        return (long *) (get_split_screen_battle_rankings());
    }
    return &TLobby__duel_result_table.value;
}

}
