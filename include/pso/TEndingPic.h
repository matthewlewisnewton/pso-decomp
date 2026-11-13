#ifndef PSO_TENDINGPIC_H
#define PSO_TENDINGPIC_H
#include "pso/TObject.h"
#include "types.h"

struct EndingPictureQuad {
    f32 left, top, right, bottom;
    f32 u0, v0, u1, v1;
};

class TEndingPic : public TObject {
public:
    TEndingPic(TObject *parent);
    virtual ~TEndingPic();
    virtual void run_task();
    virtual void render();

    void advance_animation_state();
    void draw_current_pic();
    void init_positions();

    s32 elapsed_ticks;             // 0x1C
    s32 field_20;                 // Initialized to 0xFF; no reads in this unit.
    s32 next_picture;
    s32 picture_pair;
    EndingPictureQuad quads[6];    // 0x2C; the last two are drawn here
    s32 timing_rate;               // 0xEC
};

#include <stddef.h>
typedef char TEndingPicQuads[offsetof(TEndingPic, quads) == 0x2C ? 1 : -1];
typedef char TEndingPicRate[offsetof(TEndingPic, timing_rate) == 0xEC ? 1 : -1];
typedef char TEndingPic_size[sizeof(TEndingPic) == 0xF0 ? 1 : -1];

#endif
