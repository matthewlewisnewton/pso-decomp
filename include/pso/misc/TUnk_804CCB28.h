#ifndef PSO_MISC_TUNK_804CCB28_H
#define PSO_MISC_TUNK_804CCB28_H
#include "types.h"
#include "pso/TObject.h"
#include "pso/system/vector.h"

struct TUnk_804DDF04;

class TUnk_804CCB28 : public TObject {
public:
    virtual ~TUnk_804CCB28();
    void spawn_rafoie_explosion_bursts();
    virtual void render();
    virtual void run_task();
    u8 unk_1C[0x4];
    s16 m_20;
    s16 m_22;
    TUnk_804DDF04 *m_24;
    Vec m_28;
    f32 m_34;
    f32 m_38;
    f32 m_3c;
    f32 m_40;
    f32 m_44;
    f32 m_48;
    f32 m_4c;
    f32 m_50;
    f32 m_54;
    s32 m_58;
    s32 m_5c;
    s32 m_60;
};
typedef char TUnk_804CCB28_size[sizeof(TUnk_804CCB28) == 0x64 ? 1 : -1];

#endif
