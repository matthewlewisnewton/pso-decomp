#include "types.h"
#include "pso/unk/text_800F93B4.h"

extern "C" {
s32 fn_800FFE14(s32, GslArchiveEntry *, s32);
s32 fn_800FFE04();
void fn_800F93B4(char *filename, GslArchiveEntry *entries, s32 count) {
    fn_800FFE14(fn_800FFE04(), entries, count);
}

}
