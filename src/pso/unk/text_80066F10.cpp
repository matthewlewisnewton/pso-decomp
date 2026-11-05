#include "types.h"
#include "pso/system/EnemyBmlResource.h"
#include "pso/enemy/TObjEneDD_800BB804.h"
#include "pso/boss/TBoss8Dragon_8005D700.h"
#include "pso/misc/TLanguage_801E4874.h"
#include "pso/unk/text_80066F10.h"
extern char bm_obj_boss5_common_resource_descriptor[];
extern char lbl_8043810C[];
extern void *lbl_805D4DD8;
extern void *boss5_common_texture_list;
void load_boss5_common_assets(void) {
    switch (TBoss8Dragon__sub_8005D700()) {
    case 0:
        lbl_805D4DD8 = (void *)(s32)load_enemy_bml_resource((BmlResourceDescriptor *)((u8 *)bm_obj_boss5_common_resource_descriptor));
        boss5_common_texture_list = load_gvm_texture_file((s32)lbl_8043810C);
        break;
    }
}
