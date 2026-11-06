#include "types.h"
#include "pso/player/TObjPlayer_80121D88.h"
#include "pso/item/TItemShootParticle.h"
#include "pso/item/TUnk_804A0CB8.h"
#include "pso/TObject.h"

extern "C" {

u32 spawn_shoot_particle__10TObjPlayerFUlllf(void *, s32, s32, f32);
u32 create_shoot_model__10TObjPlayerFUiiif();

void TUnk_804A0CB8::update_weapon() {
    s32 *temp_r3;
    s32 temp_r4_2;
    void *temp_r4;

    temp_r4 = *(void **)((s8 *)this + 0xF4);
    if (temp_r4 != NULL) {
        temp_r3 = *(s32 **)((s8 *)temp_r4 + 0x2C);
        temp_r4_2 = *temp_r3;
        if ((s32) *(s32 *)&this->unk_1F8 == 1) {
            if (temp_r4_2 & 8) {
                *temp_r3 = temp_r4_2 & 0xFFFFFFF7;
            }
        } else if (!(temp_r4_2 & 8)) {
            *temp_r3 = temp_r4_2 | 8;
        }
    }
}
}

u32 belra_cannon_create_extra_shot(void *player, s32 arg1, s32 arg2, f32 farg0) {
    s32 temp_r3;
    u32 temp_r31;
    u32 temp_r30;
    void *temp_r5;

    temp_r31 = create_shoot_model__10TObjPlayerFUiiif();
    temp_r30 = spawn_shoot_particle__10TObjPlayerFUlllf(player, arg1, arg2, farg0);
    if ((temp_r31 != 0U) && (temp_r30 != 0U)) {
        temp_r5 = *(void **)((s8 *)player + 0x188);
        if (temp_r5 != NULL) {
            temp_r3 = *(s32 *)((s8 *)temp_r5 + 0);
            if ((u32) (temp_r3 & 7) == 7) {
                *(s32 *)((s8 *)temp_r5 + 0) = (s32) (temp_r3 & 0xFFFFFFFD);
                *(s32 *)((s8 *)temp_r5 + 0x14) = -0x4000;
                *(s32 *)((s8 *)temp_r5 + 0x1C) = 0x8000;
            }
        }
        ((TItemShootParticle *)temp_r30)->spawn_slot_emitter(0xDD, 0);
        ((TObject *)temp_r30)->set_parent((TObject *)temp_r31);
    }
    return temp_r31;
}
