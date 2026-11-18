#include "types.h"
#include "pso/misc/TUnk_804CE7E8.h"

#pragma readonly_strings on

extern "C" {
const char *lbl_805D38B0 = "TWindowCheckBox";
}


extern const char *lbl_805D38B0;

void TUnk_804CE7E8::sub_80248B7C(s32 arg1) {
    m_name = lbl_805D38B0;
    this->m_20 = (s16)arg1;
}
