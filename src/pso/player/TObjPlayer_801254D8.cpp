#include "types.h"
#include "pso/item/TUnk_804E355C.h"
#include "pso/object/TObject_80019A50.h"
#include "pso/player/TUnk_804A2548.h"
#include "pso/player/TObjPlayer.h"

extern "C" {

s32 has_game_join_id__13TUnk_804E355CFv();

extern f32 lbl_805DAD50;

void TUnk_804A2548::run_task() {
    f32 temp_f1;
    f32 temp_f1_2;

    if (has_game_join_id__13TUnk_804E355CFv() != 0) {
        temp_f1 = this->m_40;
        if (temp_f1 < *(f32 *)&this->unk_C4) {
            this->m_40 = (f32) (temp_f1 + lbl_805DAD50);
            temp_f1_2 = *(f32 *)&this->unk_C4;
            if (temp_f1_2 < this->m_40) {
                this->m_40 = temp_f1_2;
            }
        } else {
            queue_destruction__7TObjectFv(this);
        }
        check_hits();
    }
}

}
