#ifndef PSO_MISC_TWINDOWSIMPLESTATUS_H
#define PSO_MISC_TWINDOWSIMPLESTATUS_H

#include "types.h"
#include "pso/misc/TWindowBase.h"

struct TWindowSimpleStatus : public TWindowBase {
    TWindowSimpleStatus(void *position, s32 client, u8 *descriptor);
    virtual ~TWindowSimpleStatus();
    void draw_background(u8 *);
    void apply_random_shake();
    void update_status_icons(void *);
    s16 get_width();
    virtual void render();
    u32 m_60;
    virtual void run_task();
    static TWindowSimpleStatus *create(void *position, s32 client);
    TWindowBase *icon_windows[5]; // Refresh manages five; original destructor closes four.
};

typedef char TWindowSimpleStatus_size[sizeof(TWindowSimpleStatus) == 0x78 ? 1 : -1];

typedef char SimpleStatus_icons[offsetof(TWindowSimpleStatus, icon_windows) == 0x64 ? 1 : -1];
typedef char SimpleStatus_fifth_icon[offsetof(TWindowSimpleStatus, icon_windows) + 4 * sizeof(void *) == 0x74 ? 1 : -1];

#endif
