#ifndef PSO_SYSTEM_TGSTREAM_H
#define PSO_SYSTEM_TGSTREAM_H

#include "pso/system/GslArchive.h"
#include <stddef.h>

struct TGStreamPrefix {
    char name[0x20];
    s32 adxf_handle;
    s32 direct_read_mode;
    GslArchiveEntry *archive_entry;
};
typedef char TGStreamPrefixExtent[sizeof(TGStreamPrefix) == 0x2C ? 1 : -1];
typedef char TGStreamHandleOffset[offsetof(TGStreamPrefix, adxf_handle) == 0x20 ? 1 : -1];
typedef char TGStreamReadModeOffset[offsetof(TGStreamPrefix, direct_read_mode) == 0x24 ? 1 : -1];
typedef char TGStreamEntryOffset[offsetof(TGStreamPrefix, archive_entry) == 0x28 ? 1 : -1];

extern "C" {
TGStreamPrefix *open__8TGStreamFPvPvi(TGStreamPrefix *stream, void *name, s32 direct_read_mode);
TGStreamPrefix *destroy_gstream(TGStreamPrefix *stream, s16 delete_storage);
void read_sectors_sync__8TGStreamFll(TGStreamPrefix *stream, s32 sector_count, s32 destination);
s32 read_data__8TGStreamFPUcl(TGStreamPrefix *stream, u8 *destination, s32 byte_count);
void reset__8TGStreamFv(void);
void reset_gstream_buffer(void);
}
s32 get_gstream_buffered_bytes(void);
s32 refill_gstream_buffer(s32 adxf_handle);
extern "C" {
int get_gstream_file_size(void);
}
void reset_gstream_globals(void);
extern u8 gstream_sector_buffer[0x2000];

extern "C" {
void TGStream__sub_800FDD64(void);
void TItemDrop__sub_800FE2D8(void);
}
void align_gstream_read_offset(void *self, s32 n);
extern "C" {
void close_gsl_archive(void);
TGStreamPrefix *destroy_gstream(TGStreamPrefix *arg0, s16 arg1);
}
GslArchiveEntry *find_gsl_entry(void *name);
s32 get_gstream_buffered_bytes(void);
extern "C" {
int get_gstream_file_size(void);
void load_area_gsl(void);
TGStreamPrefix *open__8TGStreamFPvPvi(TGStreamPrefix *arg0, void *file, s32 arg2);
void open_gsl_archive(char *name);
}
s32 refill_gstream_buffer(s32 arg0);
extern "C" {
void reset_gstream_buffer(void);
}
void reset_gstream_globals(void);

// --- C functions defined in TGStream.cpp ---
extern "C" {
void TGStream__sub_800FDD64(void);
void TItemDrop__sub_800FE2D8(void);
void close_gsl_archive(void);
TGStreamPrefix *destroy_gstream(TGStreamPrefix *g_stream_prefix, s16 arg1);
int get_gstream_file_size(void);
void load_area_gsl(void);
void open_gsl_archive(char *name);
void reset_gstream_buffer(void);
}
// --- end of C functions

#endif
