#include "types.h"
#include "pso/misc/TLobby.h"
#include "pso/misc/TWindowSubComCard.h"

void TLobby::set_loss_flag() { *(u16*)((char*)this + 0x70) |= 0x200; }
