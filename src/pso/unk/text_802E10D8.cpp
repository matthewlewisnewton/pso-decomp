#include "types.h"
#include "pso/system/BmlResourceClass.h"
#include "pso/unk/text_802E10D8.h"
#include "pso/ui/TAdSinglePlyChrSelectGC.h"

struct RecoveredGlobal_802E10D8_lbl_804D3900 { s32 value; u8 remaining[0xC]; };
typedef char RecoveredGlobal_802E10D8_lbl_804D3900_size[sizeof(RecoveredGlobal_802E10D8_lbl_804D3900) == 0x10 ? 1 : -1];

extern "C" {
extern RecoveredGlobal_802E10D8_lbl_804D3900 creation_menu_resource_descriptor;
extern s32 TAdMultiPlyChrSelectGC__resource_bundle;
void fn_802E10D8(void) {
    s32 temp_r3;
    s32 var_r0;
    temp_r3 = (int)new BmlResource(1, (BmlResourceDescriptor *)(&creation_menu_resource_descriptor.value), 0, 0, (void *)(0));
    var_r0 = temp_r3;
    TAdMultiPlyChrSelectGC__resource_bundle = var_r0;
}

}
