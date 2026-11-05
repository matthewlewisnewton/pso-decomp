#include "pso/THunterGuildWarning.h"
#include "pso/object/TObject_80019A50.h"

extern s32 THunterGuildWarning__instance;

struct HGW_802119F0 { u8 pad[0x1c]; s32 state; s32 timer; };

void THunterGuildWarning::run_task() {
    HGW_802119F0 *self = (HGW_802119F0 *)this;
    switch (self->state) {
    case 0:
    case 1:
        if (--self->timer < 0) {
            queue_destruction__7TObjectFv(self);
        }
        break;
    case 2:
        break;
    }
}

THunterGuildWarning::~THunterGuildWarning() {
    close_windows();
    THunterGuildWarning__instance = 0;
}
