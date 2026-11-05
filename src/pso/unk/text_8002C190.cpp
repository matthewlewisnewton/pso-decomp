#include "types.h"
#include "pso/system/EnemyBmlResource.h"
extern "C" {
s32 isV2Mode__12TBoss1DragonFv(void);
u8 *load_gvm_texture_file(s32 arg0);
extern u8 dragon_common_texture_filename[];
extern u8 lbl_8043552C[];
extern u8 dragon_common_alternate_texture_filename[];
extern u8 dragon_ground_resource_descriptor[];
extern s32 lbl_805D4B50;
extern s32 dragon_common_texture_list;
void load_dragon_ground_assets(void);
void load_dragon_ground_assets(void) {
    switch (isV2Mode__12TBoss1DragonFv()) {
    case 0:
        lbl_805D4B50 = (s32)load_enemy_bml_resource((BmlResourceDescriptor *)(dragon_ground_resource_descriptor));
        dragon_common_texture_list = (s32)load_gvm_texture_file((s32)dragon_common_texture_filename);
        break;
    case 1:
        lbl_805D4B50 = (s32)load_enemy_bml_resource_named((BmlResourceDescriptor *)(dragon_ground_resource_descriptor), (const char *)(lbl_8043552C));
        dragon_common_texture_list = (s32)load_gvm_texture_file((s32)dragon_common_alternate_texture_filename);
        break;
    }
}

}
