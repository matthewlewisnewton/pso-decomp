#include "pso/misc/TOVS2WallResources.h"
#include "types.h"
#include "pso/misc/TOVS2Wreck05.h"
#include "pso/misc/TOVS2Wall01.h"

extern "C" {

void __dl__7TObjectFPv(void *);
void *__nw__7TObjectFUl(int);

void *TOVS2Wreck05__create(void *arg0) {
    void *o = __nw__7TObjectFUl(0xD0);
    if (o != NULL) {
        o = TOVS2Wreck05__ct(o, arg0);
    }
    return o;
}

extern s32 __vt__12TOVS2Wreck05[];

}

TOVS2Wreck05::~TOVS2Wreck05() {}

extern "C" {

void *TOVS2Wreck05__ct(void *arg0, void *arg1) {
    __ct__5TOVS2FPvl(arg0, arg1, 4);
    *(s32 **)((s8 *)arg0 + 0x18) = __vt__12TOVS2Wreck05;
    ((TOVS2Wreck05 *)arg0)->m_name = lbl_805D31D8;
    return arg0;
}

}
