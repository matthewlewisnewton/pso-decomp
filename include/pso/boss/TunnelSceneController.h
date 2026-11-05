#ifndef PSO_BOSS_TUNNEL_SCENE_CONTROLLER_H
#define PSO_BOSS_TUNNEL_SCENE_CONTROLLER_H
#include "pso/TObject.h"
#include <stddef.h>
class TunnelSceneController : public TObject {
public:
    virtual ~TunnelSceneController();
    virtual void run_task();
    void spawn_segment_row_a();
    void spawn_segment_row_b();
    void init_effect();
    void update_effect();
    void sub_802F23FC();
    s32 phase;
    u8 unknown20[0x34];
    f32 segment_x;
    u8 unknown58[0x2C];
    f32 half_length;
    u32 unknown88;
    TObject* effect_nodes;
    TObject* tunnel_nodes;
};
typedef char TunnelSceneSize[sizeof(TunnelSceneController)==0x94?1:-1];
typedef char TunnelScenePhase[offsetof(TunnelSceneController,phase)==0x1C?1:-1];
typedef char TunnelSceneX[offsetof(TunnelSceneController,segment_x)==0x54?1:-1];
typedef char TunnelSceneLength[offsetof(TunnelSceneController,half_length)==0x84?1:-1];
#endif
