#include "pso/system/ArrayAllocation.h"
#include "types.h"
#include "pso/misc/TKeyBoardControl.h"
#include "pso/misc/TWindowKeyBoardBase.h"

char *TKeyBoardControl::allocate_text_copy() {
    char *out;

    out = (char *)::operator new[](((TWindowKeyBoardBase *)m_20)->get_text_buffer_size());
    ((TWindowKeyBoardBase *)m_20)->export_text(out);
    return out;
}

int TKeyBoardControl::is_keyboard_active() { return ((TWindowKeyBoardBase *)m_20)->is_active(); }
int TKeyBoardControl::is_key_active() { return ((TWindowKeyBoardBase *)m_20)->is_key_active(); }
