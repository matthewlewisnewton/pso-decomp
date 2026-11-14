#include "types.h"
#include "pso/misc/TWindowSubStatusDisp_80144B14.h"
#include "pso/misc/TWindowTimer.h"

#pragma readonly_strings on
struct Obj_80287BE8 { u8 pad[0x30]; f32 f30; f32 f34; u8 pad2[8]; f32 f40; f32 f44; };

typedef struct TimerChild_80287B60 {
    u8 pad[8];
    f32 x;
} TimerChild_80287B60;

struct En_80287AD8 { u8 pad[8]; f32 f8; };


extern "C" {
extern const f32 lbl_805DD880;
TimerChild_80287B60 *get_array_entry__11TWindowBaseFi(void *, s32);
extern const f32 lbl_805DD878;
extern const f32 lbl_805DD87C;

#pragma push
#pragma fp_contract on
void init_timer_window_layout(TWindowTimer *arg0) {
    f32 temp_f31;
    En_80287AD8 *e;
    arg0->m_60 |= 1;
    temp_f31 = (f32)calc_text_width("000:000");
    e = ((En_80287AD8 *)get_array_entry__11TWindowBaseFi(arg0, 0));
    e->f8 = -(lbl_805DD87C * temp_f31 - lbl_805DD878);
}
#pragma pop

#pragma push
#pragma fp_contract on
void init_timer_window_layout_alt(TWindowTimer *self) {
    f32 width;
    TimerChild_80287B60 *child;
    self->m_60 &= ~1;
    width = (f32)calc_text_width("0'00\"00");
    child = get_array_entry__11TWindowBaseFi(self, 0);
    child->x = lbl_805DD878 - lbl_805DD87C * width;
}
#pragma pop

#pragma push
#pragma fp_contract on
void TWindowTimer::ease_window_timer_position() {
    Obj_80287BE8 *o = (Obj_80287BE8 *)this;
    o->f40 += lbl_805DD880 * (o->f30 - o->f40);
    o->f44 += lbl_805DD880 * (o->f34 - o->f44);
}
#pragma pop

}
