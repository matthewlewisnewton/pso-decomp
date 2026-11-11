#include "types.h"
#include "pso/unk/text_8035B750.h"

extern "C" {
void __dt__11BmlResourceFv(void*, int);
extern u32 lbl_805D6F50;

void fn_8035B750(void) {
    if ((u32) lbl_805D6F50 != 0U) {
        __dt__11BmlResourceFv((void*)lbl_805D6F50, 1);
        lbl_805D6F50 = 0U;
    }
}

}
