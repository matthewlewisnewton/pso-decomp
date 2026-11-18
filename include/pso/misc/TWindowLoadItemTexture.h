#ifndef PSO_MISC_TWINDOWLOADITEMTEXTURE_H
#define PSO_MISC_TWINDOWLOADITEMTEXTURE_H

#include "types.h"
#include "pso/misc/TWindowBase.h"

class TItemTexLoad;
struct GinjaTextureList;

struct TWindowLoadItemTexture : public TWindowBase {
    TWindowLoadItemTexture(void *position, void *extent, s32 client);
    virtual ~TWindowLoadItemTexture();
    virtual void render();
    virtual void run_task();
    static TWindowLoadItemTexture *create(void *position, s32 client);
    void sub_80262814(s32 item);

    u8 m_60;
    u8 m_61;
    u8 _pad62[0x2];
    f32 m_64;
    f32 m_68;
    TItemTexLoad *m_6c; // Managed task; destruction is queued, not immediate.
    GinjaTextureList *m_70; // Borrowed from the loader after it reports readiness.
};

typedef char TWindowLoadItemTexture_size[sizeof(TWindowLoadItemTexture) == 0x74 ? 1 : -1];
typedef char LoadTexture_scale[offsetof(TWindowLoadItemTexture, m_64) == 0x64 ? 1 : -1];
typedef char LoadTexture_loader[offsetof(TWindowLoadItemTexture, m_6c) == 0x6C ? 1 : -1];
typedef char LoadTexture_list[offsetof(TWindowLoadItemTexture, m_70) == 0x70 ? 1 : -1];

extern "C" {
TWindowLoadItemTexture *fn_802628C0(void *position, void *extent, s32 client);
void fn_8026287C(TWindowLoadItemTexture *window);
void fn_80262C2C(TWindowLoadItemTexture *window);
}

#endif
