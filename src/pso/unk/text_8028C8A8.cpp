#include "types.h"
#include "pso/TChCrLoadGmNjReq.h"

extern s32 chr_select_slot_state;

void TChCrLoadGmNjReq::sub_8028C8A8() {
    if (chr_select_slot_state < 0 || chr_select_slot_state > 1) return;
    if (slot_claimed == 0) return;
    chr_select_slot_state--;
    slot_claimed = 0;
}
