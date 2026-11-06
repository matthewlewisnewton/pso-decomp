#include "types.h"
#include "pso/player/TObjPlayer_801BFE50.h"
#include "pso/player/TObjPlayer_801BFED4.h"
#include "pso/player/TObjPlayer.h"

extern "C" {
extern const f32 TObjPlayer__data_805DC278;
s32 setup_state__10TObjPlayerFv();

void*TObjPlayer::init_pair() { TObjPlayer__sub_801BFE88((u8 *)this); TObjPlayer__sub_801BFE88((u8 *)((char*)this + 0xc)); return this; }

extern "C" {

void TObjPlayer__sub_801BFE88(u8 *arg0) {
    *(f32 *)((s8 *)arg0 + 8) = (f32) TObjPlayer__data_805DC278;
    *(f32 *)((s8 *)arg0 + 4) = (f32) TObjPlayer__data_805DC278;
    *(f32 *)((s8 *)arg0 + 0) = (f32) TObjPlayer__data_805DC278;
}

s32 init_state__10TObjPlayerFi(s32 arg0) {
    setup_state__10TObjPlayerFv();
    TObjPlayer__sub_801BFED4((void *)arg0);
    return arg0;
}

}

}
