#ifndef PSO_ITEM_TITEMMENUCTRL_80115AF0_H
#define PSO_ITEM_TITEMMENUCTRL_80115AF0_H

#include "types.h"

void advance_angle_wrap(s32 *value, s32 step);
class TObject;
class TEffStarLight2D;

// The opaque position/parameter boundary follows the shared effect constructor.
TEffStarLight2D *spawn_star_light_2d(void *position, void *parameters, TObject *parent);

#endif
