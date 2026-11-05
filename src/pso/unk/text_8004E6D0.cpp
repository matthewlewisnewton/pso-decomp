#include "types.h"
#include "pso/boss/TBoss4DarkFalz.h"
#include "pso/boss/TBoss4Uro.h"
#include "pso/misc/CameraHelpers.h"
#include "pso/misc/TCameraCtrl_800687BC.h"
#include "pso/object/TObjFish.h"
#include "pso/player/TObjPlayer.h"
#include "pso/system/SoundEffect.h"
#include "pso/system/vector.h"

typedef struct Rec_8004E918 {
    s32 a;
    s32 b;
    s32 c;
} Rec_8004E918;

typedef struct Obj_8004E918 {
    u8 pad0[0x90];
    Rec_8004E918 recs[2];
    s32 fa8;
    f32 fac[3];
    s32 fb8;
    s32 fbc;
    f32 fc0;
} Obj_8004E918;

struct Demo1Part {
    s32 model;
    s32 texlist;
    s32 motion;
};

// Overlay of TObjDFDemo1. The linked demo unit already uses m_10c and m_114;
// this TU only constructs the object, so the extra fields stay local.
struct Demo1Obj {
    s32 name;
    u8 pad4[0x18 - 0x4];
    void *vt;
    u8 pad1c[0x38 - 0x1C];
    Vec position;
    u8 pad44[0x90 - 0x44];
    s32 emitters[4];
    Demo1Part body[6];
    Demo1Part zanzo[2];
    Vec pos;
    s32 angle;
    s32 timer;
    f32 frame;
    f32 scroll;
    u8 strips[0x14];
};

struct Demo1Tables {
    u8 pad[0x60];
    s32 body_motion[6];
    s32 zanzo_motion[2];
    CameraPlayback camera;
};

typedef char Demo1Obj_size[sizeof(Demo1Obj) == 0x130 ? 1 : -1];
typedef char Demo1Obj_angle[offsetof(Demo1Obj, angle) == 0x10C ? 1 : -1];
typedef char Demo1Obj_frame[offsetof(Demo1Obj, frame) == 0x114 ? 1 : -1];
typedef char Demo1Obj_strips[offsetof(Demo1Obj, strips) == 0x11C ? 1 : -1];
typedef char Demo1Tables_camera[offsetof(Demo1Tables, camera) == 0x80 ? 1 : -1];
typedef char Demo1Tables_size[sizeof(Demo1Tables) == 0x8C ? 1 : -1];

extern "C" {

void *__nw__7TObjectFUl(int);
void __ct__8TObjBaseFP7TObject(void *, void *);
s32 get_bml_model(s32 resource, s32 index);
s32 TObjFish__sub_8001EDB0(s32 resource, s32 index);
s32 get_bml_motion(s32 resource, s32 index);
void init_model_node_tables(void *tables, void *specs, s32 count);

extern Demo1Tables lbl_80485590;
extern s32 lbl_80485EB0[];
extern s32 boss4_zanzo_bml_index_table[];
extern s32 lbl_805D2780;
__declspec(section ".sdata2") extern const f32 lbl_805D89B0;
__declspec(section ".sdata2") extern const f32 lbl_805D8990;
extern const CameraAngles lbl_8043731C;
extern u8 lbl_80437328[];

void *TObjDFDemo1__ct(void *mem, void *parent, void *pos, void *angle) {
    Demo1Obj *self = (Demo1Obj *)mem;
    u8 *tables = (u8 *)&lbl_80485590;
    void *vt = tables + 0xB0;
    s32 resource;
    s32 i;
    s32 id;
    s32 part;
    CameraAngles angles;

    __ct__8TObjBaseFP7TObject(self, parent);
    // The vtable sits 0xB0 past this TU's data anchor; the linked demo unit owns the bytes.
    self->vt = vt;
    self->name = lbl_805D2780;
    VecCopy(&self->pos, (const Vec *)pos);
    self->angle = (s32)angle;
    resource = TBoss4Uro::get_instance_count();
    {
        s32 *body_motion = (s32 *)(tables + 0x60);
        s32 off;
        part = 0;
        for (i = 0; i < 6; i++) {
            id = lbl_80485EB0[i];
            off = part + 0xA0;
            *(s32 *)((u8 *)self + off) = get_bml_model(resource, id);
            off = part + 0xA4;
            *(s32 *)((u8 *)self + off) = TObjFish__sub_8001EDB0(resource, id);
            off = part + 0xA8;
            *(s32 *)((u8 *)self + off) = get_bml_motion(resource, body_motion[i]);
            part += 0xC;
        }
    }
    {
        s32 *zanzo_motion = (s32 *)(tables + 0x78);
        s32 off;
        part = 0;
        for (i = 0; i < 2; i++) {
            id = boss4_zanzo_bml_index_table[i];
            off = part + 0xE8;
            *(s32 *)((u8 *)self + off) = get_bml_model(resource, id);
            off = part + 0xEC;
            *(s32 *)((u8 *)self + off) = TObjFish__sub_8001EDB0(resource, id);
            off = part + 0xF0;
            *(s32 *)((u8 *)self + off) = get_bml_motion(resource, zanzo_motion[i]);
            part += 0xC;
        }
    }
    self->frame = lbl_805D89B0;
    for (i = 0; i < 4; i++) {
        self->emitters[i] = 0;
    }
    activate_camera_mode(5);
    {
        const s32 *src = (const s32 *)&lbl_8043731C;
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
    cache_target_and_forward__11TCameraCtrlFl((CameraPlayback *)(tables + 0x80), 0x4000);
    play_sound_effect(0x4003A324, &self->position, 0, 1);
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
