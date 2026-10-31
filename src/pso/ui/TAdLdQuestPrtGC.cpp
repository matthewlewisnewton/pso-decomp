#include "types.h"
#include "pso/object/TObject_80019A50.h"
#include "pso/ui/TAdLdQuestPrtGC.h"
#include "pso/TParticleCtrl.h"
#include "pso/unk/text_80086E28.h"

struct RecoveredGlobal_8000F764_TKeyBoardControl__data_80506270 {
    s32 value;
    u8 remaining[0xAC];
};

struct RecoveredGlobal_8000F7FC_lbl_80515F48 {
    s32 value;
    u8 remaining[0x24];
};

struct RecoveredGlobal_8000F9E4_lbl_804FE120 {
    s32 value;
    u8 remaining[0x14];
};

struct RecoveredGlobal_8000F90C_lbl_804FE120 {
    s32 value;
    u8 remaining[0x14];
};

struct RecoveredGlobal_8000F9CC_lbl_804FE120 {
    s32 value;
    u8 remaining[0x14];
};

struct RecoveredGlobal_8000F8FC_lbl_804FE120 {
    s32 value;
    u8 remaining[0x14];
};

struct RecoveredGlobal_8000F8EC_lbl_804FE120 {
    s32 value;
    u8 remaining[0x14];
};

struct RecoveredGlobal_8000F91C_lbl_804FE120 {
    s32 value;
    u8 remaining[0x14];
};

struct Obj_80322E90 { u8 pad[0x18]; void *vt; void *items[4]; };

extern "C" {
int ansi_fp_abs(int);
void TAdLdQuestPrtGC::render() {  }
typedef char RecoveredGlobal_8000F764_TKeyBoardControl__data_80506270_size[sizeof(RecoveredGlobal_8000F764_TKeyBoardControl__data_80506270) == 0xB0 ? 1 : -1];

}
TAdLdQuestPrtGC::~TAdLdQuestPrtGC() {
    u32 i;
    for (i = 0; i < 4; i++) {
        if (((Obj_80322E90 *)this)->items[i] != 0) {
            queue_destruction__7TObjectFv(((Obj_80322E90 *)this)->items[i]);
            ((Obj_80322E90 *)this)->items[i] = 0;
        }
    }
}

// The original caller passes a signed stick value in r3, not a receiver.
extern "C" int get_abs__15TAdLdQuestPrtGCFv(int value) { return ansi_fp_abs(value); }
typedef char RecoveredGlobal_8000F7FC_lbl_80515F48_size[sizeof(RecoveredGlobal_8000F7FC_lbl_80515F48) == 0x28 ? 1 : -1];
typedef char RecoveredGlobal_8000F90C_lbl_804FE120_size[sizeof(RecoveredGlobal_8000F90C_lbl_804FE120) == 0x18 ? 1 : -1];
typedef char RecoveredGlobal_8000F8FC_lbl_804FE120_size[sizeof(RecoveredGlobal_8000F8FC_lbl_804FE120) == 0x18 ? 1 : -1];
typedef char RecoveredGlobal_8000F8EC_lbl_804FE120_size[sizeof(RecoveredGlobal_8000F8EC_lbl_804FE120) == 0x18 ? 1 : -1];
typedef char RecoveredGlobal_8000F91C_lbl_804FE120_size[sizeof(RecoveredGlobal_8000F91C_lbl_804FE120) == 0x18 ? 1 : -1];
typedef char RecoveredGlobal_8000F9E4_lbl_804FE120_size[sizeof(RecoveredGlobal_8000F9E4_lbl_804FE120) == 0x18 ? 1 : -1];
typedef char RecoveredGlobal_8000F9CC_lbl_804FE120_size[sizeof(RecoveredGlobal_8000F9CC_lbl_804FE120) == 0x18 ? 1 : -1];

struct QuestParticleCameraRay { Vec origin, direction; };
extern "C" {
extern const u32 lbl_80476610[6];
extern const char *lbl_805D4168;
extern QuestParticleCameraRay lbl_804FF5E8;
extern const f32 lbl_805DF548;
extern const f32 lbl_805DF54C;
}

#pragma push
#pragma fp_contract on
#pragma opt_common_subs on
TAdLdQuestPrtGC::TAdLdQuestPrtGC(TObject *parent) : TObject(parent) {
    m_name = lbl_805D4168;
    color_index = 0;
    color_frames = 0;
    frames = 0;
    for (u32 i = 0; i < 4; i++) {
        colors[i].r = (f32)((lbl_80476610[0] >> 24) & 0xFF);
        colors[i].g = (f32)((lbl_80476610[0] >> 16) & 0xFF);
        colors[i].b = (f32)((lbl_80476610[0] >> 8) & 0xFF);
        colors[i].a = (f32)(lbl_80476610[0] & 0xFF);
        positions[i].x = lbl_805DF548 * lbl_804FF5E8.direction.x + lbl_804FF5E8.origin.x - lbl_805DF54C;
        positions[i].y = lbl_805DF548 * lbl_804FF5E8.direction.y + lbl_804FF5E8.origin.y;
        positions[i].z = lbl_805DF548 * lbl_804FF5E8.direction.z + lbl_804FF5E8.origin.z;
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

// The physical bank's stick samples and extent are established by the input updater.
struct QuestPhysicalPortBank {
    u8 unknown_00[0x34];
    s16 stick_x, stick_y;
    u8 remaining[0x178];
};
extern "C" {
extern QuestPhysicalPortBank controller_physical_port_bank;
extern u8 controller_input_state[0x1B0];
// Existing names encode obsolete class ownership; both receive an input record
// in r3 and a button mask in r4, as in the neighboring loading UI callers.
s32 TWindowShortListCtrl__check_controller_button(void *, s32);
s32 test_flag_4c__23TAdSinglePlyChrSelectGCFv(void *, s32);
extern const f32 lbl_805DF540, lbl_805DF544;
}

#pragma push
#pragma opt_common_subs on
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
        static f32 input_scale = lbl_805DF540;
        const f32 multiplier = input_scale;
        x = (s32)((f32)x * multiplier);
        f32 x_angle = lbl_805DF544 * (f32)-x;
        y = (s32)((f32)y * multiplier);
        f32 y_angle = lbl_805DF544 * (f32)-y;
        angle_steps[0].x = (s32)x_angle / 5;
        angle_steps[0].z = (s32)y_angle / 5;
        angle_steps[1].x = (s32)(lbl_805DF544 * (f32)(-x * 2)) / 4;
        angle_steps[1].z = (s32)(lbl_805DF544 * (f32)(-y * 2)) / 3;
        angle_steps[2].x = (s32)y_angle / 2;
        angle_steps[2].z = (s32)(lbl_805DF544 * (f32)x) / 6;
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

#pragma pop
