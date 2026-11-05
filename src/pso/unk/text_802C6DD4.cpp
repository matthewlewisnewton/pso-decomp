#include "types.h"
#include "pso/unk/text_802C6DD4.h"
#include "pso/ui/TAdMultiPlyChrSelectGC.h"
#include "pso/ui/TAdMultiPlyChrSelectGC_802C6F88.h"
#include "pso/ui/TAdPlyPltAnimCtrlGC.h"

extern "C" {
void __ct__7TObjectFP7TObject(void *, void *);
void *TAdChrSelPlyPlateGC__ct(void *, void *, void *);
void TAdMultiPlyChrSelectGC__sub_802C5F1C(void *);
void copy_vec2__28TWindowSubSymbolChatPartsSetFPv(void *, void *);
u8 *__nw__7TObjectFUl(s32);

extern char *lbl_805D3EE0;
extern s32 lbl_805D67D0;
extern s32 lbl_805D67D4;
extern s32 TAdMultiPlyChrSelectGC__select_mode;
extern s32 TAdMultiPlyChrSelectGC__selected_slot;
extern s32 TAdMultiPlyChrSelectGC__data_805D67D8;
extern f32 TAdMultiPlyChrSelectGC__data_805DE56C;
extern s32 TAdMultiPlyChrSelectGC__data_804E0A48[];
extern u32 ad_chr_sel_ply_plate_instance;
extern s32 tl_clipout;

/* Offsets taken from the original stores: name at 0, vtable at 0x18, unk_1c at
   0x1C, unk_20 at 0x20, cursor alpha at 0x444, cursor color at 0x474, position
   at 0x4A4, sel at 0x4AC, unk_4dc at 0x4DC, cursor column and the three words
   after it at 0x4EC, unk_500 at 0x500, unk_534 at 0x534. */
struct PlateInit {
    char *name;
    u8 pad04[0x14];
    s32 *vtable;
    s32 unk_1c;
    s32 unk_20;
    u8 pad24[0x444 - 0x24];
    s32 cursor_alpha[4][3];
    s32 cursor_color[4][3];
    u8 pos[8];
    s32 sel[4][3];
    s32 unk_4dc[3];
    s32 unk_4e8;
    s32 cursor_col;
    s32 unk_4f0;
    s32 unk_4f4;
    s32 unk_4f8;
    s32 unk_4fc;
    s32 unk_500[4][3];
    u8 pad530[0x534 - 0x530];
    s32 unk_534;
};

void *TAdChrSelPlyPlateGC__ct(void *self, void *parent, void *pos) {
    PlateInit *plate = (PlateInit *)self;
    u32 i;
    u32 j;
    f32 zero;
    /* The original keeps one base for the whole .data block and reaches the
       vtable, the shown flags, and the tag alphas as +200, +152, and +168. */
    u8 *base = (u8 *)TAdMultiPlyChrSelectGC__data_804E0A48;
    s32 *vtable = (s32 *)(base + 200);
    s32 *shown;
    f32 *alpha;

    __ct__7TObjectFP7TObject(self, parent);
    plate->vtable = vtable;
    plate->name = lbl_805D3EE0;
    lbl_805D67D0 = TAdMultiPlyChrSelectGC__sub_802C6FA8();
    lbl_805D67D4 = TAdMultiPlyChrSelectGC::get_global_6700();
    TAdMultiPlyChrSelectGC__select_mode = 0;
    copy_vec2__28TWindowSubSymbolChatPartsSetFPv(plate->pos, pos);
    plate->unk_1c = -1;
    plate->unk_4e8 = 0;
    TAdMultiPlyChrSelectGC__selected_slot = 0;
    TAdMultiPlyChrSelectGC__data_805D67D8 = 0;
    plate->cursor_col = 0;
    plate->unk_4f0 = 0;
    plate->unk_4f4 = 0;
    plate->unk_4f8 = 0;
    plate->unk_4fc = 0;
    plate->unk_20 = TAdMultiPlyChrSelectGC__data_805D67D8;
    plate->unk_534 = 1;
    TAdMultiPlyChrSelectGC__sub_802C5F1C(self);
    zero = TAdMultiPlyChrSelectGC__data_805DE56C;
    shown = (s32 *)(base + 152);
    alpha = (f32 *)(base + 168);
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 3; j++) {
            u8 *col = (u8 *)plate + j * 4;
            ((s32 *)(col + 0x474))[i * 3] = 0;
            ((s32 *)(col + 0x444))[i * 3] = 0;
            ((s32 *)(col + 0x500))[i * 3] = 0;
            ((s32 *)(col + 0x4AC))[i * 3] = 0;
            *(s32 *)(col + 0x4DC) = 0;
        }
        shown[i] = 0;
        alpha[i] = zero;
    }
    TAdMultiPlyChrSelectGC::reset_slot_selection_table();
    TAdPlyPltAnimCtrlGC::get_instance(tl_clipout);
    return self;
}

u8 *fn_802C6F20(s32 arg0, s32 arg1) {
    u8 *temp_r3;
    u8 *var_r0;
    if ((void *)ad_chr_sel_ply_plate_instance != NULL) {
        return NULL;
    }
    temp_r3 = (u8 *)(__nw__7TObjectFUl(0x538));
    var_r0 = temp_r3;
    if (var_r0 != NULL) {
        var_r0 = (u8 *)(TAdChrSelPlyPlateGC__ct(temp_r3, (void *)arg0, (void *)arg1));
    }
    ad_chr_sel_ply_plate_instance = (u32)var_r0;
    return var_r0;
}

}
