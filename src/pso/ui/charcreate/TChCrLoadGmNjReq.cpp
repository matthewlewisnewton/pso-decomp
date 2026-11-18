#define TOBJECT_OUT_OF_LINE_HELPERS
#include "pso/system/BmlResource.h"
#include "pso/ui/charcreate/TChCrLoadGmNjReq.h"
#include "pso/system/task/TObject.h"

#include "types.h"

#pragma push
#pragma readonly_strings on
const char *TChCrLoadGmNjReq__name = "TChCrLoadGmNjReq";
#pragma pop

// The argument block create_ch_cr_load_gm_nj_req passes to the constructor.
struct TChCrLoadGmNjReqArgs {
    const char *name;
    u32 *model_out;
    s32 load_slot;
    s32 completion_mask;
    s32 *completion_flags;
};

extern "C" {

void strncpy(void *, const void *, int);

void TChCrLoadGmNjReq::run_task() {
    s32 timer;
    timer = lifetime_remaining - 1;
    lifetime_remaining = timer;
    if (timer < 0) {
        queue_destruction();
        return;
    }
    switch (state) {
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
}

TChCrLoadGmNjReq::TChCrLoadGmNjReq(TObject *parent, void *args) : TObject(parent) {
    m_name = TChCrLoadGmNjReq__name;
    load_slot = ((TChCrLoadGmNjReqArgs *)args)->load_slot;
    completion_flags = ((TChCrLoadGmNjReqArgs *)args)->completion_flags;
    model_out = ((TChCrLoadGmNjReqArgs *)args)->model_out;
    completion_mask = ((TChCrLoadGmNjReqArgs *)args)->completion_mask;
    strncpy(name, ((TChCrLoadGmNjReqArgs *)args)->name, 48);
    model_ids[0] = name;
    model_ids[1] = NULL;
    loaded_bml = 0;
    slot_claimed = 0;
    lifetime_remaining = 5370;
    state = 0;
}

void *create_ch_cr_load_gm_nj_req(void *parent, void *args) {
    return new TChCrLoadGmNjReq((TObject *)parent, args);
}
