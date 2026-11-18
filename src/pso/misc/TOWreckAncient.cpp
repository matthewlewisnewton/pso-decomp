#include "pso/misc/TOWreckAncientResources.h"
#include "pso/system/BmlTextureList.h"
#include "pso/system/BmlResource.h"
#include "pso/system/CurrentTextureList.h"
#include "types.h"
#include "pso/system/BmlResourceClass.h"
#include "pso/system/GinjaMaterial.h"
#include "pso/unk/text_803D96A8.h"
#include "pso/object/TObjMotion.h"
#include "pso/system/BmlResourceDescriptor.h"
#include "pso/misc/TOWreckAncient.h"
#include "pso/object/TObjFish.h"
#include "pso/player/TObjPlayer.h"
#include "pso/ui/TAdSinglePlyChrSelectGC.h"

extern const char *bm_fe_obj_o_hahen_motion_names[];
extern const char *bm_fe_obj_o_hahen_model_names[10];

struct Base1_8017dce0 { char pad[0x18]; };
struct VObj1_8017dce0 : Base1_8017dce0 {
    virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3();
    virtual void m4(); virtual void m5(); virtual void m6(); virtual void m7();
    virtual s32 m8(f32, f32);
};



struct RecoveredGlobal_8017DE94___vt__14TOWreckAncient {
    s32 value;
    u8 remaining[0x38];
};

extern "C" {
s32 __ct__14TObjCollidableFP7TObject(void *, int);
extern s32 __vt__14TOWreckAncient[];
extern const char *TOWreckAncient__name;
extern s32 tl_05;
static const f32 lbl_805DBAD0 = 400.0f;
static const f32 lbl_805DBAD4 = 40.0f;
u8 *TOWreckAncient__ct(u8 *arg0, s32 arg1);
s32 post_translate_matrix(void *);
s32 free_collision_body_parts(void *);
s32 rotate_matrix_y(s32, s32);
s32 push_matrix();

void TOWreckAncient::render() {
    u8 *arg0 = (u8 *)this;
    VObj1_8017dce0 *self = (VObj1_8017dce0 *)arg0;
    if (self->m8(*(f32 *)&this->unk_AC, this->m_b0) != 0) {
        push_matrix();
        post_translate_matrix((u8 *)&this->position);
        rotate_matrix_y(0, this->rotation.yaw);
        set_current_texture_list((GinjaTextureList *)(this->texlist));
        draw_ginja_object(this->model);
        pop_matrix();
    }
}

void TOWreckAncient::free_statics() {
    if (wreck_ancient_bml_resource != NULL) {
        delete wreck_ancient_bml_resource;
        wreck_ancient_bml_resource = NULL;
    }
    if (wreck_ancient_brakable_bml_resource != NULL) {
        delete wreck_ancient_brakable_bml_resource;
        wreck_ancient_brakable_bml_resource = NULL;
    }
}

void TOWreckAncient::load_resources() {
    wreck_ancient_bml_resource = new BmlResource(1, &bm_o_wreck_ancient_resource_descriptor, 0, 0, NULL);
    wreck_ancient_brakable_bml_resource = new BmlResource(1, &TOWreckAncient__resource_descriptor, 0, 0, NULL);
}

TOWreckAncient::~TOWreckAncient() {
    unregister_object_by_id();
    free_collision_body_parts(this);
}
typedef char RecoveredGlobal_8017DE94___vt__14TOWreckAncient_size[sizeof(RecoveredGlobal_8017DE94___vt__14TOWreckAncient) == 0x3C ? 1 : -1];
u8 *TOWreckAncient__ct(u8 *wreck_ancient, s32 arg1) {
    __ct__14TObjCollidableFP7TObject(wreck_ancient, tl_05);
    *(s32 **)((s8 *)wreck_ancient + 0x18) = &(*(RecoveredGlobal_8017DE94___vt__14TOWreckAncient *)&__vt__14TOWreckAncient).value;
    *(s32 *)((s8 *)wreck_ancient + 0) = (s32) TOWreckAncient__name;
    *(s32 *)((s8 *)wreck_ancient + 0x34) = (s32)get_bml_model(wreck_ancient_bml_resource, (s32)arg1);
    ((TOWreckAncient *)wreck_ancient)->texlist = (s32)TObjFish__sub_8001EDB0(wreck_ancient_bml_resource, (s32)arg1);
    *(f32 *)((s8 *)wreck_ancient + 0xAC) = (f32) lbl_805DBAD0;
    ((TOWreckAncient *)wreck_ancient)->m_b0 = (f32) lbl_805DBAD4;
    return wreck_ancient;
}

}
