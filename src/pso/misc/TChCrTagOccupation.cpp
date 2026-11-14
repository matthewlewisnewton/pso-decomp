#include "types.h"
#include "pso/TChCrTagOccHeader.h"
#include "pso/TObject.h"
#include "pso/TChCrTagOccupation.h"
extern "C" void render__18TChCrTagOccupationFv();
#include "pso/TChCrCharSelect.h"

extern "C" {
void *__dt__8TChCrTagFv(void *, s16);
void __dl__7TObjectFPv(void *);
u8 *__ct__8TChCrTagFP7TObjectPv(void *, s32);
void *__nw__7TObjectFUl(int);
s32 get_selected_char__15TChCrCharSelectFv();
s32 update_fade__8TChCrTagFPv();
void render_shadows__7TObjectFv();
}

#define get_selected_char__15TChCrCharSelectFv (*(s32 (*)(void *))&get_selected_char__15TChCrCharSelectFv)
#define update_fade__8TChCrTagFPv (*(void (*)())&update_fade__8TChCrTagFPv)
extern void *tl_03;

#include "pso/TMath.h"

struct RecoveredGlobal_802A300C___vt__18TChCrTagOccupation {
    s32 value;
    u8 remaining[0x1C];
};

struct VBase_802A2DF4 { char pad[0x18]; };
struct Tag_802A2DF4 : VBase_802A2DF4 {
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual void m3();
    virtual s32 m4();
    s32 f1c;
    s32 f20;
    f32 f24;
    u8 pad28[0x30 - 0x28];
    f32 f30;
    u8 pad34[0x3C - 0x34];
    f32 f3c;
    f32 f40;
};

struct Obj_802A2F78 { u8 pad[0x20]; s32 f20; };

