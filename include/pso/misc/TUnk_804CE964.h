#ifndef PSO_MISC_TUNK_804CE964_H
#define PSO_MISC_TUNK_804CE964_H
#include "types.h"
#include "pso/misc/TWindowBase.h"

struct ComCardWindowOffset { f32 x, y; };

class TUnk_804CE964 : public TWindowBase {
public:
    TUnk_804CE964(TWindowBase *, ComCardWindowOffset *, s32, s32, s32);
    virtual ~TUnk_804CE964();
    void set_selected_index(s32 value);
    virtual void render();
    virtual void run_task();
    TWindowBase *m_60;
    ComCardWindowOffset offset;
    s32 m_6c;
    s32 m_70;
};
typedef char ComCardFollower_parent[offsetof(TUnk_804CE964, m_60) == 0x60 ? 1 : -1];
typedef char ComCardFollower_offset[offsetof(TUnk_804CE964, offset) == 0x64 ? 1 : -1];
typedef char ComCardFollower_value[offsetof(TUnk_804CE964, m_70) == 0x70 ? 1 : -1];
typedef char TUnk_804CE964_size[sizeof(TUnk_804CE964) == 0x74 ? 1 : -1];

#endif
