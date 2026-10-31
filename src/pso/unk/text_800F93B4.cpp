#include "types.h"
#include "pso/unk/text_800F93B4.h"

extern "C" {
s32 fn_800FFE14(s32, s32, void *);
s32 fn_800FFE04();
void fn_800F93B4(s32 arg0, s32 arg1, void *arg2) {
    fn_800FFE14(fn_800FFE04(), arg1, arg2);
}

}
