#include "types.h"
#include "pso/misc/TOWreckAncient02.h"

#include "pso/unk/text_8017DFB0.h"

extern "C" {

void *__nw__7TObjectFUl(int);

void *TOWreckAncient02__create(void *arg0) {
    void *o = __nw__7TObjectFUl(0xB4);
    if (o != NULL) {
        o = TOWreckAncient02__ct((u8 *)o, (s32)arg0);
    }
    return o;
}


}
TOWreckAncient02::~TOWreckAncient02() {

}
