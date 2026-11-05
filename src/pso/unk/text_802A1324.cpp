#include "types.h"
#include "pso/unk/text_802A1324.h"
#include "pso/TAdSelectGameModeGC.h"
#include "pso/misc/TLobby.h"
#include "pso/ui/TAdSinglePlyChrSelectGC.h"
#include "pso/ui/Language.h"

struct RecoveredGlobal_802A1324_lbl_804DCB64 {
    s32 value;
    u8 remaining[0x18];
};

extern "C" {
void __ct__7TObjectFP7TObject(void *,void *);
u8 *__ct__6TMovieFP7TObjectPSclll(void *,void *,const s8 *,void (*)(s32),s32,s32,s32);
void set_movie_finished_flag(s32);
extern const s8 *opening_movie_path_table[10];
u8 *__nw__7TObjectFUl(s32);
extern RecoveredGlobal_802A1324_lbl_804DCB64 lbl_804DCB64;
extern s32 opening_movie_selector;
extern u8 *tl_00;
extern u8 *tl_01;
extern u8 opening_movie_purpose;
typedef char RecoveredGlobal_802A1324_lbl_804DCB64_size[sizeof(RecoveredGlobal_802A1324_lbl_804DCB64) == 0x1C ? 1 : -1];
u8 *create_opening_movie_sequence(u8 *object) {
    u8 *temp_r3;
    u8 *temp_r3_2;
    __ct__7TObjectFP7TObject(object, tl_01);
    *(s32 **)((s8 *)object + 0x18) = &lbl_804DCB64.value;
    TLobby::update_menu_cursor();
    if ((TAdSinglePlyChrSelectGC::get_data() == 1) && (TAdSelectGameModeGC::get_mode_data() == 1)) {
        set_movie_finished_flag(0);
        return object;
    }
    if ((s8) opening_movie_purpose == 0) {
        temp_r3 = (u8 *)(__nw__7TObjectFUl(0x4C));
        if (temp_r3 != NULL) {
            __ct__6TMovieFP7TObjectPSclll(temp_r3, tl_00, opening_movie_path_table[current_language + (opening_movie_selector * 5)], set_movie_finished_flag, 1, 1, 0);
        }
        opening_movie_selector = 1 - opening_movie_selector;
    } else {
        temp_r3_2 = (u8 *)(__nw__7TObjectFUl(0x4C));
        if (temp_r3_2 != NULL) {
            __ct__6TMovieFP7TObjectPSclll(temp_r3_2, tl_00, opening_movie_path_table[current_language], set_movie_finished_flag, 1, 1, 0);
        }
    }
    return object;
}

}
