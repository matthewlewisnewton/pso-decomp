#include "types.h"
#include "pso/object/TObjEZBoneRotPlayer_800FE834.h"
#include "pso/TObjEZBoneRotPlayer.h"
#include "pso/TObjEZBoneRotBase.h"

struct EZBoneRotKey {
    s32 bone;
    f32 axis[3];
};

struct EZBoneRotDesc {
    s32 period;
    u8 unk_04[0x4];
    s32 phase_step;
    f32 amplitude_scale;
    EZBoneRotKey *keys;
};

struct EZBoneRotState {
    u8 pad0[0x18];
    void **vtable;
    void *root;
    EZBoneRotDesc *desc;
    u8 pad24[0x84 - 0x24];
    s32 phase;
    u8 pad88[0x94 - 0x88];
    f32 scale;
};

struct RecoveredGlobal_800FE930___vt__19TObjEZBoneRotPlayer {
    s32 value;
    u8 remaining[0x14];
};

extern "C" {
TObjEZBoneRotBase *TObjEZBoneRotBase__ct(TObjEZBoneRotBase *self, TObject *parent, void *root, EZBoneRotDesc *desc);
extern RecoveredGlobal_800FE930___vt__19TObjEZBoneRotPlayer __vt__19TObjEZBoneRotPlayer;
extern s32 TObjEZBoneRotPlayer__name;
void *__nw__7TObjectFUl(int);

void TObjEZBoneRotPlayer::run_task() {
    f32 temp_f1;
    s32 temp_r4;
    void *temp_r6;

    temp_r6 = *(void **)((s8 *)this + 0x98);
    temp_r4 = *(s32 *)((s8 *)temp_r6 + 0x320) & 0xDF7FF;
    if (temp_r4 & 0x99003) {
        *(f32 *)((s8 *)this + 0x94) += -0.016666668f;
    } else if ((temp_r4 & 0x1E0) || ((s32) *(s32 *)((s8 *)this + 0x9C) != (s32) *(s32 *)((s8 *)temp_r6 + 0x60))) {
        *(f32 *)((s8 *)this + 0x94) += 0.13333334f;
    } else if (temp_r4 & 0x4661C) {
        *(f32 *)((s8 *)this + 0x94) += 0.016666668f;
    } else {
        *(f32 *)((s8 *)this + 0x94) += -0.016666668f;
    }
    temp_f1 = *(f32 *)((s8 *)this + 0x94);
    if (temp_f1 < 0.0f) {
        *(f32 *)((s8 *)this + 0x94) = (f32) 0.0f;
    } else if (temp_f1 > 1.0f) {
        *(f32 *)((s8 *)this + 0x94) = (f32) 1.0f;
    }
    advance_bone_rotation();
    *(s32 *)((s8 *)this + 0x9C) = (s32) *(s32 *)((s8 *)(*(void **)((s8 *)this + 0x98)) + 0x60);
}
typedef char RecoveredGlobal_800FE930___vt__19TObjEZBoneRotPlayer_size[sizeof(RecoveredGlobal_800FE930___vt__19TObjEZBoneRotPlayer) == 0x18 ? 1 : -1];
u8 *__ct__19TObjEZBoneRotPlayerFv(u8 *arg0, s32 arg1, u8 *arg2, void * _w3) {
    TObjEZBoneRotBase__ct((TObjEZBoneRotBase *)arg0, (TObject *)arg1, arg2, (EZBoneRotDesc *)_w3);
    *(s32 **)((s8 *)arg0 + 0x18) = &__vt__19TObjEZBoneRotPlayer.value;
    *(s32 *)((s8 *)arg0 + 0) = (s32) TObjEZBoneRotPlayer__name;
    *(s32 *)((s8 *)arg0 + 0x98) = arg1;
    *(s32 *)((s8 *)arg0 + 0x9C) = (s32) *(s32 *)((s8 *)(*(s32 *)((s8 *)arg0 + 0x98)) + 0x60);
    return arg0;
}
void *TObjEZBoneRotPlayer::create(void *arg0, void *arg1, void *arg2) {
    void *o;
    o = __nw__7TObjectFUl(0xA0);
    if (o != NULL) {
        o = ((void *)__ct__19TObjEZBoneRotPlayerFv((u8 *)o, (s32)arg0, (u8 *)arg1, (void *)arg2));
    }
    return o;
}
void TObjEZBoneRotPlayer::advance_bone_rotation() {
    start_bone_rotation_sequence(*(s32 *)((s8 *)this + 0x84));
    if (*(f32 *)((s8 *)this + 0x94) > 0.0f) {
        *(s32 *)((s8 *)this + 0x84) = (s32) (*(s32 *)((s8 *)this + 0x84) + *(s32 *)((s8 *)(*(void **)((s8 *)this + 0x20)) + 4));
    }
}

}

