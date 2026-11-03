#include "types.h"

struct PlateLayout {
    f32 origin[2];
    u8 color[4];
    s32 settings;
};
typedef char PlateLayout_size[sizeof(PlateLayout) == 0x10 ? 1 : -1];

extern "C" {
__declspec(section ".rodata") extern const PlateLayout chr_sel_a_slot_plate_layout_b = {
    {180.0f, 38.0f}, {0x36, 0xBC, 0x30, 0x01}, 0
};
__declspec(section ".rodata") extern const f32 lbl_80475858[4][2] = {
    {28.0f, 182.0f}, {28.0f, 225.0f}, {28.0f, 268.0f}, {28.0f, 311.0f}
};
__declspec(section ".rodata") extern const f32 lbl_80475878[3][2] = {
    {234.0f, 182.0f}, {234.0f, 225.0f}, {234.0f, 268.0f}
};
}
