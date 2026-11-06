struct NJS_OBJECT;
#include "types.h"
#include "pso/unk/text_803D96A8.h"
#include "pso/enemy/TObjEneRecon.h"
#include "pso/TParticleCtrl.h"

extern "C" {

s32 update_camera_sequence__9TObjEneDDFv();
s32 matrix_mult_vec(s32, s32, s32);
s32 push_matrix();

extern s32 recon_intro_stage;
extern s32 recon_model_matrix_ptr;

void TObjEneRecon::advance_intro_stage(NJS_OBJECT *) {
    switch ((s32) recon_intro_stage) {
    case 0:
        push_matrix();
        update_camera_sequence__9TObjEneDDFv();
        matrix_mult_vec(0, recon_model_matrix_ptr, recon_model_matrix_ptr);
        pop_matrix();
        break;
    case 10:
        TParticleCtrl::begin_effect_render();
        break;
    }
    recon_intro_stage += 1;
}

}
