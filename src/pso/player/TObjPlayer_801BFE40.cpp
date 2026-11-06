#include "types.h"
#include "pso/player/TObjPlayer.h"

void TObjPlayer::set_scale_xyz(f32 farg0) {
    *(f32 *)((s8 *)this + 0x14) = farg0;
    *(f32 *)((s8 *)this + 0x10) = farg0;
    *(f32 *)((s8 *)this + 0xC) = farg0;
}
