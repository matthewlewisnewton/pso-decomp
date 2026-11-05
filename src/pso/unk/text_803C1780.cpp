#include "pso/unk/text_803C1780.h"

#include <stddef.h>
#include <string.h>

struct WaveFormatChunk {
    u32 tag;
    u32 size;
    u16 format;
    u16 channels;
    u32 sample_rate;
    u32 byte_rate;
    u16 block_align;
    u16 bits_per_sample;
};
struct WaveDataChunk {
    u32 tag;
    u32 size;
};
typedef char WaveFormatChunk_size[sizeof(WaveFormatChunk) == 0x18 ? 1 : -1];
typedef char WaveFormatChunk_format[offsetof(WaveFormatChunk, format) == 8 ? 1 : -1];
typedef char WaveFormatChunk_channels[offsetof(WaveFormatChunk, channels) == 0xA ? 1 : -1];
typedef char WaveFormatChunk_rate[offsetof(WaveFormatChunk, sample_rate) == 0xC ? 1 : -1];
typedef char WaveFormatChunk_align[offsetof(WaveFormatChunk, block_align) == 0x14 ? 1 : -1];
typedef char WaveFormatChunk_bits[offsetof(WaveFormatChunk, bits_per_sample) == 0x16 ? 1 : -1];
typedef char WaveDataChunk_size[sizeof(WaveDataChunk) == 8 ? 1 : -1];

// The middleware uses -inline off. These local expressions take only unsigned
// values or side-effect-free 16-bit field reads and emit no out-of-line helpers.
#define WAVE_SWAP16(value) ((((value) >> 8) & 0xFF) | (((value) << 8) & 0xFF00))
#define WAVE_SWAP32(value) ((((value) >> 24) & 0xFF) | (((value) >> 8) & 0xFF00) | \
                            (((value) << 8) & 0xFF0000) | (((value) << 24) & 0xFF000000))
extern "C" {
extern char *lbl_805D4650;
extern char *lbl_805D4654;
// Propagation folds the chunk address into indexed loads and changes register
// allocation. Keep the explicit header views needed to reproduce the original 600-byte body.
#pragma push
#pragma opt_propagation off
s32 TLobby__sub_803C1780(u8 *buffer, s32 size, s16 *data_offset,
                        s8 *flags, s8 *bits_per_sample, s8 *block_align,
                        s8 *channels, s32 *sample_rate, s32 *sample_count,
                        s32 *codec, s16 *encoding) {
    s32 offset;
    WaveFormatChunk *format;
    WaveDataChunk *data;
    s32 data_size;
    s16 payload_offset;
    for (offset = 0; offset < size; ++offset) {
        if (memcmp(buffer + offset, lbl_805D4650, 4) == 0) {
            break;
        }
    }
    if (offset == size) {
        return -1;
    }
    if (offset % 4 != 0) {
        return -1;
    }
    // Keep 32-bit address addition at the file-layout boundary: pointer addition
    // reverses the add operands under GC/2.6. Both views are read-only in use.
    format = reinterpret_cast<WaveFormatChunk *>(offset + reinterpret_cast<u32>(buffer));
    if (static_cast<s16>(WAVE_SWAP16(format->format)) > 1) {
        return -1;
    }
    for (offset = 0; offset < size; ++offset) {
        if (memcmp(buffer + offset, lbl_805D4654, 4) == 0) {
            break;
        }
    }
    if (offset == size) {
        return -1;
    }
    data = reinterpret_cast<WaveDataChunk *>(offset + reinterpret_cast<u32>(buffer));
    data_size = WAVE_SWAP32(static_cast<u32>(data->size));
    payload_offset = offset + 8;
    *data_offset = payload_offset;
    *flags = -1;
    *sample_rate = WAVE_SWAP32(format->sample_rate);
    *channels = WAVE_SWAP16(format->channels);
    *bits_per_sample = WAVE_SWAP16(format->bits_per_sample);
    *block_align = WAVE_SWAP16(format->block_align);
    // Preserve the original validation order; these divisions precede the
    // zero/channel checks below. This is a matching parser, not a hardened one.
    *sample_count = data_size / *block_align;
    *codec = 1;
    if (*bits_per_sample == 16) {
        *encoding = 0;
    } else if (*bits_per_sample == 8) {
        *encoding = 1;
    } else if (*bits_per_sample == 4) {
        *block_align = *channels * 2;
        *codec = 4;
        *sample_count = (data_size / 2) / *channels;
        *bits_per_sample = 16;
        *encoding = 2;
    }
    if (*bits_per_sample == 0) {
        return -1;
    }
    if (*block_align == 0) {
        return -1;
    }
    if (*channels <= 0 || *channels > 2) {
        return -1;
    }
    return *sample_rate == 0 ? -1 : 0;
}
#pragma pop
}

#undef WAVE_SWAP16
#undef WAVE_SWAP32

#include "pso/misc/TLobby.h"

typedef void (*RecoveredCallback_1268626c296b)(void *);
struct Obj_803C1A24 { u8 pad[0xAC]; void *fac; };

extern RecoveredCallback_1268626c296b lbl_805D7514;
extern s32 (*lbl_805D7510)();

void TLobby__sub_803C19D8(void) {
    lbl_805D7510();
}
void TLobby__sub_803C1A00(u8 *arg0, s32 arg1) {
    *(s32 *)((s8 *)arg0 + 0xB0) = arg1;
    *(u32 *)((s8 *)arg0 + 0xB4) = (u32) (arg1 / 96);
}
void TLobby::invoke_notify_callback() {
    Obj_803C1A24 *arg0 = (Obj_803C1A24 *)this;
    if (arg0->fac != 0) {
        lbl_805D7514(arg0->fac);
    }
}
