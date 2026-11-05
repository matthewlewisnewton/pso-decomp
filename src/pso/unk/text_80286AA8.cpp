#include "types.h"
#include "pso/misc/TWindowSubTechnique.h"

extern "C" {
s32 get_selected_menu_value(int);
s32 TWindowSubTechnique::sub_80286AA8() {
    if ((u32) this->m_34 == 0U) {
        return 0;
    }
    if ((s32) this->m_2c == get_selected_menu_value(this->m_34)) {
        return 0;
    }
    this->m_2c = get_selected_menu_value(this->m_34);
    return 1;
}

}
