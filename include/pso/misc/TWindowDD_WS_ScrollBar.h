#ifndef PSO_MISC_TWINDOWDD_WS_SCROLLBAR_H
#define PSO_MISC_TWINDOWDD_WS_SCROLLBAR_H
#include "types.h"
#include "pso/misc/TWindowBase.h"

class TWindowDD_WS_ScrollBar : public TWindowBase {
public:
    virtual ~TWindowDD_WS_ScrollBar();
    void *dt(s16);
    // The setters store counts and positions as floats for thumb geometry.
    f32 inverse_item_count;
    f32 item_count;
    f32 visible_count;
    f32 first_index;
};
typedef char TWindowDD_WS_ScrollBar_size[sizeof(TWindowDD_WS_ScrollBar) == 0x70 ? 1 : -1];

typedef char TWindowDD_WS_ScrollBar_inverse_item_count[offsetof(TWindowDD_WS_ScrollBar, inverse_item_count) == 0x60 ? 1 : -1];
typedef char TWindowDD_WS_ScrollBar_item_count[offsetof(TWindowDD_WS_ScrollBar, item_count) == 0x64 ? 1 : -1];
typedef char TWindowDD_WS_ScrollBar_visible_count[offsetof(TWindowDD_WS_ScrollBar, visible_count) == 0x68 ? 1 : -1];
typedef char TWindowDD_WS_ScrollBar_first_index[offsetof(TWindowDD_WS_ScrollBar, first_index) == 0x6C ? 1 : -1];

#endif
