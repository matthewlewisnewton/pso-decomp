#define TOBJECT_OUT_OF_LINE_HELPERS
#include "pso/boss/derolle/TObjBoss2Dust.h"
#include "pso/system/vector.h"

#include "types.h"
#include "pso/system/task/TObject.h"

struct RecoveredGlobal_8003AA9C___vt__13TObjBoss2Dust {
    s32 value;
    u8 remaining[0x14];
};

extern "C" {
s32 TObjBoss2DustCtrl__sub_8003AB5C();
s32 __ct__7TObjectFP7TObject(void *, void *);
extern RecoveredGlobal_8003AA9C___vt__13TObjBoss2Dust __vt__13TObjBoss2Dust;
extern s32 TObjBoss2Dust__name;

extern const f32 boss2_raft_step;

void TObjBoss2Dust::run_task() {
    position.z -= boss2_raft_step;
    ticks++;
    if (ticks >= 90) {
        queue_destruction();
    }
}
typedef char RecoveredGlobal_8003AA9C___vt__13TObjBoss2Dust_size[sizeof(RecoveredGlobal_8003AA9C___vt__13TObjBoss2Dust) == 0x18 ? 1 : -1];
TObjBoss2Dust::~TObjBoss2Dust() {}
u8 *__ct__13TObjBoss2DustFv(u8 *object, s32 arg1, s32 arg2) {
    __ct__7TObjectFP7TObject((void *)object, (void *)arg1);
    *(s32 **)((s8 *)object + 0x18) = &__vt__13TObjBoss2Dust.value;
    *(s32 *)((s8 *)object + 0) = (s32) TObjBoss2Dust__name;
    TObjBoss2Dust *dust = (TObjBoss2Dust *)object;
    VecCopy(&dust->position, (const Vec *)arg2);
    dust->ticks = 0;
    dust->strip_slot = TObjBoss2DustCtrl__sub_8003AB5C();
    return object;
}

}

__declspec(section ".sdata2") const f32 boss2_raft_step = 9.259259f;
