#include "types.h"
#include "pso/unk/text_80130EA0.h"
#include "pso/player/TObjPlayer.h"

extern "C" {

s32 scale_current_matrix(s32);
s32 post_translate_matrix(s32);
}

void yasminkov_2000h_node_callback(s32 arg0) {
    s32 player_list;

    player_list = TObjPlayer::get_player_list();
    switch (player_list) {
    case 1:
        post_translate_matrix(arg0 + 0x20C);
        return;
    case 2:
        scale_current_matrix(arg0 + 0x1FC);
        return;
    }
}
