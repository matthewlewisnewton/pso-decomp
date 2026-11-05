#include "types.h"
#include "pso/unk/text_802FF028.h"

extern "C" {
u8 * TObjFish__sub_8001EDB0(void *, int);
extern u8 *admultisave_shared_model_resource;
u8 * get_bml_model(void *, int);
u8 *fn_802FF028(s32 arg0) {
    if ((void *) admultisave_shared_model_resource != NULL) {
        return TObjFish__sub_8001EDB0(admultisave_shared_model_resource, arg0);
    }
    return NULL;
}
u8 *fn_802FF064(s32 arg0) {
    if ((void *) admultisave_shared_model_resource != NULL) {
        return get_bml_model(admultisave_shared_model_resource, arg0);
    }
    return NULL;
}

}
