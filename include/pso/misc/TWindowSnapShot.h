#ifndef PSO_MISC_TWINDOWSNAPSHOT_H
#define PSO_MISC_TWINDOWSNAPSHOT_H

#include "types.h"
#include "pso/misc/TWindowBase.h"

struct TWindowSnapShot : public TWindowBase {
    virtual ~TWindowSnapShot();
    virtual void render();
    u8 m_60;
    static void free_shared_instance();
    s32 get_size();
    s32 get_field_8();
    static int get_height();
    void play_open_sound();
    virtual void run_task();
    void reset();
    u8 *init_and_reset();
    void update_both();
    s32 start_capture(const void *name);
    static int get_width();
    static void init_default();
    static void alloc_buffer();
    u8 unk_61[0x3];
    void free_buffer();
    s32 open_stream(const void *name);
    void set_mode(s32 v);
    s32 get_buffer_size();
};

typedef char TWindowSnapShot_size[sizeof(TWindowSnapShot) == 0x64 ? 1 : -1];

extern "C" {
u8 *TWindowSnapShot__ct(TWindowSnapShot *arg0, s32 arg1);
const char *TWindowSnapShot__sub_802A7EAC(void);
void *__dt__15TWindowSnapShotFv(void *arg0, s16 arg1);
}
s32 load_player_motion_data(void);
extern "C" {
void render__15TWindowSnapShotFv(u8 *arg0);
}

#endif
