#include "pso/network/ModemLaunchContext.h"
#include "dolphin/os/OSCache.h"
#include "dolphin/os/OSReset.h"
#include "string.h"

// Reserved launch record. fn_8042E8B8 returns this address.
extern u8 launch_record[] AT_ADDRESS(0x80003100);

// Copies the launch context onto launch_record, shuts the OS down
// (OS_RESET_SHUTDOWN returns), and loads the DOL image at field_104.
// A zero file offset ends that section list. Text is stored and
// instruction-invalidated; data is stored; BSS is cleared.
//
// Not exact. Built on the ntutl profile (GC/2.6 -O4,p -inline off
// -use_lmw_stmw on) with -opt nocse,nostrength for this unit: the original
// loops index with lwzx off a byte induction variable and recompute
// base+index per load, which is what those two optimizations would have
// folded. With that the loop bodies are the original instruction sequence.
// Left: the original holds the zero it compares each offset against in a
// register (cmplw) copied from the counter before each loop, which no
// spelling of the compare produces; and the tail is lwz/isync/mtlr/blr with
// the link bit clear (the frame restore at 0x8042E9FC never runs), while
// __isync() followed by image->entry() is isync/mtctr/bctrl plus a live
// epilogue. GC/2.6 has no mtlr intrinsic and no noreturn.
extern "C" void LaunchDol(ModemLaunchContext *ctx) {
    u32 size = (ctx->payload_size + 0x132) & ~0x1Fu;
    DolImageHeader *image = ctx->field_104;
    // Section sources are file offsets from the header, which is the image base.
    u8 *file = static_cast<u8 *>(static_cast<void *>(image));

    memmove(launch_record, ctx, size);
    DCStoreRange(launch_record, size);
    OSResetSystem(OS_RESET_SHUTDOWN, 0, FALSE);

    memset(image->bss_address, 0, image->bss_size);
    DCStoreRange(image->bss_address, image->bss_size);

    for (u32 i = 0; i < 7; i++) {
        u32 offset = image->text_offset[i];
        void *dest = image->text_address[i];
        u32 length = image->text_size[i];
        if (offset == 0) {
            break;
        }
        memmove(dest, file + offset, length);
        DCStoreRange(dest, length);
        ICInvalidateRange(dest, length);
    }
    for (u32 i = 0; i < 11; i++) {
        u32 offset = image->data_offset[i];
        void *dest = image->data_address[i];
        u32 length = image->data_size[i];
        if (offset == 0) {
            break;
        }
        memmove(dest, file + offset, length);
        DCStoreRange(dest, length);
    }

    __isync();
    image->entry();
}
