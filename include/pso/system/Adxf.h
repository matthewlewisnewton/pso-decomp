#ifndef PSO_SYSTEM_ADXF_H
#define PSO_SYSTEM_ADXF_H

#include "types.h"

struct AdxfHandle;

extern "C" {
void ADXF_Close(AdxfHandle *file);
s32 ADXF_Stop(AdxfHandle *file);
}

#endif
