#include "pso/TBoss4ZakoDraw.h"
#include "pso/boss/TBoss4ZakoDraw_8030A96C.h"
#include "pso/object/TObject_80019A50.h"

#include "types.h"
#include "pso/TParticleCtrl.h"
#include "pso/player/TObjPlayer.h"

extern u8 boss4_zako_draw_buffers[];
extern u32 dark_falz_controller_instance;
extern s32 TBoss4ZakoDraw__draw_buffer_index;
extern s32 TBoss4ZakoDraw__rotation_phase;

void TBoss4ZakoDraw::render() { TObjPlayer::toggle_particle_effect(); TCameraCtrl__sub_8030ABF4(); TParticleCtrl::end_effect_render(); }
void TBoss4ZakoDraw::run_task() {
    s32 old;
    if (dark_falz_controller_instance == 0U) {
        queue_destruction__7TObjectFv(this);
        return;
    }
    old = TBoss4ZakoDraw__draw_buffer_index;
    *(s32 *)(boss4_zako_draw_buffers + old * 0x784) = 0;
    TBoss4ZakoDraw__draw_buffer_index = old ^ 1;
    if (++TBoss4ZakoDraw__rotation_phase >= 4) {
        TBoss4ZakoDraw__rotation_phase = 0;
    }
}
TBoss4ZakoDraw::~TBoss4ZakoDraw() {}
