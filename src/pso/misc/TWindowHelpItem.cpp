#include "types.h"
#include "pso/misc/TWindowAddition.h"
#include "pso/misc/TWindowHelpItem.h"
#include "pso/misc/TWindowSubStatusDisp.h"

void TWindowSubStatusDisp::clear_visible_flag() { *(u16 *)&this->m_name &= 0xfffffffd; }
void TWindowHelpItem::set_flag0_bit2() { *(u16*)((char*)this + 0x0) |= 0x2; }
void TWindowAddition::set_position_xy(f32 a, f32 b) { m_60 = a; m_64 = b; }
