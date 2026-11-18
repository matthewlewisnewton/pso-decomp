#ifndef PSO_MISC_TWINDOWDD_WS_STRING_H
#define PSO_MISC_TWINDOWDD_WS_STRING_H
#include "types.h"
#include "pso/misc/TWindowBase.h"

class TWindowDD_WS_String : public TWindowBase {
public:
    TWindowDD_WS_String(void *position, void *size, s32 text, s32 mode);
    virtual ~TWindowDD_WS_String();
    virtual void run_task();
    virtual void render();
    void draw(s32, s32, f32);
    void draw_entry_if_visible(void *);
    s32 m_mode;
    f32 m_position[2];
    f32 m_size[2];
};
typedef char TWindowDD_WS_String_mode[offsetof(TWindowDD_WS_String, m_mode) == 0x60 ? 1 : -1];
typedef char TWindowDD_WS_String_position[offsetof(TWindowDD_WS_String, m_position) == 0x64 ? 1 : -1];
typedef char TWindowDD_WS_String_extent[offsetof(TWindowDD_WS_String, m_size) == 0x6C ? 1 : -1];
typedef char TWindowDD_WS_String_size[sizeof(TWindowDD_WS_String) == 0x74 ? 1 : -1];

#endif
