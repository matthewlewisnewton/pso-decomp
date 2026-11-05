#include "types.h"
#include "pso/player/TObjPlayer.h"

extern "C" {

s32 rand();

extern f32 lbl_805DAE78;
extern f32 lbl_805DAE7C;

s32 TObjPlayer::is_rand_below_threshold() {
    return (u32)__cntlzw(((lbl_805DAE78 * (f32) rand()) < lbl_805DAE7C)) >> 5;
}

}
