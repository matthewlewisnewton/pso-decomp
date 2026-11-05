#ifndef PSO_MISC_TUNK_804CE964_H
#define PSO_MISC_TUNK_804CE964_H
#include "types.h"
#include "pso/misc/TUnk_804CE018.h"
#include "pso/misc/TWindowBase.h"

class TUnk_804CE964 : public TUnk_804CE018 {
public:
    virtual ~TUnk_804CE964();
    virtual void render();
    virtual void run_task();
    void * m_60;
    u8 unk_64[0x4];
    f32 m_68;
    u8 unk_6C[0x8];
};
typedef char TUnk_804CE964_size[sizeof(TUnk_804CE964) == 0x74 ? 1 : -1];

#endif
