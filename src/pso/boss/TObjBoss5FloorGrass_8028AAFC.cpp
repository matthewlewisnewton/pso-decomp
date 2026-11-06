#include "types.h"
#include "pso/TObjBoss5FloorGrass.h"

extern "C" {

void *__ct__19TObjBoss5FloorGrassFv(void *, void *);
void *__nw__7TObjectFUl(int);

extern void *tl_02;

void *TObjBoss5FloorGrass::create() {
    void *o = __nw__7TObjectFUl(0x1C);
    if (o != NULL) {
        o = __ct__19TObjBoss5FloorGrassFv(o, tl_02);
    }
    return o;
}

}
