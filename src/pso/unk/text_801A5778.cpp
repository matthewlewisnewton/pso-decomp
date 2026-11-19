#include "pso/system/memory.h"
#include "pso/system/ResourceFile.h"
#include "types.h"
#include "pso/unk/text_801A5778.h"

extern "C" {
s32 fn_803DAFA8(void *, void *);
s32 DCStoreRange(void *, int);
void fn_801A5778(const char *filename, s32 *arg1) {
    u8 *temp_r3;
    temp_r3 = load_disc_file(filename);
    fn_803DAFA8(temp_r3, arg1);
    DCStoreRange((void *) (*arg1), 0x40000);
    safe_free(temp_r3);
}

}
