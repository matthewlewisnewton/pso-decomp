#include "pso/ui/PlayerWindowDispatch.h"
#include "types.h"
#include "pso/unk/text_8024AB18.h"
#include "pso/unk/text_8024AB98.h"

extern "C" {

int get_flag_bit4__11TWindowCtrlFv(void*);
}

void close_window_if_active(void* p) { if (get_flag_bit4__11TWindowCtrlFv(p) == 0) { disable_player_main_menu((s32)p); } }
