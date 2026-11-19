#include "pso/effect/particle/ParticleFactory.h"
#include "types.h"
#include "pso/unk/text_80087278.h"
#include "pso/effect/particle/TParticleCtrl.h"
#include "pso/system/task/TObject.h"
struct ParticleEntry { u8 data[0x98]; };

extern "C" {
extern s32 particle_pool_limit;
extern ParticleEntry *particle_global_entry_table;
extern ParticleEntry *particle_area_entry_table;
void *initialize_with_flags__13TParticleCtrlFPCvlllllUs(void *, const void *, void *, s32, s32, s32, s32, s32);

#pragma push
#pragma opt_propagation off
TParticleCtrl *spawn_particle_effect_with_flags(const Vec *pos, s32 id, s32 flags) {
    void *p;
    s32 idx = id;
    if (particle_pool_limit > idx) {
        p = TObject::operator new((u32)(0x78));
        if (p != 0) {
            p = initialize_with_flags__13TParticleCtrlFPCvlllllUs(p, pos, &particle_global_entry_table[idx], 1, 0, 0, 0, flags);
        }
        return (TParticleCtrl *)p;
    }
    if (particle_pool_limit + 0x40 > idx) {
        idx -= 0x200;
        p = TObject::operator new((u32)(0x78));
        if (p != 0) {
            p = initialize_with_flags__13TParticleCtrlFPCvlllllUs(p, pos, &particle_area_entry_table[idx], 1, 0, 0, 0, flags);
        }
        return (TParticleCtrl *)p;
    }
    return 0;
}
#pragma pop

TParticleCtrl *spawn_particle_effect(const Vec *pos, s32 id) {
    TParticleCtrl *particle;
    if (particle_pool_limit > id) {
        particle = (TParticleCtrl *)TObject::operator new(0x78);
        if (particle != 0) {
            particle = particle->initialize(pos, (s32)&particle_global_entry_table[id], 1, 0, 0, 0);
        }
        return particle;
    }
    if (particle_pool_limit + 0x40 > id) {
        s32 idx = id - 0x200;
        particle = (TParticleCtrl *)TObject::operator new(0x78);
        if (particle != 0) {
            particle = particle->initialize(pos, (s32)&particle_area_entry_table[idx], 1, 0, 0, 0);
        }
        return particle;
    }
    return 0;
}

TParticleCtrl *spawn_continuous_particle_effect_with_flags(void *parent, s32 idx, s32 flags) {
    void *p;
    if (particle_pool_limit > idx) {
        p = TObject::operator new(0x78);
        if (p != 0) {
            p = initialize_with_flags__13TParticleCtrlFPCvlllllUs(p, parent, &particle_global_entry_table[idx], 0, 0, 0, 0, flags);
        }
        return (TParticleCtrl *)p;
    } else if (particle_pool_limit + 0x40 > idx) {
        s32 j = idx - 0x200;
        p = TObject::operator new(0x78);
        if (p != 0) {
            p = initialize_with_flags__13TParticleCtrlFPCvlllllUs(p, parent, &particle_area_entry_table[j], 0, 0, 0, 0, flags);
        }
        return (TParticleCtrl *)p;
    } else {
        return 0;
    }
}

}
