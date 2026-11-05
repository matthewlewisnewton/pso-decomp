#include "types.h"
#include "pso/system/BmlResourceClass.h"
#include "pso/object/TObjGbAdvance.h"
#include "pso/ui/TAdSinglePlyChrSelectGC.h"

struct RecoveredGlobal_80187DC8_lbl_804B6228 { s32 value; u8 remaining[0xC]; };
typedef char RecoveredGlobal_80187DC8_lbl_804B6228_size[sizeof(RecoveredGlobal_80187DC8_lbl_804B6228) == 0x10 ? 1 : -1];

extern "C" {
extern RecoveredGlobal_80187DC8_lbl_804B6228 bm_obj_gba_resource_descriptor;
extern u32 TObjGbAdvance__data_805D5B74;
void TObjGbAdvance::free_shared_data() {
    if ((u32) TObjGbAdvance__data_805D5B74 != 0U) {
        delete (BmlResource *)((void*)TObjGbAdvance__data_805D5B74);
        TObjGbAdvance__data_805D5B74 = 0U;
    }
}
void TObjGbAdvance::load_resource_instance() {
    s32 temp_r3;
    s32 var_r0;
    temp_r3 = (int)new BmlResource(5, (BmlResourceDescriptor *)(&bm_obj_gba_resource_descriptor.value), 0, 0, (void *)(0));
    var_r0 = temp_r3;
    (*(s32 *)&TObjGbAdvance__data_805D5B74) = var_r0;
}

}