extern "C" {
void draw_ui_sprite_shaded(s32 sprite_id, const vec2f *position, const vec2f *scale,
                           f32 depth, f32 alpha, f32 brightness);
extern vec2f lbl_80466474[];
extern vec2f lbl_8046647C[];
static const f32 lbl_805DDED8 = 0.6000000238418579f;
static const f32 lbl_805DDEDC = 0.4000000059604645f;
static const f32 lbl_805DDEE0 = -3.375f;
static const f32 lbl_805DDEE4 = -3.6875f;
static const f32 lbl_805DDEE8 = 0.3125f;
static const f32 lbl_805DDEEC = 25.0f;
static const f32 lbl_805DDEF0 = 1.0f;
static const f32 lbl_805DDEF4 = 108.0f;
static const f32 lbl_805DDEF8 = 0.25f;
static const f32 lbl_805DDEFC = 0.75f;
extern void *__vt__18TChCrTagOccupation[];
void *__dt__18TChCrTagOccupationFv(void *self, s16 m);
extern s32 chcr_tag_occupation_class_name;
static const f32 lbl_805DDF00 = 0.03333333507180214f;
static const f32 lbl_805DDF04 = -0.02222222276031971f;
static const f32 lbl_805DDF08 = 0.6666666865348816f;
static const f32 lbl_805DDF0C = -0.06666667014360428f;
static const f32 lbl_805DDF10 = 0.800000011920929f;
static const f32 lbl_805DDF14 = 0.053333330899477005f;
u8 *__ct__18TChCrTagOccupationFv(u8 *arg0, s32 arg1, s32 _w2);
int TChCrTagOccupation__vt4(Obj_802A2F78 *self);
#pragma push
#pragma fp_contract on
void TChCrTagOccupation::sub_802A2DF4() {
    f32 t;
    f32 s;
    f32 depth;
    s32 id = ((Tag_802A2DF4 *)this)->f20 + 0x39;
    vec2f pos = lbl_80466474[0];
    vec2f scale = lbl_8046647C[0];
    if (((Tag_802A2DF4 *)this)->f24 > ((Tag_802A2DF4 *)this)->f3c) {
        t = (((Tag_802A2DF4 *)this)->f24 - ((Tag_802A2DF4 *)this)->f3c) / (((Tag_802A2DF4 *)this)->f40 - ((Tag_802A2DF4 *)this)->f3c);
    } else {
        return;
    }
    switch (TChCrCharSelect::get_selected_index()) {
    case 0:
        s = lbl_805DDEDC * ((Tag_802A2DF4 *)this)->f30 + lbl_805DDED8;
        break;
    default:
        s = ((Tag_802A2DF4 *)this)->f30;
        break;
    }
    if (((Tag_802A2DF4 *)this)->m4() != 0) {
        depth = lbl_805DDEE0;
    } else {
        depth = lbl_805DDEE8 * s + lbl_805DDEE4;
    }
    pos.x = lbl_805DDEEC * (lbl_805DDEF0 - t) + pos.x;
    pos.y = lbl_805DDEF4 * (f32)((Tag_802A2DF4 *)this)->f20 + pos.y;
    draw_ui_sprite_shaded(id, &pos, &scale, depth, lbl_805DDEF0, lbl_805DDEFC * (s * s) + lbl_805DDEF8);
}
#pragma pop

void TChCrTagOccupation::render() { sub_802A2DF4(); }

int TChCrTagOccupation__vt4(Obj_802A2F78 *self) {
    if (get_selected_char__15TChCrCharSelectFv(self) == self->f20) return 1;
    return 0;
}

void *__dt__18TChCrTagOccupationFv(void *self, s16 m) {
    if (self != NULL) {
        *(void ***)((s8 *)self + 0x18) = __vt__18TChCrTagOccupation;
        __dt__8TChCrTagFv(self, 0);
        if (m > 0) {
            __dl__7TObjectFPv(self);
        }
    }
    return self;
}
#pragma push
#pragma fp_contract on
typedef char RecoveredGlobal_802A300C___vt__18TChCrTagOccupation_size[sizeof(RecoveredGlobal_802A300C___vt__18TChCrTagOccupation) == 0x20 ? 1 : -1];

u8 *__ct__18TChCrTagOccupationFv(u8 *ch_cr_tag, s32 arg1, s32 _w2) {
    __ct__8TChCrTagFP7TObjectPv(ch_cr_tag, arg1);
    *(s32 **)((s8 *)ch_cr_tag + 0x18) = (s32 *)__vt__18TChCrTagOccupation;
    *(s32 *)((s8 *)ch_cr_tag + 0) = (s32) chcr_tag_occupation_class_name;
    *(f32 *)((s8 *)ch_cr_tag + 0x28) = (f32) lbl_805DDF00;
    *(f32 *)((s8 *)ch_cr_tag + 0x2C) = (f32) lbl_805DDF04;
    *(f32 *)((s8 *)ch_cr_tag + 0x34) = (f32) lbl_805DDF08;
    *(f32 *)((s8 *)ch_cr_tag + 0x38) = (f32) lbl_805DDF0C;
    *(f32 *)((s8 *)ch_cr_tag + 0x3C) = (f32) ((lbl_805DDF14 * (f32) *(s32 *)((s8 *)ch_cr_tag + 0x20)) + lbl_805DDF10);
    *(f32 *)((s8 *)ch_cr_tag + 0x40) = (f32) lbl_805DDEF0;
    return ch_cr_tag;
}
#pragma pop

void *TChCrTagOccupation::create(void *arg0) {
    void *o = __nw__7TObjectFUl(0x44);
    if (o != NULL) {
        o = __ct__18TChCrTagOccupationFv((u8 *)o, (s32)tl_03, (s32)arg0);
    }
    return o;
}

void TChCrTagOccupation::create_all() { { int i; for (i = 0; i < 3; i++) { TChCrTagOccupation::create((void *)((void*)i)); } } }

void *__vt__18TChCrTagOccupation[8] = {
    0,
    0,
    (void *)__dt__18TChCrTagOccupationFv,
    (void *)update_fade__8TChCrTagFPv,
    (void *)&render__18TChCrTagOccupationFv,
    (void *)render_shadows__7TObjectFv,
    (void *)TChCrTagOccupation__vt4,
    0,
};
}

#undef get_selected_char__15TChCrCharSelectFv
#undef update_fade__8TChCrTagFPv
