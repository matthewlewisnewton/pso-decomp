#include "types.h"
#include "pso/network/ModemLaunchContext.h"
#include "dolphin/os/OSReset.h"

#include <stddef.h>

// In-memory DOL header at ModemLaunchContext::field_104. The 7 text and 11
// data slots are the DOL format; offsets are relative to this header. This is
// a view of that layout, not a recovered original type name.
struct DolImageView {
    u32 text_offset[7];
    u32 data_offset[11];
    u32 text_address[7];
    u32 data_address[11];
    u32 text_size[7];
    u32 data_size[11];
    u32 bss_address;
    u32 bss_size;
    u32 entry;
};

typedef char DolImageViewBss[offsetof(DolImageView, bss_address) == 0xD8 ? 1 : -1];
typedef char DolImageViewEntry[offsetof(DolImageView, entry) == 0xE0 ? 1 : -1];

extern "C" {
void *memmove(void *, const void *, u32);
void *memset(void *, int, u32);
void DCStoreRange(void *, u32);
void ICInvalidateRange(void *, u32);
void __isync(void);

// Copies the launch context to the reserved block at 0x80003100, shuts the OS
// down (OS_RESET_SHUTDOWN returns), loads the DOL image at field_104, and
// transfers to its entry. Text sections are stored and instruction-invalidated;
// data sections are stored only. A zero section offset ends that list.
//
// Not an exact match under this unit's GC/2.6 -O4,p profile. The original tail
// is `lwz r0, 0xE0(r26); isync; mtlr r0; blr` (link bit clear), so the
// frame-restore epilogue at 0x8042E9FC never runs. __isync() is a real MWCC
// intrinsic and does emit one `isync`, but an indirect call is
// `mtctr`/`bctrl` (GC/2.6) or `mtlr`/`blrl` (GC/1.2.5, link bit set) followed
// by a live epilogue. Nothing in the installed compilers emits a computed
// `mtlr`/`blr` that leaves that epilogue in place: __attribute__((noreturn))
// is a syntax error here, and there is no mtlr intrinsic. The 0x14 bytes stay
// the gap after this function; widening the symbol does not reproduce them.
void LaunchDol(ModemLaunchContext *ctx) {
    u32 size = (ctx->payload_size + 0x132) & ~0x1Fu;
    DolImageView *image = reinterpret_cast<DolImageView *>(ctx->field_104);
    void *reserved = reinterpret_cast<void *>(0x80003100);

    memmove(reserved, ctx, size);
    DCStoreRange(reserved, size);
    OSResetSystem(OS_RESET_SHUTDOWN, 0, FALSE);

    memset(reinterpret_cast<void *>(image->bss_address), 0, image->bss_size);
    DCStoreRange(reinterpret_cast<void *>(image->bss_address), image->bss_size);

    for (u32 i = 0; i < 7; i++) {
        u32 offset = image->text_offset[i];
        void *dest = reinterpret_cast<void *>(image->text_address[i]);
        u32 length = image->text_size[i];
        if (offset == 0) {
            break;
        }
        memmove(dest, reinterpret_cast<u8 *>(image) + offset, length);
        DCStoreRange(dest, length);
        ICInvalidateRange(dest, length);
    }
    for (u32 i = 0; i < 11; i++) {
        u32 offset = image->data_offset[i];
        void *dest = reinterpret_cast<void *>(image->data_address[i]);
        u32 length = image->data_size[i];
        if (offset == 0) {
            break;
        }
        memmove(dest, reinterpret_cast<u8 *>(image) + offset, length);
        DCStoreRange(dest, length);
    }

    __isync();
    reinterpret_cast<void (*)()>(image->entry)();
}

}
