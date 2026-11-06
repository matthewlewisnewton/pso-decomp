#include "types.h"
#include "pso/player/TObjPlayer_801BE1C0.h"
#include "pso/player/TObjPlayer_801BFED4.h"
#include "pso/unk/text_801BE104.h"
#include "pso/player/TObjPlayer.h"

extern "C" {
extern u8 TObjPlayer__char_data_array[];
void __destroy_arr(void *arr, void *dtor, u32 size, u32 n);
void __register_global_object(void *obj, void *dtor, void *chain);
void *__construct_array(void *, void *, void *, u32, u32);
void init_char_data__10TObjPlayerFv(void *);

u8 TObjPlayer__arrival_override_table[0xF0];
u8 player_slot_table[0x30];
u8 lobby_rule_settings[0x24];
u8 lbl_8050EA64[0xC];
u8 TObjPlayer__char_data_array[0x42C * 0xC];
void TObjPlayer__sub_801BE104(void) {
    __construct_array(TObjPlayer__arrival_override_table, (void *)TObjPlayer__sub_801BFF80, NULL, 0x14, 0xC);
    ((TObjPlayer *)lobby_rule_settings)->reset_lobby_settings();
    __construct_array(TObjPlayer__char_data_array, (void *)init_char_data__10TObjPlayerFv, (void *)destroy_char_data__10TObjPlayerFis, 0x42C, 0xC);
    __register_global_object(NULL, (void *)TObjPlayer::destroy_char_data_array, lbl_8050EA64);
}

void TObjPlayer::destroy_char_data_array() {
    __destroy_arr(TObjPlayer__char_data_array, (void *)destroy_char_data__10TObjPlayerFis, 0x42c, 0xc);
}

}

__declspec(section ".ctors") static void *const __sinit_text_801BE104_cpp_ref = (void *)TObjPlayer__sub_801BE104;
