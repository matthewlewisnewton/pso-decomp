#include "pso/player/demo_mode.h"
#include "types.h"
#include "pso/boss/TBoss8Dragon_802F4324.h"
#include "pso/enemy/TObjEneDD.h"
#include "pso/boss/TBoss8Dragon.h"

extern "C" {


void TBoss8Dragon::render_shadows() { if (check_demo_mode() == 0) { draw(); } }
int TBoss8Dragon__sub_802F4360(void* p) { return ((TObjEneDD *)p)->get_target_info(); }

}
