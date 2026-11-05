#include "types.h"
#include "pso/unk/text_80307964.h"
#include "pso/player/TObjPlayer.h"
extern "C" {
void *__ct__6TMovieFP7TObjectPSclll(void *, void *, void *, void *, s32, s32, s32);
void *__nw__7TObjectFUl(u32);
void *__ct__7TObjectFP7TObject(void *, void *);
extern u8 lbl_80475450[];
extern u8 __vt__13TUnk_804E71A0[];
extern s32 game_difficulty_selection;
extern void *tl_00;
extern void *tl_04;
extern s32 ending_movie_active_flag;
u8 *init_ending_movie(u8 *object) {
    void *p;
    __ct__7TObjectFP7TObject(object, tl_04);
    *(void **)(object + 0x18) = __vt__13TUnk_804E71A0;
    ending_movie_active_flag = 0;
    switch (game_difficulty_selection) {
    case 0:
    case 1:
    case 2:
        p = __nw__7TObjectFUl(0x4C);
        if (p != 0) {
            __ct__6TMovieFP7TObjectPSclll(p, tl_00, lbl_80475450, (void *)TObjPlayer::disable_keyboard_control, 0, 1, 0);
        }
        break;
    case 3:
        p = __nw__7TObjectFUl(0x4C);
        if (p != 0) {
            __ct__6TMovieFP7TObjectPSclll(p, tl_00, lbl_80475450, (void *)TObjPlayer::disable_keyboard_control, 0, 0, 0);
        }
        break;
    }
    return object;
}

}
