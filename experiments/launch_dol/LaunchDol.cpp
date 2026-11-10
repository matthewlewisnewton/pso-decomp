// Research-only candidate preserved from PR #284. Never link this object
// into the game: production LaunchDol is already provided by the exact
// whole-function orig_asm implementation. See README.md for limitations.
#if !defined(PSO_LAUNCH_DOL_EXPERIMENT) || !defined(__MWERKS__)
#error This experiment requires explicit opt-in and target MWCC; it is not a host fallback.
#endif

#include "pso/network/ModemLaunchContext.h"
#include "dolphin/os/OSCache.h"
#include "dolphin/os/OSReset.h"
#include "string.h"

// Reserved launch record. fn_8042E8B8 returns this address.
extern u8 launch_record[] AT_ADDRESS(0x80003100);

static inline void LaunchDolInline(ModemLaunchContext *ctx) {
    u32 offset;
    u8 *src;
    u32 offset2;
    u8 *src2;
    u8 *rec = launch_record;
    u32 raw_size = ctx->payload_size + 0x132;
    u32 size = raw_size & ~0x1Fu;
    DolImageHeader *image = ctx->field_104;
    u32 i;
    void *dest;
    u32 length;
    u32 zero;

    memmove(rec, ctx, size);
    DCStoreRange(launch_record, size);
    OSResetSystem(OS_RESET_SHUTDOWN, 0, FALSE);

    memset(image->bss_address, 0, image->bss_size);
    DCStoreRange(image->bss_address, image->bss_size);

    for (i = 0; i < 7; i++) {
        offset = image->text_offset[i];
        dest = image->text_address[i];
        length = image->text_size[i];
        zero = 0;
        if (offset == zero) {
            break;
        }
        src = reinterpret_cast<u8 *>(image) + offset;
        memmove(dest, src, length);
        DCStoreRange(dest, length);
        ICInvalidateRange(dest, length);
    }
    for (i = 0; i < 11; i++) {
        offset2 = image->data_offset[i];
        dest = image->data_address[i];
        length = image->data_size[i];
        zero = 0;
        if (offset2 == zero) {
            break;
        }
        src2 = reinterpret_cast<u8 *>(image) + offset2;
        memmove(dest, src2, length);
        DCStoreRange(dest, length);
    }

    void (*entry)() = image->entry;
    __isync();
    // Known non-equivalence: this emits a linking CTR call, not the original
    // nonlinking LR handoff that abandons the frame. Do not run as a replacement.
    entry();
}

extern "C" void LaunchDol(ModemLaunchContext *ctx) {
    LaunchDolInline(ctx);
}
