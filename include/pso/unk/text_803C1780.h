#ifndef PSO_UNK_TEXT_803C1780_H
#define PSO_UNK_TEXT_803C1780_H

#include "types.h"

extern "C" {
// WAV fmt/data scanner. The placeholder name retains unresolved library ownership.
s32 TLobby__sub_803C1780(u8 *buffer, s32 size, s16 *data_offset,
                        s8 *flags, s8 *bits_per_sample, s8 *block_align,
                        s8 *channels, s32 *sample_rate, s32 *sample_count,
                        s32 *codec, s16 *encoding);
void TLobby__sub_803C19D8(void);
void TLobby__sub_803C1A00(u8 *arg0, s32 arg1);
}

#endif
