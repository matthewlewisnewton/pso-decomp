#define TOBJECT_OUT_OF_LINE_HELPERS
#include "types.h"
#include "pso/unk/TLobby_801C25B4.h"
#include "pso/system/task/TObject_80019A50.h"
#include "pso/unk/text_801C23A8.h"
#include "pso/unk/TUnk_804C3E60.h"
#include "pso/unk/TLobby.h"
#include "pso/player/TPlayerBattleCtrl4P_8031012C.h"
#include "pso/ui/window/TWindowDuelResult_801C2528.h"
#include "pso/ui/hud/TRaderMapCore.h"
#include "pso/system/task/TObject.h"

extern "C" {
extern TObject *tl_00;

void set_timed_music_gain_offset(s32 gain, s32 duration) {
    if (battle_music_gain_task != NULL) {
        battle_music_gain_task->countdown = duration;
        battle_music_gain_task->gain_offset = gain;
        TLobby::set_and_notify(gain);
        return;
    }
    battle_music_gain_task = new TUnk_804C3E60(tl_00, gain, duration);
}

TUnk_804C3E60::~TUnk_804C3E60() {
    battle_music_gain_task = NULL;
}

void TUnk_804C3E60::run_task() {
    if (--countdown <= 0) {
        TLobby::set_and_notify(0);
        queue_destruction();
        return;
    }
    if (countdown <= 15) {
        TLobby::set_and_notify((s32)((0.06666667f * (f32)countdown) * (f32)gain_offset));
    }
}

TUnk_804C3E60::TUnk_804C3E60(TObject *parent, s32 gain, s32 duration) : TObject(parent) {
    countdown = duration;
    gain_offset = gain;
    TLobby::set_and_notify(gain);
}

s32 *TWindowDuelResult__sub_801C257C(void) {
    if (TRaderMapCore::is_not_split_screen() == 1) {
        return (long *) (get_split_screen_battle_rankings());
    }
    return &TLobby__duel_result_table.value;
}

}
