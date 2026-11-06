#include "types.h"
#include "pso/item/TItemShootParticle.h"
#include "pso/player/TObjPlayer.h"
#include "pso/TObject.h"

extern "C" {

u32 spawn_shoot_particle__10TObjPlayerFUlllf(s32, s32, s32, f32);
u32 TObjPlayer__sub_80128BD4(u32, s32, s32, s32, f32);
u32 __nw__7TObjectFUl(s32);

u32 TObjPlayer::spawn_shot_effect(s32 owner, s32 arg1, s32 arg2, f32 farg0) {
    u32 var_r31;
    u32 temp_r30;

    var_r31 = 0U;
    if (owner != 0) {
        var_r31 = __nw__7TObjectFUl(0x6C);
        if (var_r31 != 0U) {
            var_r31 = TObjPlayer__sub_80128BD4(var_r31, owner, arg1, arg2, farg0);
        }
        temp_r30 = spawn_shoot_particle__10TObjPlayerFUlllf(owner, arg1, arg2, farg0);
        if ((var_r31 != 0U) && (temp_r30 != 0U)) {
            ((TItemShootParticle *)temp_r30)->spawn_slot_emitter(0x1BB, 0);
            ((TObject *)temp_r30)->set_parent((TObject *)var_r31);
        }
    }
    return var_r31;
}

}
