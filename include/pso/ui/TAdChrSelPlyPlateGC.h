#ifndef PSO_UI_TADCHRSELPLYPLATEGC_H
#define PSO_UI_TADCHRSELPLYPLATEGC_H

#include "types.h"
#include "pso/TObject.h"

/* Screen quad: x0, y0, x1, y1, then the texture rectangle u0, v0, u1, v1. */
struct TAdChrSelPlyPlateGCQuad {
    f32 x, y, z, w, u0, v0, u1, v1;
};

struct TAdChrSelPlyPlateGCPoint {
    f32 x, y;
};

/* Multiplayer character-select plate grid. fn_802C6F20 allocates 0x538 bytes
   for it, and its vtable (lbl_804E0B10) holds the destructor, update_selection
   and update. Rows 0-3 of quad are the 4x3 selection cells; rows 4-7, column 0,
   are each player's confirmed quad. */
struct TAdChrSelPlyPlateGC : public TObject {
    virtual ~TAdChrSelPlyPlateGC();
    void find_first_open_cell(u32 *cell);
    void move_cursor(s32 x_, s32 y_, s32 dx, s32 dy, s32 depth);
    void update_option_cursor();
    void handle_dpad_input();
    s32 find_active_slot();
    void update_selection();
    s32 f1C;
    s32 f20;
    TAdChrSelPlyPlateGCQuad quad[8][3];
    f32 cursor[3][8];
    TAdChrSelPlyPlateGCPoint home[4][3];
    u8 unk_3E4[0x444 - 0x3E4];
    s32 alpha[4][3];
    s32 col[4][3];
    f32 ox;
    f32 oy;
    s32 sel[4][3];
    s32 f4DC[4];
    s32 f4EC;
    u8 unk_4F0[0x4F8 - 0x4F0];
    s32 f4F8;
    s32 f4FC;
    s32 b[4][3];
    s32 f530;
    s32 f534;
};

typedef char TAdChrSelPlyPlateGC_size[sizeof(TAdChrSelPlyPlateGC) == 0x538 ? 1 : -1];

extern "C" {
void *__dt__19TAdChrSelPlyPlateGCFv(void *arg0, s16 arg1);
}

// --- C functions defined in TAdChrSelPlyPlateGC.cpp ---
extern "C" {
void *__dt__19TAdChrSelPlyPlateGCFv(void *arg0, s16 arg1);
}
// --- end of C functions

#endif
