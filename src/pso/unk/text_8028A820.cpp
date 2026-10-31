#include "types.h"
#include "pso/system/BmlResourceClass.h"
#include "pso/misc/TLanguage_801E4874.h"
#include "pso/unk/text_8028A820.h"
#include "pso/map/FloorArea.h"
extern "C" {
}
extern u8 lbl_80450C50[];
extern u8 lbl_80450C6C[];
extern u8 bm_obj_door_ruins_resource_descriptor[];
extern u8 bm_obj_door_space_resource_descriptor[];
extern void *green_door_bml_resource;
extern void *green_door_texture_handle;
void load_green_door_resources(void) {
    void *p;
    green_door_bml_resource = 0;
    green_door_texture_handle = 0;
    switch (get_current_floor_area()) {
    case AREA_VR_TEMPLE_ALPHA:
    case AREA_VR_TEMPLE_BETA:
        p = new BmlResource(5, (BmlResourceDescriptor *)(bm_obj_door_ruins_resource_descriptor), 0, 0, (void *)(0));
        green_door_bml_resource = p;
        green_door_texture_handle = load_gvm_texture_file((s32)lbl_80450C50);
        break;
    case AREA_VR_SPACESHIP_ALPHA:
    case AREA_VR_SPACESHIP_BETA:
        p = new BmlResource(5, (BmlResourceDescriptor *)(bm_obj_door_space_resource_descriptor), 0, 0, (void *)(0));
        green_door_bml_resource = p;
        green_door_texture_handle = load_gvm_texture_file((s32)lbl_80450C6C);
        break;
    }
}
