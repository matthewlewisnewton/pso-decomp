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
   for it. Rows 0-3 of quad are the 4x3 selection cells; rows 4-7, column 0,
   are each player's confirmed quad. */
struct TAdChrSelPlyPlateGC : public TObject {
    TAdChrSelPlyPlateGC(TObject *parent, const TAdChrSelPlyPlateGCPoint *initial_origin);
    virtual ~TAdChrSelPlyPlateGC();
    virtual void run_task();
    virtual void render();
    void draw_selection_cursors();
    void find_first_open_cell(u32 *cell);
    void move_cursor(s32 x_, s32 y_, s32 dx, s32 dy, s32 depth);
    void update_option_cursor();
    void handle_dpad_input();
    s32 find_active_slot();
    s32 f1C;
    s32 f20;
    TAdChrSelPlyPlateGCQuad quad[8][3];
    f32 cursor[3][8];
    TAdChrSelPlyPlateGCPoint home[4][3];
    u8 unk_3E4[0x444 - 0x3E4];
    s32 alpha[4][3];
    s32 col[4][3];
    TAdChrSelPlyPlateGCPoint origin;
    s32 sel[4][3];
    s32 f4DC[3];
    s32 f4E8;
    s32 f4EC;
    s32 f4F0;
    s32 f4F4;
    s32 f4F8;
    s32 f4FC;
    s32 b[4][3];
    s32 f530;
    s32 f534;
};

typedef char TAdChrSelPlyPlateGC_size[sizeof(TAdChrSelPlyPlateGC) == 0x538 ? 1 : -1];

extern "C" {
extern TAdChrSelPlyPlateGC *ad_chr_sel_ply_plate_instance;
TAdChrSelPlyPlateGC *fn_802C6F20(TObject *parent, const TAdChrSelPlyPlateGCPoint *initial_origin);
}

#endif
