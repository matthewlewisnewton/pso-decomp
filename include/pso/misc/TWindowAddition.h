#ifndef PSO_MISC_TWINDOWADDITION_H
#define PSO_MISC_TWINDOWADDITION_H
#include "types.h"
#include <stddef.h>
#include "pso/misc/TWindowBase.h"

class TWindowAddition : public TWindowBase {
public:
    TWindowAddition(u8 *descriptor, s16 client, u8 *position);
    virtual ~TWindowAddition();
    s32 sub_80266B18(s32);
    void sub_802443B4(u8 *descriptor);
    void step_window_tween();
    void set_position_xy(f32, f32);

    f32 m_60;
    f32 m_64;
    f32 m_68;
    f32 m_6c;
};

typedef char TWindowAddition_size[sizeof(TWindowAddition) == 0x70 ? 1 : -1];
typedef char TWindowAddition_m60[offsetof(TWindowAddition, m_60) == 0x60 ? 1 : -1];
typedef char TWindowAddition_m64[offsetof(TWindowAddition, m_64) == 0x64 ? 1 : -1];
typedef char TWindowAddition_m68[offsetof(TWindowAddition, m_68) == 0x68 ? 1 : -1];
typedef char TWindowAddition_m6c[offsetof(TWindowAddition, m_6c) == 0x6C ? 1 : -1];

#endif
