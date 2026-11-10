#include "pso/misc/ParticleFactory.h"
#include "pso/effect/TechniqueChargeEmitter.h"
#include "pso/object/TObject_80019A50.h"
#include "pso/unk/text_80087278.h"
#include "types.h"
#include "pso/misc/TechniqueBoost.h"
#include "pso/player/TObjPlayer.h"
extern u32 dark_technique_charge_effect_ids[];
// The compiler constructs all six TechniqueBoost members before this body.
TechniqueBoostTable::TechniqueBoostTable() {
    clear();
}

void updateDarkTechniqueCharge(TechniqueChargeEmitter* state) {
    ++state->age;
    if(state->age%10==0) {
        for(int i=0;i<3;++i)spawn_particle_effect((const Vec *)(state->position), (s32)(dark_technique_charge_effect_ids[i]));
    }
    if(!((TObjPlayer *)(state->actor))->check_flag_0x80())queue_destruction__7TObjectFv(state);
    else if(state->age>=180)queue_destruction__7TObjectFv(state);
}
