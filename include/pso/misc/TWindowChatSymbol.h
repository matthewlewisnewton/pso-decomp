#ifndef PSO_MISC_TWINDOWCHATSYMBOL_H
#define PSO_MISC_TWINDOWCHATSYMBOL_H

#include "types.h"
#include "pso/misc/TWindowBase.h"

struct TWindowChatSymbol : public TWindowBase {
    virtual ~TWindowChatSymbol();
    virtual void render();
    u32 m_60;
    u32 m_64;
    virtual void run_task();
    void *destroy(s16 arg1);
    void set_selection(u32 preset);
    void update_visibility();
};

typedef char TWindowChatSymbol_size[sizeof(TWindowChatSymbol) == 0x68 ? 1 : -1];
#endif
