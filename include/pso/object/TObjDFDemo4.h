#ifndef PSO_OBJECT_TOBJDFDEMO4_H
#define PSO_OBJECT_TOBJDFDEMO4_H

#include "types.h"
#include "pso/object/TObjMotion.h"

class ModelNodePositionCapture;
class TParticleCtrl;
struct AnimationMotion;
struct NJS_OBJECT;

struct TObjDFDemo4Part {
    NJS_OBJECT *model;
    s32 texlist;
    AnimationMotion *motion;
};

struct TObjDFDemo4 : public TObjBase {
    TObjDFDemo4(TObject *parent, const Vec *position, s32 angle);
    virtual ~TObjDFDemo4();
    void draw_afterimages();
    void draw_body();
    virtual void render();
    virtual void run_task();
    // State shared by the legacy strip initialization, scrolling and release helpers.
    u8 strips[0x14];
    TParticleCtrl *particle_emitters[2];
    TObjDFDemo4Part afterimages[2];
    TObjDFDemo4Part body_parts[3];
    Vec camera_position;
    s32 angle;
    s32 timer;
    f32 frame;
    ModelNodePositionCapture *node_capture;
    Vec emitter_positions[2];

    static TObjDFDemo4 *create(TObject *parent, const Vec *position, s32 angle);
};

typedef char TObjDFDemo4_size[sizeof(TObjDFDemo4) == 0x11C ? 1 : -1];
typedef char TObjDFDemo4_camera_position_offset[offsetof(TObjDFDemo4, camera_position) == 0xE8 ? 1 : -1];
#endif
