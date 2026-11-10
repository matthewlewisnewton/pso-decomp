#include "types.h"
#include "pso/misc/TWindowKeyBoardBase.h"
#include "pso/misc/TWindowKeyBoardHard.h"
#include "pso/misc/TKeyBoardControl_8025CB70.h"
#include "pso/ui/Language.h"

void TWindowKeyBoardHard::reset_composer_input_flags() {
    if (m_70 != 0U) {
        m_60 |= 0x40;
        ((TWindowKeyBoardBase *)m_70)->set_input_flags_12();
        switch (current_language) {
        case LANGUAGE_JAPANESE:
        case LANGUAGE_ENGLISH:
            break;
        case LANGUAGE_GERMAN:
        case LANGUAGE_FRENCH:
        case LANGUAGE_SPANISH:
            m_6c = 7;
            break;
        }
    }
}
