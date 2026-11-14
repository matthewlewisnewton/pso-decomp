#include "pso/misc/TWindowMeseta.h"
#include "pso/misc/TWindowOptionCtrl_8026CBA4.h"
#include "pso/misc/TWindowSubStatusDisp.h"

extern "C" {
#pragma push
#pragma scheduling off
TWindowMeseta *create_meseta_window(s32 client) {
    return new TWindowMeseta(get_window_layout_position(0x28), client,
        (s32)TWindowSubStatusDisp::get_message_10(0x82));
}
#pragma pop
}
