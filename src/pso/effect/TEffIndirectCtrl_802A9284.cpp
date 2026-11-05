#include "types.h"
#include "pso/effect/TEffIndirectCtrl_802A9284.h"
#include "pso/player/TObjPlayer_802A8368.h"
#include "pso/effect/TEffIndirectCtrl.h"

extern "C" {
s32 read_disc_file(s32, u8 *);
u8 *xmalloc__FUl(u32);
s32 xfree__FPv(s32);
void *memcpy(void *, const void *, u32);
extern s32 TEffIndirectCtrl__source_buffers[];
extern s32 indirect_dat_filename;

void TEffIndirectCtrl::free_all() {
    s32 var_r28;
    s32 var_r30;
    s32 var_r31;
    s32 allocation;

    TObjPlayer__sub_802A83F4();
    TEffIndirectCtrl::free_buffers();
    var_r31 = 0;
    var_r30 = var_r31;
    var_r28 = 0;
    do {
        allocation = *(TEffIndirectCtrl__source_buffers + var_r31);
        if ((u32)allocation != 0U) {
            xfree__FPv(allocation);
            *(TEffIndirectCtrl__source_buffers + var_r31) = var_r30;
        }
        var_r28 += 1;
        var_r31 += 1;
    } while (var_r28 < 8);
}
}
void load_indirect_dat(void) {
    s32 i;
    s32 fail;
    s32 j;
    u8 *buf;
    u8 *p;
    s32 k;
    fail = 0;
    for (i = 0; i < 8; i++) {
        TEffIndirectCtrl__source_buffers[i] = 0;
    }
    for (i = 0; i < 8; i++) {
        TEffIndirectCtrl__source_buffers[i] = (s32)xmalloc__FUl(0x1020);
        if ((u32)TEffIndirectCtrl__source_buffers[i] == 0) {
            fail = 1;
        }
    }
    if (fail != 0) {
        for (j = 0; j < 8; j++) {
            if ((u32)TEffIndirectCtrl__source_buffers[j] != 0) {
                xfree__FPv(TEffIndirectCtrl__source_buffers[j]);
                TEffIndirectCtrl__source_buffers[j] = 0;
            }
        }
    }
    p = xmalloc__FUl(0x8100);
    if (p != NULL) {
        buf = p;
        if (read_disc_file(indirect_dat_filename, p) == 0x8100) {
            for (k = 0; k < 8; k++) {
                memcpy((void *)TEffIndirectCtrl__source_buffers[k], p, 0x1020);
                p += 0x1020;
            }
            if (buf != NULL) {
                xfree__FPv((s32)buf);
            }
            load_indirect_info();
            TObjPlayer__sub_802A841C();
        }
    }
}
