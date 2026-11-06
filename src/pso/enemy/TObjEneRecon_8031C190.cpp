#include "types.h"
#include "pso/map/CsnQuery.h"
#include "pso/system/vector.h"
#include "pso/enemy/TObjEneRecon.h"

struct Stack_8031C190 {
    s32 sp8;
    f32 spC;
};

extern s32 actor_frame_tick;
extern const f32 TObjEneRecon__data_805DF3C0;
void TObjEneRecon::update_ground_probe() {
    u8 *arg0 = (u8 *)this;
    Stack_8031C190 stack;
    u8 *temp_r3;
    if ((actor_frame_tick % 5) == 0) {
        VecCopy((Vec *)&stack.sp8, (const Vec *)&this->position);
        stack.spC += TObjEneRecon__data_805DF3C0;
        temp_r3 = (u8 *)(csnVectorUnder((Vec *)&stack.sp8, (u32 *)&this->m_120, 0x4000));
        if (temp_r3 != NULL) {
            *(s32 *)((s8 *)arg0 + 0x418) = (s32) *(s32 *)((s8 *)(*(u8 **)((s8 *)temp_r3 + 4)) + 0x18);
            VecCopy((Vec *)&this->m_438, (const Vec *)(*(u8 **)((s8 *)temp_r3 + 4)));
        } else {
            VecCopy((Vec *)&this->m_438, (const Vec *)&this->position);
        }
    }
    if (*(s32 *)((s8 *)arg0 + 0x418) & 0x4000) {
        TObjEneRecon::set_active();
    }
}
