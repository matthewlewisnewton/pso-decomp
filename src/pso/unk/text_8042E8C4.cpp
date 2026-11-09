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
// The tail at 0x8042E9EC..0x8042E9F8 is an epilogue-free computed jump
// (lwz r0, 0xE0(r26); isync; mtlr r0; blr) followed by a stranded 20-byte
// epilogue at 0x8042E9FC (pad_03_8042E9FC_text). The tested MWCC versions
// do not emit this jump from an ordinary C++ indirect call. Under __MWERKS__ we keep upstream #172/#350's orig_asm
// body (registered in docs/porting-exceptions.md section 7); the #else
// branch holds the C++ implementation, which matches all 74 pre-tail
// instructions (0x000..0x124, 93.40% overall) byte-for-byte under GC/2.6
// -O4,p -use_lmw_stmw on -inline auto -opt nocse,nostrength,noprop.
#ifdef __MWERKS__
extern "C" {
asm void LaunchDol(register ModemLaunchContext *ctx) {
#include "orig_asm/pso/unk/text_8042E8C4/LaunchDol.inc"
}
}
#else
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
    entry();
}

extern "C" void LaunchDol(ModemLaunchContext *ctx) {
    LaunchDolInline(ctx);
}
#endif
