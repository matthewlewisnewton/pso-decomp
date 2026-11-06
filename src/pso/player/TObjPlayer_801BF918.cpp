#include "types.h"
#include "pso/player/TObjPlayer_801BF918.h"
#include "pso/player/TObjPlayer.h"
#include "pso/misc/TMainCursor.h"
#include "pso/misc/TWindowSubStatusDisp.h"

    extern const float TObjPlayer__data_805DC278;

u8 TObjPlayer__sub_801BF918(u8 *arg0) {
    return (u8) (*(s32 *)((s8 *)arg0 + 4) == 2);
}

s16 TObjPlayer::get_action_id() { return *(s16*)((char*)this + 0x2); }
void* TObjPlayer__sub_801BF934(void* p) { return (char*)p + 0xc; }
void TObjPlayer__sub_801BF93C(void* p, s16 v) { *(s16*)((char*)p + 0x0) = v; }
void*TObjPlayer::get_sub_object() { return (char*)this + 0x8; }
s32 TObjPlayer::get_lock_timer() { return *(s32*)((char*)this + 0x4); }
void TObjPlayer__sub_801BF954(void* p, s32 v) { *(s32*)((char*)p + 0x0) = v; }
s32 TObjPlayer__sub_801BF95C(void* p) { return *(s32*)((char*)p + 0x0); }

void zero_vec3(void* a0) { *(float*)((char*)a0 + 0x0) = TObjPlayer__data_805DC278; *(float*)((char*)a0 + 0x4) = TObjPlayer__data_805DC278; *(float*)((char*)a0 + 0x8) = TObjPlayer__data_805DC278; }
