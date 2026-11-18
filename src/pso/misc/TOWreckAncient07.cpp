#include "types.h"
#include "pso/misc/TOWreckAncient07.h"
#include "pso/unk/text_8017D7CC.h"

extern "C" {

void *__nw__7TObjectFUl(int);

void *TOWreckAncient07__create(void *arg0) {
    void *o = __nw__7TObjectFUl(0xB4);
    if (o != NULL) {
        o = TOWreckAncient07__ct((u8 *)o, (s32)arg0);
    }
    return o;
}

TOWreckAncient07::~TOWreckAncient07() {}

}
