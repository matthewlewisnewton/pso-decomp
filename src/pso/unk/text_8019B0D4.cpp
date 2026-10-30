#include "types.h"
#include "pso/system/BmlResourceClass.h"
#include "pso/unk/text_8019B0D4.h"
#include "pso/ui/TAdSinglePlyChrSelectGC.h"

struct RecoveredGlobal_8019B0D4_lbl_804B8FE0 { s32 value; u8 remaining[0xC]; };
typedef char RecoveredGlobal_8019B0D4_lbl_804B8FE0_size[sizeof(RecoveredGlobal_8019B0D4_lbl_804B8FE0) == 0x10 ? 1 : -1];

extern "C" {
extern RecoveredGlobal_8019B0D4_lbl_804B8FE0 fe_obj_tutate_resource_descriptor;
extern s32 TObjTuitate__bml_resource;
void fn_8019B0D4(void) {
    s32 temp_r3;
    s32 var_r0;
    temp_r3 = (int)new BmlResource(1, (BmlResourceDescriptor *)(&fe_obj_tutate_resource_descriptor.value), 0, 0, (void *)(0));
    var_r0 = temp_r3;
    TObjTuitate__bml_resource = var_r0;
}

}
