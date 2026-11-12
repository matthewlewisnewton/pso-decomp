#include "types.h"
#include "pso/boss/olgaflow/TBoss6Zanzo.h"

extern "C" {

void *__ct__11TBoss6ZanzoFP7TObjectll(void *, TObject *, s32, s32);
void *__nw__7TObjectFUl(int);

void *TBoss6Zanzo::create(TObject *arg0, s32 arg1, s32 arg2) {
    void *o;
    o = __nw__7TObjectFUl(0x2C);
    if (o != NULL) {
        o = __ct__11TBoss6ZanzoFP7TObjectll(o, arg0, arg1, arg2);
    }
    return o;
}

}
