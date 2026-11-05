#include "types.h"
#include "pso/enemy/TObjEneDD_800B9AF8.h"
#include "pso/enemy/TObjEneDD.h"

extern "C" {

int TObjLight__sub_801337F8(void*);
int TObjLight__sub_801337FC(void*);

    extern int lbl_805D555C;
    extern int current_scene_light;
void TObjEneDD::init_lights() { TObjLight__sub_801337F8((void*)current_scene_light); TObjLight__sub_801337FC((void*)lbl_805D555C); }

void TObjEneDD__sub_800B9B24(void) {  }
s32 TObjEneDD::clamp_frame_index(s32 arg0) {
    s32 limit;
    s32 idx;

    idx = arg0;
    limit = 0xE;
    if (TObjEneDD::check_v2_mode() != 0) {
        limit = 0x1D;
    }
    if (idx < 0) {
        idx = 0;
    } else if (idx >= limit) {
        idx = limit - 1;
    }
    return idx;
}

}
