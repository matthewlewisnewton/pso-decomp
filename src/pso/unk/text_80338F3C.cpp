#include "pso/misc/TUnk_804EF4E0.h"
#include "pso/misc/TWindowOptionCtrl_8026CBA4.h"

extern "C" u8 lbl_804EF4CC[];

TUnk_804EF4E0::TUnk_804EF4E0(s32 heading)
    : TUnk_804D0948(get_window_layout_position(0xB0), heading, 0x40, lbl_804EF4CC) {}
