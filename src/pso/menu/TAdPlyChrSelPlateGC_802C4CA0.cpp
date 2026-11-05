#include "types.h"
#include "pso/misc/TWindowSubSymbolChatPartsSet.h"
#include "pso/TAdPlyChrSelPlateGC.h"
#include "pso/TMainTask.h"
#include "pso/system/ModelDrawContext.h"

typedef struct V_802C4DD0 { s32 x, y; } V_802C4DD0;

typedef struct S_802C4DD0 {
    u8 pad0[0x1C];
    V_802C4DD0 v1C[32];
    V_802C4DD0 v11C[32];
    s32 pad21C[2];
    s32 f224;
} S_802C4DD0;

typedef struct V_802C4E38 { f32 x, y; } V_802C4E38;

typedef struct Q_802C4E38 { u8 b[4]; } Q_802C4E38;

typedef struct S_802C4E38 {
    u8 pad0[0x1C];
    V_802C4E38 v1C[32];
    V_802C4E38 v11C[32];
    s32 pad21C[2];
    s32 f224;
    s32 a[32];
    f32 fl[32];
    Q_802C4E38 c[32];
    u8 col[4];
    s32 f3AC;
} S_802C4E38;

extern "C" {
extern const f32 lbl_805DE548;
extern const f32 lbl_805DE54C;
void copy_vec2__28TWindowSubSymbolChatPartsSetFPv(f32 *destination, const f32 *source);
void TAdEnterSerialAccessGC__sub_802C4B64(void *, void *, Q_802C4E38, int);
extern const f32 lbl_805DE550;
extern const f32 lbl_805DE554;
extern const f32 lbl_805DE558;
#pragma push
#pragma peephole off
void TAdPlyChrSelPlateGC::render() {
    S_802C4E38 *self = (S_802C4E38 *)this;
    u32 i;
    if (TMainTask::get_render_pass() != 1) {
        set_color_blending_mode(0, 8);
        set_color_blending_mode(1, 10);
        for (i = 0; i < self->f224; i++) {
            if (self->a[i] != 0) {
                V_802C4E38 *pos = &self->v1C[0];
                Q_802C4E38 col = self->c[i];
                TAdEnterSerialAccessGC__sub_802C4B64(this, pos + i, col, i);
            }
        }
        set_color_blending_mode(0, 8);
        set_color_blending_mode(1, 6);
    }
}
#pragma pop

s32 TAdPlyChrSelPlateGC::is_slot_value_ready(s32 i) {
    return m_progress[i] >= lbl_805DE548 ? 1 : 0;
}
void TAdPlyChrSelPlateGC::reset_selection_slots() {
    s32 i;
    m_frame = -1;
    m_count = 0;
    for (i = 0; i < 0x20; i++) {
        m_active[i] = 0;
        m_progress[i] = lbl_805DE54C;
        m_colors[i][0] = 0;
        m_colors[i][1] = 0;
        m_colors[i][2] = 0;
        m_colors[i][3] = 0;
    }
}
void push_plate_position__19TAdPlyChrSelPlateGCFv(TAdPlyChrSelPlateGC *self, const f32 *position) {
    if (self->m_count < 0x20) {
        copy_vec2__28TWindowSubSymbolChatPartsSetFPv(self->m_target[self->m_count], position);
        copy_vec2__28TWindowSubSymbolChatPartsSetFPv(self->m_current[self->m_count], self->m_target[0]);
        self->m_count = self->m_count + 1;
    }
}

#pragma push
#pragma fp_contract on
#pragma opt_propagation off
void TAdPlyChrSelPlateGC::run_task() {
    s32 half;
    s32 m;
    u32 i;
    s32 j;
    if (m_frame < m_count * 2 + 1) {
        m_frame = m_frame + 1;
    }
    for (i = 0; i < 32; i++) {
        if (m_active[i] != 0) {
            if (m_active[i] == -1) {
                m_colors[i][2] = 0xFF;
                m_colors[i][1] = 0xFF;
                m_colors[i][0] = 0xFF;
                m_colors[i][3] = 0x22;
                m_active[i] = 1;
            } else {
                m_progress[i] += lbl_805DE550;
                m_progress[i] = (m_progress[i] > lbl_805DE548) ? lbl_805DE548 : m_progress[i];
                m_colors[i][2] = m_color[2];
                m_colors[i][1] = m_color[1];
                m_colors[i][0] = m_color[0];
                m_colors[i][3] = (s32)m_progress[i];
            }
            for (j = 0; j < 32; j++) {
                s32 k = 0;
                m_current[j][0] = m_target[j][0];
                m_current[j][1] += (m_target[j][1] - m_target[0][1]) / (lbl_805DE558 * (f32)k + lbl_805DE554);
                m_current[j][1] = (m_current[j][1] > m_target[j][1]) ? m_target[j][1] : m_current[j][1];
            }
        }
    }
    if (m_frame % 2 == 0) {
        half = m_frame / 2;
        m = half - 1;
        if (m < m_count && half - 1 >= 0 && m < 32) {
            m_active[half - 1] = 1;
        }
    }
}
#pragma pop

}
