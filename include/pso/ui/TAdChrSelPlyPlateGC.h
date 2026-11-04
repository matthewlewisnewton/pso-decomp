#ifndef PSO_UI_TADCHRSELPLYPLATEGC_H
#define PSO_UI_TADCHRSELPLYPLATEGC_H

#include "types.h"
#include "pso/TObject.h"
#include <stddef.h>

/* Multiplayer character-select plates. The constructor's name string is
   "TAdChrSelPlyPlateGC" (0x80471CE8). The vtable at 0x804E0B10 holds the dtor
   (0x802C6D64), update_selection (0x802C6AC8) and update (0x802C54C4).
   sub_802C5688 / sub_802C6660 address quads at 0x24, the alpha grid at 0x444,
   sel at 0x4AC and the cursor column at 0x4EC. */
struct TAdChrSelPlyPlateQuad {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
    f32 u0;
    f32 v0;
    f32 u1;
    f32 v1;
};

struct TAdChrSelPlyPlateGC : public TObject {
    virtual ~TAdChrSelPlyPlateGC();
    s32 unk_1c;
    s32 unk_20;
    TAdChrSelPlyPlateQuad quad[8][3];
    u8 pad_324[0x444 - 0x324];
    s32 a[4][3];
    u8 pad_474[0x4AC - 0x474];
    s32 sel[4][3];
    s32 f4DC[4];
    s32 f4EC;
    u8 pad_4f0[0x538 - 0x4F0];

    /* Callers pass this in r3 and the out pointer in r4 (0x802C58F4, 0x802C67F8,
       0x802C6B24). The body overwrites r3 on entry and never reads it. */
    void find_first_open_cell(u32 *out);
    void move_cursor(s32 x_, s32 y_, s32 dx, s32 dy, s32 depth);
    void update_option_cursor();
    void handle_dpad_input();
    s32 find_active_slot();
    void update_selection();
};

typedef char TAdChrSelPlyPlateGC_size[sizeof(TAdChrSelPlyPlateGC) == 0x538 ? 1 : -1];
typedef char TAdChrSelPlyPlateGC_off_unk_20[(offsetof(TAdChrSelPlyPlateGC, unk_20) == 0x20) ? 1 : -1];
typedef char TAdChrSelPlyPlateGC_off_quad[(offsetof(TAdChrSelPlyPlateGC, quad) == 0x24) ? 1 : -1];
typedef char TAdChrSelPlyPlateGC_off_a[(offsetof(TAdChrSelPlyPlateGC, a) == 0x444) ? 1 : -1];
typedef char TAdChrSelPlyPlateGC_off_sel[(offsetof(TAdChrSelPlyPlateGC, sel) == 0x4AC) ? 1 : -1];
typedef char TAdChrSelPlyPlateGC_off_f4EC[(offsetof(TAdChrSelPlyPlateGC, f4EC) == 0x4EC) ? 1 : -1];

extern "C" {
void *__dt__19TAdChrSelPlyPlateGCFv(void *arg0, s16 arg1);
}

// --- C functions defined in TAdChrSelPlyPlateGC.cpp ---
extern "C" {
void *__dt__19TAdChrSelPlyPlateGCFv(void *arg0, s16 arg1);
}
// --- end of C functions

#endif
