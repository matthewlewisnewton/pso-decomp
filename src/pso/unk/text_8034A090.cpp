#include "types.h"
#include "pso/object/TObject_80019A50.h"
#include "pso/unk/text_8034A090.h"
#include "pso/ui/TAdLoadQuestPrtTxtGC.h"
#include "pso/TParticleCtrl.h"
#include "pso/misc/TNowLoading.h"

struct RecoveredGlobal_8034A5D0_lbl_804EFF80 {
    s32 value;
    u8 remaining[0x8];
};

struct Vec3_8034A090 {
    f32 x;
    f32 y;
    f32 z;
};

struct TAdLoadQuestPrtTxtGC_8034A090 {
    u8 pad0[0x1C];
    s32 count;
    void *particles[32];
    Vec3_8034A090 pos[32];
    s32 state;
    s32 timer;
};

struct T_8034A198 {
    u8 pad0[0x18];
    void *vt;
    s32 count;
    void *objs[32];
    u8 pada0[0x220 - 0xA0];
    s32 slot;
};

extern "C" {
s32 __nw__7TObjectFUl(int);
s32 TAdLoadQuestPrtTxtGC__ct(int, void *, void *);
extern RecoveredGlobal_8034A5D0_lbl_804EFF80 quest_load_prt_txt_by_slot;
extern const f32 lbl_805DFD20;
extern const f32 lbl_805DFD24;
typedef char RecoveredGlobal_8034A5D0_lbl_804EFF80_size[sizeof(RecoveredGlobal_8034A5D0_lbl_804EFF80) == 0xC ? 1 : -1];

void TAdLoadQuestPrtTxtGC::run_task() {
    TAdLoadQuestPrtTxtGC_8034A090 *self = (TAdLoadQuestPrtTxtGC_8034A090 *)this;
    s32 i;
    switch (self->state) {
    case 0:
        self->timer++;
        if (self->timer > 0xF0) {
            self->timer = 0;
        }
        for (i = 0; i < self->count; i++) {
            if (self->timer > i * 0x14 && self->timer < i * 0x14 + 0x28) {
                if (self->particles[i] != NULL) {
                    ((TParticleCtrl *)(self->particles[i]))->clear_active_flag();
                    self->pos[i].x += lbl_805DFD20;
                    ((TParticleCtrl *)self->particles[i])->set_position(&self->pos[i]);
                }
            } else {
                if (self->particles[i] != NULL) {
                    ((TParticleCtrl *)(self->particles[i]))->enable();
                    self->pos[i].x = lbl_805DFD24;
                    ((TParticleCtrl *)self->particles[i])->set_position(&self->pos[i]);
                }
            }
        }
        break;
    case 1:
        break;
    case 2:
        break;
    }
}

}
TAdLoadQuestPrtTxtGC::~TAdLoadQuestPrtTxtGC() {
    s32 i;
    if (((u32 *)&quest_load_prt_txt_by_slot)[((T_8034A198 *)this)->slot] != 0) {
        ((u32 *)&quest_load_prt_txt_by_slot)[((T_8034A198 *)this)->slot] = 0;
    }
    for (i = 0; i < ((T_8034A198 *)this)->count; i++) {
        if (((T_8034A198 *)this)->objs[i] != NULL) {
            queue_destruction__7TObjectFv(((T_8034A198 *)this)->objs[i]);
            ((T_8034A198 *)this)->objs[i] = NULL;
        }
    }
}

s32 get_or_create_prt_txt__14TAdLoadQuestGCFii(s32 arg0, s32 arg1) {
    s32 temp_r30;
    s32 temp_r3;
    s32 var_r0;
    temp_r30 = arg1 * 4;
    if ((u32) *(s32 *)((s8 *)&quest_load_prt_txt_by_slot.value + temp_r30) == 0U) {
        temp_r3 = __nw__7TObjectFUl(0x228);
        var_r0 = temp_r3;
        if (var_r0 != 0) {
            var_r0 = TAdLoadQuestPrtTxtGC__ct((int)temp_r3, (void *)arg0, (void *)arg1);
        }
        *(s32 *)((s8 *)&quest_load_prt_txt_by_slot.value + temp_r30) = var_r0;
    }
    return *(s32 *)((s8 *)&quest_load_prt_txt_by_slot.value + temp_r30);
}
