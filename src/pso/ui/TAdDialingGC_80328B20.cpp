#include "pso/ui/TAdDialingGC_80328B20.h"

#include "pso/misc/TLobby_801E2F94.h"
#include "pso/ui/TAdDialingGC.h"

extern "C" {

// The rectangle coordinates are in the original read-only data contribution.
extern const ColorLineVertex lbl_804767A8[];
extern const ColorLineVertex lbl_804767B0[];
extern const ColorLineVertex lbl_804767B8[];
extern const ColorLineVertex lbl_804767C0[];

void TAdDialingGC__sub_80328B20(TAdDialingGC *) {}

void draw_dialing_rectangle(const ColorLineVertex *origin, const ColorLineVertex *extent) {
    ColorLineVertex vertices[4];
    ColorLineList rectangle;
    u32 colors[4];
    const u32 color = 0x0000008F;

    rectangle.verts = vertices;
    rectangle.colors = colors;
    rectangle.unk_8 = 0;
    rectangle.count = 4;

    rectangle.verts[0].x = origin->x;
    rectangle.verts[0].y = origin->y;
    rectangle.colors[0] = color;
    rectangle.verts[1].x = origin->x;
    rectangle.verts[1].y = origin->y + extent->y;
    rectangle.colors[1] = color;
    rectangle.verts[2].x = origin->x + extent->x;
    rectangle.verts[2].y = origin->y + extent->y;
    rectangle.colors[2] = color;
    rectangle.verts[3].x = origin->x + extent->x;
    rectangle.verts[3].y = origin->y;
    rectangle.colors[3] = color;

    rectangle.draw_tri_fan_2d( 4, 7, -120.0f);
}
}

void TAdDialingGC::draw_if_flag_set() {
    if (m_a4 & 1) {
        draw_dialing_rectangle(lbl_804767B8, lbl_804767C0);
    }
}

void TAdDialingGC::render_if_flag_set() {
    if ((m_a4 & 1) && static_cast<s32>(m_1c) == 0) {
        draw_dialing_rectangle(lbl_804767A8, lbl_804767B0);
    }
}
