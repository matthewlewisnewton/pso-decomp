#ifndef PSO_TADPLYCHRSELPLATEGC_H
#define PSO_TADPLYCHRSELPLATEGC_H
#include "pso/TObject.h"
#include "types.h"

class TAdPlyChrSelPlateGC : public TObject {
public:
    virtual ~TAdPlyChrSelPlateGC();
    virtual void run_task();
    virtual void render();
public:
    s32 is_slot_value_ready(s32 i);
    void reset_selection_slots();
    f32 m_current[32][2];
    f32 m_target[32][2];
    f32 m_origin[2];
    s32 m_count;
    s32 m_active[32];
    f32 m_progress[32];
    u8 m_colors[32][4];
    u8 m_color[4];
    s32 m_frame;
    s32 m_settings;
};

typedef char TAdPlyChrSelPlateGC_size[sizeof(TAdPlyChrSelPlateGC) == 0x3B4 ? 1 : -1];
extern "C" void push_plate_position__19TAdPlyChrSelPlateGCFv(TAdPlyChrSelPlateGC *self, const f32 *position);

struct ColorLineVertex;

struct SelectionPlateColor {
    u32 packed;
};

// Some callers construct the plate in raw storage through the legacy constructor.
extern "C" void draw_selection_plate(const void *plate, const ColorLineVertex *position,
                                     SelectionPlateColor color, u32 index);

#endif
