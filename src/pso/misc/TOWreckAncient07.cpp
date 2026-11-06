#include "types.h"
#include "pso/misc/TOWreckAncient07.h"
#include "pso/unk/text_8017D7CC.h"

extern "C" {

void __dl__7TObjectFPv(void *);
void *__dt__14TOWreckAncientFv(void *arg0, s16 arg1);
void *__nw__7TObjectFUl(int);

void *TOWreckAncient07__create(void *arg0) {
    void *o = __nw__7TObjectFUl(0xB4);
    if (o != NULL) {
        o = TOWreckAncient07__ct((u8 *)o, (s32)arg0);
    }
    return o;
}

extern s32 __vt__16TOWreckAncient07[];

void *__dt__16TOWreckAncient07Fv(void *arg0, s16 arg1) {
    if (arg0 != NULL) {
        *(s32 **)((s8 *)arg0 + 0x18) = __vt__16TOWreckAncient07;
        __dt__14TOWreckAncientFv(arg0, 0);
        if (arg1 > 0) {
            __dl__7TObjectFPv(arg0);
        }
    }
    return arg0;
}

}
