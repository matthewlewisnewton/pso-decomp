#include "pso/map/CsnGroundQuery.h"
#include "pso/system/NinjaTypes.h"
#include <dolphin/mtx.h>
#include "pso/misc/TRaderMapCore.h"
#include "pso/boss/TUnk_804ECDC0.h"
#include "pso/system/vector.h"
#include "pso/item/TItem.h"
#include "pso/TBoss5GryphonLightning.h"
#include "pso/TBoss5GryphonLightningHorn.h"

#include "types.h"

#include <stddef.h>
#include "pso/boss/TBoss8Dragon.h"
#include "pso/misc/TTecSlicer.h"
#include "pso/player/TObjPlayer.h"

struct RecoveredGlobal_8012DBF4_lbl_804A5B20 {
    s32 value;
    u8 remaining[0xF4];
};

typedef struct SlicerLaunchData_8012D9C8 {
    u16 player; u16 pad;
    void *textures; void *model; u32 weapon;
    s16 kind, stage; f32 multiplier; f32 color[4];
    s32 facing, spin; f32 first[3], second[3];
} SlicerLaunchData_8012D9C8;

extern "C" {
f32 sin_table_lookup(int);
f32 cos_table_lookup(int);
extern const char *lbl_805D41A0;
extern const f32 lbl_805DF630;
extern const f32 lbl_805DF634;
extern const f32 lbl_805DF644;
static const f32 lbl_805DF650 = 5.0f;
extern const f32 lbl_805D8D48;
static const f32 lbl_805DF654 = 12.0f;
void init_slicer_launch_state(void *arg0);
u16 get_entity_id(void *);
s16 TObjPlayer__sub_801D2F4C(s16 *arg0);
s16 get_validated_attack_stage(u8 *arg0);
f32 query_extended_state__10TObjPlayerFv(void *);
void get_weapon_color__11TItemWeaponFPv(f32 *, void *);
void launch_slicer__10TObjPlayerFPv(u8 *weapon);
void *__dt__13TUnk_804ECDC0Fv(void *arg0, s16 arg1);
void fn_80325F7C(void *arg0);

void TBoss5GryphonLightningHorn::render() {  }
void TBoss5GryphonLightningHorn::run_task() { rebuild_lightning_segments(); fn_80325F7C(this); spawn_gryphon_lightning(); }
TBoss5GryphonLightningHorn::~TBoss5GryphonLightningHorn() {}
TBoss5GryphonLightningHorn::TBoss5GryphonLightningHorn(TObject *parent, const Vec *source, s32 direction)
    : TBoss5GryphonLightning(parent, lbl_805DF644, source) {
    m_name = lbl_805D41A0;
    angle = direction;
    velocity.x = lbl_805DF650 * sin_table_lookup(angle);
    velocity.y = lbl_805DF630;
    velocity.z = lbl_805DF650 * cos_table_lookup(angle);
    m_8c = lbl_805DF634;
    m_90 = 4;
}

s32 TBoss8Dragon::spawn_ground_lightning(TObject *parent, const Vec *source, s32 direction) {
    Vec position;
    f32 ground_height;
    u8* collision;
    VecCopy(&position, source);
    collision = (u8 *)csnVecterUnder(&position, 0x16EF);
    if (collision == NULL) {
        position.y = lbl_805D8D48;
    } else {
        ground_height = *(f32*)((s8 *)(*(u8**)((s8 *)collision + 4)) + 4);
        if (ground_height > lbl_805D8D48) {
            position.y = lbl_805D8D48;
        } else {
            position.y = ground_height;
        }
    }
    position.y += lbl_805DF654;
    return (s32)new TBoss5GryphonLightningHorn(parent, &position, direction);
}

extern s32 lbl_804ECDC0[];

void launch_slicer__10TObjPlayerFPv(u8 *weapon) {
    f32 tmp[4];
    SlicerLaunchData_8012D9C8 launch;
    init_slicer_launch_state(&launch);
    launch.player = get_entity_id(*(u8 * *)&((TUnk_804ECDC0 *)weapon)->owner);
    launch.weapon = ((TItem *)weapon)->get_item_id();
    launch.textures = *(void **)((s8 *)weapon + 0x24);
    launch.model = *(void **)((s8 *)weapon + 0x188);
    launch.kind = TObjPlayer__sub_801D2F4C((s16 *)(*(u8 * *)&((TUnk_804ECDC0 *)weapon)->owner + 0x7CC));
    launch.stage = get_validated_attack_stage(*(u8 * *)&((TUnk_804ECDC0 *)weapon)->owner + 0x7CC);
    launch.multiplier = query_extended_state__10TObjPlayerFv(*(u8 * *)&((TUnk_804ECDC0 *)weapon)->owner);
    get_weapon_color__11TItemWeaponFPv(tmp, weapon);
    copy_argb((NJS_ARGB *)launch.color, (NJS_ARGB *)tmp);
    launch.facing = *(s32 *)((s8 *)(*(u8 * *)&((TUnk_804ECDC0 *)weapon)->owner) + 0x60);
    ((TItemWeapon *)weapon)->get_joint_position(0x2, launch.first);
    ((TItemWeapon *)weapon)->get_joint_position(0x1, launch.second);
    TTecSlicer::create((u16*)&launch);
}
typedef char RecoveredGlobal_8012DBF4_lbl_804A5B20_size[sizeof(RecoveredGlobal_8012DBF4_lbl_804A5B20) == 0xF8 ? 1 : -1];

void *__dt__13TUnk_804ECDC0Fv(void *arg0, s16 arg1) {
    if (arg0 != NULL) {
        *(s32 **)((s8 *)arg0 + 0x18) = lbl_804ECDC0;
        __dt__11TItemWeaponFv(arg0, 0);
        if (arg1 > 0) {
            TItem::operator delete(arg0);
        }
    }
    return arg0;
}

}
