#ifndef PSO_MISC_TWINDOWLOCKON_H
#define PSO_MISC_TWINDOWLOCKON_H

#include "types.h"
#include "pso/misc/TUnk_804CE018.h"

struct TWindowLockOn : public TUnk_804CE018 {
    virtual ~TWindowLockOn();
    void request_close();
    virtual void render();
    u16 m_60;
    u8 _pad62[0x2];
    u32 m_64;
    void* m_68;
    u8 _pad6C[0x4];
    u32 m_70;
    u32 m_74;
    u32 m_78;
    s32 get_target_id();
    static f32 get_target_distance();
    void validate_target();
    static void refresh_ground_item();
    void update_photon_blast_marker();
    static void *create_for_target(s32 arg0, u16 arg1);
    virtual void run_task();
    void update_for_player_index(s32 arg1);
    void refresh_enemy_statuses();
};

typedef char TWindowLockOn_size[sizeof(TWindowLockOn) == 0x7C ? 1 : -1];
#endif
