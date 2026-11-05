#include "types.h"
#include "pso/system/BmlResourceClass.h"
#include "pso/unk/text_803516F8.h"
#include "pso/ui/TAdSinglePlyChrSelectGC.h"

struct RecoveredGlobal_803516F8_lbl_804F0E4C { s32 value; u8 remaining[0xC]; };
typedef char RecoveredGlobal_803516F8_lbl_804F0E4C_size[sizeof(RecoveredGlobal_803516F8_lbl_804F0E4C) == 0x10 ? 1 : -1];

extern "C" {
extern RecoveredGlobal_803516F8_lbl_804F0E4C bm_butterfly_lobby_resource_descriptor;
extern s32 lobby_butterfly_bml_resource;
void fn_803516F8(void) {
    s32 temp_r3;
    s32 var_r0;
    temp_r3 = (int)new BmlResource(1, (BmlResourceDescriptor *)(&bm_butterfly_lobby_resource_descriptor.value), 0, 0, (void *)(0));
    var_r0 = temp_r3;
    lobby_butterfly_bml_resource = var_r0;
}

}
