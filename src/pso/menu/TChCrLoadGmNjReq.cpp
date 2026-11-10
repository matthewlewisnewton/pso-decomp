#include "pso/TChCrLoadGmNjReq.h"
#include "pso/system/BmlResourceClass.h"
#include "pso/menu/TChCrLoadGmNjReq.h"
#include "pso/object/TObject_80019A50.h"

#include "types.h"

#pragma push
#pragma readonly_strings on
const char *lbl_805D3B58 = "TChCrLoadGmNjReq";
#pragma pop

extern "C" {
void __ct__7TObjectFP7TObject(void *, void *);
void *__nw__7TObjectFUl(int);
void strncpy(void *, void *, int);

extern s32 __vt__16TChCrLoadGmNjReq[];

void TChCrLoadGmNjReq::run_task() {
    s32 temp_r0;
    temp_r0 = lifetime_remaining - 1;
    lifetime_remaining = temp_r0;
    if (temp_r0 < 0) {
        queue_destruction__7TObjectFv(this);
        return;
    }
    switch (load_state) {
    case 0:
        start_character_load_task();
        return;
    case 1:
        update_model_load();
        return;
    }
}

TChCrLoadGmNjReq::~TChCrLoadGmNjReq() {
    sub_8028C8A8();
    if (loaded_bml != nullptr) {
        delete loaded_bml;
    }
}
void *TChCrLoadGmNjReq__ct(void *ch_cr_load_gm_nj_req, void *arg1, void *arg2) {
    TChCrLoadGmNjReq *self = (TChCrLoadGmNjReq *)ch_cr_load_gm_nj_req;
    __ct__7TObjectFP7TObject(ch_cr_load_gm_nj_req, arg1);
    *(s32 **)((s8 *)ch_cr_load_gm_nj_req + 0x18) = __vt__16TChCrLoadGmNjReq;
    ((TChCrLoadGmNjReq *)ch_cr_load_gm_nj_req)->m_name = lbl_805D3B58;
    self->load_slot = *(s32 *)((s8 *)arg2 + 0x8);
    ((TChCrLoadGmNjReq *)ch_cr_load_gm_nj_req)->m_28 = *(void **)((s8 *)arg2 + 0x10);
    *(void **)((s8 *)ch_cr_load_gm_nj_req + 0x1C) = *(void **)((s8 *)arg2 + 0x4);
    ((TChCrLoadGmNjReq *)ch_cr_load_gm_nj_req)->m_20 = *(void **)((s8 *)arg2 + 0xC);
    strncpy(self->name_buffer, *(void **)((s8 *)arg2 + 0x0), 48);
    ((TChCrLoadGmNjReq *)ch_cr_load_gm_nj_req)->model_ids = self->name_buffer;
    *(u32 *)((s8 *)ch_cr_load_gm_nj_req + 0x64) = 0;
    *(u32 *)((s8 *)ch_cr_load_gm_nj_req + 0x68) = 0;
    self->slot_claimed = 0;
    self->lifetime_remaining = 5370;
    self->load_state = 0;
    return ch_cr_load_gm_nj_req;
}
}

void * create_ch_cr_load_gm_nj_req(void *arg0, void *arg1) {
    void *o;
    o = __nw__7TObjectFUl(0x78);
    if (o != NULL) {
        o = TChCrLoadGmNjReq__ct(o, arg0, arg1);
    }
    return o;
}
