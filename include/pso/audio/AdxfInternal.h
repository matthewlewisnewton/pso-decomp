#ifndef PSO_AUDIO_ADXFINTERNAL_H
#define PSO_AUDIO_ADXFINTERNAL_H

#include "pso/system/Adxf.h"
#include <stddef.h>

struct AdxStreamFile;
struct SjRingBuffer;

struct AdxfHandle {
    s8 used;
    s8 state;
    s8 f2;
    u8 f3;
    AdxStreamFile *stream;
    SjRingBuffer *buffer;
    s32 sector_count;
    s32 byte_size;
    s32 sector_position;
    s32 read_start_sector;
    s32 read_sector_count;
    s32 sectors_read;
    void *read_destination;
    s32 read_buffer_size;
    s32 requested_read_sectors;
    s32 archive_start_sector;
    u8 pad_34[0x138 - 0x34];
};

typedef char AdxfHandleSize[sizeof(AdxfHandle) == 0x138 ? 1 : -1];
typedef char AdxfHandleByteSizeOffset[offsetof(AdxfHandle, byte_size) == 0x10 ? 1 : -1];
typedef char AdxfHandleReadDestinationOffset[offsetof(AdxfHandle, read_destination) == 0x24 ? 1 : -1];

extern "C" {
extern AdxfHandle adxf_file_handle_pool[16];
extern AdxfHandle *lobby_adxf_open_file_handle;
}

#endif
