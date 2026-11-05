#ifndef PSO_MISC_TUNK_804CF918_H
#define PSO_MISC_TUNK_804CF918_H

#include "types.h"
#include <stddef.h>

class TWindowKeyBoardSoft;

// 0x18-byte dispatch table stored at object +4. That slot is this class's
// vptr: linked callers of calc_bar_width load it with lwz r12,4(r3) and the
// function at table+0x14. A separate pointer member would sit beside the
// vptr and grow the object.
struct TUnk_804CF918_table {
    s32 top_offset;
    s32 rtti;
    void (*destroy)(void *, s16);
    void (*fn_0c)();
    void (*fn_10)();
    void (*calc_bar_width)();
};

extern "C" {
extern TUnk_804CF918_table lbl_804CF918;
extern TUnk_804CF918_table lbl_804CF930;
}

class TUnk_804CF918 {
public:
    u16 flags;
    s16 m_2;

    virtual ~TUnk_804CF918();
    virtual void update();
    virtual void render(TWindowKeyBoardSoft *context);
    virtual void calc_bar_width() = 0;
};

typedef char TUnk_804CF918_size[sizeof(TUnk_804CF918) == 8 ? 1 : -1];
typedef char TUnk_804CF918_flags_offset[offsetof(TUnk_804CF918, flags) == 0 ? 1 : -1];
typedef char TUnk_804CF918_m_2_offset[offsetof(TUnk_804CF918, m_2) == 2 ? 1 : -1];

#endif
