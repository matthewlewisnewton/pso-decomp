#ifndef PSO_MISC_TWINDOWSUBEQUIPKIND_H
#define PSO_MISC_TWINDOWSUBEQUIPKIND_H

#include "types.h"
#include "pso/misc/TWindowMenuIconLine.h"

struct TWindowSubEquipKind : public TWindowMenuIconLine {
    TWindowSubEquipKind(void *position, s32 client);
    virtual ~TWindowSubEquipKind();
    void draw_tab_label(void *);
    virtual void render();
    s16 m_88;
    s16 m_8a;
    virtual void run_task();
};

typedef char TWindowSubEquipKind_size[sizeof(TWindowSubEquipKind) == 0x8C ? 1 : -1];
typedef char TWindowSubEquipKind_state[offsetof(TWindowSubEquipKind, m_88) == 0x88 ? 1 : -1];
typedef char TWindowSubEquipKind_timer[offsetof(TWindowSubEquipKind, m_8a) == 0x8A ? 1 : -1];

#endif
