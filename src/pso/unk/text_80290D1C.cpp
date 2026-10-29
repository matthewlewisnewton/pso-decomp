#include "types.h"
#include "pso/unk/text_80290D1C.h"
#include "pso/player/TObjPlayer.h"

extern "C" {
__declspec(section ".rodata") s32 creation_ruler_line_vertices[96] = {
    -1056964608, 0, 0, 1090519040, 0, 0, -1056964608, 1092616192,
    0, 1090519040, 1092616192, 0, -1058013184, 1093664768, 0, 1089470464,
    1093664768, 0, -1058013184, 1094713344, 0, 1089470464, 1094713344, 0,
    -1058013184, 1095761920, 0, 1089470464, 1095761920, 0, -1058013184, 1096810496,
    0, 1089470464, 1096810496, 0, -1056964608, 1097859072, 0, 1090519040,
    1097859072, 0, -1058013184, 1098907648, 0, 1089470464, 1098907648, 0,
    -1058013184, 1099431936, 0, 1089470464, 1099431936, 0, -1058013184, 1099956224,
    0, 1089470464, 1099956224, 0, -1058013184, 1100480512, 0, 1089470464,
    1100480512, 0, -1056964608, 1101004800, 0, 1090519040, 1101004800, 0,
    -1058013184, 1101529088, 0, 1089470464, 1101529088, 0, -1058013184, 1102053376,
    0, 1089470464, 1102053376, 0, -1058013184, 1102577664, 0, 1089470464,
    1102577664, 0, -1058013184, 1103101952, 0, 1089470464, 1103101952, 0,
};
}


struct Desc_80290D1C { void *verts; u32 *colors; int start; int count; };

extern "C" {
s32 draw_line_list(void *, int, int);
s32 __cvt_fp2unsigned(f32);
}
extern s32 creation_ruler_line_vertices[96];
extern u32 creation_ruler_line_colors[4];
extern s32 lbl_804DA98C[];
void draw_creation_ruler_lines(f32 farg0) {
    Desc_80290D1C d;
    u32 colors[32];
    u32 c;
    s32 i;
    c = ((u32)__cvt_fp2unsigned(24.0f * farg0) << 24) | 0xFF0000 | 0xFFA0;
    for (i = 0; i < 32; i++) {
        colors[i] = c;
    }
    d.verts = creation_ruler_line_vertices;
    d.colors = colors;
    d.start = 0;
    d.count = 32;
    draw_line_list(&d, 0x10, 5);
    c = __cvt_fp2unsigned(64.0f * farg0) | 0x40400000 | 0x4000;
    creation_ruler_line_colors[0] = creation_ruler_line_colors[1] = c;
    ((TObjPlayer *)lbl_804DA98C)->draw_tri_fan_3d(4, 7);
}
