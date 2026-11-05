#ifndef PSO_TBOSS7TENTACLE_H
#define PSO_TBOSS7TENTACLE_H
#include "pso/TObject.h"
#include "pso/system/NinjaTypes.h"
#include "pso/system/vector.h"
#include "types.h"
#include <stddef.h>

class TBoss7Tentacle : public TObject {
public:
    TBoss7Tentacle(TObject *parent, const f32 (*matrix)[4], s32 kind);
    virtual ~TBoss7Tentacle();
    void sub_802F09FC();
    void sub_802F09EC();
    virtual void render();
    virtual void run_task();

public:
    void update_extend_amount();
    void switch_state();
    void advance_path_position();
    void reset_state();
    void setup_state();
    void init_segments();
    void start_attack_at_position(const Vec *target, s32 arg2);

    NJS_OBJECT *model;
    NJS_MOTION *motion;
    // z is the extend amount update_extend_amount moves between 0 and 1.
    Vec scale;
    s32 m_30;
    s32 m_34;
    s32 m_38;
    s32 m_3c;
    // World position of the attach point, from m_130 in run_task.
    Vec base;
    s32 kind;
    Vec segments[14];
    s32 m_f8[14];
    const f32 (*m_130)[4];
    f32 m_134;
    f32 m_138;
    s32 m_13c;
    s32 m_140;
    s32 m_144;
    s32 m_148;
    Vec m_14c;
    f32 m_158;
    f32 m_15c;
    f32 m_160;
    s32 m_164;
    s32 m_168;
};

typedef char TBoss7TentacleBaseOffset[offsetof(TBoss7Tentacle, base) == 0x40 ? 1 : -1];
typedef char TBoss7TentacleSegmentsOffset[offsetof(TBoss7Tentacle, segments) == 0x50 ? 1 : -1];
typedef char TBoss7TentacleSize[sizeof(TBoss7Tentacle) == 0x16C ? 1 : -1];

#endif
