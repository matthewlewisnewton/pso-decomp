#ifndef PSO_MISC_TWINDOWQUANTITY_H
#define PSO_MISC_TWINDOWQUANTITY_H

#include "types.h"
#include "pso/misc/TWindowBase.h"

struct TWindowQuantity : public TWindowBase {
    TWindowQuantity(s32 client);
    virtual ~TWindowQuantity();
    virtual void render();
    f32 m_60;
    f32 m_64;
    void set_position(s32 arg1);
    virtual void run_task();
    f32 m_68;
};

typedef char TWindowQuantity_size[sizeof(TWindowQuantity) == 0x6C ? 1 : -1];

typedef char TWindowQuantity_scale_x[offsetof(TWindowQuantity, m_64) == 0x64 ? 1 : -1];
typedef char TWindowQuantity_scale_y[offsetof(TWindowQuantity, m_68) == 0x68 ? 1 : -1];

extern "C" TWindowQuantity *create_window_quantity(s32 client);

#endif
