#include "types.h"
#include "pso/misc/TOWreckAncient06.h"
#include "pso/unk/text_8017D8F0.h"

extern "C" {

void *__nw__7TObjectFUl(int);

void *TOWreckAncient06__create(void *arg0) {
    void *o = __nw__7TObjectFUl(0xB4);
    if (o != NULL) {
        o = TOWreckAncient06__ct((u8 *)o, (s32)arg0);
    }
    return o;
}

TOWreckAncient06::~TOWreckAncient06() {}

}
