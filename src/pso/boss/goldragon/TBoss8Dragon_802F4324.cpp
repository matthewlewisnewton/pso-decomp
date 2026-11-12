#include "types.h"
#include "pso/boss/goldragon/TBoss8Dragon_802F4324.h"
#include "pso/enemy/dd/TObjEneDD.h"
#include "pso/boss/goldragon/TBoss8Dragon.h"

extern "C" {

int check_demo_mode__Fv(void*);

void TBoss8Dragon::render_shadows() { if (check_demo_mode__Fv(this) == 0) { draw(); } }
int vfunc_105__12TBoss8DragonFv(void* p) { return ((TObjEneDD *)p)->get_target_info(); }

}
