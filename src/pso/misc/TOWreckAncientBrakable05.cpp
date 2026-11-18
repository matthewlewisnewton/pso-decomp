#include "types.h"
#include "pso/misc/TOWreckAncientBrakable05.h"

extern "C" {

void *TOWreckAncientBrakable05__create(void *arg0);
u8 *TOWreckAncientBrakable05__ct(TOWreckAncientBrakable05 *arg0, s32 arg1);
void *__nw__7TObjectFUl(int);

void *TOWreckAncientBrakable05__create(void *arg0) {
    void *o = __nw__7TObjectFUl(0xBC);
    if (o != NULL) {
        o = TOWreckAncientBrakable05__ct((TOWreckAncientBrakable05 *)((u8 *)o), (s32)arg0);
    }
    return o;
}

TOWreckAncientBrakable05::~TOWreckAncientBrakable05() {}

}
