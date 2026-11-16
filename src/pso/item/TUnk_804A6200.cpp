#include "pso/math/ClampedStep.h"
#include "pso/system/SoundEffect.h"
#include "types.h"
#include "pso/item/TUnk_804A6200.h"
#include "pso/unk/text_8012F0F8.h"
#include "pso/item/TItemEffOrgaFlowShot.h"
#include "pso/item/TItemEquipVariant_80120CF8.h"
#include "pso/item/TItemEquipVariant_8012F1F4.h"
#include "pso/player/TObjPlayer.h"
#include "pso/item/TItem.h"

extern "C" {

#ifdef __MWERKS__
#pragma push
#pragma dont_inline off
#pragma inline_depth(1)
#endif
void TUnk_804A6200::update_idle() {
    if (animation.update_idle() == 1) {
        play_sound_effect(0x4001AA24, (const Vec *)((*(s32 *)((s8 *)((u8 *)this) + 0xF0) + 0x38)), 0, 0);
    }
}
#ifdef __MWERKS__
#pragma pop
#endif


}

#ifdef __MWERKS__
#pragma push
#pragma dont_inline off
#pragma inline_depth(1)
#endif
void TUnk_804A6200::update_attack() {
    animation.update_attack();
}
#ifdef __MWERKS__
#pragma pop
#endif


extern s32 lbl_804A6200[];

void *__dt__13TUnk_804A6200Fv(void *arg0, s16 arg1) {
    if (arg0 != NULL) {
        *(s32 **)((s8 *)arg0 + 0x18) = lbl_804A6200;
        __dt__11TItemWeaponFv(arg0, 0);
        if (arg1 > 0) {
            TItem::operator delete(arg0);
        }
    }
    return arg0;
}

extern "C" {

int __ct__11TItemWeaponFP7TObjectPUc(void);

void*TUnk_804A6200::set_mode_vector() { __ct__11TItemWeaponFP7TObjectPUc(); *(int*)((char*)this + 0x18) = (int)lbl_804A6200; animation.third = 1.0f; animation.second = 1.0f; animation.first = 1.0f; return this; }

}
