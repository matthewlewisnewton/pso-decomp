#include "pso/system/BmlTextureList.h"
#include "pso/system/BmlResource.h"
#include "types.h"
#include "pso/unk/text_802FF028.h"

extern "C" {
extern u8 *admultisave_shared_model_resource;
u8 *fn_802FF028(s32 arg0) {
    if ((void *) admultisave_shared_model_resource != NULL) {
        return (u8 *)TObjFish__sub_8001EDB0((BmlResource *)admultisave_shared_model_resource, (s32)arg0);
    }
    return NULL;
}
u8 *fn_802FF064(s32 arg0) {
    if ((void *) admultisave_shared_model_resource != NULL) {
        return (u8 *)get_bml_model((BmlResource *)admultisave_shared_model_resource, arg0);
    }
    return NULL;
}

}
