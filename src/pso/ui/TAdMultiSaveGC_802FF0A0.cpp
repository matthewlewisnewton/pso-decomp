#include "types.h"
#include "pso/system/BmlResourceClass.h"
#include "pso/ui/TAdMultiSaveGC.h"
#include "pso/TAdMultiChgGameModeGC.h"
#include "pso/TMainTask.h"
#include "pso/ui/TAdSinglePlyChrSelectGC.h"

struct RecoveredGlobal_802FF0D8_lbl_804E6570 { s32 value; u8 remaining[0xC]; };
typedef char RecoveredGlobal_802FF0D8_lbl_804E6570_size[sizeof(RecoveredGlobal_802FF0D8_lbl_804E6570) == 0x10 ? 1 : -1];

extern "C" {
extern RecoveredGlobal_802FF0D8_lbl_804E6570 TAdMultiSaveGC__shared_resource_desc;
extern u32 admultisave_shared_model_resource;
void TAdMultiSaveGC::free_window() {
    if ((u32) admultisave_shared_model_resource != 0U) {
        delete (BmlResource *)((void*)admultisave_shared_model_resource);
        admultisave_shared_model_resource = 0U;
    }
}

void TAdMultiSaveGC::load_shared_resource() {
    s32 temp_r3;
    s32 var_r0;
    temp_r3 = (int)new BmlResource(1, (BmlResourceDescriptor *)(&TAdMultiSaveGC__shared_resource_desc.value), 0, 0, (void *)(0));
    var_r0 = temp_r3;
    (*(s32 *)&admultisave_shared_model_resource) = var_r0;
}
void TAdMultiSaveGC::render() {
    if (TMainTask::get_render_pass() == 1) return;
}

}
