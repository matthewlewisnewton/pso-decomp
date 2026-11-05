#ifndef PSO_MISC_TWINDOWDUELRESULT_H
#define PSO_MISC_TWINDOWDUELRESULT_H

#include "types.h"
#include "pso/misc/TUnk_804CE018.h"

struct TWindowDuelResult : public TUnk_804CE018 {
    virtual ~TWindowDuelResult();
    u8 _pad28[8];
    u32 m_68;
    void *init(void *arg1, void *arg2, void *arg3);
    static int set_default_status(void* p, int a1);
};

typedef char TWindowDuelResult_size[sizeof(TWindowDuelResult) == 0x6C ? 1 : -1];
#endif
