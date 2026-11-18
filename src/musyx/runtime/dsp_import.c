#include "types.h"

extern "C" {

// salInitDsp uploads this vendor firmware from main memory to DSP IRAM.
u8 dspSlave[] ATTRIBUTE_ALIGN(32) = {
#include "musyx/dsp_image.inc"
};

u16 dspSlaveLength = sizeof(dspSlave);

}
