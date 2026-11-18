#include "pso/system/BmlTextureList.h"
#include "pso/system/BmlResource.h"
#include "types.h"
#include "pso/unk/text_8028A714.h"

extern "C" {
u8 * get_bml_motion(void *, int);
extern u8 *green_door_bml_resource;
u8 *fn_8028A714(s32 arg0) {
    if ((void *) green_door_bml_resource != NULL) {
        return get_bml_motion(green_door_bml_resource, arg0);
    }
    return NULL;
}
u8 *fn_8028A750(s32 arg0) {
    if ((void *) green_door_bml_resource != NULL) {
        return (u8 *)TObjFish__sub_8001EDB0((BmlResource *)green_door_bml_resource, (s32)arg0);
    }
    return NULL;
}
u8 *fn_8028A78C(s32 arg0) {
    if ((void *) green_door_bml_resource != NULL) {
        return (u8 *)get_bml_model((BmlResource *)green_door_bml_resource, arg0);
    }
    return NULL;
}

}
