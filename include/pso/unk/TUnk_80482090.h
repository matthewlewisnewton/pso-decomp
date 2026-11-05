#ifndef PSO_UNK_TUNK_80482090_H
#define PSO_UNK_TUNK_80482090_H
#include "types.h"
#include "pso/player/TUnk_804820C0.h"

class TUnk_80482090 : public TUnk_804820C0 {
public:
    virtual ~TUnk_80482090();
    virtual void render();
    virtual void run_task();
    u8 unk_20[0x4D0];
    s32 m_4f0;
    u8 unk_4F4[0xC];
};
typedef char TUnk_80482090_size[sizeof(TUnk_80482090) == 0x500 ? 1 : -1];

#endif
