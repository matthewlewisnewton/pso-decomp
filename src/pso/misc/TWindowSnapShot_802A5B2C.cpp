#include "pso/system/ArrayAllocation.h"
#include "pso/system/RlcArchive.h"
#include "types.h"
#include "pso/misc/TWindowSnapShot_802A5B2C.h"
#include "pso/system/memory.h"
#include "pso/misc/SnapshotCaptureAbi.h"
#include "pso/misc/TGStream.h"
#include "pso/misc/TLobby.h"

struct RecoveredGlobal_802A5F24_lbl_804DD098 {
    s32 value;
    u8 remaining[0xC];
};

extern "C" {
s32 strncpy(void *, const void *, int);
s32 strcpy(void *, const void *);
s32 strlen(const void *);

extern s32 lbl_804DD098[];

s32 memset(void *, int, int);

}

u32 RlcDirectoryEntry::get_size() { return read_be32(size_be); }
u32 RlcDirectoryEntry::get_offset() { return read_be32(offset_be); }
u32 RlcDirectoryEntry::read_be32(const s8 *bytes) {
    // Keep the u64 byte conversions and direct lane masks: GC 2.6 needs
    // these lifetimes to retain the byte extensions and accumulator copy.
    s64 result = (u32)bytes[0] << 24;
    result |= (u32)__rlwinm((u32)(u64)bytes[1], 16, 8, 15);
    result |= (u32)__rlwinm((u32)(u64)bytes[2], 8, 16, 23);
    result |= (u32)(u64)bytes[3] & 0xFF;
    return (u32)result;
}

u32 RlcHeader::get_directory_offset() { return read_be32(directory_offset_be); }
u32 RlcHeader::get_chunk_count() { return read_be32(chunk_count_be); }
u32 RlcHeader::read_be32(const s8 *bytes) {
    // Use the same unsigned byte lanes and widening as the directory reader.
    s64 result = (u32)bytes[0] << 24;
    result |= (u32)__rlwinm((u32)(u64)bytes[1], 16, 8, 15);
    result |= (u32)__rlwinm((u32)(u64)bytes[2], 8, 16, 23);
    result |= (u32)(u64)bytes[3] & 0xFF;
    return (u32)result;
}

s32 fn_802A5C3C(u32 *arg0) {
    u32 temp_r0;
    temp_r0 = *arg0;
    if (temp_r0 == 0U) {
        set_mode__15TWindowSnapShotFl((SnapshotCaptureStorage *)arg0, 7);
        return -1;
    }
    return ((RlcHeader *)temp_r0)->get_chunk_count();
}

void fn_802A5C7C(void *arg0) {
    *(s32 *)((s8 *)arg0 + 4) = (s32) (*(s32 *)((s8 *)arg0 + 8) + ((RlcHeader *)(*(s32 *)((s8 *)arg0 + 0)))->get_directory_offset());
}
void fn_802A5CB8(void* p) { *(u32*)((char*)p + 0x0) = *(u32*)((char*)p + 0x8); }

void fn_802A5CC4(u8 *arg0, const void *name) {
    if (strlen(name) > 0x1F) {
        strncpy(arg0 + 0x1C, name, 0x1F);
        *(s8 *)((s8 *)arg0 + 0x3B) = 0;
        return;
    }
    strcpy(arg0 + 0x1C, name);
}

void free_buffer__15TWindowSnapShotFv(SnapshotCaptureStorage *capture) {
    if (*(void **)((u8 *)capture + 8) != NULL) {
        ::operator delete[](*(void **)((u8 *)capture + 8));
        *(void **)((u8 *)capture + 8) = 0;
    }
}

