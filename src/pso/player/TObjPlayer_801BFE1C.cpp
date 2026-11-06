#include "types.h"
#include "pso/player/TObjPlayer.h"

extern "C" {

s32 set_scale_xyz__10TObjPlayerFf();

void TObjPlayer::set_speed(f32 farg0) {
    *(f32 *)((s8 *)this + 8) = farg0;
    set_scale_xyz__10TObjPlayerFf();
}

}
