#include "types.h"
#include <string.h>
#include "pso/player/TObjPlayer_802D5B78.h"

struct S_802D5B78 {
    u8 pad0[0xC];
    f32 scale;
    u8 pad10[0xC];
    f32 f1C;
    f32 f20;
    f32 f24;
    u8 pad28[4];
};

extern "C" {

void normalize_vector(void *);

#pragma push
#pragma fp_contract on

void TObjPlayer__sub_802D5B78(void *arg0, void *arg1, const Vec_802D5B78 *arg2) {
    // The original copies the incoming vector with three integer loads before
    // the call; this defined representation copy reproduces that schedule.
    union {
        Vec_802D5B78 v;
        u32 w[3];
    } u;
    const u32 *src = (const u32 *)arg2;
    u.w[0] = src[0];
    u.w[1] = src[1];
    u.w[2] = src[2];
    normalize_vector(&u.v);
    S_802D5B78 *tab = *(S_802D5B78 **)((s8 *)*(void **)arg0 + 0xA4);
    S_802D5B78 *e = (S_802D5B78 *)((s8 *)tab + *(s32 *)((s8 *)arg0 + 4) * 0x2C);
    f32 s = e->scale;
    f32 *out = (f32 *)arg1;
    out[0] = e->f1C - u.v.x * s;
    out[1] = e->f20 - u.v.y * s;
    out[2] = e->f24 - u.v.z * s;
}

#pragma pop

}
