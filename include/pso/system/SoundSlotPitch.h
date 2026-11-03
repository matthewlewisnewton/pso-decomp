#ifndef PSO_SYSTEM_SOUNDSLOTPITCH_H
#define PSO_SYSTEM_SOUNDSLOTPITCH_H
#include "types.h"
extern "C" {
void set_sound_slot_pitch(s32 slot,s32 pitch,s32 duration);
// Preserve the historical exported symbol; the three scalar inputs are real
// sound arguments, not an effect object or implicit surviving registers.
void update_technique_slot__10TTecRaFoieFl(s32 slot,s32 pitch,s32 duration);
}
#endif
