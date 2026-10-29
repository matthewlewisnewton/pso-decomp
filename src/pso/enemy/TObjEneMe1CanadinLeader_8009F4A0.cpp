#include "types.h"
#include "pso/enemy/TObjEneMe1CanadinLeader.h"

extern "C" {

void *__nw__7TObjectFUl(int);

extern void *tl_04;

void *TObjEneMe1CanadinLeader::create_canadin(void *arg0, void *arg1, void *arg2, void *arg3) {
    void *o;
    o = __nw__7TObjectFUl(0x4CC);
    if (o != NULL) {
        o = TObjEneMe1Canadin__ct((u8 *)o, (s32)tl_04, (u8 *)arg0, (s32)arg1, (s32)arg2, (s32)arg3);
    }
    return o;
}

}
