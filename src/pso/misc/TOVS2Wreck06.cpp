#include "pso/misc/TOVS2WallResources.h"
#include "types.h"
#include "pso/misc/TOVS2Wreck06.h"
#include "pso/misc/TOVS2Wall01.h"

extern "C" {

void __dl__7TObjectFPv(void *);
void *__nw__7TObjectFUl(int);

void *TOVS2Wreck06__create(void *arg0) {
    void *o = __nw__7TObjectFUl(0xD0);
    if (o != NULL) {
        o = TOVS2Wreck06__ct(o, arg0);
    }
    return o;
}

extern s32 __vt__12TOVS2Wreck06[];

}

TOVS2Wreck06::~TOVS2Wreck06() {}

extern "C" {

void *TOVS2Wreck06__ct(void *arg0, void *arg1) {
    __ct__5TOVS2FPvl(arg0, arg1, 5);
    *(s32 **)((s8 *)arg0 + 0x18) = __vt__12TOVS2Wreck06;
    ((TOVS2Wreck06 *)arg0)->m_name = TOVS2Wreck06__class_name;
    return arg0;
}

}
