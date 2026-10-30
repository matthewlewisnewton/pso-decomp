#include "types.h"
#include "pso/system/BmlResourceClass.h"
#include "pso/object/TObjWarpLobby.h"
#include "pso/ui/TAdSinglePlyChrSelectGC.h"

struct Sub_801A0B38 { u8 pad[0xc]; s32 value; };

struct Obj_801A0B38 { u8 pad[0x42c]; Sub_801A0B38 *sub; };

extern "C" {
extern u8 warp_lobby_resource_descriptor[];
extern s32 TObjWarpLobby__instance;
extern s32 lbl_805D5CCC;
void TObjWarpLobby__sub_801A0B38(void);
void TObjWarpLobby::release_static() {
    delete (BmlResource *)(TObjWarpLobby__instance);
    TObjWarpLobby__instance = 0;
}
void TObjWarpLobby__sub_801A0B38(void) {
    u8 *p = (u8 *)new BmlResource(1, (BmlResourceDescriptor *)(warp_lobby_resource_descriptor), 0, 0, (void *)(0));
    TObjWarpLobby__instance = (s32)p;
    lbl_805D5CCC = ((Obj_801A0B38 *)TObjWarpLobby__instance)->sub->value;
}

}
