#include "types.h"
#include "pso/system/EnemyBmlResource.h"
#include "pso/enemy/TObjEneDD_800BB804.h"
#include "pso/unk/text_802FE8CC.h"
extern "C" {
extern char bm_obj_boss1_common_j_resource_descriptor[];
extern char lbl_80474C64[];
extern s32 boss8_eff_tail_bml_resource;
extern s32 dragon_tail_gvm_texture_handle;
u8 *load_gvm_texture_file(s32 arg0);
void fn_802FE8CC(void) {
    boss8_eff_tail_bml_resource = (s32)load_enemy_bml_resource((BmlResourceDescriptor *)((u8 *)bm_obj_boss1_common_j_resource_descriptor));
    dragon_tail_gvm_texture_handle = (s32)load_gvm_texture_file((s32)lbl_80474C64);
}

}
