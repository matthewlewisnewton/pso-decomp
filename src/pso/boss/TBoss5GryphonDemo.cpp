#include "pso/misc/CameraHelpers.h"
#include "pso/TBoss5GryphonDemo.h"
#include "pso/system/vector.h"
#include "pso/object/TObjMotion.h"
#include "pso/boss/TBoss5GryphonColli_C.h"
#include "types.h"
#include "pso/misc/TCameraCtrl.h"
#include "pso/misc/TLobby.h"
#include "pso/player/TObjPlayer.h"

#pragma readonly_strings on

extern "C" {
const char *lbl_805D2810 = "TBoss5GryphonDemo";
}


struct Obj_800665FC { s32 f0; u8 pad4[0x14]; void *f18; f32 f1c; f32 f20; s32 f24; };



extern "C" {
void queue_destruction__7TObjectFv(void *arg0);
void set_camera_capture_overlay_alpha(int a0);
s32 restore_player_cameras();

int TBoss8Dragon__sub_8005D700(void);
s32 activate_camera_mode(s32 arg0);
extern const char *lbl_805D2810;

void TBoss5GryphonDemo::render() {  }

void TBoss5GryphonDemo::run_task() {
    u8 *arg0 = (u8 *)this;
    CameraPlayback *scripted_camera_playback;
    scripted_camera_playback = get_scripted_camera_playback();
    set_camera_capture_overlay_alpha(0x8F);
    if ((scripted_camera_playback->flags & 1) || ((s32) **(s32 **)((s8 *)arg0 + 0x24) == 0)) {
        restore_player_cameras();
        queue_destruction__7TObjectFv((arg0));
    }
}
TBoss5GryphonDemo::~TBoss5GryphonDemo() {}
}
TBoss5GryphonDemo::TBoss5GryphonDemo(TObject *parent, s32 arg2, f32 farg0) : TObject(parent) {
    CameraPlayback c;
    ((Obj_800665FC *)this)->f0 = ((s32)lbl_805D2810);
    ((Obj_800665FC *)this)->f1c = farg0;
    ((Obj_800665FC *)this)->f20 = 0.0f;
    ((Obj_800665FC *)this)->f24 = arg2;
    switch (TBoss8Dragon__sub_8005D700()) {
    case 0:
        c.bank = 1;
        c.index = 0;
        c.flags = 0;
        c.frame = ((Obj_800665FC *)this)->f20;
        c.frame_step = ((Obj_800665FC *)this)->f1c;
        activate_camera_mode(5);
        cache_target_and_forward__11TCameraCtrlFl(&c, 0x238E);
        break;
    }
}
