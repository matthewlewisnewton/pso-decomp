#include "pso/TAdChrSelMovePlateGC.h"
#include "pso/ui/TAdMultiPlyChrSelectGC_802C6F88.h"
#include "pso/TMainTask.h"

extern "C" {
extern const f32 lbl_805DF60C, lbl_805DF610, lbl_805DF614, lbl_805DF618;
extern const f32 lbl_805DF604, lbl_805DF608;
extern const char *lbl_805D4190;
extern s32 chr_sel_move_plate_texture;

void TAdChrSelMovePlateGC::render() {
    if (TMainTask::get_render_pass() != 1) { draw_move_plate_quads(this); }
}
void TAdChrSelMovePlateGC::clear_entries() {
    u32 i;
    for (i = 0; i < count; i++) { opacity[i] = 0; }
    count = 0;
}
void add_plate_rect__20TAdChrSelMovePlateGCFPvPv(TAdChrSelMovePlateGC *plate, f32 *position) {
    plate->quads[plate->count].values[0] = position[0];
    plate->quads[plate->count].values[1] = position[1];
    plate->quads[plate->count].values[2] = lbl_805DF604 + position[0];
    plate->quads[plate->count].values[3] = lbl_805DF608 + position[1];
    plate->opacity[plate->count] = 0;
    plate->count++;
}
void TAdChrSelMovePlateGC::init_plate_rects() {
    s32 i;
    for (i = 0; i < 12; i++) {
        quads[i].values[4] = lbl_805DF60C;
        quads[i].values[5] = lbl_805DF610;
        quads[i].values[6] = lbl_805DF614;
        quads[i].values[7] = lbl_805DF618;
    }
}
void TAdChrSelMovePlateGC::run_task() {
    u32 i;
    for (i = 0; i < count; i++) {
        s32 v;
        opacity[i] += 0x16;
        v = opacity[i];
        if (v > 0xFF) { v = 0xFF; }
        opacity[i] = v;
    }
}
TAdChrSelMovePlateGC::~TAdChrSelMovePlateGC() {}
TAdChrSelMovePlateGC::TAdChrSelMovePlateGC(TObject *parent) : TObject(parent) {
    s32 i;
    m_name = lbl_805D4190;
    chr_sel_move_plate_texture = TAdMultiPlyChrSelectGC__sub_802C6FA8();
    mode = -1;
    count = 0;
    init_plate_rects();
    TAdChrSelMovePlateGC *owner = this;
    for (i = 0; i < 12; i++) {
        owner->other[i] = 0;
        owner->opacity[i] = 0;
    }
}
}
