#include "types.h"
#include "pso/TMainTask.h"
#include "pso/boss/TBoss8Dragon.h"
#include "pso/misc/TCameraCtrl.h"
#include "pso/player/demo_mode.h"

extern "C" s32 is_split_screen();

void TBoss8Dragon::render() {
    s32 view = 0;
    u8 pos[0xC];

    if (check_demo_mode() != 0) {
        draw_motion_model();
        return;
    }
    if (is_split_screen() != 0) {
        view = TCameraCtrl::get_camera_mode();
    }
    sub_802F4098(pos);
    if (defer_render() != 0) {
        if ((TCameraCtrl::get_mode(&main_task) & MAIN_TASK_SCENE_PASSES) == 0) {
            render_body_model();
            copy_vectors();
        }
        if (renderFadeStates[view].isFading() == 0) {
            draw_with_fade((s32)pos, view);
        }
        render_nodes_flagged();
    } else if (renderFadeStates[view].isFading() != 0) {
        draw_with_fade((s32)pos, view);
    }
}
