#include "pso/enemy/TObjEnemy.h"
#include "types.h"
#include "pso/enemy/TObjEneDD.h"
#include "pso/misc/TOTrapAncient01_80226534.h"
#include "pso/unk/text_80362164.h"
#include "pso/unk/TObjEneEpsilonBody.h"
#include "pso/boss/TBoss8Dragon.h"
#include "pso/enemy/TObjEneEpsilonGuard.h"
#include "pso/player/TObjPlayer.h"

void TObjEneEpsilonBody::run_task() {
    if (TObjPlayer::check_demo_mode() != 0) {
        this->vfunc_105();
        return;
    }
    if (this->vfunc_83() != 4) {
        this->update_guard_flag();
        this->vfunc_85();
    } else if ((s16) this->mode == 1) {
        transition_enemy_state(0);
    }
    if ((s16) this->mode != 9) {
        play_persistent_sound(0x4003AD43, (s32)this, (u32)(((u8 *)this) + 0x38), 0, 0);
    }
    this->vfunc_88();
    ((TObjEneEpsilonGuard *)((u8 *)this))->update_position();
    ((TObjEnemy *)((u8 *)this))->submit_default_cursor_candidate();
    this->vfunc_100();
}
