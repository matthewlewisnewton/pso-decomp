#include "pso/TBoss5GryphonLightning.h"
#include "pso/unk/text_80087278.h"

extern "C" {
extern const char *lbl_805D4180;
extern const f32 lbl_805DF5E0;
}

TBoss5GryphonLightning::TBoss5GryphonLightning(TObject *parent, f32 parameter, const Vec *source)
    : TObject(parent) {
    m_name = lbl_805D4180;
    VecCopy(&position_a, source);
    VecCopy(&position_b, &position_a);
    m_1c = parameter;
    m_94 = 0;
    m_38 = spawn_continuous_particle_effect_with_flags(&position_a, 0x20C, 0x40);
    m_3c = spawn_continuous_particle_effect_with_flags(&position_a, 0x20E, 0x40);
    m_40 = spawn_continuous_particle_effect_with_flags(&position_b, 0x20F, 0x40);
    m_44 = spawn_continuous_particle_effect_with_flags(&position_b, 0x216, 0x40);
    for (s32 i = 0; i < 4; i++) {
        VecCopy(&points[i].position, &position_a);
        points[i].field_c = lbl_805DF5E0;
    }
    m_88 = lbl_805DF5E0;
    m_8c = lbl_805DF5E0;
    m_90 = 1;
}
