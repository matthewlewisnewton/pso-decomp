#include "pso/system/CurrentTextureList.h"
#include "types.h"
#include "pso/unk/text_803D96A8.h"
#include "pso/object/TObjGbAdvance.h"

struct VObjBase { char pad[0x18]; };
struct VObj : VObjBase {
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual void m3();
    virtual void m4();
    virtual void m5();
    virtual void m6();
    virtual void m7();
    virtual s32 m8(f32, f32);
};

extern "C" {

s32 post_translate_matrix(void *);
s32 draw_ginja_object();
s32 TObjFish__sub_8001EDB0(s32, s32);
s32 get_bml_model(s32, s32);
s32 rotate_matrix_y(s32, s32);
s32 push_matrix();

extern s32 TObjGbAdvance__data_805D5B74;
extern const f32 lbl_805DBCDC;
extern const f32 lbl_805DBCE0;

void TObjGbAdvance::render() {
    u8 *arg0 = (u8 *)this;
    if (((VObj*)arg0)->m8(lbl_805DBCDC, lbl_805DBCE0) != 0) {
        set_current_texture_list((GinjaTextureList *)(TObjFish__sub_8001EDB0(TObjGbAdvance__data_805D5B74, 0)));
        push_matrix();
        post_translate_matrix((u8 *)&this->position);
        rotate_matrix_y(0, this->rotation.yaw);
        get_bml_model(TObjGbAdvance__data_805D5B74, 0);
        draw_ginja_object();
        get_bml_model(TObjGbAdvance__data_805D5B74, 1);
        draw_ginja_object();
        get_bml_model(TObjGbAdvance__data_805D5B74, 2);
        draw_ginja_object();
        get_bml_model(TObjGbAdvance__data_805D5B74, 3);
        draw_ginja_object();
        pop_matrix();
    }
}

}
