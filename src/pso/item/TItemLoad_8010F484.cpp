#include "types.h"
#include "pso/item/TUnk_8049F3F4.h"
#include "pso/TItemLoad.h"
#include "pso/item/TUnk_8049F42C.h"

extern "C" {

void __ct__7TObjectFP7TObject(void *);

extern s32 lbl_8049F3F4[];

void *TUnk_8049F3F4::init(void *arg1, void *arg2, void *arg3, void *arg4) {
    __ct__7TObjectFP7TObject(this);
    *(s32 **)((s8 *)this + 0x18) = lbl_8049F3F4;
    *(void * *)&this->unk_1C = arg2;
    this->m_20 = 0;
    *(void * *)&this->unk_24 = arg3;
    *(void * *)&this->m_28 = arg4;
    ((TItemLoad *)((char *)this + 44))->clear_slots();
    this->m_20 = 1;
    return this;
}

extern TUnk_8049F42C *item_texture_archive_loader;
extern TUnk_8049F42C *item_model_chunk_loader;

void TItemLoad::update_all() {
    TUnk_8049F42C *temp_r3;
    temp_r3 = item_texture_archive_loader;
    if (temp_r3 != 0) {
        temp_r3->update_state();
    }
    temp_r3 = item_model_chunk_loader;
    if (temp_r3 != 0) {
        temp_r3->update_state();
    }
}

}
