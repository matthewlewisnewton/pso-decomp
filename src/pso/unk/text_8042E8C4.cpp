#include "pso/network/ModemLaunchContext.h"
#include "dolphin/os/OSCache.h"
#include "dolphin/os/OSReset.h"
#include "string.h"

// Reserved launch record. fn_8042E8B8 returns this address.
extern u8 launch_record[] AT_ADDRESS(0x80003100);

extern "C" void __isync(void);

// Copies the launch context onto launch_record, shuts the OS down
// (OS_RESET_SHUTDOWN returns), and loads the DOL image at field_104.
// A zero file offset ends that section list. Text is stored and
// instruction-invalidated; data is stored; BSS is cleared.
//
// Not exact on the ntutl profile (GC/2.6 -O4,p -inline off -use_lmw_stmw on).
// The original tail is lwz/isync/mtlr/blr with the link bit clear, so the
// frame restore at 0x8042E9FC never runs. __isync() emits the isync. The
// indirect call is mtctr/bctrl plus a live epilogue. Dolphin SDK flags
// without -use_lmw_stmw call the GPR save helper instead of stmw, which this
// prologue does not do. GC/1.2.5's indirect call is mtlr/blrl (link bit set)
// and its prologue is the older unscheduled form. __attribute__((noreturn))
// is rejected and there is no mtlr intrinsic.
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
