#include "pso/system/SoundEffect.h"
#include <dolphin/mtx.h>
#include "pso/map/CsnQuery.h"
#include "pso/boss/TBoss5GryphonLightningWing.h"
#include "pso/object/TObject_80019A50.h"
#include "pso/system/vector.h"
#include "pso/TBoss5GryphonLightning.h"
#include "pso/TBoss5GryphonLightningWing.h"

#include "types.h"

#include <stddef.h>
#include "pso/misc/TLobby.h"
#include "pso/boss/TBoss8Dragon.h"

#pragma readonly_strings on

extern "C" {
const char *lbl_805D4368 = "TBoss5GryphonLightningWing";
}


#pragma opt_lifetimes off
struct Stack_80351A80 {
    s32 sp8;
    u8 trailing_storage[0x8];
};

extern "C" {
extern const f32 lbl_805D8D48;

extern const char *lbl_805D4368;
s32 TBoss8Dragon__sub_80063FB8(s32, s32 *, f32);


void TBoss5GryphonLightningWing::apply_lightning_effect() {
    s32 sp8;
    s32 instance_count;
    s32 arg0 = (s32)this;

    instance_count = TBoss8Dragon::get_instance_count();
    if (instance_count != 0) {
        ((TBoss5GryphonLightningWing *)arg0)->get_wing_position((s32)&sp8);
        TBoss8Dragon__sub_80063FB8(instance_count, &sp8, 10.0f);
    }
}

void TBoss5GryphonLightningWing::render() {  }

#pragma push
#pragma opt_common_subs off
void TBoss5GryphonLightningWing::run_task() {
    TBoss5GryphonLightningWing *boss5_gryphon_lightning_wing = this;
    Stack_80351A80 stack;
    *(f32 *)((s8 *)boss5_gryphon_lightning_wing + 0x88) = (f32) ((f32) *(s32 *)((s8 *)boss5_gryphon_lightning_wing + 0x94) / (f32) *(s32 *)((s8 *)boss5_gryphon_lightning_wing + 0x9C));
    if (*(f32 *)((s8 *)boss5_gryphon_lightning_wing + 0x88) > 1.0f) {
        *(f32 *)((s8 *)boss5_gryphon_lightning_wing + 0x88) = 1.0f;
    }
    *(f32 *)((s8 *)boss5_gryphon_lightning_wing + 0x8C) = (f32) ((f32) *(s32 *)((s8 *)boss5_gryphon_lightning_wing + 0x94) / (f32) *(s32 *)((s8 *)boss5_gryphon_lightning_wing + 0x98));
    if (*(f32 *)((s8 *)boss5_gryphon_lightning_wing + 0x8C) > 1.0f) {
        *(f32 *)((s8 *)boss5_gryphon_lightning_wing + 0x8C) = 1.0f;
    }
    boss5_gryphon_lightning_wing->update_wing_segments();
    boss5_gryphon_lightning_wing->apply_lightning_effect();
    if ((s32) *(s32 *)((s8 *)boss5_gryphon_lightning_wing + 0x94) == (s32) *(s32 *)((s8 *)boss5_gryphon_lightning_wing + 0x98)) {
        boss5_gryphon_lightning_wing->get_wing_position((s32)&stack.sp8);
        play_sound_effect(0x40032516, (const Vec *)(&stack.sp8), 0, 0);
    }
    ((TBoss5GryphonLightning *)boss5_gryphon_lightning_wing)->spawn_gryphon_lightning();
    if ((s32) *(s32 *)((s8 *)boss5_gryphon_lightning_wing + 0x94) >= (s32) *(s32 *)((s8 *)boss5_gryphon_lightning_wing + 0x9C)) {
        queue_destruction__7TObjectFv((boss5_gryphon_lightning_wing));
    }
}
#pragma pop

TBoss5GryphonLightningWing::~TBoss5GryphonLightningWing() {}
TBoss5GryphonLightningWing::TBoss5GryphonLightningWing(TObject *parent, const Vec *start, Vec *middle, const Vec *end, s32 duration, s32 delay)
    : TBoss5GryphonLightning(parent, 20.0f, start) {
    s32 i;
    m_name = lbl_805D4368;
    m_90 = 3;
    m_98 = duration;
    m_9c = duration + delay;
    VecCopy(&points[0].position, start);
    VecCopy(&points[m_90 - 1].position, end);
    // Keep the mutable middle-point borrow and the real base-subobject view:
    // MWCC then preserves the native per-iteration coordinate loads/stores.
    TBoss5GryphonLightning *lightning = this;
    for (i = 1; i < m_90 - 1; i++) {
        lightning->points[i].position.x = middle->x;
        lightning->points[i].position.y = middle->y;
        lightning->points[i].position.z = middle->z;
    }
}

s32 spawn_lightning_wing__12TBoss8DragonFiiiiii(TObject *parent, const Vec *start, Vec *middle, const Vec *end, s32 duration, s32 delay) {
    Vec position;
    f32 ground_height;
    u8* collision;
    VecCopy(&position, end);
    collision = (u8 *)csnVecterUnder(&position, 0x16EF);
    if (collision == NULL) {
        position.y = lbl_805D8D48;
    } else {
        ground_height = *(f32*)((s8 *)(*(u8**)((s8 *)collision + 4)) + 4);
        if (ground_height > lbl_805D8D48) {
            position.y = lbl_805D8D48;
        } else {
            position.y = ground_height;
        }
    }
    return (s32)new TBoss5GryphonLightningWing(parent,
        start, middle, &position, duration, delay);
}

void fn_80351DA8(TObject *parent, Vec *start, Vec *end, s32 duration, s32 delay) {
    Vec middle;
    middle.x = end->x;
    middle.y = start->y;
    middle.z = end->z;
    spawn_lightning_wing__12TBoss8DragonFiiiiii(parent, start, &middle, end, duration, delay);
}

}
