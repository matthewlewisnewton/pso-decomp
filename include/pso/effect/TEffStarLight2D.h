#ifndef PSO_TEFFSTARLIGHT2D_H
#define PSO_TEFFSTARLIGHT2D_H
#include "pso/TObject.h"
#include "types.h"
#include "pso/render/ColorLineList.h"
#include <stddef.h>
#include <dolphin/mtx/GeoTypes.h>

union StarLightColor {
    struct { u8 a, r, g, b; } channels;
    u32 packed;
};

struct StarLightParameters {
    f32 width;
    f32 speed;
    StarLightColor color;
    s32 blend_mode;
    f32 alpha_step;

    void copy_from(StarLightParameters *source);
};

class TEffStarLight2D : public TObject {
public:
    TEffStarLight2D(void *position, void *parameters, TObject *parent);
    virtual ~TEffStarLight2D();
    virtual void render();
    virtual void run_task();
public:
    void copy_from_subobject(void *source);
    void copy_position(const Vec *position);
    void queue_child_destruction();
    void draw_segment(ColorLineVertex *a, ColorLineVertex *b,
                      ColorLineVertex *c, ColorLineVertex *d, s32 index);

    ColorLineVertex screen_position;
    ColorLineVertex previous_screen_position;
    Vec position;
    StarLightParameters parameters;
};

typedef char StarLightColorSize[sizeof(StarLightColor) == 4 ? 1 : -1];
typedef char StarLightParametersSize[sizeof(StarLightParameters) == 0x14 ? 1 : -1];
typedef char TEffStarLight2DSize[sizeof(TEffStarLight2D) == 0x4C ? 1 : -1];

typedef char StarLightParameterOffsets[(offsetof(StarLightParameters, width) == 0 &&
    offsetof(StarLightParameters, speed) == 4 &&
    offsetof(StarLightParameters, color) == 8 &&
    offsetof(StarLightParameters, blend_mode) == 0xC &&
    offsetof(StarLightParameters, alpha_step) == 0x10) ? 1 : -1];
typedef char StarLightObjectOffsets[(offsetof(TEffStarLight2D, screen_position) == 0x1C &&
    offsetof(TEffStarLight2D, previous_screen_position) == 0x24 &&
    offsetof(TEffStarLight2D, position) == 0x2C &&
    offsetof(TEffStarLight2D, parameters) == 0x38) ? 1 : -1];

#endif
