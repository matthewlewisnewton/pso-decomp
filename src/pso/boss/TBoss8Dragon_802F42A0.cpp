#include "types.h"
#include "pso/unk/text_803D96A8.h"
#include "pso/boss/TBoss8Dragon.h"

extern "C" {

s32 scale_current_matrix(void *);
s32 post_translate_matrix(void *);
s32 rotate_matrix_z(int, int);
s32 rotate_matrix_x(int, int);
s32 rotate_matrix_y(int, int);
s32 push_matrix();
s32 draw__10TObjMotionFv(void *, int);

extern u8 *TBoss8Dragon__data_805D6988;

void TBoss8Dragon::draw() {
    void *saved_model;
    u8 *temp_r4;

    push_matrix();
    post_translate_matrix((void *)&this->position);
    rotate_matrix_y(0, this->rotation.yaw);
    rotate_matrix_x(0, this->rotation.pitch);
    rotate_matrix_z(0, this->rotation.roll);
    scale_current_matrix((void *)&this->scale);
    saved_model = this->model;
    temp_r4 = (unsigned char *) (*(void **)((s8 *)TBoss8Dragon__data_805D6988 + 0x42C));
    this->model = *(void **)((s8 *)temp_r4 + 0x28);
    draw__10TObjMotionFv(this, (int)temp_r4);
    this->model = saved_model;
    pop_matrix();
}

}
