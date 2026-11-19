#include "pso/item/TUnk_8049F40C.h"
#include "pso/system/Adxf.h"
#include "pso/item/TItemLoad.h"
#include "pso/item/TUnk_8049F42C.h"

#include "types.h"

struct O_80110788 { s32 arr[4]; s32 f10; s32 f14; };

extern "C" {
s32 test_flags_any(s32 *flags, s32 mask);

s32 TUnk_8049F40C::model_chunk(s32 i) {
    return chunks[i];
}

int TUnk_8049F42C::update_item() { return test_flags_any((s32 *)((char*)this + 0x1c), 2); }

void TItemLoad::clear_slots() {
    O_80110788 *self = (O_80110788 *)this;
    s32 i;
    for (i = 0; i < 4; i++) {
        self->arr[i] = 0;
    }
    self->f10 = 0;
    self->f14 = 0;
}

void TUnk_8049F42C::vfunc_3() {  }
s32 ItemArchiveReader::get_status() { return ADXF_GetStat(handle); }
s32 TItemLoad__sub_801107DC(void* p) { return *(s32*)((char*)p + 0xc); }
s32 TItemLoad__sub_801107E4(void* p) { return *(s32*)((char*)p + 0x1c); }
void* TItemLoad__sub_801107EC(void* p) { return (char*)p + 0x2c; }
int TItemLoad__sub_801107F4(void* p) { return *(u32*)((char*)p + 0x20) == 0; }
TItemLoad::~TItemLoad() {}

}
