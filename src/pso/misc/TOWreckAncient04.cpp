#include "types.h"
#include "pso/misc/TOWreckAncient04.h"
#include "pso/unk/text_8017DB38.h"

extern "C" {

void __dl__7TObjectFPv(void *);
void *__dt__14TOWreckAncientFv(void *arg0, s16 arg1);
void *__nw__7TObjectFUl(int);

void *TOWreckAncient04__create(void *arg0) {
    void *o = __nw__7TObjectFUl(0xB4);
    if (o != NULL) {
        o = TOWreckAncient04__ct((u8 *)o, (s32)arg0);
    }
    return o;
}

extern s32 __vt__16TOWreckAncient04[];

void *__dt__16TOWreckAncient04Fv(void *arg0, s16 arg1) {
    if (arg0 != NULL) {
        *(s32 **)((s8 *)arg0 + 0x18) = __vt__16TOWreckAncient04;
        __dt__14TOWreckAncientFv(arg0, 0);
        if (arg1 > 0) {
            __dl__7TObjectFPv(arg0);
        }
    }
    return arg0;
}

}
