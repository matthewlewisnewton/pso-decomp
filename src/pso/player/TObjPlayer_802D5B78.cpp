#include "types.h"
#include <dolphin/mtx/GeoTypes.h>
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

f32 normalize_vector(Vec *);

#pragma push
#pragma fp_contract on

void TObjPlayer__sub_802D5B78(void *arg0, void *arg1, const Vec *arg2) {
    // The incoming vector is copied before normalization; GC/1.3.2 keeps the
    // three loads of this plain copy grouped ahead of the normalizer call.
    Vec normalized = *arg2;
    (void)normalize_vector(&normalized);
    S_802D5B78 *tab = *(S_802D5B78 **)((s8 *)*(void **)arg0 + 0xA4);
    S_802D5B78 *e = (S_802D5B78 *)((s8 *)tab + *(s32 *)((s8 *)arg0 + 4) * 0x2C);
    f32 s = e->scale;
    Vec *out = (Vec *)arg1;
    out->x = e->f1C - normalized.x * s;
    out->y = e->f20 - normalized.y * s;
    out->z = e->f24 - normalized.z * s;
}

#pragma pop

}
