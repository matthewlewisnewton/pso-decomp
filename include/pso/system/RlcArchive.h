#ifndef PSO_SYSTEM_RLC_ARCHIVE_H
#define PSO_SYSTEM_RLC_ARCHIVE_H

#include "types.h"

// RLC stores header and directory words in big-endian byte order.
struct RlcDirectoryEntry {
    s8 offset_be[4];
    s8 size_be[4];

    u32 get_size();
    u32 get_offset();
    u32 read_be32(const s8 *bytes);
};

struct RlcHeader {
    u8 m_00[0x10];
    s8 chunk_count_be[4];
    s8 directory_offset_be[4];
    u8 m_18[8];

    u32 get_directory_offset();
    u32 get_chunk_count();
    u32 read_be32(const s8 *bytes);
};

typedef char RlcDirectoryEntry_size[sizeof(RlcDirectoryEntry) == 8 ? 1 : -1];
typedef char RlcHeader_size[sizeof(RlcHeader) == 0x20 ? 1 : -1];

struct RlcFile {
    RlcHeader *header;
    RlcDirectoryEntry *directory;
    u8 *buffer;
    s32 buffer_size;
    u32 unknown_10;
    s32 loaded;
    s32 status;
    char filename[32];
    s32 *dispatch;

    s32 get_chunk_count();
    void locate_directory();
    void locate_header();
    void set_filename(const char *name);
    void free_buffer();
    s32 allocate_buffer();
    s32 read_file(const char *name);
    s32 measure_file(const char *name);
    void reset();
    RlcFile *initialize();
    void clear();
    s32 load(const char *name);
    void set_status(s32 value);
    s32 get_buffer_size();
    s32 has_data();
    RlcHeader *get_header();
    u8 *get_buffer();

};

extern RlcFile *shared_snapshot_capture;

typedef char RlcFileSize[sizeof(RlcFile) == 0x40 ? 1 : -1];

#endif
