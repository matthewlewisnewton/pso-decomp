#include "pso/misc/TUnk_804CF0B8.h"
#include "pso/misc/TWindowCtrl.h"
#include "pso/system/ArrayAllocation.h"

TUnk_804CF0B8::~TUnk_804CF0B8() {
    if (is_flag_set() != 0) {
        clear_visible_flag();
        TWindowCtrl::release_slot(&m_73);
    }
    if (name != NULL) {
        ::operator delete[](name);
        name = NULL;
    }
}
