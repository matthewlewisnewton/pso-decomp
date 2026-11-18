#include "types.h"
#include "pso/unk/text_803DA798.h"
#include "pso/player/TObjPlayer_803DF7A8.h"
#include "pso/player/TObjPlayer.h"

struct Vec_803E1B1C { f32 x, y, z; };

extern "C" {
extern const f32 lbl_805E1038;
extern const f32 lbl_805E103C;
__declspec(section ".sdata2") extern const f64 lbl_805E1040;
__declspec(section ".sdata2") extern const f64 lbl_805E1048;
}

#pragma push
#pragma scheduling off
f32 xyz_distance(Vec *a, Vec *b) {
    f32 x = (a->z - b->z) * (a->z - b->z) + ((a->x - b->x) * (a->x - b->x) + (a->y - b->y) * (a->y - b->y));
    f32 r;
    if (x < lbl_805E1038) {
        return lbl_805E103C;
    }
    if (x > lbl_805E103C) {
        volatile f32 y;
        f64 g = __frsqrte(x);
        g = lbl_805E1040 * g * (lbl_805E1048 - g * g * x);
        g = lbl_805E1040 * g * (lbl_805E1048 - g * g * x);
        g = lbl_805E1040 * g * (lbl_805E1048 - g * g * x);
        y = (f32)(x * g);
        r = y;
    } else {
        r = x;
    }
    return r;
}
#pragma pop


extern "C" void calc_bounds_min_max__10TObjPlayerFPvPvPv(struct Vec_803E1B1C *pts, struct Vec_803E1B1C *mn, struct Vec_803E1B1C *mx) {
    s32 i;
    mn->x = pts->x;
    mn->y = pts->y;
    mn->z = pts->z;
    mx->x = pts->x;
    mx->y = pts->y;
    mx->z = pts->z;
    pts++;
    for (i = 1; i < 8; i++, pts++) {
        if (pts->x < mn->x) mn->x = pts->x;
        if (pts->y < mn->y) mn->y = pts->y;
        if (pts->z < mn->z) mn->z = pts->z;
        if (pts->x > mx->x) mx->x = pts->x;
        if (pts->y > mx->y) mx->y = pts->y;
        if (pts->z > mx->z) mx->z = pts->z;
    }
}

void TObjPlayer::calc_bounds(u8 *arg1, u8 *arg2) {
    u8 *arg0 = (u8 *)this;
    *(f32 *)((s8 *)arg1 + 0) = (f32) (*(f32 *)((s8 *)arg0 + 0) - *(f32 *)((s8 *)arg0 + 0xC));
    *(f32 *)((s8 *)arg1 + 4) = (f32) (*(f32 *)((s8 *)arg0 + 4) - *(f32 *)((s8 *)arg0 + 0xC));
    *(f32 *)((s8 *)arg1 + 8) = (f32) (*(f32 *)((s8 *)arg0 + 8) - *(f32 *)((s8 *)arg0 + 0xC));
    *(f32 *)((s8 *)arg2 + 0) = (f32) (*(f32 *)((s8 *)arg0 + 0) + *(f32 *)((s8 *)arg0 + 0xC));
    *(f32 *)((s8 *)arg2 + 4) = (f32) (*(f32 *)((s8 *)arg0 + 4) + *(f32 *)((s8 *)arg0 + 0xC));
    *(f32 *)((s8 *)arg2 + 8) = (f32) (*(f32 *)((s8 *)arg0 + 8) + *(f32 *)((s8 *)arg0 + 0xC));
}

extern "C" {
extern __declspec(section ".sdata2") const f32 lbl_805E1038 = 0.025f;
extern __declspec(section ".sdata2") const f32 lbl_805E103C = 0.0f;
extern __declspec(section ".sdata2") const f64 lbl_805E1040 = 0.5;
extern __declspec(section ".sdata2") const f64 lbl_805E1048 = 3.0;
}
