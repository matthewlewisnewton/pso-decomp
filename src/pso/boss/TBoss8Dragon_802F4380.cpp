#include "types.h"
#include "pso/TMainTask.h"
#include "pso/boss/TBoss8Dragon.h"
#include "pso/misc/TCameraCtrl.h"
#include "pso/player/demo_mode.h"

extern "C" s32 is_split_screen();

extern "C" void TBoss8Dragon__sub_802F4380(TBoss8Dragon *self) {
    s32 view = 0;
    u8 pos[0xC];

    if (check_demo_mode() != 0) {
        self->draw_motion_model();
        return;
    }
    if (is_split_screen() != 0) {
        view = TCameraCtrl::get_camera_mode();
    }
    self->sub_802F4098(pos);
    if (self->defer_render() != 0) {
        if ((TCameraCtrl::get_mode(&main_task) & MAIN_TASK_SCENE_PASSES) == 0) {
            self->render_body_model();
            self->copy_vectors();
        }
        if (self->renderFadeStates[view].isFading() == 0) {
            self->draw_with_fade((s32)pos, view);
        }
        self->render_nodes_flagged();
    } else if (self->renderFadeStates[view].isFading() != 0) {
        self->draw_with_fade((s32)pos, view);
    }
}
