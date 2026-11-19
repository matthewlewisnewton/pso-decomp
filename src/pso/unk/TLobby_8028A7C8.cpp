#include "pso/render/GvmTextureArchive.h"
#include "pso/system/BmlResource.h"
#include "types.h"
#include "pso/unk/TLobby.h"
#include "pso/ui/frontend/TAdSinglePlyChrSelectGC.h"

extern "C" {

s32 release_texture_list(void*);

void *green_door_bml_resource;
GinjaTextureList *green_door_texture_handle;

void TLobby::free_shared_objects() {
    if (green_door_texture_handle != NULL) {
        release_texture_list(green_door_texture_handle);
        TAdSinglePlyChrSelectGC::safe_free((u32)green_door_texture_handle);
        green_door_texture_handle = NULL;
    }
    if (green_door_bml_resource != NULL) {
        delete (BmlResource *)green_door_bml_resource;
        green_door_bml_resource = NULL;
    }
}

}
