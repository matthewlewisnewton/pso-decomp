#include "types.h"
#include "pso/item/TUnk_804A1098.h"
#include "pso/player/TObjPlayer.h"

void TUnk_804A1098::update_weapon() {
    s32 temp_r0;
    s32 temp_r4;
    s32 temp_r4_2;
    temp_r0 = this->m_1fc;
    if (temp_r0 == 2) {
        temp_r4 = *(s32 *)&this->unk_1F8;
        if (temp_r4 < 0x2AAA) {
            *(s32 *)&this->unk_1F8 = (temp_r4 + 0x888);
            if ((s32) *(s32 *)&this->unk_1F8 >= 0x2AAA) {
                *(s32 *)&this->unk_1F8 = 0x2AAA;
                this->m_1fc = 3;
            }
        }
    } else if (temp_r0 == 1) {
        temp_r4_2 = *(s32 *)&this->unk_1F8;
        if (temp_r4_2 > 0) {
            *(s32 *)&this->unk_1F8 = (temp_r4_2 - 0x444);
            if ((s32) *(s32 *)&this->unk_1F8 <= 0) {
                *(s32 *)&this->unk_1F8 = 0;
                this->m_1fc = 0;
            }
        }
    }
}
