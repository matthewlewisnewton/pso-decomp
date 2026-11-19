#ifndef PSO_UNK_TEXT_800D8830_H
#define PSO_UNK_TEXT_800D8830_H

#include "types.h"
class TObject;
struct Vec;

extern "C" {
void play_floor_area_persistent_sound(const TObject *owner, const Vec *position);
s32 play_floor_area_sound_effect(const Vec *position);
}

#endif
