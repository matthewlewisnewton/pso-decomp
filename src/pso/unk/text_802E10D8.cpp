#include "types.h"
#include "pso/system/BmlResourceClass.h"
#include "pso/unk/text_802E10D8.h"
#include "pso/ui/TAdSinglePlyChrSelectGC.h"
#include "pso/misc/TCharaMaking.h"
#include "pso/system/BmlResourceLoader.h"


extern "C" {

extern s32 TAdMultiPlyChrSelectGC__resource_bundle;
void fn_802E10D8(void) {
    s32 temp_r3;
    s32 var_r0;
    temp_r3 = (int)new BmlResource(1, (BmlResourceDescriptor *)(&creation_menu_resource_descriptor), 0, 0, (void *)(0));
    var_r0 = temp_r3;
    TAdMultiPlyChrSelectGC__resource_bundle = var_r0;
}

}
