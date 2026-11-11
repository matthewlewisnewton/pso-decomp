#include "pso/misc/WordSelectMessage.h"
#include "types.h"
#include "pso/misc/TWindowDD_803471C0.h"
#include "pso/misc/TWindowDD.h"
#include "pso/misc/TWindowCtrl.h"

extern "C" {

extern s32 window_dd_buffer_a;

void show_word_select_message(WordSelectMessage *words, s32 player) {
    format_word_select_message(words, (char *)window_dd_buffer_a, player);
    TWindowCtrl::open(player, window_dd_buffer_a, 0x4F);
}

u8 TWindowDD::is_id_in_special_range(s16 id) {
    s32 r = 0;
    if (id >= 0x45d && id <= 0x46f && id != 0x46d && id != 0x46e) {
        r = 1;
    }
    return r;
}

s32 TWindowDD__sub_80347238(s16 arg0) {
    u8 var_r3;
    var_r3 = 0;
    if ((arg0 >= 0x300) && (arg0 <= 0x395)) {
        var_r3 = 1;
    }
    return var_r3;
}

}
