#ifndef PSO_MISC_TUNK_804CDFE8_H
#define PSO_MISC_TUNK_804CDFE8_H
#include "types.h"
#include "pso/misc/TUnk_804CE018.h"

class TUnk_804CDFE8 : public TUnk_804CE018 {
public:
    virtual ~TUnk_804CDFE8();
    s32 sub_80266B18(s32);
    void *construct_with_parent(void *);
    void *destroy_window(s16);
    void sub_802443B4();
    void step_window_tween();
    void set_position_xy(f32, f32);
};

#endif
