#ifndef PSO_UI_WINDOW_TWINDOWSNAPSHOT_H
#define PSO_UI_WINDOW_TWINDOWSNAPSHOT_H

#include "types.h"
#include "pso/ui/window/TWindowBase.h"

struct TWindowSnapShot : public TWindowBase {
    TWindowSnapShot(void *position);
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
    s32 start_capture(s32 arg1);
    static int get_width();
    static void init_default();
    static void alloc_buffer();
    u8 unk_61[0x3];
    void free_buffer();
    s32 open_stream(s32 arg1);
    void set_mode(s32 v);
    s32 get_buffer_size();
};

typedef char TWindowSnapShot_size[sizeof(TWindowSnapShot) == 0x64 ? 1 : -1];

extern "C" {
int TWindowSnapShot__sub_802A7EAC(void);
}
s32 load_player_motion_data(void);

#endif
