#include "types.h"
#include "pso/enemy/TObjEneMorfosArm_80335218.h"
#include "pso/enemy/TObjEneMorfosArm.h"
#include "pso/enemy/TObjEneMorfos.h"

extern "C" {
void *__nw__7TObjectFUl(int);

void TObjEneMorfosArm::unload_static_data() {}

extern s32 TObjEneMorfosArm__parent_morfos_instance;

void *TObjEneMorfosArm::create(void *arg0, void *arg1) {
    void *o;
    o = __nw__7TObjectFUl(0x104);
    if (o != NULL) {
        o = TObjEneMorfosArm__ct((TObjEneMorfosArm *)((u8 *)o), (s32)((s32)arg0), (u8 *)((u8 *)arg1));
    }
    return o;
}

void TObjEneMorfosArm::init_global() {
    TObjEneMorfosArm__parent_morfos_instance = (s32)TObjEneMorfos::get_resources();
}

}
