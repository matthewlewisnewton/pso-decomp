#include "types.h"
#include "pso/unk/TUnk_804C3F48.h"


struct RecoveredGlobal_801C5380_lbl_804C3F48 {
    s32 value;
    u8 remaining[0x14];
};

struct RecoveredGlobal_801C5320_lbl_804C3F48 {
    s32 value;
    u8 remaining[0x14];
};

struct Ply_801C51D4 { u8 pad[0x30]; u32 flags; u8 pad34[4]; f32 pos[3]; };

struct Self_801C51D4 { u8 pad[0x1C]; s32 life; s32 timer; Ply_801C51D4 *owner; };

extern "C" {
s32 update_battle_controller__10TObjPlayerFv();
s32 __ct__7TObjectFP7TObject(void *, void *);
extern RecoveredGlobal_801C5380_lbl_804C3F48 lbl_804C3F48;
u8 *fn_801C5380(u8 *arg0, s32 arg1);
u8 * __dt__7TObjectFv(void *, s16);
void __dl__7TObjectFPv(s32);
extern s32 ad_single_ply_chr_select_instance;
u8 *__dt__13TUnk_804C3F48Fv(u8 *arg0, s16 arg1);
f32 newton_sqrtf(f32);
void queue_destruction__7TObjectFv(void *);
f32 xz_distance_squared(void *, void *);
void *get_player_by_client_id(s32 i);
void update_technique_slot__10TTecRaFoieFl(void *, s32, s32);
void *play_sound_effect(s32, s32, s32, s32, f32);
typedef char RecoveredGlobal_801C5380_lbl_804C3F48_size[sizeof(RecoveredGlobal_801C5380_lbl_804C3F48) == 0x18 ? 1 : -1];

typedef char RecoveredGlobal_801C5320_lbl_804C3F48_size[sizeof(RecoveredGlobal_801C5320_lbl_804C3F48) == 0x18 ? 1 : -1];

#pragma push
#pragma fp_contract on
void TUnk_804C3F48::run_task() {
    Self_801C51D4 *self = (Self_801C51D4 *)this;
    s32 i;
    Ply_801C51D4 *p;
    f32 min;
    f32 d;
    f32 f;
    if (--self->life <= 0) {
        queue_destruction__7TObjectFv(self);
        return;
    }
    if (self->life > 0x5A) {
        if (--self->timer <= 0) {
            min = 2250000.0f;
            for (i = 0; i < 4; i++) {
                p = (Ply_801C51D4 *)get_player_by_client_id(i);
                if (p != NULL && p != self->owner && !(p->flags & 0x800)) {
                    d = xz_distance_squared(self->owner->pos, p->pos);
                    min = min < d ? min : d;
                }
            }
            f = newton_sqrtf(min) > 200.0f ? newton_sqrtf(min) : 200.0f;
            f -= 200.0f;
            min = 1.0f - 0.00076923077f * f;
            update_technique_slot__10TTecRaFoieFl(play_sound_effect(0x23230, 0, 0, 0, f), 256.0f * min, 0);
            self->timer = (s32)(-53.0f * min) + 0x3C;
        }
    }
}
#pragma pop

u8 *__dt__13TUnk_804C3F48Fv(u8 *arg0, s16 arg1) {
    if (arg0 != NULL) {
        *(s32 **)((s8 *)arg0 + 0x18) = &(*(RecoveredGlobal_801C5320_lbl_804C3F48 *)&lbl_804C3F48).value;
        ad_single_ply_chr_select_instance = 0;
        __dt__7TObjectFv(arg0, 0);
        if (arg1 > 0) {
            __dl__7TObjectFPv((s32) arg0);
        }
    }
    return arg0;
}

u8 *fn_801C5380(u8 *arg0, s32 arg1) {
    __ct__7TObjectFP7TObject((void *)arg0, (void *)arg1);
    *(s32 **)((s8 *)arg0 + 0x18) = &lbl_804C3F48.value;
    *(s32 *)((s8 *)arg0 + 0x1C) = 0x3DE;
    ((TUnk_804C3F48 *)arg0)->m_20 = 0x1E;
    *(s32 *)((s8 *)arg0 + 0x24) = update_battle_controller__10TObjPlayerFv();
    return arg0;
}

}
