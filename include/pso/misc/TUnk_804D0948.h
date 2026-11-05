#ifndef PSO_MISC_TUNK_804D0948_H
#define PSO_MISC_TUNK_804D0948_H
#include "types.h"
#include "pso/misc/TUnk_804D0618.h"

class TUnk_804D0948 : public TUnk_804D0618 {
public:
    virtual ~TUnk_804D0948();
    void sub_8026DE94();
    virtual void render();
    virtual void run_task();
    u8 unk_88[0x4];
};
typedef char TUnk_804D0948_size[sizeof(TUnk_804D0948) == 0x8C ? 1 : -1];

#endif
