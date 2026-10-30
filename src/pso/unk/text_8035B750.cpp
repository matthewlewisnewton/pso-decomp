#include "types.h"
#include "pso/system/BmlResourceClass.h"
#include "pso/unk/text_8035B750.h"

extern "C" {
extern u32 lbl_805D6F50;

void fn_8035B750(void) {
    if ((u32) lbl_805D6F50 != 0U) {
        delete (BmlResource *)((void*)lbl_805D6F50);
        lbl_805D6F50 = 0U;
    }
}

}
