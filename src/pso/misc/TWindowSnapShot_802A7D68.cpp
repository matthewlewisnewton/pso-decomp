#include "types.h"
#include "pso/misc/TWindowSnapShot_802A7D68.h"
#include "pso/misc/TWindowSnapShot.h"
#include "pso/misc/TLobby.h"

extern "C" {

int Dolphin_ARAlloc(void);

    extern int shared_snapshot_capture;
    extern int lbl_805D669C;
    extern int snapshot_aligned_buffer_size;
void TWindowSnapShot::init_default() { TLobby::aram_transfer_sync((s32)((void*)1), (u32)((void*)((TWindowSnapShot *)shared_snapshot_capture)->get_field_8()), lbl_805D669C, snapshot_aligned_buffer_size); }

void TWindowSnapShot__sub_802A7DA0(void) {  }

void TWindowSnapShot::alloc_buffer() {
    s32 name = TWindowSnapShot__sub_802A7EAC();
    snapshot_aligned_buffer_size = (TLobby::get_resource_file_size((const char *)name) + 0x1f) & 0xffffffe0;
    lbl_805D669C = Dolphin_ARAlloc();
}

}
