#include "types.h"
#include "pso/TChCrTagOccHeader.h"
#include "pso/TObject.h"
#include "pso/TChCrTagOccupation.h"
extern "C" void render__18TChCrTagOccupationFv();
#include "pso/TChCrCharSelect.h"

extern "C" {

int render__17TChCrTagOccHeaderFv(void* p);
int fn_802A2A00(void*);

void TChCrTagOccHeader::render() { fn_802A2A00(this); }

}

struct Hdr_802A2C30 {
    u8 pad[0x20];
    s32 f20;
};

extern "C" {
s32 get_selected_char__15TChCrCharSelectFv();
s32 TChCrTagOccHeader__vt4(Hdr_802A2C30 *arg0);
void run_task__17TChCrTagOccHeaderFv(u8 *arg0);
s32 update_fade__8TChCrTagFPv();

void TChCrTagOccHeader::run_task() {
    u8 *arg0 = (u8 *)this;
    update_fade__8TChCrTagFPv();
    *(s32 *)((s8 *)arg0 + 0x3C) = (s32) (*(s32 *)((s8 *)arg0 + 0x3C) + 1);
}
s32 TChCrTagOccHeader__vt4(Hdr_802A2C30 *arg0) {
    switch (TChCrCharSelect::get_selected_index()) {
    case 0:
        if (arg0->f20 < 3 && arg0->f20 == get_selected_char__15TChCrCharSelectFv()) {
            return 1;
        }
        break;
    default:
        if (arg0->f20 >= 3 && arg0->f20 - 3 == TChCrCharSelect::get_instance()) {
            return 1;
        }
        break;
    }
    return 0;
}

extern void *__vt__17TChCrTagOccHeader[];
void *__dt__8TChCrTagFv(void *, s16);
void __dl__7TObjectFPv(void *);
void *__dt__17TChCrTagOccHeaderFv(void *self, s16 m) {
    if (self != NULL) {
        *(void ***)((s8 *)self + 0x18) = __vt__17TChCrTagOccHeader;
        __dt__8TChCrTagFv(self, 0);
        if (m > 0) {
            __dl__7TObjectFPv(self);
        }
    }
    return self;
}

void render_shadows__7TObjectFv();
void *__vt__17TChCrTagOccHeader[] = {
    0, 0,
    (void *)__dt__17TChCrTagOccHeaderFv,
    (void *)run_task__17TChCrTagOccHeaderFv,
    (void *)render__17TChCrTagOccHeaderFv,
    (void *)render_shadows__7TObjectFv,
    (void *)TChCrTagOccHeader__vt4,
    0,
};

#define update_fade__8TChCrTagFPv (*(void (*)())&update_fade__8TChCrTagFPv)
#define get_selected_char__15TChCrCharSelectFv (*(s32 (*)(void *))&get_selected_char__15TChCrCharSelectFv)

u8 * __ct__8TChCrTagFP7TObjectPv(void *, s32);
void *__ct__17TChCrTagOccHeaderFv(void *arg0);

extern const f32 lbl_805DDECC;
extern const f32 lbl_805DDED0;
extern void *chcr_tag_occ_header_class_name;

void *__ct__17TChCrTagOccHeaderFv(void *ch_cr_tag_occ_header) {
    ((void (*)(void *))__ct__8TChCrTagFP7TObjectPv)(ch_cr_tag_occ_header);
    *(void ***)((s8 *)ch_cr_tag_occ_header + 0x18) = __vt__17TChCrTagOccHeader;
    *(void * *)&((TChCrTagOccHeader *)ch_cr_tag_occ_header)->m_name = chcr_tag_occ_header_class_name;
    *(f32 *)((s8 *)ch_cr_tag_occ_header + 0x28) = lbl_805DDECC;
    *(f32 *)((s8 *)ch_cr_tag_occ_header + 0x2C) = lbl_805DDED0;
    *(f32 *)((s8 *)ch_cr_tag_occ_header + 0x34) = lbl_805DDECC;
    *(f32 *)((s8 *)ch_cr_tag_occ_header + 0x38) = lbl_805DDED0;
    return ch_cr_tag_occ_header;
}

void *__nw__7TObjectFUl(int);
}
extern void *tl_03;

void *create_ch_cr_tag_occ_header(void *arg0) {
    void *o = __nw__7TObjectFUl(0x40);
    if (o != NULL) {
        o = ((void *(*)(void *, void *, void *))__ct__17TChCrTagOccHeaderFv)(o, tl_03, arg0);
    }
    return o;
}

void create_all_ch_cr_tag_headers(void);

void create_all_ch_cr_tag_headers(void) { { int i; for (i = 0; i < 15; i++) { ((int (*)(void *))create_ch_cr_tag_occ_header)((void*)i); } } }

