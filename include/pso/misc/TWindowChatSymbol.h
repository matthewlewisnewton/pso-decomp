#ifndef PSO_MISC_TWINDOWCHATSYMBOL_H
#define PSO_MISC_TWINDOWCHATSYMBOL_H

#include "types.h"
#include "pso/misc/TUnk_804CE018.h"

struct TWindowChatSymbol : public TUnk_804CE018 {
    virtual ~TWindowChatSymbol();
    virtual void render();
    u32 m_60;
    u32 m_64;
    virtual void run_task();
    void *destroy(s16 arg1);
};

typedef char TWindowChatSymbol_size[sizeof(TWindowChatSymbol) == 0x68 ? 1 : -1];
#endif
