#include "types.h"
#include "pso/unk/text_801A5778.h"
#include "pso/ui/TAdSinglePlyChrSelectGC.h"

extern "C" {
s32 fn_803DAFA8(void *, void *);
u8 *set_stream_and_load_file__6TLobbyFPCv();
s32 DCStoreRange(void *, int);
void fn_801A5778(s32 arg0, s32 *arg1) {
    u8 *temp_r3;
    temp_r3 = (u8 *)(set_stream_and_load_file__6TLobbyFPCv());
    fn_803DAFA8(temp_r3, arg1);
    DCStoreRange((void *) (*arg1), 0x40000);
    TAdSinglePlyChrSelectGC::safe_free((void *)temp_r3);
}

}
