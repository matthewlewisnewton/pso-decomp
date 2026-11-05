#include "types.h"
#include "pso/unk/text_80271400.h"

struct RecoveredGlobal_80271400_lbl_804D0F78 { s32 value; u8 remaining[0x10]; };
typedef char RecoveredGlobal_80271400_lbl_804D0F78_size[sizeof(RecoveredGlobal_80271400_lbl_804D0F78) == 0x14 ? 1 : -1];

extern "C" {
s32 is_split_screen();
s32 __nw__7TObjectFUl(int);
s32 get_window_layout_position(int);
s32 create__19TWindowSimpleStatusFPv(int, void *);
s32 TWindowStatus__ct(int, int, void *, void *);
}
extern RecoveredGlobal_80271400_lbl_804D0F78 status_window_settings;
s32 create_status_window(s32 arg0) {
    s32 window_layout_position;
    s32 temp_r3;
    s32 var_r0;
    window_layout_position = get_window_layout_position(0x1C);
    if (is_split_screen() != 0) {
        return create__19TWindowSimpleStatusFPv((int)window_layout_position, (void *)arg0);
    }
    temp_r3 = __nw__7TObjectFUl(0x78);
    var_r0 = temp_r3;
    if (var_r0 != 0) {
        var_r0 = TWindowStatus__ct((int)temp_r3, (int)window_layout_position, (void *)arg0, &status_window_settings.value);
    }
    return var_r0;
}
