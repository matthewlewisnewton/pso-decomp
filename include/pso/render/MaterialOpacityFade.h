#ifndef PSO_RENDER_MATERIALOPACITYFADE_H
#define PSO_RENDER_MATERIALOPACITYFADE_H
#include "types.h"
#include "pso/render/MaterialColorFade.h"

class MaterialOpacityFade : public MaterialColorFade {
public:
    MaterialOpacityFade();
    virtual ~MaterialOpacityFade();
    virtual void set_rate_from_divisor(s32);
    virtual void reset_color();
    virtual void reset_obstruction_fade();
    virtual s32 decay_value_toward_floor();
    virtual s32 advance_toward_max();
    virtual void set_flags_and_apply_damage_color();
    virtual s32 has_visible_opacity();
    void update_alpha();
    void start_fade_in();
    s32 advance_to(f32);
    void set_rate(f32);
    void start_fade_out();
    f32 value;
};

// Unrecovered enclosing constructors call the native constructor by its ABI symbol.
extern "C" void *__ct__19MaterialOpacityFadeFv(void *);

typedef char FadeValueOffset[offsetof(MaterialOpacityFade, value) == 0x18 ? 1 : -1];
typedef char FadeValueSize[sizeof(MaterialOpacityFade) == 0x1c ? 1 : -1];

#endif
