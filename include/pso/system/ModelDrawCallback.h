#ifndef PSO_SYSTEM_MODELDRAWCALLBACK_H
#define PSO_SYSTEM_MODELDRAWCALLBACK_H

#include "types.h"

typedef s32 (*ModelDrawCallback)(void *model);

struct ModelDrawContext {
    u8 prefix[0xC];
    ModelDrawCallback draw;
};

extern "C" {
extern ModelDrawContext * const model_draw_context;
s32 draw_ginja_model_lists(void *model);
}

#endif
