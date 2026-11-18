#ifndef PSO_UNK_TUNK_804C3E60_H
#define PSO_UNK_TUNK_804C3E60_H
#include "types.h"
#include <stddef.h>
#include "pso/TObject.h"

class TUnk_804C3E60 : public TObject {
public:
    TUnk_804C3E60(TObject *parent, s32 gain_offset, s32 countdown);
    virtual ~TUnk_804C3E60();
    virtual void run_task();
    s32 countdown;
    s32 gain_offset;
};
typedef char TUnk_804C3E60_size[sizeof(TUnk_804C3E60) == 0x24 ? 1 : -1];

typedef char TUnk_804C3E60_countdown_offset[offsetof(TUnk_804C3E60, countdown) == 0x1C ? 1 : -1];
typedef char TUnk_804C3E60_gain_offset[offsetof(TUnk_804C3E60, gain_offset) == 0x20 ? 1 : -1];

extern "C" TUnk_804C3E60 *lbl_805D5D90;
#endif
