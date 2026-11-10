#include "dolphin/os/OSAlloc.h"
#include "pso/network/NetworkConfigLifecycle.h"
#include "pso/network/NetworkInfoLoader.h"

struct Big_803F47BC;

extern "C" {
extern const u32 lbl_805E10F8;
extern u32 lbl_805D79AC;
extern u32 lbl_805D7980;
extern u32 lbl_805D7984;
extern s32 lbl_805D79B0;
extern Big_803F47BC *lobby_net_config_buffer;
extern void *lbl_805D79E0;
}

// As in request_network_info_load, the original aligns the frame to 32 bytes
// even though the body never accesses a local stack slot.
#ifdef __MWERKS__
#define NETWORK_CONFIG_FRAME_ALIGN ATTRIBUTE_ALIGN(32)
#pragma push
#pragma scheduling off
#else
#define NETWORK_CONFIG_FRAME_ALIGN
#endif
s32 TLobby__sub_803F3BF8(s32 backup_mode NETWORK_CONFIG_FRAME_ALIGN, void *buffer, u32 status) {
    lbl_805D79AC = lbl_805E10F8;
    if (get_network_config_mode() != 0) {
        return -1;
    }
    lbl_805D7980 = status;
    lbl_805D7984 = status;
    if (backup_mode != 0) {
        return -2;
    }

    get_or_set_network_config_mode(1);
    get_or_set_network_config_backup_mode(backup_mode);
    lbl_805D79B0 = 0;
    if (buffer == NULL) {
        Big_803F47BC *allocated =
            static_cast<Big_803F47BC *>(OSAlloc(get_network_config_buffer_size(backup_mode)));
        lobby_net_config_buffer = allocated;
        if (allocated == NULL) {
            return -4;
        }
        lbl_805D79B0 = 1;
    } else {
        lobby_net_config_buffer = static_cast<Big_803F47BC *>(buffer);
    }
    // The original retains this backup-buffer check after rejecting nonzero modes.
    if (backup_mode == 1) {
        lbl_805D79E0 = reinterpret_cast<u8 *>(lobby_net_config_buffer) + 0x19D4;
    }
    set_network_config_card_channel(2);
    return 0;
}
#ifdef __MWERKS__
#pragma pop
#endif
#undef NETWORK_CONFIG_FRAME_ALIGN

#pragma push
#pragma peephole off
s32 update_network_info_request(void) {
    if (get_network_config_mode() == 0) {
        return -1;
    }
    switch (network_info_load_state.request_kind) {
    case 2:
        update_network_info_load();
        break;
    case 1:
        update_network_info_exists();
        break;
    case 3:
    case 4:
        break;
    }
    return 0;
}
#pragma pop

s32 TLobby__sub_803F3D60(void) {
    if (get_network_config_mode() == 0) {
        return -1;
    }
    if (lbl_805D79B0 == 1 && lobby_net_config_buffer != NULL) {
        OSFree(lobby_net_config_buffer);
        lobby_net_config_buffer = NULL;
    }
    get_or_set_network_config_mode(0);
    get_or_set_network_config_backup_mode(0);
    set_network_config_card_channel(2);
    return 0;
}
