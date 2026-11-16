#ifndef PSO_PROTOCOL_PACKET_BUFFER_H
#define PSO_PROTOCOL_PACKET_BUFFER_H

#include "types.h"

/* Verified cursor/length prefix of the native packet allocation. */
typedef struct B_803FADA0 { u8 *buf; u16 len; } B_803FADA0;

u8 *alloc_from_buffer(B_803FADA0 *frame, s16 length);
u32 buffer_length(B_803FADA0 *frame);

#endif
