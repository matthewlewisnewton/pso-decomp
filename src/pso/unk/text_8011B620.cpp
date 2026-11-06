#include "pso/misc/ParticleFactory.h"
#include "types.h"
#include "pso/unk/text_80087278.h"
#include "pso/unk/text_8011B620.h"

extern "C" {
s32 __ct__13TItemShootGunFPvPC3VecPC3Vecf(int, void *, void *, void *, f32);
s32 __nw__7TObjectFUl(int);
s32 create_gun_shot(s32 arg0, s32 arg1, s32 arg2, f32 farg0) {
    s32 temp_r3;
    s32 var_r0;
    spawn_particle_effect((const Vec *)(arg1), 9);
    temp_r3 = __nw__7TObjectFUl(0x74);
    var_r0 = temp_r3;
    if (var_r0 != 0) {
        var_r0 = __ct__13TItemShootGunFPvPC3VecPC3Vecf((int)temp_r3, (void *)arg0, (void *)arg1, (void *)arg2, (f32)farg0);
    }
    return var_r0;
}

}
