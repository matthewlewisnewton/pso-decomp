#include "types.h"
#include "pso/enemy/TObjEneDD_800BA754.h"
#include "pso/enemy/TObjEneDD.h"

struct Part_800BA030 { u8 pad[0x2c]; };

struct Obj_800BA030 { u8 pad[0xa4]; Part_800BA030 *parts; s32 count; };

struct Part_800BA084 { u8 pad[0x2c]; };

struct Obj_800BA084 { u8 pad[0xa4]; Part_800BA084 *parts; s32 count; };

extern "C" {
f32 random_ratio__9TObjCharaFv();

extern f32 lbl_805D9E98;
extern f32 lbl_805D9E9C;

f32 TObjEneDD::calc_elapsed_scaled() {
    return lbl_805D9E98 * (random_ratio__9TObjCharaFv() - lbl_805D9E9C);
}

s32 TObjEneDD::vfunc_99() {
    return (u8)(((this->actorFlags & 0x10) - 0x10) == 0);
}

void TObjEneDD::vfunc_98() {
    Obj_800BA030 *self = (Obj_800BA030 *)this;
    s32 i;
    for (i = 0; i < self->count; i++) {
        set_collider_contact_low((u8 *)&self->parts[i]);
    }
}

void TObjEneDD::vfunc_97() {
    Obj_800BA084 *self = (Obj_800BA084 *)this;
    s32 i;
    for (i = 0; i < self->count; i++) {
        set_collider_contact_high((u8 *)&self->parts[i]);
    }
}

void TObjEneDD::vfunc_96() {
    this->vfunc_92();
    this->vfunc_93();
    this->actorFlags = (s32) (this->actorFlags & 0xFBFBFFFF);
}

}
