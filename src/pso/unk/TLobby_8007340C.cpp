#include "types.h"
#include "pso/ui/window/TWindowMenu.h"
#include "pso/ui/window/TWindowSubComCard.h"

void TWindowMenu::set_loss_flag() { *(u16*)((char*)this + 0x70) |= 0x200; }
