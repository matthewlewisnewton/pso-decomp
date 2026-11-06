#include "types.h"
#include "pso/enemy/TObjEneRecon.h"

struct Vec_8031DBD8 { f32 x, y, z; };

extern "C" {
s32 project_actor_to_ground(void *, void *, int);
extern const f32 lbl_805DF3C8;
void TObjEneRecon::vfunc_88() {
    u8 *arg0 = (u8 *)this;
    f32 d;
    u8 *t = *(u8 **)((s8 *)arg0 + 0x390);
    if (t != NULL && *(s16 *)((s8 *)arg0 + 0x326) == 2) {
        *(f32 *)((s8 *)arg0 + 0x3C) = *(f32 *)((s8 *)t + 0x3C);
    } else {
        Vec_8031DBD8 v = *(Vec_8031DBD8 *)(arg0 + 0x38);
        v.y += *(f32 *)((s8 *)arg0 + 0x448);
        if (project_actor_to_ground(arg0, &v, (int)(arg0 + 0x248)) != 0) {
            *(f32 *)((s8 *)arg0 + 0x3C) = v.y;
        }
    }
    d = *(f32 *)((s8 *)arg0 + 0x448) - *(f32 *)((s8 *)arg0 + 0x3C);
    if (d >= lbl_805DF3C8) {
        this->vfunc_97();
    } else {
        this->vfunc_98();
    }
    *(f32 *)((s8 *)(*(u8 **)((s8 *)arg0 + 0xA4)) + 4) = d;
}

}
