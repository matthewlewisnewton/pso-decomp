#define TOBJECT_OUT_OF_LINE_HELPERS
#include "pso/boss/TBoss8DragonEffBreath.h"
#include "pso/boss/TBoss8Dragon.h"
#include "pso/boss/TBoss8Dragon_800BC53C.h"
#include "pso/system/vector.h"
#include "pso/system/MatrixOps.h"
#include "pso/object/TObjControl.h"

extern "C" {
extern const char lbl_80474B50[] = "TBoss8DragonEffBreath";
const char *TBoss8DragonEffBreath__name = lbl_80474B50;
}

void TBoss8DragonEffBreath::render() {}

void TBoss8DragonEffBreath::run_task() {
    vec3_add_to(&position, &velocity);
    f32 height = position.y;
    if (height < -10.0f) {
        queue_destruction();
        return;
    }
    if (height < 30.0f) {
        void *dragon = get_enemy_entity(entity_id);
        if (dragon != NULL) {
            TBoss8Dragon::setup_breath_instance(dragon, (int)&position, m_34, (int)attack_history);
        }
    }
}

TBoss8DragonEffBreath::~TBoss8DragonEffBreath() {
    __dt__17AreaAttackHistoryFv((s32)attack_history, 1);
    attack_history = NULL;
}

TBoss8DragonEffBreath::TBoss8DragonEffBreath(TObject *parent, void *p, void *v, s32 a, s16 b)
    : TObject(parent) {
    m_name = TBoss8DragonEffBreath__name;
    VecCopy(&position, (const Vec *)p);
    VecCopy(&velocity, (const Vec *)v);
    velocity.x *= 5.0f;
    velocity.y *= 5.0f;
    velocity.z *= 5.0f;
    m_34 = a;
    entity_id = b;
    void *history = ::operator new(0x10);
    if (history != NULL) {
        history = __ct__17AreaAttackHistoryFl((u8 *)history, 4);
    }
    attack_history = history;
}
