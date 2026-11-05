#ifndef PSO_MISC_TWINDOWFUKIDASI_H
#define PSO_MISC_TWINDOWFUKIDASI_H

#include "types.h"
#include "pso/misc/TUnk_804CF0B8.h"

// The vtable at 0x804CF0B8 holds __dt__13TUnk_804CF0B8, run_task and render,
// so TUnk_804CF0B8 and TWindowFukidasi name one class. The methods symbols.txt
// assigns to TWindowFukidasi live here; this adds no fields or virtuals.
class TWindowFukidasi : public TUnk_804CF0B8 {
public:
    static void draw_resolved_window(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
    void hide();
    int get_visible_flag();
    int is_bit10_set();
    s32 check_card_match_enabled(s32 arg1);
    void get_boundary_offset(s32 angle, f32 *out);
    void find_balloon_overlap_for(s32 arg1);
    void rearm_balloon(s32 arg1);
    void open(u32 *parts, s32 flags);
    void set_text(const char *str, s32 flags);
    void init_flags(s32 flags);
};

extern "C" {
s32 clamp_position__13TUnk_804CF0B8FPvf(void *arg0, void *arg1, f32 farg0);
void complete_speech_balloon(u8 *arg0);
s32 is_speech_balloon_ready(u8 *arg0);
}

#endif
