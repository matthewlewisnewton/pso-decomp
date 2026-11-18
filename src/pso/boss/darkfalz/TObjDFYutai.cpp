#define TOBJECT_OUT_OF_LINE_HELPERS
#include "types.h"
#include "pso/boss/darkfalz/TBoss4Type3_800524E8.h"
#include "pso/system/task/TObject_80019A50.h"
#include "pso/unk/text_803D96A8.h"
#include "pso/system/vector.h"
#include "pso/boss/darkfalz/TObjDFYutai.h"
#include "pso/player/TObjPlayer.h"
#include "pso/unk/text_803D8F74.h"
#include "pso/player/TObjPlayer_801AF2F0.h"
#include "pso/system/MatrixOps.h"
#include "pso/system/task/TObject.h"

struct Range_800502FC {
    f32 min;
    f32 max;
    f32 lerp(f32 t) const { return t * (max - min) + min; }
};

typedef struct Data_800502FC {
    u8 pad0[0x20];
    Range_800502FC r20;
    Range_800502FC r28;
    Range_800502FC r30;
} Data_800502FC;

extern "C" {
extern const f32 lbl_805D8A30;
extern const f32 lbl_805D8A34;
void push_matrix();
void post_translate_matrix(void *);

void *lbl_804858A8[3] = {
    (void *)0x0, (void *)0x0, (void *)0xc2a20000,
};
void *dark_falz_jisin_zero_vec[3] = {
    (void *)0x0, (void *)0x0, (void *)0x0,
};
__declspec(section ".data") void *TObjDFJisin__particle_emitter_id_table[2] = {
    (void *)0xe0, (void *)0xf4,
};
__declspec(section ".data") void *lbl_804858C8[2] = {
    (void *)0x41200000, (void *)0x0,
};
__declspec(section ".data") void *lbl_804858D0[2] = {
    (void *)0x40000000, (void *)0x3f800000,
};
__declspec(section ".data") void *lbl_804858D8[2] = {
    (void *)0x0, (void *)0x3f400000,
};
#define lbl_804858C8 (*(Range_800502FC *)lbl_804858C8)
#define lbl_804858D0 (*(Range_800502FC *)lbl_804858D0)
#define lbl_804858D8 (*(Range_800502FC *)lbl_804858D8)
#pragma fp_contract on
#pragma dont_inline off
#pragma inline_depth(1)
void TObjDFYutai::render() {
    Vec v;
    u8 *p;
    f32 s;
    f32 w;
    p = (u8 *)get_player_by_client_id(client_id);
    if (p == NULL || TBoss4Type3__sub_8005254C(client_id) == 0) {
        return;
    }
    s = lbl_804858D0.lerp(progress);
    w = lbl_804858D8.lerp(progress);
    VecCopy((Vec *)&v, (const Vec *)(p + 0x38));
    v.y += lbl_804858C8.min + progress * (lbl_804858C8.max - lbl_804858C8.min);
    push_matrix();
    post_translate_matrix(&v);
    rotate_matrix_y(0, *(s32 *)(p + 0x60));
    scale_matrix(0, s, s, s);
    TObjPlayer::draw_player_model_by_id(client_id, w);
    pop_matrix();
}

#pragma push
#pragma opt_common_subs off
void TObjDFYutai::run_task() {
    if (TBoss4Type3__sub_8005254C(client_id) == 0) {
        queue_destruction();
        return;
    }
    progress += progress_step;
    if (progress <= lbl_805D8A30) {
        progress = lbl_805D8A30;
        queue_destruction();
        return;
    }
    if (progress >= lbl_805D8A34) {
        progress = lbl_805D8A34;
        queue_destruction();
    }
}
#pragma pop

}

TObjDFYutai::~TObjDFYutai() {}


extern "C" const char *TObjDFYutai__name;

TObjDFYutai::TObjDFYutai(s32 parent, s32 effect_mode, s16 player_id) : TObject((TObject *)parent) {
    m_name = TObjDFYutai__name;
    mode = effect_mode;
    client_id = player_id;
    switch (mode) {
    case 0:
        progress = lbl_805D8A34;
        progress_step = fade_out_step;
        break;
    case 1:
        progress = lbl_805D8A30;
        progress_step = fade_in_step;
        break;
    case 2:
        progress = lbl_805D8A34;
        progress_step = fast_fade_out_step;
        break;
    }
}

extern "C" {
__declspec(section ".sdata2") extern const f32 lbl_805D8A30 = 0.0f;
__declspec(section ".sdata2") extern const f32 lbl_805D8A34 = 1.0f;
}

__declspec(section ".sdata2") const f32 TObjDFYutai::fade_out_step = -0.011111111f;
__declspec(section ".sdata2") const f32 TObjDFYutai::fade_in_step = 0.016666668f;
__declspec(section ".sdata2") const f32 TObjDFYutai::fast_fade_out_step = -0.11111111f;
