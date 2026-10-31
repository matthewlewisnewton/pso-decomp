struct NJS_OBJECT;
#include "types.h"
#include "pso/unk/text_803D96A8.h"
#include "pso/player/TObjPlayer.h"

extern "C" {

s32 update_camera_sequence__9TObjEneDDFv();
s32 mult_vec_array__10TObjPlayerFUll(s32, s32, s32, s32);
s32 rotate_matrix_y(s32, s32);
s32 push_matrix();

extern s32 lbl_805D5178;
extern s32 lbl_805D517C;
extern s32 lbl_805D5180;

void TObjPlayer::update_effect_sequence(NJS_OBJECT *) {
    switch ((s32) lbl_805D5178) {
    case 1:
        rotate_matrix_y(0, lbl_805D517C);
        break;
    case 14:
        push_matrix();
        update_camera_sequence__9TObjEneDDFv();
        mult_vec_array__10TObjPlayerFUll(0, lbl_805D5180, lbl_805D5180, 2);
        pop_matrix();
        break;
    }
    lbl_805D5178 += 1;
}

}
