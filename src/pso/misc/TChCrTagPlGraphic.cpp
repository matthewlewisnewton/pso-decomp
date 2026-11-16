#include "pso/TChCrTagPlGraphic.h"

#include "types.h"
#include "pso/TChCrCharSelect.h"

/* One 0x18-byte parameter row per slot in the externally owned
 * TChCrTagPlGraphic__data_804664A4 rodata. field_04 is the class match value
 * compared against tag_player_graphic_match_value_table; pair is copied into
 * the tag at +0x48 by the constructor. */
struct TChCrTagPlGraphicRow {
    f32 field_00;
    f32 field_04;
    f32 pair[2];
    f32 field_10;
    f32 field_14;
};

extern "C" {
u8 * __ct__8TChCrTagFP7TObjectPv(void *, s32, s32);
extern const TChCrTagPlGraphicRow TChCrTagPlGraphic__data_804664A4[12];
extern void *__vt__17TChCrTagPlGraphic[];
extern s32 ch_cr_tag_pl_graphic_class_name;
extern const f32 lbl_805DDF18;
static const f32 lbl_805DDF2C = 0.13333334f;
extern const f32 lbl_805DDF30;
static const f32 lbl_805DDF20 = 0.25f;
static const f32 lbl_805DDF24 = -2.75f;
static const f32 lbl_805DDF28 = 1.0f;
u8 *__ct__17TChCrTagPlGraphicFv(u8 *arg0, s32 arg1, s32 _w2);
s32 TChCrTagPlGraphic__vt4(u8 *arg0);
void render__17TChCrTagPlGraphicFv(void* p);
void run_task__17TChCrTagPlGraphicFv(void* p);
void TChCrTagPlGraphic__sub_802A3230(u8 *tag);
void update_fade__8TChCrTagFPv(u8 *arg0);
void *__nw__7TObjectFUl(int);
void render_shadows__7TObjectFv();
void copy_vec2__28TWindowSubSymbolChatPartsSetFPv(f32 *destination, const void *source);
void restore_saved_depth_alpha_state(void);
int set_depth_buffer_settings_1__Fv(void*);

void render__17TChCrTagPlGraphicFv(void* p) { set_depth_buffer_settings_1__Fv(p); ((TChCrTagPlGraphic *)p)->draw_class_illustration(); restore_saved_depth_alpha_state(); }


struct VBase_802A3230 { char pad[0x18]; };
struct VTag_802A3230 : VBase_802A3230 {
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual void m3();
    virtual s32 m4();
};

#pragma push
#pragma fp_contract on
void TChCrTagPlGraphic__sub_802A3230(u8 *tag) {
    const TChCrTagPlGraphicRow *e;

    e = &TChCrTagPlGraphic__data_804664A4[*(s32 *)(tag + 0x20)];
    *(f32 *)(tag + 0x3C) = *(f32 *)(tag + 0x24) * *(f32 *)(tag + 0x30);
    switch (TChCrCharSelect::get_selected_index()) {
    case 0:
        *(f32 *)(tag + 0x40) += lbl_805DDF20 * (e->field_04 - *(f32 *)(tag + 0x40));
        *(f32 *)(tag + 0x44) += lbl_805DDF20 * (e->field_00 - *(f32 *)(tag + 0x44));
        *(f32 *)(tag + 0x48) += lbl_805DDF20 * (e->pair[0] - *(f32 *)(tag + 0x48));
        *(f32 *)(tag + 0x4C) += lbl_805DDF20 * (e->pair[1] - *(f32 *)(tag + 0x4C));
        break;
    default:
        if (((VTag_802A3230 *)tag)->m4() != 0) {
            *(f32 *)(tag + 0x40) += lbl_805DDF20 * (lbl_805DDF24 - *(f32 *)(tag + 0x40));
            *(f32 *)(tag + 0x44) += lbl_805DDF20 * (lbl_805DDF28 - *(f32 *)(tag + 0x44));
            *(f32 *)(tag + 0x48) += lbl_805DDF20 * (e->field_10 - *(f32 *)(tag + 0x48));
            *(f32 *)(tag + 0x4C) += lbl_805DDF20 * (e->field_14 - *(f32 *)(tag + 0x4C));
        }
        break;
    }
}
#pragma pop

void run_task__17TChCrTagPlGraphicFv(void* p) { update_fade__8TChCrTagFPv((u8 *)p); TChCrTagPlGraphic__sub_802A3230((u8 *)p); }

extern void *tl_03;
extern f32 tag_player_graphic_match_value_table[];

typedef char RecoveredGlobal_802A3454_TChCrTagPlGraphic__data_804664A4_size[sizeof(TChCrTagPlGraphic__data_804664A4) == 0x120 ? 1 : -1];

s32 TChCrTagPlGraphic__vt4(u8 *arg0) {
    switch (TChCrCharSelect::get_selected_index()) {
    case 0:
        if (*(s32 *)(arg0 + 0x20) / 4 == TChCrCharSelect::get_selected_char()) {
            return 1;
        }
        break;
    default:
        if (*(s32 *)(arg0 + 0x20) == TChCrCharSelect::get_instance()) {
            return 1;
        }
        break;
    }
    return 0;
}

void *__dt__8TChCrTagFv(void *, s16);
void __dl__7TObjectFPv(void *);

void *__dt__17TChCrTagPlGraphicFv(void *self, s16 arg1) {
    if (self != NULL) {
        *(void ***)((s8 *)self + 0x18) = __vt__17TChCrTagPlGraphic;
        __dt__8TChCrTagFv(self, 0);
        if (arg1 > 0) {
            __dl__7TObjectFPv(self);
        }
    }
    return self;
}

u8 *__ct__17TChCrTagPlGraphicFv(u8 *ch_cr_tag, s32 arg1, s32 _w2) {
    const TChCrTagPlGraphicRow *row;
    __ct__8TChCrTagFP7TObjectPv(ch_cr_tag, arg1, _w2);
    *(s32 **)((s8 *)ch_cr_tag + 0x18) = (s32 *)__vt__17TChCrTagPlGraphic;
    *(s32 *)((s8 *)ch_cr_tag + 0) = (s32) ch_cr_tag_pl_graphic_class_name;
    *(f32 *)((s8 *)ch_cr_tag + 0x28) = (f32) lbl_805DDF2C;
    *(f32 *)((s8 *)ch_cr_tag + 0x2C) = (f32) lbl_805DDF30;
    *(f32 *)((s8 *)ch_cr_tag + 0x34) = (f32) lbl_805DDF2C;
    *(f32 *)((s8 *)ch_cr_tag + 0x38) = (f32) lbl_805DDF30;
    *(f32 *)((s8 *)ch_cr_tag + 0x3C) = (f32) lbl_805DDF18;
    row = &TChCrTagPlGraphic__data_804664A4[*(s32 *)((s8 *)ch_cr_tag + 0x20)];
    *(f32 *)((s8 *)ch_cr_tag + 0x40) = (f32) row->field_04;
    *(f32 *)((s8 *)ch_cr_tag + 0x44) = (f32) row->field_00;
    copy_vec2__28TWindowSubSymbolChatPartsSetFPv((f32 *)((s8 *)ch_cr_tag + 0x48), row->pair);
    return ch_cr_tag;
}

void *TChCrTagPlGraphic::create(void *arg0) {
    void *o = __nw__7TObjectFUl(0x50);
    if (o != NULL) {
        o = __ct__17TChCrTagPlGraphicFv((u8 *)o, (s32)tl_03, (s32)arg0);
    }
    return o;
}

void TChCrTagPlGraphic::create_matching_tags() {
    s32 i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 12; j++) {
            if (TChCrTagPlGraphic__data_804664A4[j].field_04 == tag_player_graphic_match_value_table[i]) {
                TChCrTagPlGraphic::create((void *)j);
            }
        }
    }
}

void *__vt__17TChCrTagPlGraphic[8] = {
    0, 0,
    (void *)__dt__17TChCrTagPlGraphicFv,
    (void *)run_task__17TChCrTagPlGraphicFv,
    (void *)render__17TChCrTagPlGraphicFv,
    (void *)render_shadows__7TObjectFv,
    (void *)TChCrTagPlGraphic__vt4,
    0,
};

}
