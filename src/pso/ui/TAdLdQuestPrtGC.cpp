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
