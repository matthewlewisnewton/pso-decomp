#ifndef PSO_ENEMY_TOBJENESHARK_H
#define PSO_ENEMY_TOBJENESHARK_H

#include "pso/enemy/TUnk_80493450.h"
#include "pso/misc/MaterialOpacityFade.h"
#include "pso/misc/RenderFadeState.h"
#include "pso/unk/TUnk_80494968.h"
#include "pso/system/BmlResource.h"

struct SharkMovementParameters {
    f32 target_range;
    f32 movement_speed;
    s32 turn_step;
    u32 unknown_0c;
    u32 unknown_10;
    u32 unknown_14;
    u32 unknown_18;
};

typedef char SharkMovementParamsSize[sizeof(SharkMovementParameters) == 0x1C ? 1 : -1];

class TObjEneShark : public TUnk_80493450 {
public:
    TObjEneShark(TObject *parent, void *setData);
    virtual ~TObjEneShark();
    void bind_variant_model(s32);
    void configure_subtype();
    virtual void vfunc_83();
    virtual void vfunc_101();
    virtual void vfunc_98();
    virtual void vfunc_97();
    virtual void vfunc_96();
    virtual void vfunc_95();
    virtual void vfunc_94();
    virtual void vfunc_93();
    virtual void render();

    MaterialOpacityFade appearance_fade;
    TUnk_80494968 *attack_trails[2];
    RenderFadeState camera_fades[4];
    static void *create(void *setData);
    static void free_resources();
    static void load_resources();
    static void update_node_particle_state();
};

typedef char SharkFadeOffset[offsetof(TObjEneShark, appearance_fade) == 0x3A8 ? 1 : -1];
typedef char SharkTrailsOffset[offsetof(TObjEneShark, attack_trails) == 0x3C4 ? 1 : -1];
typedef char SharkCameraFadesOffset[offsetof(TObjEneShark, camera_fades) == 0x3CC ? 1 : -1];
typedef char SharkSize[sizeof(TObjEneShark) == 0x43C ? 1 : -1];

#endif
