#ifndef PSO_MISC_TWINDOWCHATSYMBOL_H
#define PSO_MISC_TWINDOWCHATSYMBOL_H

#include "types.h"
#include "pso/misc/TWindowBase.h"

struct TWindowChatSymbol : public TWindowBase {
    TWindowChatSymbol(void *position, void *size);
    virtual ~TWindowChatSymbol();
    virtual void render();
    u32 m_60;
    u32 m_64;
    virtual void run_task();
};

typedef char TWindowChatSymbol_size[sizeof(TWindowChatSymbol) == 0x68 ? 1 : -1];
#endif
