#define TOBJECT_OUT_OF_LINE_HELPERS
#include "pso/effect/TDPBShower.h"
#include "pso/boss/TBoss4Type2_800874F4.h"
#include "pso/enemy/TObjEneDD.h"
#include "pso/system/vector.h"
#include "pso/TParticleCtrl.h"

extern "C" {
extern const char TDPBShower__class_name_string[] = "TDPBShower";
const char *TDPBShower__class_name = TDPBShower__class_name_string;
}

void TDPBShower::run_task() {
    if (TObjEneDD::query_teammate_state() == 0) {
        m_position.y += -60.0f;
        if (m_emitter != NULL) {
            m_emitter->set_position(&m_position);
        }
        if (--m_countdown < 0) {
            queue_destruction();
        }
    }
}

TDPBShower::~TDPBShower() {
    if (m_emitter != NULL) {
        TParticleCtrl::release(m_emitter);
    }
}

TDPBShower::TDPBShower(TObject *parent, const Vec *position) : TObject(parent) {
    m_name = TDPBShower__class_name;
    m_countdown = 5;
    VecCopy(&m_position, position);
    m_position.y += 300.0f;
    TParticleCtrl *emitter = create_particle_emitter(&m_position, 0x134);
    m_emitter = emitter;
    if (emitter != NULL) {
        m_emitter->set_flags(0x40);
    }
}

void *create_TDPBShower(void *parent, void *position) {
    return new TDPBShower(static_cast<TObject *>(parent), static_cast<const Vec *>(position));
}
