#ifndef PSO_MISC_SNAPSHOTCAPTUREABI_H
#define PSO_MISC_SNAPSHOTCAPTUREABI_H

#include "types.h"

// Opaque 0x40-byte capture storage, separate from the 0x64-byte window.
// Preserve the historical exports and word-valued address/status contracts.
// Native capture identity and the dispatch-at-0x3C lifetime protocol stay held.
struct SnapshotCaptureStorage;
extern "C" {
void free_buffer__15TWindowSnapShotFv(SnapshotCaptureStorage *);
s32 alloc_buffer__15TWindowSnapShotFPv(SnapshotCaptureStorage *);
s32 open_stream__15TWindowSnapShotFPCv(SnapshotCaptureStorage *, const void *);
s32 init__15TWindowSnapShotFPvi(SnapshotCaptureStorage *, const void *);
void reset__15TWindowSnapShotFv(SnapshotCaptureStorage *);
u8 *init_and_reset__15TWindowSnapShotFv(SnapshotCaptureStorage *);
void update_both__15TWindowSnapShotFv(SnapshotCaptureStorage *);
s32 start_capture__15TWindowSnapShotFPCv(SnapshotCaptureStorage *, const void *);
void set_mode__15TWindowSnapShotFl(SnapshotCaptureStorage *, s32);
s32 get_buffer_size__15TWindowSnapShotFv(SnapshotCaptureStorage *);
s32 get_size__15TWindowSnapShotFv(SnapshotCaptureStorage *);
s32 get_field_8__15TWindowSnapShotFv(SnapshotCaptureStorage *);
int get_width__15TWindowSnapShotFv();
int get_height__15TWindowSnapShotFv();
void init_default__15TWindowSnapShotFv();
void alloc_buffer__15TWindowSnapShotFv();
void free_shared_instance__15TWindowSnapShotFv();
const char *TWindowSnapShot__sub_802A7EAC(void);
}

s32 load_player_motion_data(void);

#endif
