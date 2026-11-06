#include "types.h"
#include "pso/player/TObjPlayer_801BCD28.h"
#include "pso/player/TObjPlayer.h"

extern "C" {

int TObjPlayer__sub_801BEF60(void*, int);

int TObjPlayer::is_flag_set_550() { return TObjPlayer__sub_801BEF60((char*)this + 0x550, 0); }
void TObjPlayer__sub_801BCD50(void) {  }
void TObjPlayer__sub_801BCD54(void) {  }

}
