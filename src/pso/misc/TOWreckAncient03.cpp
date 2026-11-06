#include "types.h"
#include "pso/misc/TOWreckAncient03.h"

#include "pso/unk/text_8017E0D0.h"

extern "C" {

void *__nw__7TObjectFUl(int);

void *TOWreckAncient03__create(void *arg0) {
    void *o = __nw__7TObjectFUl(0xB4);
    if (o != NULL) {
        o = TOWreckAncient03__ct((u8 *)o, (s32)arg0);
    }
    return o;
}


}
TOWreckAncient03::~TOWreckAncient03() {

}
