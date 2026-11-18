#ifndef PSO_UI_WINDOW_TWINDOWMESETA_H
#define PSO_UI_WINDOW_TWINDOWMESETA_H

#include "types.h"
#include "pso/ui/window/TWindowBase.h"

struct TWindowMeseta : public TWindowBase {
    virtual ~TWindowMeseta();
    virtual void render();
    u8 unknown_30[0x30];
    f32 m_60;
    u32 m_64;
    u32 m_68;
    void* m_6c;
    void run_task();
    s32 get_meseta_value();
    void draw_value(s32 arg1);
    u8 unk_70[0x4];
};

typedef char TWindowMeseta_size[sizeof(TWindowMeseta) == 0x74 ? 1 : -1];
#endif
