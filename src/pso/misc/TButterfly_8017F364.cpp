#include "types.h"
#include "pso/system/BmlResourceClass.h"
#include "pso/misc/TButterfly_8017F364.h"
#include "pso/system/vector.h"
#include "pso/misc/TButterfly.h"
#include "pso/system/BmlResourceDescriptor.h"
#include "pso/player/TObjPlayer.h"

extern "C" {

void __ct__8TObjBaseFP7TObject(void *);
void *__nw__7TObjectFUl(int);

extern s32 __vt__10TButterfly[];
extern void *TButterfly__name;

void *TButterfly__ct(void *butterfly, void *arg1, void *arg2) {
    __ct__8TObjBaseFP7TObject(butterfly);
    *(s32 **)((s8 *)butterfly + 0x18) = __vt__10TButterfly;
    *(void * *)&((TButterfly *)butterfly)->m_name = TButterfly__name;
    VecCopy((Vec *)((char *)butterfly + 56), (const Vec *)((char *)arg2 + 12));
    copy_xyz((char *)butterfly + 92, (void *)((char *)arg2 + 24));
    VecCopy((Vec *)((char *)butterfly + 104), (const Vec *)((char *)arg2 + 36));
    ((TButterfly *)butterfly)->init_motion();
    return butterfly;
}

extern void *tl_05;

void *TButterfly__create(void *arg0) {
    void *o = __nw__7TObjectFUl(0xBC);
    if (o != NULL) {
        o = TButterfly__ct(o, tl_05, arg0);
    }
    return o;
}

extern u32 butterfly_bml_resource;

void TButterfly::destroy_instance() {
    if ((u32) butterfly_bml_resource != 0U) {
        delete (BmlResource *)((void*)butterfly_bml_resource);
        butterfly_bml_resource = 0U;
    }
}

extern BmlResourceDescriptor bm_o_abe_butterfly_resource_descriptor;
void TButterfly::load_resources() {
    void *resource;
    u32 loaded;
    resource = new BmlResource(1, (BmlResourceDescriptor *)&bm_o_abe_butterfly_resource_descriptor, 0, 0, NULL);
    loaded = (u32)resource;
    butterfly_bml_resource = loaded;
}

}
