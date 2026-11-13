#define TOBJECT_OUT_OF_LINE_HELPERS
#include "pso/misc/ParticleFactory.h"
#include "pso/TItemEffBringer.h"
#include "pso/TParticleCtrl.h"
#include "pso/system/vector.h"
#include "pso/math/AngleLookup.h"
#include "pso/math/MatrixTransforms.h"
#include "pso/player/TObjPlayer.h"
#include "pso/player/TObjPlayer_80011014.h"
#include "pso/system/MatrixStack.h"

#include "types.h"
#include "dolphin/mtx.h"

extern "C" {
extern const char TItemEffBringer__class_name_string[] = "TItemEffBringer";
const char *TItemEffBringer__class_name = TItemEffBringer__class_name_string;
}

void TItemEffBringer::hook() {
    Vec work = this->m_pos;
    for (int i = 0; i != this->m_particle_count; i++) {
        spawn_particle_effect(&work, 0x9C);
        subtract_vector(&work, &this->m_particle_step);
    }
}

TItemEffBringer::~TItemEffBringer() {
    for (int i = 0; i != this->m_particle_count; i++) {
        TParticleCtrl::release(this->m_particles[i]);
    }
}

#pragma push
#pragma fp_contract on
TItemEffBringer::TItemEffBringer(void *owner, const Vec *src, const Vec *dir, f32 life)
    : TItemShoot(owner, src, dir, life) {
    Vec w;
    Vec out;
    Vec z;
    f32 r;
    f32 n;
    s32 i;
    m_name = TItemEffBringer__class_name;
    push_matrix();
    z.x = z.y = z.z = 0.0f;
    TObjPlayer::invert_matrix_in_place(0);
    transform_point_by_current_matrix(&z.x, &out);
    VecCopy(&w, src);
    subtract_vector(&w, &out);
    pop_matrix();
    r = sin_table_lookup(m_count - (s32)(10430.38043493439 * atan2_float(w.x, w.z)));
    if (r < 0.0f) {
        r *= -1.0f;
    }
    n = 4.0f * r + 1.0f;
    VecCopy(&m_particle_step, &m_dir);
    m_particle_step.x /= n;
    m_particle_step.y /= n;
    m_particle_step.z /= n;
    m_particle_count = (s32)n + 1;
    for (i = 0; i != m_particle_count; i++) {
        m_particles[i] = 0;
    }
    disallow_rendering();
}
#pragma pop

// The weapon-effect factory table carries pointers in 32-bit integer arguments.
void *TItemEffBringer::create(u32 owner, s32 pos, s32 dir, f32 life) {
    if ((0.0f != life) && (owner != 0U)) {
        return new TItemEffBringer((void *)owner, (const Vec *)pos, (const Vec *)dir, life);
    }
    return NULL;
}
