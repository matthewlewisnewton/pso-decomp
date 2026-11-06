#include "types.h"
#include "pso/player/TUnk_804A3D20.h"
#include "pso/player/TObjPlayer.h"

extern "C" {

void construct_srank_weapon(void *);

extern s32 lbl_804A3D20[];
extern s32 spawn_weapon_impact_effect[];

void *TUnk_804A3D20::setup_shoot_model_callback() {
    construct_srank_weapon(this);
    *(s32 **)((s8 *)this + 0x18) = lbl_804A3D20;
    (*(s32 * *)((u8 *)this + 0x1EC)) = spawn_weapon_impact_effect;
    return this;
}

}
