#include "types.h"
#include "pso/ui/window/TWindowAddition.h"
#include "pso/ui/window/TWindowHelpItem.h"
#include "pso/ui/window/TWindowSubStatusDisp.h"

void TWindowSubStatusDisp::clear_visible_flag() { *(u16 *)&this->m_name &= 0xfffffffd; }
void TWindowHelpItem::set_flag0_bit2() { *(u16*)((char*)this + 0x0) |= 0x2; }
void TWindowAddition::set_content_scale(f32 x, f32 y) {
    content_scale[0] = x;
    content_scale[1] = y;
}
