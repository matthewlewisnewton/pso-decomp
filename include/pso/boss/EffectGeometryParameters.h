#ifndef PSO_BOSS_EFFECT_GEOMETRY_PARAMETERS_H
#define PSO_BOSS_EFFECT_GEOMETRY_PARAMETERS_H
#include "types.h"
#include <stddef.h>

// Same twenty-byte storage as the existing typed Dragon attack templates.
// Only field_4 and field_8 are interpreted by this copy/geometry boundary;
// the other fields retain the existing template initializer representation.
struct EffectGeometryParameters {
    s32 field_0;
    f32 field_4;
    f32 field_8;
    f32 field_C;
    s32 field_10;
};
typedef char EffectGeometryParametersSize[sizeof(EffectGeometryParameters) == 20 ? 1 : -1];
typedef char EffectGeometryParametersFloat4[offsetof(EffectGeometryParameters, field_4) == 4 ? 1 : -1];
typedef char EffectGeometryParametersRadius[offsetof(EffectGeometryParameters, field_8) == 8 ? 1 : -1];
extern "C" {
void TBoss1Dragon__sub_80027A80(EffectGeometryParameters *destination, const EffectGeometryParameters *source);
extern const EffectGeometryParameters TBoss1Dragon__head_fall_effect_params;
extern const EffectGeometryParameters boss1_dragon_attack_sphere_params;
extern EffectGeometryParameters TBoss8Dragon__body_effect_parameters;
extern EffectGeometryParameters lbl_804744B4;
extern EffectGeometryParameters boss8_dragon_attack_params;
extern EffectGeometryParameters gryphon_effect_param_block;
extern EffectGeometryParameters boss5_gryphon_params_b;
extern EffectGeometryParameters lbl_80437D68;
extern EffectGeometryParameters gryphon_collider_desc;
extern EffectGeometryParameters gryphon_part_attack_params;
}
#endif
