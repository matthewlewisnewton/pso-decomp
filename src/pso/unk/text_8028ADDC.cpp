#include "types.h"
#include "pso/boss/TObjBoss5PillarDemo.h"
#include "pso/system/ModelDrawContext.h"
#include "pso/unk/text_8028ADDC.h"
#include "pso/misc/TNowLoading.h"
#include "pso/TParticleCtrl.h"

struct O_8028AE1C { u8 pad[0x1c]; s32 count; void **a; void **b; };

extern "C" {
extern s32 boss5_pillar_demo_index;
extern void *boss5_pillar_demo_ptr;
extern u8 lbl_80450CD0[];
void fn_8028AE1C(O_8028AE1C *arg0);
void fn_8028ADDC(void *p) {
    if (p) {
        boss5_pillar_demo_index = 0;
        boss5_pillar_demo_ptr = p;
        set_model_node_callback((s32)TObjBoss5PillarDemo__sub_8028AD88);
    }
}
void fn_8028AE1C(O_8028AE1C *arg0) {
    s32 i;
    for (i = 0; i < arg0->count; i++) {
        if (arg0->a[i] != 0) {
            ((TParticleCtrl *)arg0->a[i])->set_position(lbl_80450CD0);
        }
        if (arg0->b[i] != 0) {
            ((TParticleCtrl *)arg0->b[i])->set_position(lbl_80450CD0);
        }
    }
}

}
