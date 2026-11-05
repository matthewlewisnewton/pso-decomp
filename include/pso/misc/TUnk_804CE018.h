#ifndef PSO_MISC_TUNK_804CE018_H
#define PSO_MISC_TUNK_804CE018_H
#include "types.h"
#include <stddef.h>
#include "pso/misc/TWindowAddition.h"

// Shared window image from 0x1C through 0x5F. The methods stay on TWindowBase
// so their symbols stay close__11TWindowBaseFv and the rest of that set.
// Descendants that no longer repeat this prefix inherit this class.
class TUnk_804CE018 : public TWindowAddition {
public:
    u8 frame_pad_1c;
    s8 m_1d;
    u8 frame_pad_1e;
    s8 m_1f;
    union { s16 m_20; u16 m_20u; };
    s16 unk_22;
    void *m_24;
    u8 frame_pad_28[2];
    s16 m_2a;
    union { s32 m_2c; u32 m_2cu; };
    f32 m_30;
    union { s32 m_34; f32 m_34f; u32 m_34u; };
    f32 m_38;
    union { f32 m_3c; f32 unk_3c; s32 *m_3cp; };
    union { f32 m_40; u32 m_40u; };
    union { f32 m_44; u32 m_44u; };
    f32 m_48;
    union { f32 m_4c; void *m_4cp; };
    union { u32 unk_50; u32 m_50; };
    union { f32 m_54; u32 m_54u; };
    f32 m_58;
    union { s32 m_5c; u32 m_5cu; };
};

typedef char TUnk_804CE018_size[sizeof(TUnk_804CE018) == 0x60 ? 1 : -1];
typedef char TUnk_804CE018_unk22[offsetof(TUnk_804CE018, unk_22) == 0x22 ? 1 : -1];
typedef char TUnk_804CE018_m2c[offsetof(TUnk_804CE018, m_2c) == 0x2C ? 1 : -1];
typedef char TUnk_804CE018_m40[offsetof(TUnk_804CE018, m_40) == 0x40 ? 1 : -1];
typedef char TUnk_804CE018_m48[offsetof(TUnk_804CE018, m_48) == 0x48 ? 1 : -1];
typedef char TUnk_804CE018_m54[offsetof(TUnk_804CE018, m_54) == 0x54 ? 1 : -1];
typedef char TUnk_804CE018_m5c[offsetof(TUnk_804CE018, m_5c) == 0x5C ? 1 : -1];

#endif
