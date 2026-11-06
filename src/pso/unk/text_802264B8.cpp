#include <dolphin/mtx.h>
#include "types.h"
#include "pso/unk/text_802264B8.h"
struct Queued_802264B8 { s32 flags; s32 remaining; s32 position; u8 pad[0x28 - 0xC]; };

extern "C" {
s32 check_sound_admission_range(const Vec *);
extern struct Queued_802264B8 lbl_805145F0[];
s32 fn_802264B8(s32 slot) {
    s32 r;
    if (lbl_805145F0[slot].flags & 0x2000) {
        r = 0;
    } else {
        r = check_sound_admission_range((const Vec *)lbl_805145F0[slot].position);
    }
    if (r == -0x100) {
        lbl_805145F0[slot].flags |= 0x100;
        return 0;
    }
    lbl_805145F0[slot].flags &= ~0x100;
    return 1;
}

}
