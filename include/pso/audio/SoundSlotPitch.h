#ifndef PSO_AUDIO_SOUNDSLOTPITCH_H
#define PSO_AUDIO_SOUNDSLOTPITCH_H

#include "types.h"

extern "C" {
void set_sound_slot_pitch(s32 slot, s32 pitch, s32 duration);
// This entry point keeps its original linker name and takes three sound arguments.
void update_technique_slot__10TTecRaFoieFl(s32 slot, s32 pitch, s32 duration);
}

#endif
