#include "types.h"
#include "pso/system/byteswap.h"
#include "pso/misc/TLobby.h"

extern u8 *lbl_805D60C4;
extern s32 lbl_805D60C8;

void TLobby::append_swapped_u32(s32 *arg0) {
    s32 sp8;

    if (lbl_805D60C4 != NULL) {
        sp8 = *arg0;
        bswap_32((u32 *)&sp8);
        move_data(lbl_805D60C4 + lbl_805D60C8, &sp8, 4);
        lbl_805D60C8 += 4;
    }
}

void TLobby::append_entity_entry() {
    if (lbl_805D60C4 != NULL) {
        move_data(lbl_805D60C4 + lbl_805D60C8, this, 1);
        lbl_805D60C8 += 1;
    }
}
