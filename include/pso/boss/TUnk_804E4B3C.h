#ifndef PSO_BOSS_TUNK_804E4B3C_H
#define PSO_BOSS_TUNK_804E4B3C_H
#include "types.h"
#include "pso/TObject.h"

class TUnk_804E4B3C : public TObject {
public:
    virtual ~TUnk_804E4B3C();
    virtual void run_task();
    void *destroy(s16);
    void update_phase_motion();
    void spawn(s32, s32);
    virtual void render();
    // run_task's phase handlers (indexed by phase)
    void init_effect();
    void sub_802F2400();
    void sub_802F23FC();
    void update_dust_spawn();
    void update_spawn_timer(s32 arg1, s32 arg2, s32 arg3);
    void advance_effect_timer();
    // Same object as TunnelSceneController (size 0x94); names shared with it.
    s32 phase;          // index into run_task's phase handlers
    u8 pad_20[0x34];
    f32 segment_x;      // a segment's position.x
    f32 scroll_offset;  // update_spawn_timer adds scroll_speed, spawns a segment per 800
    f32 scroll_speed;   // a segment's z step per frame
    u8 pad_60[0x10];
    s32 spawn_index;    // update_spawn_timer's index into its spawn table
    u8 pad_74[0xC];
    f32 unk_80;
    f32 half_length;
    TObject *tunnel_col; // the TObjBoss7TunnelCol the constructor creates
    void *effect_nodes;  // parent of the segments spawn creates
    u8 pad_90[0x4];
};
typedef char TUnk_804E4B3C_size[sizeof(TUnk_804E4B3C) == 0x94 ? 1 : -1];

#endif
