#ifndef PSO_UI_WINDOW_TUNK_804D0948_H
#define PSO_UI_WINDOW_TUNK_804D0948_H
#include "types.h"
#include "pso/ui/window/TWindowMenuIconLine.h"

class TUnk_804D0948 : public TWindowMenuIconLine {
public:
    TUnk_804D0948(void *position, s32 heading, u32 count, u8 *descriptor);
    TUnk_804D0948(s32 heading, u32 count, s32 client);
    virtual ~TUnk_804D0948();
    void sub_8026DE94(s32 heading);
    virtual void render();
    virtual void run_task();
    s32 capacity;
};
typedef char TUnk_804D0948_size[sizeof(TUnk_804D0948) == 0x8C ? 1 : -1];

#endif
