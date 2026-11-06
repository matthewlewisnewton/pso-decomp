#include "types.h"
#include "pso/item/TUnk_804A2A58.h"

void TUnk_804A2A58::update_weapon() {
    s32 temp_r4;

    temp_r4 = this->m_1fc;
    if (temp_r4 > 0) {
        this->m_1fc = (temp_r4 - 0x888);
        *(s32 *)((s8 *)this + 0x1F8) = (s32) (*(s32 *)((s8 *)this + 0x1F8) - 0x888);
    }
}
