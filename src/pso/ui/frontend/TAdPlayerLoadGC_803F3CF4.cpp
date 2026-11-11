#include "types.h"
#include "pso/network/NetworkInfoLoader.h"
#include "pso/ui/frontend/TAdPlayerLoadGC_803F3CF4.h"

extern "C" {
void *OSAllocFromHeap(int, u32);
extern s32 __OSCurrHeap;
extern u32 lbl_805D79AC;
extern u32 lobby_net_config_mode;
extern u32 lbl_805D7984;
extern s32 lobby_net_config_load_state;
extern u32 lobby_net_config_buffer;
extern void *lobby_net_config_card_base;
extern const u32 lbl_805E10F8;

#pragma push
#pragma scheduling off
s32 TLobby__sub_803F3BF8(s32 backup_mode ATTRIBUTE_ALIGN(32), void *buffer, u32 status) {
    lbl_805D79AC = lbl_805E10F8;
    if (get_network_config_mode() != 0) {
        return -1;
    }
    lobby_net_config_mode = status;
    lbl_805D7984 = status;
    if (backup_mode != 0) {
        return -2;
    }
    get_or_set_network_config_mode(1);
    get_or_set_network_config_backup_mode(backup_mode);
    lobby_net_config_load_state = 0;
    if (buffer == NULL) {
        void *allocated = OSAllocFromHeap(__OSCurrHeap, get_network_config_buffer_size(backup_mode));
        lobby_net_config_buffer = (u32)allocated;
        if (allocated == NULL) {
            return -4;
        }
        lobby_net_config_load_state = 1;
    } else {
        lobby_net_config_buffer = (u32)buffer;
    }
    if (backup_mode == 1) {
        lobby_net_config_card_base = (u8 *)lobby_net_config_buffer + 0x19D4;
    }
    set_network_config_card_channel(2);
    return 0;
}
#pragma pop
}

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

extern "C" {
s32 OSFreeToHeap(int, void *);

s32 TLobby__sub_803F3D60(void) {
    if (get_network_config_mode() == 0) {
        return -1;
    }
    if (((s32) lobby_net_config_load_state == 1) && ((u32) lobby_net_config_buffer != 0U)) {
        OSFreeToHeap((int)__OSCurrHeap, (void *)lobby_net_config_buffer);
        lobby_net_config_buffer = 0U;
    }
    get_or_set_network_config_mode(0);
    get_or_set_network_config_backup_mode(0);
    set_network_config_card_channel(2);
    return 0;
}

}
