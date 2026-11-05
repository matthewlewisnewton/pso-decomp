#include "types.h"
#include "pso/object/TObjDFDemo0.h"

extern "C" {
void *TObjDFDemo0__ct(void *, void *);
void *__nw__7TObjectFUl(int);
}

void *TObjDFDemo0::create(void *arg0) {
    void *o = __nw__7TObjectFUl(0x110);
    if (o != NULL) {
        o = TObjDFDemo0__ct(o, arg0);
    }
    return o;
}
