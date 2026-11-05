#include "types.h"
#include "pso/unk/text_801815A0.h"

extern "C" {

void __dt__7TObjectFv(void *, int);
void __dl__7TObjectFPv(void *);
extern s32 __vt__19TObjCityAirCar_Ctrl[];

void *__dt__19TObjCityAirCar_CtrlFv(void *arg0, s16 arg1) {
    if (arg0 != NULL) {
        *(s32 **)((s8 *)arg0 + 0x18) = __vt__19TObjCityAirCar_Ctrl;
        __dt__7TObjectFv(arg0, 0);
        if (arg1 > 0) {
            __dl__7TObjectFPv(arg0);
        }
    }
    return arg0;
}

}
