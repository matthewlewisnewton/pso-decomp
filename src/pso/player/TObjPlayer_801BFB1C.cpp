#include "types.h"
#include "pso/player/TObjPlayer_801BFB1C.h"
#include "pso/player/TObjPlayer.h"

extern "C" {
extern const f32 TObjPlayer__data_805DC278;
s32 TObjPlayer__sub_801BF8F8();
int clear_movement_history(void*);

s32 TObjPlayer::reset_and_return(s32 arg0) {
    TObjPlayer__sub_801BF8F8();
    return arg0;
}

void TObjPlayer__sub_801BFB4C(u8 *arg0) {
    *(f32 *)((s8 *)arg0 + 8) = (f32) TObjPlayer__data_805DC278;
    *(f32 *)((s8 *)arg0 + 4) = (f32) TObjPlayer__data_805DC278;
    *(f32 *)((s8 *)arg0 + 0) = (f32) TObjPlayer__data_805DC278;
}

void TObjPlayer::clear_base() { *(s32*)((char*)this + 0x0) = 0; }
void*TObjPlayer::forward_release() { clear_movement_history(this); return this; }
void*TObjPlayer::set_vec3_const_wrapper() { set_vec3_const(); return this; }

}
