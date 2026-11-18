#ifndef PSO_SYSTEM_BML_RESOURCE_H
#define PSO_SYSTEM_BML_RESOURCE_H

#include "pso/system/BmlResourceClass.h"

struct NJS_OBJECT;

extern "C" NJS_OBJECT *get_bml_model(BmlResource *resource, s32 index);

#endif
