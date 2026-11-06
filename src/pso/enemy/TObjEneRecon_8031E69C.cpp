#include "types.h"
#include "pso/enemy/TObjEneRecon.h"

extern "C" {

void *TObjEneRecon__ct(void *, void *, void *, void *, void *, void *, void *);
void *__nw__7TObjectFUl(int);

extern void *tl_04;

void *TObjEneRecon::create(void *arg0, void *arg1, void *arg2, void *arg3, void *arg4) {
    void *o;
    o = __nw__7TObjectFUl(0x4E4);
    if (o != NULL) {
        o = TObjEneRecon__ct(o, tl_04, arg0, arg1, arg2, arg3, arg4);
    }
    return o;
}

}
