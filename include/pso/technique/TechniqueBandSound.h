#ifndef PSO_TECHNIQUE_BAND_SOUND_H
#define PSO_TECHNIQUE_BAND_SOUND_H
#include "pso/effect/TUnk_804CCC68.h"
#include "pso/system/SoundEffect.h"
#include "pso/system/SoundSlotPitch.h"

// Barta, GiBarta and Megid share the same band-dependent pitch schedule.
// An unsupported band plays nothing; failed handles never receive a pitch update.
inline void play_technique_band_sound(TUnk_804CCC68 *technique, u32 sound_id) {
    s32 handle;

    switch (technique->band) {
    case 0:
        handle = play_sound_effect(sound_id, &technique->position, 0, 0);
        if (handle >= 0) {
            update_technique_slot__10TTecRaFoieFl(handle, 0x100, 0);
        }
        return;
    case 1:
        play_sound_effect(sound_id, &technique->position, 0, 0);
        return;
    case 2:
    case 3:
        handle = play_sound_effect(sound_id, &technique->position, 0, 0);
        if (handle >= 0) {
            update_technique_slot__10TTecRaFoieFl(handle, -0x180, 0);
        }
        break;
    case 4:
        handle = play_sound_effect(sound_id, &technique->position, 0, 0);
        if (handle >= 0) {
            update_technique_slot__10TTecRaFoieFl(handle, -0x250, 0);
        }
        break;
    case 5:
        handle = play_sound_effect(sound_id, &technique->position, 0, 0);
        if (handle >= 0) {
            update_technique_slot__10TTecRaFoieFl(handle, -0x100, 0);
        }
        break;
    }
}

#endif
