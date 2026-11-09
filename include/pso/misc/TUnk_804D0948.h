#ifndef PSO_MISC_TUNK_804D0948_H
#define PSO_MISC_TUNK_804D0948_H
#include "types.h"
#include "pso/misc/TWindowMenuIconLine.h"

class TUnk_804D0948 : public TWindowMenuIconLine {
public:
    TUnk_804D0948(void *position, s32 heading, u32 count, u8 *descriptor);
    TUnk_804D0948(s32 heading, u32 count, s32 client);
    virtual ~TUnk_804D0948();
    void sub_8026DE94(s32 heading);
    virtual void render();
    virtual void run_task();
    u8 unk_88[0x4];
};
typedef char TUnk_804D0948_size[sizeof(TUnk_804D0948) == 0x8C ? 1 : -1];

typedef char TUnk_804D0948_unk_88_offset[offsetof(TUnk_804D0948, unk_88) == 0x88 ? 1 : -1];

#endif
