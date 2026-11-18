#include "pso/object/TObjWarpResources.h"
#include "types.h"
#include "pso/system/BmlResourceClass.h"
#include "pso/misc/TLanguage_801E4874.h"
#include "pso/unk/text_8019DBB4.h"
#include "pso/ui/TAdSinglePlyChrSelectGC.h"

extern const char lbl_80446470[] = "fs_obj_warp.gvm";
void load_forest_warp_resources(void) {
    forest_warp_bml_resource = new BmlResource(5, &forest_warp_resource_descriptor, 0, 0, NULL);
    forest_warp_texture_list = load_gvm_texture_file(lbl_80446470);
}
