#ifndef PSO_MISC_TWINDOWSUBAREAMAPDISP_H
#define PSO_MISC_TWINDOWSUBAREAMAPDISP_H

#include "types.h"
#include "pso/misc/TWindowBase.h"

struct TWindowSubAreaMapDisp : public TWindowBase {
    TWindowSubAreaMapDisp();
    virtual ~TWindowSubAreaMapDisp();
    f32 m_60;
    f32 m_64;
    f32 m_68;
    u32 m_6c;
    void *m_70; // Owned opaque heading under the legacy release protocol.
    char *m_74; // Owned terminator-inclusive text array.
    void update_manual_scroll();
    virtual void render();
    virtual void run_task();
    void update_visibility();
};

typedef char TWindowSubAreaMapDisp_size[sizeof(TWindowSubAreaMapDisp) == 0x78 ? 1 : -1];

typedef char AreaMapDisp_scroll[offsetof(TWindowSubAreaMapDisp, m_60) == 0x60 ? 1 : -1];
typedef char AreaMapDisp_heading[offsetof(TWindowSubAreaMapDisp, m_70) == 0x70 ? 1 : -1];
typedef char AreaMapDisp_text[offsetof(TWindowSubAreaMapDisp, m_74) == 0x74 ? 1 : -1];

extern "C" {
void TWindowSubStatusDisp__sub_80271A6C(s32 arg0, u8 *arg1);
void fn_80271848(s32 arg0, u8 *arg1);
}

#endif
