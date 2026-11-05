#include "types.h"
#include "pso/ui/TAdDialingGC.h"

extern "C" {

s32 TAdDialingGC__ct(void *, s32);
u32 __nw__7TObjectFUl(s32);

extern s32 tl_window;
extern u32 TAdDialingGC__instance;

void TAdDialingGC::create() {
    void *temp_r3;

    if ((u32) TAdDialingGC__instance == 0U) {
        temp_r3 = (void *) __nw__7TObjectFUl(0xA8);
        if (temp_r3 != NULL) {
            TAdDialingGC__ct(temp_r3, tl_window);
        }
    }
}

}
