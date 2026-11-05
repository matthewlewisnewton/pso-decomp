#ifndef PSO_UNK_TEXT_800D8830_H
#define PSO_UNK_TEXT_800D8830_H

#include "types.h"
class TObject;
struct Vec;

extern "C" {
void play_floor_area_persistent_sound(TObject *owner, Vec *position);
s32 play_floor_area_sound_effect(Vec *position);
}

#endif