extern "C" {
f32 sin_table_lookup(s32);

void TObjEZBoneRotPlayer::calc_bone_offsets_recursive(void *arg1, s32 arg2, s32 arg3) {
    s32 k;
    f32 t;
    do {
        k = *(s32 *)((s8 *)(*(s32 **)((s8 *)this + 0x8C)) + 0);
        if (k < 0) {
            return;
        }
        if (k == *(s32 *)((s8 *)this + 0x88)) {
            t = (f32) arg3 * sin_table_lookup(arg2);
            *(s32 *)((s8 *)arg1 + 0x14) = *(s32 *)((s8 *)(*(u8 **)((s8 *)this + 0x90)) + 0) + (s32) (*(f32 *)((s8 *)(*(u8 **)((s8 *)this + 0x8C)) + 4) * t);
            *(s32 *)((s8 *)arg1 + 0x18) = *(s32 *)((s8 *)(*(u8 **)((s8 *)this + 0x90)) + 4) + (s32) (*(f32 *)((s8 *)(*(u8 **)((s8 *)this + 0x8C)) + 8) * t);
            *(s32 *)((s8 *)arg1 + 0x1C) = *(s32 *)((s8 *)(*(u8 **)((s8 *)this + 0x90)) + 8) + (s32) (*(f32 *)((s8 *)(*(u8 **)((s8 *)this + 0x8C)) + 0xC) * t);
            *(u8 **)((s8 *)this + 0x90) = *(u8 **)((s8 *)this + 0x90) + 0xC;
            *(u8 **)((s8 *)this + 0x8C) = *(u8 **)((s8 *)this + 0x8C) + 0x10;
            if (*(s32 *)((s8 *)(*(s32 **)((s8 *)this + 0x8C)) + 0) < 0) {
                return;
            }
        }
        *(s32 *)((s8 *)this + 0x88) = *(s32 *)((s8 *)this + 0x88) + 1;
        if (*(void **)((s8 *)arg1 + 0x2C) != NULL) {
            calc_bone_offsets_recursive(*(void **)((s8 *)arg1 + 0x2C), arg2 + *(s32 *)((s8 *)(*(u8 **)((s8 *)this + 0x20)) + 8), (s32) (*(f32 *)((s8 *)(*(u8 **)((s8 *)this + 0x20)) + 0xC) * (f32) arg3));
        }
        arg1 = *(void **)((s8 *)arg1 + 0x30);
    } while (arg1 != NULL);
}

void TObjEZBoneRotPlayer::start_bone_rotation_sequence(s32 arg1) {
    *(s32 *)((s8 *)((u8 *)this) + 0x88) = 0;
    *(s32 *)((s8 *)((u8 *)this) + 0x8C) = (s32) *(s32 *)((s8 *)(*(u8 **)((s8 *)((u8 *)this) + 0x20)) + 0x10);
    *(s32 *)((s8 *)((u8 *)this) + 0x90) = (s32) (((u8 *)this) + 0x24);
    calc_bone_offsets_recursive((void *)(*(u8 **)((s8 *)((u8 *)this) + 0x1C)), arg1, (s32)((s32) ((f32) *(s32 *)((s8 *)(*(u8 **)((s8 *)((u8 *)this) + 0x20)) + 0) * *(f32 *)((s8 *)((u8 *)this) + 0x94))));
}

void TObjEZBoneRotBase::sub_800FEC40(u8 *arg1) {
    s32 temp_r3;
    u8 *temp_r4;
    u8 *var_r31;
    var_r31 = arg1;
loop_1:
    temp_r3 = *(s32 *)((s8 *)(*(s32 **)((s8 *)((u8 *)this) + 0x8C)) + 0);
    if (temp_r3 >= 0) {
        if (temp_r3 == (s32) *(s32 *)((s8 *)((u8 *)this) + 0x88)) {
            *(s32 *)((s8 *)var_r31 + 0) = (s32) (*(s32 *)((s8 *)var_r31 + 0) & 0xFFFFFFFD);
            *(s32 *)((s8 *)(*(u8 **)((s8 *)((u8 *)this) + 0x90)) + 0) = (s32) *(s32 *)((s8 *)var_r31 + 0x14);
            *(s32 *)((s8 *)(*(u8 **)((s8 *)((u8 *)this) + 0x90)) + 4) = (s32) *(s32 *)((s8 *)var_r31 + 0x18);
            *(s32 *)((s8 *)(*(u8 **)((s8 *)((u8 *)this) + 0x90)) + 8) = (s32) *(s32 *)((s8 *)var_r31 + 0x1C);
            *(u8 **)((s8 *)((u8 *)this) + 0x90) = (unsigned char *) ((void *) ((u8 *)(*(u8 **)((s8 *)((u8 *)this) + 0x90)) + 0xC));
            *(s32 **)((s8 *)((u8 *)this) + 0x8C) = (s32 *) ((u8 *)(*(s32 **)((s8 *)((u8 *)this) + 0x8C)) + 0x10);
            if ((s32) *(s32 *)((s8 *)(*(s32 **)((s8 *)((u8 *)this) + 0x8C)) + 0) >= 0) {
                goto block_4;
            }
        } else {
block_4:
            *(s32 *)((s8 *)((u8 *)this) + 0x88) = (s32) (*(s32 *)((s8 *)((u8 *)this) + 0x88) + 1);
            temp_r4 = (u8 *)(*(u8 **)((s8 *)var_r31 + 0x2C));
            if (temp_r4 != NULL) {
                sub_800FEC40(temp_r4);
            }
            var_r31 = (u8 *)(*(u8 **)((s8 *)var_r31 + 0x30));
            if (var_r31 != NULL) {
                goto loop_1;
            }
        }
    }
}

void TObjEZBoneRotBase::sub_800FED0C() {
    *(s32 *)((s8 *)((u8 *)this) + 0x88) = 0;
    *(s32 *)((s8 *)((u8 *)this) + 0x8C) = (s32) *(s32 *)((s8 *)(*(u8 **)((s8 *)((u8 *)this) + 0x20)) + 0x10);
    *(s32 *)((s8 *)((u8 *)this) + 0x90) = (s32) (((u8 *)this) + 0x24);
    sub_800FEC40((u8 *)(*(u8 **)((s8 *)((u8 *)this) + 0x1C)));
}

}

TObjEZBoneRotBase::~TObjEZBoneRotBase() {}

extern "C" {
void __ct__7TObjectFP7TObject(TObject *self, TObject *parent);
extern void *__vt__17TObjEZBoneRotBase[];
extern const char *lbl_805D2B48;

TObjEZBoneRotBase *TObjEZBoneRotBase__ct(TObjEZBoneRotBase *self, TObject *parent, void *root, EZBoneRotDesc *desc) {
    EZBoneRotState *state = (EZBoneRotState *)self;
    TObjEZBoneRotBase *base;
    EZBoneRotKey *key;

    __ct__7TObjectFP7TObject(self, parent);
    base = (TObjEZBoneRotBase *)(TObject *)self;
    state->vtable = __vt__17TObjEZBoneRotBase;
    self->m_name = lbl_805D2B48;
    state->root = root;
    state->desc = desc;
    key = state->desc->keys;
    while (key->bone >= 0) {
        key++;
    }
    base->sub_800FED0C();
    state->phase = 0;
    state->scale = 0.0f;
    return self;
}
}
