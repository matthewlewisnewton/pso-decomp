#include "pso/TItemEffLandHit.h"
#include "pso/object/TObject_80019A50.h"

void TItemEffLandHit::run_task() {
    if (this->m_38) {
        queue_destruction__7TObjectFv(this);
    }
}

TItemEffLandHit::~TItemEffLandHit() {}
