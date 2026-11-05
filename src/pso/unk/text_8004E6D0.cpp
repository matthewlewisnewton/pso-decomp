#include "types.h"
#include "pso/boss/TBoss4DarkFalz.h"
#include "pso/boss/TBoss4Uro.h"
#include "pso/misc/CameraHelpers.h"
#include "pso/misc/TCameraCtrl_800687BC.h"
#include "pso/object/TObjMotion.h"
#include "pso/system/SoundEffect.h"
#include "pso/system/vector.h"

// The emitter table, motion ids and scripted camera block are one object.
// The vtable that follows them is emitted by the linked TObjDFDemo0 unit.
struct DFDemo1Emitter {
    s32 effect;
    s32 start;
    s32 end;
    f32 offset[3];
};

struct DFDemo1Tables {
    DFDemo1Emitter emitters[4];
    s32 body_motions[6];
    s32 zanzo_motions[2];
    CameraPlayback camera;
};

struct DFDemo1Part {
    s32 model;
    s32 texlist;
    s32 motion;
};

struct DFDemo1Obj {
    s32 name;
    u8 pad4[0x18 - 0x4];
    void *vt;
    u8 pad1c[0x90 - 0x1C];
    void *emitters[4];
    DFDemo1Part body[6];
    DFDemo1Part zanzo[2];
    Vec pos;
    s32 angle;
    s32 timer;
    f32 frame;
    f32 scroll;
    u8 strips[0x14];
};

extern "C" {
extern DFDemo1Tables lbl_80485590;
extern s32 lbl_80485EB0[];
extern s32 boss4_zanzo_bml_index_table[];
extern const CameraAngles lbl_8043731C;
extern u8 lbl_80437328[];
extern u8 __vt__11TObjDFDemo1[];
__declspec(section ".sdata") extern const char *lbl_805D2780;
__declspec(section ".sdata2") extern const f32 lbl_805D89B0;
__declspec(section ".sdata2") extern const f32 lbl_805D8990;

void __ct__8TObjBaseFP7TObject(void *, void *);
s32 get_bml_model(s32, s32);
s32 TObjFish__sub_8001EDB0(s32, s32);
s32 get_bml_motion(s32, s32);
void init_model_node_tables(void *, void *, s32);
void *__nw__7TObjectFUl(int);

void *TObjDFDemo1__ct(void *arg0, void *parent, void *pos, void *angle) {
    DFDemo1Obj *self = (DFDemo1Obj *)arg0;
    s32 i;
    s32 cnt;

    __ct__8TObjBaseFP7TObject(self, parent);
    self->vt = __vt__11TObjDFDemo1;
    self->name = (s32)lbl_805D2780;
    VecCopy(&self->pos, (const Vec *)pos);
    self->angle = (s32)angle;
    cnt = TBoss4Uro::get_instance_count();
    for (i = 0; i < 6; i++) {
        s32 id = lbl_80485EB0[i];
        self->body[i].model = get_bml_model(cnt, id);
        self->body[i].texlist = TObjFish__sub_8001EDB0(cnt, id);
        self->body[i].motion = get_bml_motion(cnt, lbl_80485590.body_motions[i]);
    }
    for (i = 0; i < 2; i++) {
        s32 id = boss4_zanzo_bml_index_table[i];
        self->zanzo[i].model = get_bml_model(cnt, id);
        self->zanzo[i].texlist = TObjFish__sub_8001EDB0(cnt, id);
        self->zanzo[i].motion = get_bml_motion(cnt, lbl_80485590.zanzo_motions[i]);
    }
    self->frame = lbl_805D89B0;
    for (i = 0; i < 4; i++) {
        self->emitters[i] = NULL;
    }
    activate_camera_mode(5);
    {
        CameraAngles angles = lbl_8043731C;
        angles.yaw = self->angle;
        set_scripted_camera_pose(&self->pos, &self->pos, &angles);
    }
    cache_target_and_forward__11TCameraCtrlFl(&lbl_80485590.camera, 0x4000);
    play_sound_effect(0x4003A324, &static_cast<TObjBase *>(arg0)->position, 0, 1);
    self->scroll = lbl_805D8990;
    init_model_node_tables(self->strips, lbl_80437328, 6);
    self->timer = 0;
    return self;
}

void *TBoss4DarkFalz::create_demo1(void *arg0, void *arg1, void *arg2) {
    void *o;
    o = __nw__7TObjectFUl(0x130);
    if (o != NULL) {
        o = TObjDFDemo1__ct(o, arg0, arg1, arg2);
    }
    return o;
}

}
