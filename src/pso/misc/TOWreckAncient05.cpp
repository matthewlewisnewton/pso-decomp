#include "types.h"
#include "pso/misc/TOWreckAncient05.h"
#include "pso/unk/text_8017DA14.h"

extern "C" {

void *__nw__7TObjectFUl(int);

void *TOWreckAncient05__create(void *arg0) {
    void *o = __nw__7TObjectFUl(0xB4);
    if (o != NULL) {
        o = TOWreckAncient05__ct((u8 *)o, (s32)arg0);
    }
    return o;
}

TOWreckAncient05::~TOWreckAncient05() {}

}
