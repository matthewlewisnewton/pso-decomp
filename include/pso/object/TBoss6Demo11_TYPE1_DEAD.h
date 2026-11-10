#ifndef PSO_OBJECT_TBOSS6DEMO11_TYPE1_DEAD_H
#define PSO_OBJECT_TBOSS6DEMO11_TYPE1_DEAD_H
#include "types.h"
#include "pso/TObject.h"
#include "pso/system/vector.h"

struct AnimationMotion;
class ModelNodePositionCapture;
class TParticleCtrl;
struct TBoss6PlotFalz;

class TBoss6Demo11_TYPE1_DEAD : public TObject {
public:
    TBoss6Demo11_TYPE1_DEAD(TBoss6PlotFalz *parent, const Vec *target);
    virtual ~TBoss6Demo11_TYPE1_DEAD();
    void render_fade_model();
    virtual void render();
    virtual void run_task();

    struct Model {
        s32 object;
        s32 textures;
        AnimationMotion *motion;
    };

    Vec origin;
    Model models[2];
    f32 frame;
    s32 elapsed;
    TBoss6PlotFalz *plot;
    Vec captured_positions[5];
    ModelNodePositionCapture *capture;
    TParticleCtrl *emitter;
};
typedef char TBoss6Demo11_TYPE1_DEAD_size[sizeof(TBoss6Demo11_TYPE1_DEAD) == 0x90 ? 1 : -1];

#endif
