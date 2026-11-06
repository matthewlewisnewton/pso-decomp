#include "types.h"
#include "pso/object/TObject_80019A50.h"
#include "pso/boss/TObjBoss1Rock.h"

extern "C" {
s32 vec3_add_to(void *, void *);
extern const f32 lbl_805D8204;
extern const f32 lbl_805D8208;
extern const f32 lbl_805D820C;
extern const f32 lbl_805D8210;
extern const f32 lbl_805D8214;
extern const f32 lbl_805D8218;
#pragma push
#pragma opt_common_subs off
#pragma opt_propagation off
void TObjBoss1Rock::run_task() {
    u8 *arg0 = (u8 *)this;
    f32 temp_f2;
    this->m_3c = (this->m_3c + 1);
    if ((s32) this->m_3c > 0x28) {
        *(f32 *)((s8 *)arg0 + 0x40) = (f32) (*(f32 *)((s8 *)arg0 + 0x40) - lbl_805D8204);
        if (*(f32 *)((s8 *)arg0 + 0x40) < lbl_805D8208) {
            *(f32 *)((s8 *)arg0 + 0x40) = (f32) lbl_805D8208;
            queue_destruction__7TObjectFv(arg0);
        }
    }
    vec3_add_to((u8 *)&this->m_1c, (u8 *)&this->m_28);
    temp_f2 = *(f32 *)((s8 *)arg0 + 0x20);
    if (temp_f2 < lbl_805D8208) {
        *(f32 *)((s8 *)arg0 + 0x20) = (f32) (temp_f2 * lbl_805D820C);
        *(f32 *)&this->unk_2C = (f32) (*(f32 *)&this->unk_2C * lbl_805D8210);
        *(f32 *)&this->m_28 = (f32) (*(f32 *)&this->m_28 * lbl_805D8214);
        this->m_30 = (f32) (this->m_30 * lbl_805D8214);
    }
    *(f32 *)&this->unk_2C = (f32) (*(f32 *)&this->unk_2C + lbl_805D8218);
    this->m_34 = (this->m_34 + 0x60);
    this->m_38 = (this->m_38 + 0x110);
}
#pragma pop

}
