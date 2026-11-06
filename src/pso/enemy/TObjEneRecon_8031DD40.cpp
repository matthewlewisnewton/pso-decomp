#include "types.h"
#include "pso/enemy/TObjEneRecon.h"

extern "C" {

s32 VecCopy__FP3VecPC3Vec(void *, void *, void *);

void TObjEneRecon::update_position_from_offsets() {
    u8 *arg0 = (u8 *)this;
    *(f32 *)((s8 *)arg0 + 0x2FC) = (f32) *(f32 *)((s8 *)arg0 + 0x38);
    *(f32 *)((s8 *)arg0 + 0x304) = (f32) *(f32 *)((s8 *)arg0 + 0x40);
    VecCopy__FP3VecPC3Vec(arg0 + 0x74, arg0 + 0x2FC, arg0);
}

}
