#ifndef PSO_OBJECT_TOBJDFDEMO1_H
#define PSO_OBJECT_TOBJDFDEMO1_H
#include "types.h"
#include "pso/object/TObjMotion.h"

struct TObjDFDemo1Part {
    s32 model;
    s32 texlist;
    s32 motion;
};

class TObjDFDemo1 : public TObjBase {
public:
    TObjDFDemo1(TObject *parent, const Vec *pos, s32 angle);
    virtual ~TObjDFDemo1();
    virtual void run_task();
    void draw_fading_model();
    void sub_8004E068();
    virtual void render();

    void *particle_emitters[4];
    TObjDFDemo1Part body_parts[6];
    TObjDFDemo1Part zanzo_parts[2];
    Vec demo_pos;
    s32 m_10c;
    s32 timer;
    f32 m_114;
    f32 scroll;
    u8 strips[0x14];
};
typedef char TObjDFDemo1_size[sizeof(TObjDFDemo1) == 0x130 ? 1 : -1];

#endif