s32 alloc_buffer__15TWindowSnapShotFPv(SnapshotCaptureStorage *capture) {
    *(u32 *)((s8 *)capture + 8) = (u32)::operator new[](get_buffer_size__15TWindowSnapShotFv(capture));
    if ((u32) *(u32 *)((s8 *)capture + 8) == 0U) {
        set_mode__15TWindowSnapShotFl(capture, 4);
        return 0;
    }
    return 1;
}
s32 open_stream__15TWindowSnapShotFPCv(SnapshotCaptureStorage *capture, const void *name) {
    *(s32 *)((u8 *)capture + 0xC) = TGStream::read_whole_file(name, (u8 *)*(void **)((u8 *)capture + 8));
    if (TWindowSnapShot__sub_802A605C((u8 *)capture) == 0) {
        set_mode__15TWindowSnapShotFl(capture, 2);
        free_buffer__15TWindowSnapShotFv(capture);
        return 0;
    }
    return 1;
}
s32 init__15TWindowSnapShotFPvi(SnapshotCaptureStorage *capture, const void *name) {
    *(s32 *)((u8 *)capture + 0xC) = TLobby::get_resource_file_size(name);
    if (TWindowSnapShot__sub_802A605C((u8 *)capture) == 0) {
        set_mode__15TWindowSnapShotFl(capture, 1);
        return 0;
    }
    return 1;
}
void reset__15TWindowSnapShotFv(SnapshotCaptureStorage *capture) {
    u8 *arg0 = (u8 *)capture;
    *(s32 *)capture = 0;
    *(s32 *)((u8 *)capture + 4) = 0;
    memset((u8 *)capture + 0x1C, 0, 0x20);
    *(s32 *)((u8 *)capture + 8) = 0;
    *(s32 *)((u8 *)capture + 0xC) = 0;
    *(s32 *)((u8 *)capture + 0x14) = 0;
    *(s32 *)((s8 *)arg0 + 0x18) = 0;
}
void *TWindowSnapShot__sub_802A5EDC(void *arg0, s16 arg1) {
    if (arg0 != NULL) {
        *(s32 **)((s8 *)arg0 + 0x3C) = lbl_804DD098;
        if (arg1 > 0) {
            ::operator delete(arg0);
        }
    }
    return arg0;
}

typedef char RecoveredGlobal_802A5F24_lbl_804DD098_size[sizeof(RecoveredGlobal_802A5F24_lbl_804DD098) == 0x10 ? 1 : -1];
u8 *init_and_reset__15TWindowSnapShotFv(SnapshotCaptureStorage *capture) {
    u8 *arg0 = (u8 *)capture;
    *(s32 **)((u8 *)capture + 0x3C) = &(*(RecoveredGlobal_802A5F24_lbl_804DD098 *)&lbl_804DD098).value;
    reset__15TWindowSnapShotFv(capture);
    return arg0;
}

void update_both__15TWindowSnapShotFv(SnapshotCaptureStorage *capture) { free_buffer__15TWindowSnapShotFv(capture); reset__15TWindowSnapShotFv(capture); }
s32 start_capture__15TWindowSnapShotFPCv(SnapshotCaptureStorage *capture, const void *name) {
    if (name == NULL) {
        set_mode__15TWindowSnapShotFl(capture, 3);
        return 0;
    }
    if (init__15TWindowSnapShotFPvi(capture, name) == 0) {
        return 0;
    }
    if (alloc_buffer__15TWindowSnapShotFPv(capture) == 0) {
        return 0;
    }
    if (open_stream__15TWindowSnapShotFPCv(capture, name) == 0) {
        return 0;
    }
    fn_802A5CB8(capture);
    fn_802A5C7C(capture);
    fn_802A5CC4((u8 *)capture, name);
    *(s32 *)((u8 *)capture + 0x14) = 1;
    return 1;
}
int get_width__15TWindowSnapShotFv() { return 32; }
void set_mode__15TWindowSnapShotFl(SnapshotCaptureStorage *capture, s32 v) { *(s32*)((char*)capture + 0x18) = v; }
s32 get_buffer_size__15TWindowSnapShotFv(SnapshotCaptureStorage *capture) { return *(s32 *)((u8 *)capture + 0xC); }
s32 TWindowSnapShot__sub_802A605C(u8 *arg0) {
    return (u8) (*(s32 *)((s8 *)arg0 + 0xC) != 0);
}
void fn_802A6070(void* p, s32 v) { *(s32*)((char*)p + 0x4) = v; }
void fn_802A6078(void* p, s32 v) { *(s32*)((char*)p + 0x0) = v; }
