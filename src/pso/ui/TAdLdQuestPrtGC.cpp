#include "types.h"
#include "pso/object/TObject_80019A50.h"
#include "pso/ui/TAdLdQuestPrtGC.h"
#include "pso/TParticleCtrl.h"
#include "pso/unk/text_80086E28.h"

struct QuestParticleCameraRay {
    Vec origin, direction;
    u8 remaining[0x10];
};
struct QuestPhysicalPortBank {
    u8 unknown_00[0x34];
    s16 stick_x, stick_y;
    u8 remaining[0x178];
};

extern "C" {
int ansi_fp_abs(int);
int get_abs__15TAdLdQuestPrtGCFv(int);
extern QuestParticleCameraRay lbl_804FF5E8;
extern QuestPhysicalPortBank controller_physical_port_bank;
extern u8 controller_input_state[0x1B0];
// The existing helper labels describe obsolete ownership; their actual
// boundary is an input record in r3 and a button mask in r4.
s32 TWindowShortListCtrl__check_controller_button(void *, s32);
s32 test_flag_4c__23TAdSinglePlyChrSelectGCFv(void *, s32);

extern const u32 lbl_80476610[6] = {
    0xFF77FF3F, 0xFF333377, 0xFFB31A77,
    0xFFB31A1A, 0xFFFF4D1A, 0xFFB34D00
};
extern const char lbl_80476628[0x10] = "TAdLdQuestPrtGC";
const char *lbl_805D4168[2] = { lbl_80476628, 0 };
}

void TAdLdQuestPrtGC::render() {  }

void TAdLdQuestPrtGC::run_task() {
    if (TWindowShortListCtrl__check_controller_button((u8 *)&controller_physical_port_bank + 0x20, 4) != 0 ||
        test_flag_4c__23TAdSinglePlyChrSelectGCFv(controller_input_state + 0x160, 4) != 0) {
        color_frames = 0;
        ++color_index;
        if (color_index >= 6) color_index = 0;
    }
    s32 x = controller_physical_port_bank.stick_x;
    s32 y = controller_physical_port_bank.stick_y;
    if (get_abs__15TAdLdQuestPrtGCFv(x) > 0 || get_abs__15TAdLdQuestPrtGCFv(y) > 0) {
        static f32 input_scale = 0.02f;
        const f32 multiplier = input_scale;
        const f32 x_input = (f32)x;
        const s32 scaled_x = (s32)(x_input * multiplier);
        angle_steps[0].x = (s32)(182.04445f * (f32)-scaled_x) / 5;
        const f32 y_input = (f32)y;
        const s32 scaled_y = (s32)(y_input * multiplier);
        angle_steps[0].z = (s32)(182.04445f * (f32)-scaled_y) / 5;
        angle_steps[1].x = (s32)(182.04445f * (f32)(-scaled_x * 2)) / 4;
        angle_steps[1].z = (s32)(182.04445f * (f32)(-scaled_y * 2)) / 3;
        angle_steps[2].x = (s32)(182.04445f * (f32)-scaled_y) / 2;
        angle_steps[2].z = (s32)(182.04445f * (f32)scaled_x) / 6;
        // Angles are word accumulators: unsigned addition preserves their wrap.
        angles[0].x += angle_steps[0].x;
        angles[1].x += angle_steps[1].x;
        angles[2].x += angle_steps[2].x;
        angles[3].x += angle_steps[3].x;
    }
    angles[0].z += angle_steps[0].z;
    angles[1].z += angle_steps[1].z;
    angles[2].z += angle_steps[2].z;
    angles[3].z += angle_steps[3].z;
    for (u32 i = 0; i < 4; i++) {
        if (particles[i] != 0) {
            particles[i]->set_direction(&angles[i]);
            particles[i]->set_tint_color(lbl_80476610[color_index]);
        }
    }
    ++color_frames;
    color_frames = color_frames > 12 ? 12 : color_frames;
    ++frames;
}

TAdLdQuestPrtGC::~TAdLdQuestPrtGC() {
    u32 i;
    for (i = 0; i < 4; i++) {
        if (particles[i] != 0) {
            queue_destruction__7TObjectFv(particles[i]);
            particles[i] = 0;
        }
    }
}

#pragma push
#pragma fp_contract on
#pragma opt_common_subs on
TAdLdQuestPrtGC::TAdLdQuestPrtGC(TObject *parent) : TObject(parent) {
    m_name = lbl_805D4168[0];
    color_index = 0;
    color_frames = 0;
    frames = 0;
    for (u32 i = 0; i < 4; i++) {
        colors[i].r = (f32)((lbl_80476610[0] >> 24) & 0xFF);
        colors[i].g = (f32)((lbl_80476610[0] >> 16) & 0xFF);
        colors[i].b = (f32)((lbl_80476610[0] >> 8) & 0xFF);
        colors[i].a = (f32)(lbl_80476610[0] & 0xFF);
        positions[i].x = 100.0f * lbl_804FF5E8.direction.x + lbl_804FF5E8.origin.x - 11.0f;
        positions[i].y = 100.0f * lbl_804FF5E8.direction.y + lbl_804FF5E8.origin.y;
        positions[i].z = 100.0f * lbl_804FF5E8.direction.z + lbl_804FF5E8.origin.z;
        angles[i].x = i * 0xAAA;
        angles[i].y = 0;
        angles[i].z = i * 0xAAA;
        particles[i] = (TParticleCtrl *)create_particle_controller_with_angles(&positions[i], &angles[i], 0x1B, 1, 0x800);
    }
    angle_steps[0].x = 0;
    angle_steps[0].z = 0x5B;
    angle_steps[1].x = 0;
    angle_steps[1].z = -0x5B;
    angle_steps[2].x = 0;
    angle_steps[2].z = 0xB6;
    angle_steps[3].x = 0;
    angle_steps[3].z = -0x5B;
}
#pragma pop

// r3 is a signed stick sample, not a receiver.
extern "C" int get_abs__15TAdLdQuestPrtGCFv(int value) { return ansi_fp_abs(value); }
