#include "pso/system/CurrentTextureList.h"
#include "types.h"
#include "pso/system/GinjaMaterial.h"
#include "pso/unk/text_803D96A8.h"
#include "pso/object/TObjDoorJung.h"
#include "pso/object/TObjLazerFenceExtra.h"
#include "pso/TParticleCtrl.h"
#include "pso/object/TObjFish.h"
struct Obj_80192554 { u8 pad0[0x38]; u8 f38[0x24]; s32 f5C; s32 f60; u8 pad64[0x48]; s32 fAC; u8 padB0[8]; f32 fB8; s32 fBC; s32 fC0; s32 fC4; s32 fC8[4]; };

extern "C" {
void rotate_matrix_y(int, int);
void push_matrix();
void post_translate_matrix(void *);
void draw_ginja_model_with_motion(s32, s32, f32);
extern u16 lbl_80445B7C[];
extern s32 lazer_fence_norm_texture_list;
void TObjLazerFenceExtra::draw_lazer_fence_extra_model() {
    Obj_80192554 *arg0 = (Obj_80192554 *)this;
    s32 i;
    for (i = 0; i < 4; i++) {
        ((TObjDoorJung *)(arg0->fC8[i]))->free_children((void *)lbl_80445B7C[arg0->fAC]);
    }
    set_current_texture_list((GinjaTextureList *)(lazer_fence_norm_texture_list));
    push_matrix();
    post_translate_matrix(arg0->f38);
    rotate_matrix_y(0, this->rotation_y);
    draw_ginja_object((void *)this->m_d8);
    TParticleCtrl::begin_effect_render();
    draw_ginja_model_with_motion(arg0->fC0, this->m_c4, arg0->fB8);
    TParticleCtrl::end_effect_render();
    pop_matrix();
}

}
