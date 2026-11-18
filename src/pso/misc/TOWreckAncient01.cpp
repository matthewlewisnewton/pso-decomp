#include "types.h"
#include "pso/misc/TOWreckAncient01.h"
#include "pso/unk/text_8017DC5C.h"

extern "C" {

void *__nw__7TObjectFUl(int);

void *TOWreckAncient01__create(void *arg0) {
    void *o = __nw__7TObjectFUl(0xB4);
    if (o != NULL) {
        o = TOWreckAncient01__ct((u8 *)o, (s32)arg0);
    }
    return o;
}

TOWreckAncient01::~TOWreckAncient01() {}

}
