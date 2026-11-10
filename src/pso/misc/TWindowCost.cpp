#include "pso/misc/TWindowCost.h"

extern const char *TWindowCost__class_name;

TWindowCost::~TWindowCost() {}

TWindowCost::TWindowCost(void *position, s32 client, s32 text)
    : TWindowMeseta(position, client, text) {
    m_name = TWindowCost__class_name;
    fn_803094E8(this, 0);
}
