#include "types.h"
#include "pso/TMainTask.h"
#include "pso/enemy/TObjEneDD_ST.h"
#include "pso/misc/RenderFadeState.h"
#include "pso/misc/TCameraCtrl.h"
#include "pso/player/demo_mode.h"
#include <stddef.h>

// Hierarchy for this call only. TObjEneDD_ST ends at 0x3C0 with vfunc_104 in
// slot 104; vfunc_105 then draw_motion_model put that call at 0x1A8, and
// defer_render is the TObject method. The destructor is not declared here:
// defining render() as the override emits __vt__12TBoss8Dragon, which the
// hand table in TBoss8Dragon.cpp already provides. TBoss8Dragon.h stays the
// flat overlay the other TUs are matched against (float loads at 0 and 8).
struct TBoss8Dragon : TObjEneDD_ST {
    virtual s32 vfunc_105();
    virtual void draw_motion_model();
    u8 tail_3c0[0x6DC - 0x3C0];
    RenderFadeState renderFadeStates[4];
    void sub_802F4098(u8 *);
    void render_body_model();
    void copy_vectors();
    void draw_with_fade(s32, s32);
    void render_nodes_flagged();
};

typedef char TBoss8Dragon_fade_offset[(offsetof(TBoss8Dragon, renderFadeStates) == 0x6DC) ? 1 : -1];
typedef char TBoss8Dragon_base_size[(sizeof(TObjEneDD_ST) == 0x3C0) ? 1 : -1];

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
