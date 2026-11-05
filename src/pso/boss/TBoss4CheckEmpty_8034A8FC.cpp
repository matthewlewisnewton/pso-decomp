#include "types.h"
#include "pso/TBoss4CheckEmpty.h"

extern "C" {

void *__ct__16TBoss4CheckEmptyFv(void *, void *);
void *__nw__7TObjectFUl(int);

extern void *tl_02;

void *TBoss4CheckEmpty::create() {
    void *o = __nw__7TObjectFUl(0x20);
    if (o != NULL) {
        o = __ct__16TBoss4CheckEmptyFv(o, tl_02);
    }
    return o;
}

}
