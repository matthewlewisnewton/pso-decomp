#include "pso/system/SoundSlotPitch.h"
#include "types.h"
#include "pso/player/TObjPlayer.h"
#include "pso/enemy/TObjEneDD.h"

extern "C" {


extern s32 last_sound_effect_slot;

void TObjPlayer::play_effect_if_v2(s32 arg0) {
    if (TObjEneDD::check_v2_mode() != 0) {
        update_technique_slot__10TTecRaFoieFl(last_sound_effect_slot, arg0, 0);
    }
}

}
