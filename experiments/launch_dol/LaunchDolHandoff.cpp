// Research-only C++ recovery with a target-specific nonlinking handoff.
// Its 332-byte extent crosses the current 312-byte LaunchDol boundary.
// See README.md before proposing production linkage or ownership changes.
#if !defined(PSO_LAUNCH_DOL_EXPERIMENT) || !defined(__MWERKS__)
#error This experiment requires explicit opt-in and target MWCC; it is not a host fallback.
#endif

#include "pso/network/ModemLaunchContext.h"
#include "dolphin/os/OSCache.h"
#include "dolphin/os/OSReset.h"
#include "string.h"

// Reserved launch record. fn_8042E8B8 returns this address.
extern u8 launch_record[] AT_ADDRESS(0x80003100);

// Expand the helper under the normal -inline off profile. Bypassing the
// frontend global optimizer preserves the loop addresses around the asm jump.
#pragma push
#pragma dont_inline off
#pragma inline_depth(1)
#pragma global_optimizer off
static inline void LaunchDolInline(ModemLaunchContext *ctx) {
    // These shared locals and the separate size expressions preserve allocation.
    u32 offset;
    u8 *const rec = launch_record;
    const u32 raw_size = ctx->payload_size + 0x132;
    const u32 size = raw_size & ~0x1Fu;
    const DolImageHeader *const image = ctx->field_104;
    u32 i;
    void *dest;
    u32 length;
    u32 zero;

    memmove(rec, ctx, size);
    DCStoreRange(launch_record, size);
    OSResetSystem(OS_RESET_SHUTDOWN, 0, FALSE);

    memset(image->bss_address, 0, image->bss_size);
    DCStoreRange(image->bss_address, image->bss_size);

    for (i = 0; i < 7; ++i) {
        offset = image->text_offset[i];
        dest = image->text_address[i];
        length = image->text_size[i];
        zero = 0;
        if (offset == zero) {
            break;
        }
        const u8 *const src = reinterpret_cast<const u8 *>(image) + offset;
        memmove(dest, src, length);
        DCStoreRange(dest, length);
        ICInvalidateRange(dest, length);
    }
    for (i = 0; i < 11; ++i) {
        offset = image->data_offset[i];
        dest = image->data_address[i];
        length = image->data_size[i];
        zero = 0;
        if (offset == zero) {
            break;
        }
        const u8 *const src = reinterpret_cast<const u8 *>(image) + offset;
        memmove(dest, src, length);
        DCStoreRange(dest, length);
    }

    // MWCC assigns the named operand to r0. This jumps through LR without
    // linking or restoring this frame; the compiler emits the trailing restore.
    register void (*const entry)() = image->entry;
    __isync();
    asm {
        mtlr entry
        blr
    }
}

extern "C" void LaunchDol(ModemLaunchContext *ctx) {
    LaunchDolInline(ctx);
}
#pragma pop
