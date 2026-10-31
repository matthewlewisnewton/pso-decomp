#include "types.h"
#include "pso/system/BmlResourceClass.h"
#include "pso/misc/TLobby_802A018C.h"
#include "pso/misc/TLobby.h"
#include "pso/misc/TODoorFourLightBase.h"
#include "pso/ui/TAdSinglePlyChrSelectGC.h"
#include "pso/map/FloorArea.h"

extern "C" {
u8 *load_gvm_texture_file(s32 arg0);
extern s32 lbl_80466118[];
extern s32 lbl_80466138[];
extern s32 lbl_80466150[];
extern s32 lbl_80466170[];
extern s32 bm_o_door_seabed01_resource_descriptor[];
extern u32 door_labo_bml_resource;
extern u32 lbl_805D6604;
extern u32 lbl_805D6608;
s32 release_texture_list(void*);

void TLobby::free_chr_select_slots() {
    if ((u32) lbl_805D6608 != 0U) {
        release_texture_list((void*)lbl_805D6608);
        TAdSinglePlyChrSelectGC::safe_free(lbl_805D6608);
        lbl_805D6608 = 0U;
    }
    if ((u32) lbl_805D6604 != 0U) {
        release_texture_list((void*)lbl_805D6604);
        TAdSinglePlyChrSelectGC::safe_free(lbl_805D6604);
        lbl_805D6604 = 0U;
    }
    if ((u32) door_labo_bml_resource != 0U) {
        delete (BmlResource *)(door_labo_bml_resource);
        door_labo_bml_resource = 0U;
    }
}

void TLanguage__sub_802A0204(void) {
    s32 area;
    s32 var_r0;
    s32 var_r0_2;
    area = get_current_floor_area();
    switch (area) {
    case AREA_SEABED_UPPER:
        var_r0 = (int)new BmlResource(5, (BmlResourceDescriptor *)(bm_o_door_seabed01_resource_descriptor), 0, 0, (void *)(0));
        door_labo_bml_resource = var_r0;
        lbl_805D6604 = (u32)load_gvm_texture_file((s32)lbl_80466118);
        lbl_805D6608 = (u32)load_gvm_texture_file((s32)lbl_80466138);
        return;
    case AREA_SEABED_LOWER:
        var_r0_2 = (int)new BmlResource(5, (BmlResourceDescriptor *)(bm_o_door_seabed01_resource_descriptor), 0, 0, (void *)(0));
        door_labo_bml_resource = var_r0_2;
        lbl_805D6604 = (u32)load_gvm_texture_file((s32)lbl_80466150);
        lbl_805D6608 = (u32)load_gvm_texture_file((s32)lbl_80466170);
        return;
    }
}

void TODoorFourLightBase::clamp_light_index() {
    if ((s32) this->set_params[1] < 0) {
        this->set_params[1] = 0;
    }
    if ((s32) this->set_params[1] > 4) {
        *(s32 *)&this->set_params[1] = 4;
    }
    this->m_f8 = (s32) this->set_params[1];
}

}
