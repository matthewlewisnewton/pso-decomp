#ifndef PSO_MISC_TWINDOWMESETA_H
#define PSO_MISC_TWINDOWMESETA_H

#include "types.h"
#include "pso/misc/TWindowBase.h"

struct TWindowMeseta : public TWindowBase {
    TWindowMeseta(void *position, s32 client, s32 text);
    virtual ~TWindowMeseta();
    virtual void render();
    f32 m_60;
    u32 m_64;
    u32 m_68;
    f32 m_6c;
    void run_task();
    s32 get_meseta_value();
    void draw_value(s32 arg1);
    f32 m_70;
};

typedef char TWindowMeseta_size[sizeof(TWindowMeseta) == 0x74 ? 1 : -1];
typedef char TWindowMeseta_scale_x[offsetof(TWindowMeseta, m_6c) == 0x6C ? 1 : -1];
typedef char TWindowMeseta_scale_y[offsetof(TWindowMeseta, m_70) == 0x70 ? 1 : -1];

extern "C" TWindowMeseta *create_meseta_window(s32 client);

#endif
