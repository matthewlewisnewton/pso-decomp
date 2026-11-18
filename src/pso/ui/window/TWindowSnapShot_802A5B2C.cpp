#include "pso/system/RlcArchive.h"
#include "pso/system/ArrayAllocation.h"
#include "types.h"
#include "pso/ui/window/TWindowSnapShot_802A5B2C.h"
#include "pso/system/memory.h"
#include "pso/ui/window/TWindowSnapShot.h"
#include "pso/system/TGStream.h"
#include "pso/unk/TLobby.h"

#include <string.h>

extern "C" s32 lbl_804DD098[];

u32 RlcDirectoryEntry::get_size() { return read_be32(size_be); }
u32 RlcDirectoryEntry::get_offset() { return read_be32(offset_be); }
u32 RlcDirectoryEntry::read_be32(const s8 *bytes) {
    // Keep the u64 byte conversions and direct lane masks: GC 2.6 needs
    // these lifetimes to retain the byte extensions and accumulator copy.
    s64 result = (u32)bytes[0] << 24;
    result |= (((u32)(u64)bytes[1] << 16) & 0x00FF0000);
    result |= (((u32)(u64)bytes[2] << 8) & 0x0000FF00);
    result |= (u32)(u64)bytes[3] & 0xFF;
    return (u32)result;
}

u32 RlcHeader::get_directory_offset() { return read_be32(directory_offset_be); }
u32 RlcHeader::get_chunk_count() { return read_be32(chunk_count_be); }
u32 RlcHeader::read_be32(const s8 *bytes) {
    // Use the same unsigned byte lanes and widening as the directory reader.
    s64 result = (u32)bytes[0] << 24;
    result |= (((u32)(u64)bytes[1] << 16) & 0x00FF0000);
    result |= (((u32)(u64)bytes[2] << 8) & 0x0000FF00);
    result |= (u32)(u64)bytes[3] & 0xFF;
    return (u32)result;
}

s32 RlcFile::get_chunk_count() {
    if (header == NULL) {
        set_status(7);
        return -1;
    }
    return header->get_chunk_count();
}

void RlcFile::locate_directory() {
    directory = (RlcDirectoryEntry *)(buffer + header->get_directory_offset());
}

void RlcFile::locate_header() {
    header = (RlcHeader *)buffer;
}

void RlcFile::set_filename(const char *name) {
    if ((s32)strlen(name) > 31) {
        strncpy(filename, name, 31);
        filename[31] = 0;
        return;
    }
    strcpy(filename, name);
}

void RlcFile::free_buffer() {
    if (buffer != NULL) {
        ::operator delete[](buffer);
        buffer = NULL;
    }
}

s32 RlcFile::allocate_buffer() {
    buffer = (u8 *)::operator new[](get_buffer_size());
    if (buffer == NULL) {
        set_status(4);
        return 0;
    }
    return 1;
}

s32 RlcFile::read_file(const char *name) {
    buffer_size = TGStream::read_whole_file(name, buffer);
    if (!has_data()) {
        set_status(2);
        free_buffer();
        return 0;
    }
    return 1;
}

s32 RlcFile::measure_file(const char *name) {
    buffer_size = TGStream::get_resource_file_size((const char *)name);
    if (!has_data()) {
        set_status(1);
        return 0;
    }
    return 1;
}

void RlcFile::reset() {
    header = NULL;
    directory = NULL;
    memset(filename, 0, sizeof(filename));
    buffer = NULL;
    buffer_size = 0;
    loaded = 0;
    status = 0;
}

void *TWindowSnapShot__sub_802A5EDC(void *arg0, s16 arg1) {
    if (arg0 != NULL) {
        ((RlcFile *)arg0)->dispatch = lbl_804DD098;
        if (arg1 > 0) {
            ::operator delete(arg0);
        }
    }
    return arg0;
}

RlcFile *RlcFile::initialize() {
    dispatch = lbl_804DD098;
    reset();
    return this;
}

void RlcFile::clear() {
    free_buffer();
    reset();
}

s32 RlcFile::load(const char *name) {
    if (name == NULL) {
        set_status(3);
        return 0;
    }
    if (!measure_file(name)) {
        return 0;
    }
    if (!allocate_buffer()) {
        return 0;
    }
    if (!read_file(name)) {
        return 0;
    }
    locate_header();
    locate_directory();
    set_filename(name);
    loaded = 1;
    return 1;
}

int TWindowSnapShot::get_width() { return 32; }
void RlcFile::set_status(s32 value) { status = value; }
s32 RlcFile::get_buffer_size() { return buffer_size; }
s32 RlcFile::has_data() { return (u8)(buffer_size != 0); }
void fn_802A6070(void* p, s32 v) { *(s32*)((char*)p + 0x4) = v; }
void fn_802A6078(void* p, s32 v) { *(s32*)((char*)p + 0x0) = v; }
