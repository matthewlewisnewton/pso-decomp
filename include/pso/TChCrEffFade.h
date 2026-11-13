#ifndef PSO_TCHCREFFFADE_H
#define PSO_TCHCREFFFADE_H
#include "pso/TObject.h"
#include "types.h"

class TChCrEffFade : public TObject {
public:
    TChCrEffFade(s32 direction, s32 duration, s32 mode);
    virtual ~TChCrEffFade();
    virtual void run_task();
    virtual void render();
    void update_fade();
    void draw_fade_strip(f32 opacity);

private:
    s32 m_direction; // 0x1C: +1 or -1
    s32 m_duration;  // 0x20: includes the three opaque frames
    s32 m_frame;     // 0x24
    f32 m_opacity;   // 0x28
    s32 m_mode;      // 0x2C: plain or layered rendering
};

#endif
