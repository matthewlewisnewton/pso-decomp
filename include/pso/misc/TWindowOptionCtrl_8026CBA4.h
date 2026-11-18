#ifndef PSO_MISC_TWINDOWOPTIONCTRL_8026CBA4_H
#define PSO_MISC_TWINDOWOPTIONCTRL_8026CBA4_H

#include "types.h"

// Window origin for one layout slot.
struct WindowLayoutPosition {
    f32 x;
    f32 y;
};

extern "C" {
extern const WindowLayoutPosition window_layout_rect_table[210];
extern const WindowLayoutPosition window_layout_position_table[92];
WindowLayoutPosition *get_window_layout_position(s32 index);
}

#endif
