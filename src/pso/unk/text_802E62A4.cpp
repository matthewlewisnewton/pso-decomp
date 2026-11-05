#include "types.h"
#include "pso/unk/text_802E62A4.h"
typedef struct V4_802E62A4 { s32 a, b, c, d; } V4_802E62A4;

extern V4_802E62A4 lbl_804E3A98[];
void fn_802E62A4(void) {
    V4_802E62A4 t = lbl_804E3A98[0];
    lbl_804E3A98[1].a = t.a;
    lbl_804E3A98[1].b = t.b;
    lbl_804E3A98[1].c = t.c;
    lbl_804E3A98[1].d = t.d;
    lbl_804E3A98[2].a = t.a;
    lbl_804E3A98[2].b = t.b;
    lbl_804E3A98[2].c = t.c;
    lbl_804E3A98[2].d = t.d;
}

__declspec(section ".ctors") static void *const __sinit_text_802E62A4_cpp_ref = (void *)fn_802E62A4;
