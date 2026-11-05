#include "types.h"
#include "pso/TChCrLoadGmNjReq.h"
struct Obj_8028C8A8 { u8 pad[0x6c]; s32 f6c; };

extern s32 chr_select_slot_state;

void TChCrLoadGmNjReq::sub_8028C8A8() {
    Obj_8028C8A8 *o = (Obj_8028C8A8 *)this;
    if (chr_select_slot_state < 0 || chr_select_slot_state > 1) return;
    if (o->f6c == 0) return;
    chr_select_slot_state--;
    o->f6c = 0;
}
