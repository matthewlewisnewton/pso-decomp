#include "pso/misc/WordSelectMessage.h"
#include "types.h"
#include "pso/misc/TWindowDD_80348BF4.h"
#include "pso/misc/TWindowDD.h"

extern "C" {

s32 handle_word_select__9TWindowDDFv();
}
extern s32 local_client_id;
extern u32 TWindowDD__word_select_lists;

void handle_6x74_word_select(u8 *arg0) {
    handle_word_select__9TWindowDDFv();
    if ((u32) TWindowDD__word_select_lists != 0U) {
        if ((s32) *(u16 *)((s8 *)arg0 + 2) != (s32) local_client_id) {
            ((TWindowDD *)(arg0 + 4))->update_selected_id();
        }
        TWindowDD::build_player_word_lists();
        show_word_select_message((WordSelectMessage *)(arg0 + 4), *(u16 *)(arg0 + 2));
    }
}
