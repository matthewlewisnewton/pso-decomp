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
RecoveredGlobal_8034A5D0_lbl_804EFF80 quest_load_prt_txt_by_slot = {0, {0}};
static const f32 lbl_805DFD20 = 15.6f;
static const f32 lbl_805DFD24 = 0.0f;
static const f32 lbl_805DFD28 = 8.0f;
static const f32 lbl_805DFD2C = 72.0f;
static const f32 lbl_805DFD30 = 16.0f;
static const f32 lbl_805DFD34 = 0.002020202f;
static const f32 lbl_805DFD38 = 462.0f;
static const f32 lbl_805DFD3C = 50.0f;
static const f32 lbl_805DFD40 = 445.0f;
static const f32 lbl_805DFD44 = 35.0f;
static const f32 lbl_805DFD48 = 0.0022222223f;
static const f32 lbl_805DFD4C = 99.0f;
static const f32 lbl_805DFD50 = 40.0f;
static const f32 lbl_805DFD54 = 555.0f;
extern const f32 lbl_805DFD58;
// Points at the "TAdLoadQuestPrtTxtGC" class-name string.
extern const char *lbl_805D4308;
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

// Lays the loading-text particles out for this slot: a column (0), two rows (1) or a 4x8 grid (2).
// From upstream 9575dbb7c (zeroz41/pso-decomp #180). The fused multiply-adds need the unit's
// -fp_contract on; the other functions in this file do not.
TAdLoadQuestPrtTxtGC::TAdLoadQuestPrtTxtGC(TObject *parent, s32 slot) : TObject(parent) {
    s32 i;
    s32 j;
    m_name = lbl_805D4308;
    this->slot = slot;
    m_224 = 0;
    for (i = 0; i < 32; i++) {
        particles[i] = NULL;
    }
    switch (this->slot) {
    case 0:
        particle_count = 22;
        for (i = 0; i < particle_count; i++) {
            particle_pos[i].x = lbl_805DFD28;
            particle_pos[i].y = lbl_805DFD30 * i + lbl_805DFD2C;
            particle_pos[i].z = lbl_805DFD34;
            particles[i] = (TParticleCtrl *)create_particle(&particle_pos[i], 15, 1);
            if (particles[i] != NULL) {
                particles[i]->set_flags(0xC0);
                particles[i]->enable();
            }
        }
        break;
    case 1:
        particle_count = 19;
        for (i = 0; i < particle_count; i++) {
            f32 x = i > 9 ? lbl_805DFD38 : lbl_805DFD3C;
            f32 y = i > 9 ? lbl_805DFD40 : lbl_805DFD44;
            s32 column = i > 9 ? i - 9 : i;
            particle_pos[i].x = lbl_805DFD30 * column + x;
            particle_pos[i].y = y;
            particle_pos[i].z = lbl_805DFD48;
            particles[i] = (TParticleCtrl *)create_particle(&particle_pos[i], 8, 1);
            if (particles[i] != NULL) {
                particles[i]->set_flags(0xC0);
            }
        }
        break;
    case 2:
        particle_count = 32;
        for (i = 0; i < 8; i++) {
            f32 y = lbl_805DFD50 * i + lbl_805DFD4C;
            for (j = 0; j < 4; j++) {
                s32 n = i * 4 + j;
                particle_pos[n].x = lbl_805DFD30 * j + lbl_805DFD54;
                particle_pos[n].y = y;
                particle_pos[n].z = lbl_805DFD58;
                particles[n] = (TParticleCtrl *)create_particle(&particle_pos[n], 8, 1);
                // The original tests particles[i] here, not the particle just created.
                if (particles[i] != NULL) {
                    particles[i]->set_flags(0xC0);
                }
            }
        }
        break;
    }
}

// TObject::operator new is a different allocator, and -inline off will not
// inline a placement operator new, so this calls the real constructor on the
// block __nw already returned.
extern "C" s32 __ct__20TAdLoadQuestPrtTxtGCFP7TObjectl(TAdLoadQuestPrtTxtGC *self, TObject *parent, s32 slot);

s32 get_or_create_prt_txt__14TAdLoadQuestGCFii(s32 arg0, s32 arg1) {
    s32 temp_r30;
    s32 temp_r3;
    s32 var_r0;
    temp_r30 = arg1 * 4;
    if ((u32) *(s32 *)((s8 *)&quest_load_prt_txt_by_slot.value + temp_r30) == 0U) {
        temp_r3 = __nw__7TObjectFUl(0x228);
        var_r0 = temp_r3;
        if (var_r0 != 0) {
            var_r0 = __ct__20TAdLoadQuestPrtTxtGCFP7TObjectl((TAdLoadQuestPrtTxtGC *)temp_r3, (TObject *)arg0, arg1);
        }
        *(s32 *)((s8 *)&quest_load_prt_txt_by_slot.value + temp_r30) = var_r0;
    }
    return *(s32 *)((s8 *)&quest_load_prt_txt_by_slot.value + temp_r30);
}
