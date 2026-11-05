#include "types.h"
#include "pso/boss/TBoss4Uro.h"
#include "pso/misc/CameraHelpers.h"
#include "pso/misc/TCameraCtrl_800687BC.h"
#include "pso/system/ModelNodePositionCapture.h"
#include "pso/system/SoundEffect.h"
#include "pso/system/vector.h"

struct Demo5Part {
    s32 model;
    s32 texlist;
    s32 motion;
};

// Local view of TObjDFDemo5. The linked player and create units already use
// the header fields; this TU only builds the object.
struct Demo5Obj {
    s32 name;
    u8 pad4[0x18 - 0x4];
    void *vt;
    u8 pad1c[0x90 - 0x1C];
    s32 emitters[5];
    Demo5Part parts[4];
    Vec pos;
    s32 angle;
    s32 timer;
    f32 frame;
    void *node_list0;
    Vec node_pos0;
    u8 padfc[0x108 - 0xFC];
    void *node_list1;
    Vec node_pos1;
};

struct Demo5Tables {
    u8 entries0[0x30];
    u8 entries1[0x20];
    s32 motion[3];
};

typedef char Demo5Obj_size[sizeof(Demo5Obj) == 0x118 ? 1 : -1];
typedef char Demo5Obj_parts[offsetof(Demo5Obj, parts) == 0xA4 ? 1 : -1];
typedef char Demo5Obj_pos[offsetof(Demo5Obj, pos) == 0xD4 ? 1 : -1];
typedef char Demo5Obj_angle[offsetof(Demo5Obj, angle) == 0xE0 ? 1 : -1];
typedef char Demo5Obj_frame[offsetof(Demo5Obj, frame) == 0xE8 ? 1 : -1];
typedef char Demo5Tables_size[sizeof(Demo5Tables) == 0x5C ? 1 : -1];
typedef char Demo5Tables_motion[offsetof(Demo5Tables, motion) == 0x50 ? 1 : -1];

extern "C" {

void __ct__8TObjBaseFP7TObject(void *, void *);
s32 get_bml_model(s32 resource, s32 index);
s32 TObjFish__sub_8001EDB0(s32 resource, s32 index);
s32 get_bml_motion(s32 resource, s32 index);

extern Demo5Tables lbl_80485798;
extern s32 lbl_80486FB0[];
extern s32 lbl_805D27A0;
__declspec(section ".sdata2") extern const f32 lbl_805D8A1C;
extern const CameraPlayback lbl_80437424;
extern const CameraAngles lbl_80437430;

void *TObjDFDemo5__ct(void *mem, void *parent, void *pos, void *angle) {
    Demo5Obj *self = (Demo5Obj *)mem;
    u8 *tables = (u8 *)&lbl_80485798;
    void *vt = tables + 0x5C;
    s32 resource;
    s32 i;
    s32 id;
    s32 part;
    CameraAngles angles;
    CameraPlayback playback;

    __ct__8TObjBaseFP7TObject(self, parent);
    // The vtable begins where this anchor ends. The bytes belong to the next symbol.
    self->vt = vt;
    self->name = lbl_805D27A0;
    VecCopy(&self->pos, (const Vec *)pos);
    self->angle = (s32)angle;
    resource = TBoss4Uro::get_instance_count();
    {
        s32 *motion = (s32 *)(tables + 0x50);
        s32 off;
        part = 0;
        for (i = 0; i < 3; i++) {
            id = lbl_80486FB0[i];
            off = part + 0xA4;
            *(s32 *)((u8 *)self + off) = get_bml_model(resource, id);
            off = part + 0xA8;
            *(s32 *)((u8 *)self + off) = TObjFish__sub_8001EDB0(resource, id);
            off = part + 0xAC;
            *(s32 *)((u8 *)self + off) = get_bml_motion(resource, motion[i]);
            part += 0xC;
        }
    }
    self->parts[3].model = get_bml_model(resource, 1);
    self->parts[3].texlist = TObjFish__sub_8001EDB0(resource, 1);
    self->parts[3].motion = get_bml_motion(resource, 0x23);
    self->frame = lbl_805D8A1C;
    for (i = 0; i < 5; i++) {
        self->emitters[i] = 0;
    }
    activate_camera_mode(5);
    {
        const s32 *src = (const s32 *)&lbl_80437424;
        s32 *dst = (s32 *)&playback;
        s32 w0 = src[0];
        s32 w1 = src[1];
        s32 w2 = src[2];
        dst[0] = w0;
        dst[1] = w1;
        dst[2] = w2;
    }
    {
        const s32 *src = (const s32 *)&lbl_80437430;
        s32 *dst = (s32 *)&angles;
        s32 w0 = src[0];
        s32 w1 = src[1];
        s32 w2 = src[2];
        dst[0] = w0;
        dst[1] = w1;
        dst[2] = w2;
        dst[1] = self->angle;
    }
    set_scripted_camera_pose(&self->pos, &self->pos, &angles);
    cache_target_and_forward__11TCameraCtrlFl(&playback, 0x416C);
    self->node_list0 = ModelNodePositionCapture::create((ModelNodePositionEntry *)tables, &self->node_pos0);
    self->node_list1 = ModelNodePositionCapture::create((ModelNodePositionEntry *)(tables + 0x30), &self->node_pos1);
    play_sound_effect(0x4003A835, NULL, 0, 0);
    self->timer = 0;
    return self;
}

}
