#include "types.h"
#include "pso/misc/TOWreckAncient04.h"
#include "pso/unk/text_8017DB38.h"

extern "C" {

void *__nw__7TObjectFUl(int);

void *TOWreckAncient04__create(void *arg0) {
    void *o = __nw__7TObjectFUl(0xB4);
    if (o != NULL) {
        o = TOWreckAncient04__ct((u8 *)o, (s32)arg0);
    }
    return o;
}

TOWreckAncient04::~TOWreckAncient04() {}

}
