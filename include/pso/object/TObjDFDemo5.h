#ifndef PSO_OBJECT_TOBJDFDEMO5_H
#define PSO_OBJECT_TOBJDFDEMO5_H

#include "types.h"
#include "pso/object/TObjMotion.h"

class TParticleCtrl;
class ModelNodePositionCapture;
struct AnimationMotion;
struct NJS_OBJECT;

// One model of the Dark Falz death scene: its model, texture list and motion.
struct TObjDFDemo5Part {
    NJS_OBJECT *model;
    s32 texlist;
    AnimationMotion *motion;
};

struct TObjDFDemo5 : public TObjBase {
    TObjDFDemo5(TObject *parent, const Vec *pos, s32 angle);
    virtual ~TObjDFDemo5();
    virtual void run_task();
    virtual void render();
    void update_particle_emitters();
    void release_subobjects();
    void draw_fading_motion();
    static void *create(void *arg0, void *arg1, void *arg2);

    TParticleCtrl *particle_emitters[5];
    TObjDFDemo5Part parts[4];
    Vec pos;
    s32 angle;
    s32 timer;
    f32 frame;
    ModelNodePositionCapture *node_list0;     // tracks emitter_positions
    Vec emitter_positions[2];
    ModelNodePositionCapture *node_list1;     // tracks tail_position
    Vec tail_position;
};

typedef char TObjDFDemo5_size[sizeof(TObjDFDemo5) == 0x118 ? 1 : -1];
#endif
