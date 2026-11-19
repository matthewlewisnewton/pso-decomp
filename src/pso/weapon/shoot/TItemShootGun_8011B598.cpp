#include "pso/effect/particle/ParticleFactory.h"
#include "pso/weapon/shoot/TItemShootGun.h"
#include "pso/weapon/shoot/TItemShoot.h"
#include "pso/effect/particle/TParticleCtrl.h"

u32 TItemShootGun::create(s32 owner, s32 pos, s32 endpoint, f32 life) {
    TItemShootGun* result;

    spawn_particle_effect((const Vec *)pos, 0x1BF);
    result = new TItemShootGun((void *)owner, (const Vec *)pos,
                              (const Vec *)endpoint, life);
    if (result != 0) {
        result->set_texture_id(4);
    }
    return (u32) result;
}
