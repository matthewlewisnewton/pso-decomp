#include "types.h"
#include "pso/misc/TUnk_804D0618.h"
#include "pso/misc/TWindowSubStatusDisp.h"
#include "pso/misc/TWindowSubItem.h"

int TWindowSubStatusDisp::is_flag_4_set() { return *(u16 *)&this->m_name & 0x4; }
int TUnk_804D0618::get_flag() { return (this->m_70 >> 6) & 0x1; }
