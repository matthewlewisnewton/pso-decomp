#include "pso/render/reflection.h"
#include "types.h"
#include "pso/object/TObjMotion.h"
#include "pso/enemy/TObjEneRecon_8029E89C.h"
#include "pso/math/MatrixTransforms.h"
#include "pso/unk/text_803D96A8.h"
#include "pso/enemy/TObjEneRecon.h"
#include "pso/enemy/TObjEneMe3SinowZoa.h"
#include "pso/enemy/TObjEneRe7Berura.h"
#include "pso/object/TObjFish.h"

extern "C" {

s32 get_mode__11TCameraCtrlFPv(void *);
s32 post_translate_matrix(void *);
s32 rotate_matrix_y(int, int);
s32 push_matrix();

extern const f32 TObjEneMe3SinowZoa__data_805DF31C;

s32 TObjEneMe3SinowZoa::render_model_if_visible() {
    if (get_mode__11TCameraCtrlFPv(((s32 *)&main_task)) & 0x20) {
        if (push_reflection_matrix((Vec *)(((u8 *)this) + 0x3D4)) != 0) {
            TObjFish::set_global_param((int) (*(s32 *)((s8 *)((u8 *)this) + 0x24)));
            push_matrix();
            post_translate_matrix((void *) (((u8 *)this) + 0x38));
            translate_matrix(0, TObjEneMe3SinowZoa__data_805DF31C, (f32) (*(f32 *)((s8 *)((u8 *)this) + 0x3E4)), TObjEneMe3SinowZoa__data_805DF31C);
            rotate_matrix_y(0, (int) (*(s32 *)((s8 *)((u8 *)this) + 0x60)));
            this->draw();
            pop_matrix();
            restore_render_scissor(1);
        }
        return 1;
    }
    return 0;
}

}
