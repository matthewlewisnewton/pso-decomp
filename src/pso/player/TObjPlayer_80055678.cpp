#include "types.h"
#include "pso/player/TObjPlayer.h"
#include "pso/boss/TBoss4Type1.h"

void TBoss4Type1::apply_poison_status() {  }
void TBoss4Type1::apply_paralysis() {  }
void TBoss4Type1::apply_slow_status() {  }
void TBoss4Type1::apply_confusion_status() {  }
void TBoss4Type1::apply_movement_ailment(s32) {  }
void TBoss4Type1::apply_shock_status() {  }
void TBoss4Type1::clear_harmful_statuses() {  }
Vec *TObjPlayer::get_position_ptr() { return &this->position; }
