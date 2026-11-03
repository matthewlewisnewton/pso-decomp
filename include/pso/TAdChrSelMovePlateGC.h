#ifndef PSO_TADCHRSELMOVEPLATEGC_H
#define PSO_TADCHRSELMOVEPLATEGC_H
#include "pso/TObject.h"
#include "types.h"

struct MovePlateQuad { f32 values[8]; };
class TAdChrSelMovePlateGC : public TObject {
public:
    TAdChrSelMovePlateGC(TObject *parent);
    virtual ~TAdChrSelMovePlateGC();
    virtual void run_task();
    virtual void render();
    void clear_entries();
    void init_plate_rects();
    u8 reserved_1c[4];
    u32 count;
    s32 mode;
    MovePlateQuad quads[12];
    s32 opacity[12];
    s32 other[12];
};
typedef char TAdChrSelMovePlateGC_size[sizeof(TAdChrSelMovePlateGC) == 0x208 ? 1 : -1];
extern "C" {
// The legacy interface takes a mutable pointer, but only reads the pair.
void add_plate_rect__20TAdChrSelMovePlateGCFPvPv(TAdChrSelMovePlateGC *plate, f32 *position);
void draw_move_plate_quads(TAdChrSelMovePlateGC *plate);
}
#endif
