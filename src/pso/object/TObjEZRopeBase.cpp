#include "pso/TObjEZRopeBase.h"
#include "pso/TObject.h"
#include "pso/object/TObjHMS_EZRope_Player.h"
#include "pso/object/TObjEZBoneRotPlayer.h"
#include "pso/object/TObjEZRopeBase.h"
#include "pso/ui/TAdSinglePlyChrSelectGC.h"

extern "C" void run_task__21TObjHMS_EZRope_PlayerFv();
extern "C" void render_shadows__7TObjectFv();
f32 ezrope_chunk_material_color_table[12] = {
    0.5f, 1.0f, 1.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
};
Vec TObjEZBoneRotPlayer__chain_gravity = { 0.0f, -0.75f, 0.0f };
#pragma push
#pragma force_active on
void *__vt__21TObjHMS_EZRope_Player[6] = {
    (void *)0x0, (void *)0x0, (void *)&__dt__21TObjHMS_EZRope_PlayerFv, (void *)&run_task__21TObjHMS_EZRope_PlayerFv,
    (void *)&render__21TObjHMS_EZRope_PlayerFv, (void *)&render_shadows__7TObjectFv,
};
#pragma pop

TObjEZRopeBase::~TObjEZRopeBase() {
    if (points != nullptr) { TAdSinglePlyChrSelectGC::safe_free((void *)points); points = nullptr; }
}

#include "types.h"

extern "C" {

void __ct__7TObjectFP7TObject(void *);

extern s32 __vt__14TObjEZRopeBase[];
extern void *TObjEZRopeBase__name;

void *TObjEZRopeBase__ct(void *obj_ez_rope_base) {
    TObjEZRopeBase *rope = static_cast<TObjEZRopeBase *>(obj_ez_rope_base);
    __ct__7TObjectFP7TObject(obj_ez_rope_base);
    *(s32 **)((s8 *)obj_ez_rope_base + 0x18) = __vt__14TObjEZRopeBase;
    *(void * *)&rope->m_name = TObjEZRopeBase__name;
    rope->segment_count = 0;
    rope->segments = NULL;
    rope->anchors = NULL;
    rope->collision_spheres = NULL;
    rope->points = NULL;
    return obj_ez_rope_base;
}

extern char lbl_8043DF18[];
void *TObjEZRopeBase__name = lbl_8043DF18;
}
