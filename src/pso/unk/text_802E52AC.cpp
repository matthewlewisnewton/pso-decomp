#include "types.h"
#include "pso/system/BmlResourceClass.h"
#include "pso/unk/text_802E52AC.h"
#include "pso/ui/TAdSinglePlyChrSelectGC.h"

extern "C" {
extern u8 lbl_804E35E8[];
extern u32 lbl_805D68F4;

void fn_802E52AC() {
    s32 r;
    if (lbl_805D68F4 == 0) {
        r = (int)new BmlResource(5, (BmlResourceDescriptor *)(lbl_804E35E8), 0, 0, (void *)(0));
        lbl_805D68F4 = r;
        if (lbl_805D68F4 == 0) {
            return;
        }
    }
}
}
