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

// Local layout of TObjDFDemo5. The shared header is already used by linked
// units, so this translation unit keeps its own view of the constructor fields.
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
    Vec emitter_positions[2];
    void *node_list1;
    Vec tail_position;
};

struct Words3 {
    s32 a;
    s32 b;
    s32 c;
};

typedef char Demo5Obj_size[sizeof(Demo5Obj) == 0x118 ? 1 : -1];
typedef char Demo5Obj_parts[offsetof(Demo5Obj, parts) == 0xA4 ? 1 : -1];
typedef char Demo5Obj_pos[offsetof(Demo5Obj, pos) == 0xD4 ? 1 : -1];
typedef char Demo5Obj_angle[offsetof(Demo5Obj, angle) == 0xE0 ? 1 : -1];
typedef char Demo5Obj_frame[offsetof(Demo5Obj, frame) == 0xE8 ? 1 : -1];
typedef char Demo5Obj_node0[offsetof(Demo5Obj, node_list0) == 0xEC ? 1 : -1];
typedef char Demo5Obj_emitters_pos[offsetof(Demo5Obj, emitter_positions) == 0xF0 ? 1 : -1];
typedef char Demo5Obj_node1[offsetof(Demo5Obj, node_list1) == 0x108 ? 1 : -1];
typedef char Demo5Obj_tail[offsetof(Demo5Obj, tail_position) == 0x10C ? 1 : -1];

extern "C" {

void __ct__8TObjBaseFP7TObject(void *, void *);
s32 get_bml_model(s32 resource, s32 index);
s32 TObjFish__sub_8001EDB0(s32 resource, s32 index);
s32 get_bml_motion(s32 resource, s32 index);

extern u8 lbl_80485798[];
extern s32 lbl_80486FB0[];
__declspec(section ".sdata") extern const char *lbl_805D27A0;
__declspec(section ".sdata2") extern const f32 lbl_805D8A1C;
extern const Words3 lbl_80437424;
extern const Words3 lbl_80437430;

#define self ((Demo5Obj *)mem)

void *TObjDFDemo5__ct(void *mem, void *parent, void *pos, void *angle) {
    s32 k;
    s32 cnt;
    s32 i;
    // Keep the anchor in one register. A plain symbol copy is folded back to
    // lbl_80485798 and reloaded after each call.
    u8 *tables = (u8 *)(unsigned)lbl_80485798;
    s32 *motab;

    __ct__8TObjBaseFP7TObject(self, parent);
    self->vt = tables + 0x5C;
    self->name = (s32)lbl_805D27A0;
    VecCopy((Vec *)((u8 *)mem + 0xD4), (const Vec *)pos);
    self->angle = (s32)angle;
    cnt = TBoss4Uro::get_instance_count();
    motab = (s32 *)(tables + 0x50);
    for (i = 0; i < 3; i++) {
        s32 t = lbl_80486FB0[i];
        k = t;
        s32 m = get_bml_model(cnt, t);
        s32 off = i * 12 + 0xA4;
        *(s32 *)((u8 *)self + off) = m;
        m = TObjFish__sub_8001EDB0(cnt, k);
        off = i * 12 + 0xA8;
        *(s32 *)((u8 *)self + off) = m;
        m = get_bml_motion(cnt, motab[i]);
        off = i * 12 + 0xAC;
        *(s32 *)((u8 *)self + off) = m;
    }
    self->parts[3].model = get_bml_model(cnt, 1);
    self->parts[3].texlist = TObjFish__sub_8001EDB0(cnt, 1);
    self->parts[3].motion = get_bml_motion(cnt, 0x23);
    self->frame = lbl_805D8A1C;
    for (i = 0; i < 5; i++) {
        self->emitters[i] = 0;
    }
    activate_camera_mode(5);
    {
        Words3 playback = lbl_80437424;
        Words3 angles = lbl_80437430;
        angles.b = self->angle;
        set_scripted_camera_pose(&self->pos, &self->pos, (const CameraAngles *)&angles);
        cache_target_and_forward__11TCameraCtrlFl((const CameraPlayback *)&playback, 0x416C);
    }
    self->node_list0 = ModelNodePositionCapture::create((ModelNodePositionEntry *)tables, &self->emitter_positions[0]);
    self->node_list1 = ModelNodePositionCapture::create((ModelNodePositionEntry *)(tables + 0x30), &self->tail_position);
    play_sound_effect(0x4003A835, NULL, 0, 0);
    self->timer = 0;
    return self;
}

#undef self

}
