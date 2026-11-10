#include "types.h"
#include "pso/misc/TWindowSimpleStatus.h"
#include "pso/misc/TWindowStatus.h"
#include "pso/unk/text_80271400.h"

extern "C" {
s32 is_split_screen();
s32 get_window_layout_position(int);
}
extern u8 status_window_settings[];
s32 create_status_window(s32 arg0) {
    s32 window_layout_position;
    s32 var_r0;
    window_layout_position = get_window_layout_position(0x1C);
    if (is_split_screen() != 0) {
        return (s32)TWindowSimpleStatus::create((void *)window_layout_position, arg0);
    }
    var_r0 = (s32)new TWindowStatus((void *)window_layout_position, arg0, status_window_settings);
    return var_r0;
}
