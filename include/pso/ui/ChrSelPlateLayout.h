#ifndef PSO_UI_CHRSEL_PLATE_LAYOUT_H
#define PSO_UI_CHRSEL_PLATE_LAYOUT_H

#include "types.h"
#include "pso/ui/TAdChrSelSlotGC.h"

// Argument to TAdPlyChrSelPlateGC's constructor. The original objects are
// 0x10 bytes: two floats, four color bytes, then a settings word.
struct PlateLayout {
    f32 origin[2];
    u8 color[4];
    s32 settings;
};
typedef char PlateLayout_size[sizeof(PlateLayout) == 0x10 ? 1 : -1];

extern "C" {
extern const PlateLayout chr_sel_a_slot_plate_layout;
extern const f32 lbl_80475818[4][2];
extern const CharacterSlotPosition lbl_80475838;
extern const f32 lbl_80475840[2];
extern const PlateLayout chr_sel_a_slot_plate_layout_b;
extern const f32 lbl_80475858[4][2];
extern const f32 lbl_80475878[3][2];
extern const CharacterSlotPosition lbl_80475890;
extern const CharacterSlotPosition lbl_80475898;
extern const f32 lbl_804758A0[2];
extern const f32 TAdChrSelASlotGC__data_804758A8[2];
extern const f32 TAdChrSelASlotGC__data_804758B0[2];
extern const f32 TAdChrSelASlotGC__data_804758B8[2];
extern const char lbl_804758C0[];

extern const PlateLayout chr_sel_b_slot_plate_layout;
extern const f32 lbl_804758E8[4][2];
extern const CharacterSlotPosition lbl_80475908;
extern const f32 lbl_80475910[2];
extern const char lbl_80475918[];
}

#endif
