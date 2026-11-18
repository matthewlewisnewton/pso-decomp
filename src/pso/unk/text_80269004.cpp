#include "pso/misc/TUnk_804D0658.h"

extern "C" u8 choice_setting_popup_window_descriptor[];

TUnk_804D0658::TUnk_804D0658(void *position, u32 count)
    : TWindowAddition(choice_setting_popup_window_descriptor, 4, (u8 *)position) {
    initialize_entries(count);
}
