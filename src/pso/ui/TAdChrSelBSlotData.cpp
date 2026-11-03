#include "types.h"

struct PlateLayout {
    f32 origin[2];
    u8 color[4];
    s32 settings;
};
typedef char PlateLayout_size[sizeof(PlateLayout) == 0x10 ? 1 : -1];

extern "C" {
__declspec(section ".rodata") extern const PlateLayout chr_sel_b_slot_plate_layout = {
    {180.0f, 38.0f}, {0xBC, 0x98, 0x36, 0x00}, 0
};
__declspec(section ".rodata") extern const f32 lbl_804758E8[4][2] = {
    {434.0f, 182.0f}, {434.0f, 225.0f},
    {434.0f, 268.0f}, {434.0f, 311.0f}
};
}
