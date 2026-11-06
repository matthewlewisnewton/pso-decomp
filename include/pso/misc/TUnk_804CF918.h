#ifndef PSO_MISC_TUNK_804CF918_H
#define PSO_MISC_TUNK_804CF918_H

#include "types.h"
#include <stddef.h>

class TWindowDrawContext;

// Virtuals, in vtable order: destructor, update, render, calc_bar_width.
// The last slot of this base is pure, so the table word is 0.
class TUnk_804CF918 {
public:
    u16 flags;
    s16 m_2;

    virtual ~TUnk_804CF918();
    virtual void update();
    virtual void render(TWindowDrawContext *context);
    virtual void calc_bar_width() = 0;

    TUnk_804CF918(s16 arg);
};

typedef char TUnk_804CF918_size[sizeof(TUnk_804CF918) == 8 ? 1 : -1];
typedef char TUnk_804CF918_flags_offset[offsetof(TUnk_804CF918, flags) == 0 ? 1 : -1];
typedef char TUnk_804CF918_m_2_offset[offsetof(TUnk_804CF918, m_2) == 2 ? 1 : -1];

#endif
