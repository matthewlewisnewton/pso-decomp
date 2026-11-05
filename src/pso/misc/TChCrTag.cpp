#include "types.h"
#include "pso/TChCrTag.h"
#include "pso/TObject.h"
#include "pso/misc/TChCrTag.h"
#include "pso/object/TObject_80019A50.h"

extern "C" void render__8TChCrTagFv();
#include "pso/TChCrCharSelect.h"

struct VBase_18_c1c33b { char pad[0x18]; };

struct VObj_18_c1c33b : VBase_18_c1c33b {
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual void m3();
    virtual s32 m4();
};

extern "C" {
extern const f32 lbl_805DDE00;
extern const f32 lbl_805DDE04;
void __dt__7TObjectFv(void *, s16);
void __dl__7TObjectFPv(void *);
void render_shadows__7TObjectFv(void);

int TChCrTag__vt4(void) { return 0; }
void TChCrTag::render() {  }

extern void *__vt__8TChCrTag[];
extern const f32 lbl_805DDE08;
extern void *lbl_805D3D90;
extern const f32 lbl_805DDE0C;

#pragma push
#pragma opt_common_subs off
void update_fade__8TChCrTagFPv(u8 *arg0) {
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f2_3;
    if (((VObj_18_c1c33b *)(arg0))->m4() != 0) {
        temp_f2 = *(f32 *)((s8 *)arg0 + 0x30);
        if (temp_f2 < lbl_805DDE00) {
            *(f32 *)((s8 *)arg0 + 0x30) = (f32) (temp_f2 + *(f32 *)((s8 *)arg0 + 0x34));
            if (*(f32 *)((s8 *)arg0 + 0x30) > lbl_805DDE00) {
                *(f32 *)((s8 *)arg0 + 0x30) = (f32) lbl_805DDE00;
            }
        }
    } else {
        temp_f2_2 = *(f32 *)((s8 *)arg0 + 0x30);
        if (temp_f2_2 > lbl_805DDE04) {
            *(f32 *)((s8 *)arg0 + 0x30) = (f32) (temp_f2_2 + *(f32 *)((s8 *)arg0 + 0x38));
            if (*(f32 *)((s8 *)arg0 + 0x30) < lbl_805DDE04) {
                *(f32 *)((s8 *)arg0 + 0x30) = (f32) lbl_805DDE04;
            }
        }
    }
    switch (*(s32 *)((s8 *)arg0 + 0x1C)) {
    case 0:
        temp_f2_3 = *(f32 *)((s8 *)arg0 + 0x24);
        if (temp_f2_3 < lbl_805DDE00) {
            *(f32 *)((s8 *)arg0 + 0x24) = (f32) (temp_f2_3 + *(f32 *)((s8 *)arg0 + 0x28));
            if (*(f32 *)((s8 *)arg0 + 0x24) > lbl_805DDE00) {
                *(f32 *)((s8 *)arg0 + 0x24) = (f32) lbl_805DDE00;
            }
        }
        if (TChCrCharSelect::get_selected_index() == 2) {
            *(s32 *)((s8 *)arg0 + 0x1C) = 1;
            break;
        }
        break;
    case 1:
        *(f32 *)((s8 *)arg0 + 0x24) = (f32) (*(f32 *)((s8 *)arg0 + 0x24) + *(f32 *)((s8 *)arg0 + 0x2C));
        if (*(f32 *)((s8 *)arg0 + 0x24) <= lbl_805DDE04) {
            *(f32 *)((s8 *)arg0 + 0x24) = (f32) lbl_805DDE04;
            queue_destruction__7TObjectFv((arg0));
        }
        break;
    }
}
#pragma pop

void *__dt__8TChCrTagFv(void *self, s16 arg1) {
    if (self != NULL) {
        *(void ***)((s8 *)self + 0x18) = __vt__8TChCrTag;
        __dt__7TObjectFv(self, 0);
        if (arg1 > 0) {
            __dl__7TObjectFPv(self);
        }
    }
    return self;
}

}
TChCrTag::TChCrTag(TObject *object, void *arg2) : TObject(object) {
    *(void * *)&this->m_name = lbl_805D3D90;
    *(void **)((s8 *)this + 0x20) = arg2;
    *(u32 *)((s8 *)this + 0x1C) = 0;
    *(f32 *)((s8 *)this + 0x24) = lbl_805DDE04;
    *(f32 *)((s8 *)this + 0x30) = lbl_805DDE04;
    *(f32 *)((s8 *)this + 0x34) = lbl_805DDE08;
    *(f32 *)((s8 *)this + 0x28) = lbl_805DDE08;
    *(f32 *)((s8 *)this + 0x38) = lbl_805DDE0C;
    *(f32 *)((s8 *)this + 0x2C) = lbl_805DDE0C;
}


void *__vt__8TChCrTag[7] = {
    0, 0, (void *)__dt__8TChCrTagFv, (void *)update_fade__8TChCrTagFPv,
    (void *)&render__8TChCrTagFv, (void *)render_shadows__7TObjectFv,
    (void *)TChCrTag__vt4,
};

