#include "types.h"
#include "pso/enemy/sinowzoa/TObjEneMe3SinowZoa_800D72A4.h"
#include "pso/player/TObjPlayer_800D8FDC.h"
#include "pso/unk/text_803E2D70.h"
#include "pso/system/memory.h"
#include "pso/enemy/sinowzoa/TObjEneMe3SinowZoa.h"
#include "pso/player/TObjPlayer.h"
#include "pso/render/MaterialOpacityFade.h"

struct O_800D72A4 { u8 pad[0x18]; f32 f18; };

extern "C" {
extern const float lbl_805DA348;
extern const f32 lbl_805DA34C;
extern const float lbl_805DA350;
extern const f32 lbl_805DA354;
extern const f32 lbl_805DA358;
s32 TObjEneMe3SinowZoa__sub_800D72A4(O_800D72A4 *self);

s32 TObjEneMe3SinowZoa__sub_800D72A4(O_800D72A4 *self) {
    return self->f18 > (*(const f32 *)&lbl_805DA348) && self->f18 < lbl_805DA34C;
}

s32 MaterialOpacityFade::has_visible_opacity() {
    return this->value > (*(const f32 *)&lbl_805DA348);
}

void MaterialOpacityFade::set_flags_and_apply_damage_color() { MaterialColorFade::set_flags_and_apply_damage_color(); set_chunk_blend(8448); }

s32 MaterialOpacityFade::advance_to(f32 farg0) {
    *(f32 *)((s8 *)((u8 *)this) + 0x18) = (f32) (*(f32 *)((s8 *)((u8 *)this) + 0x18) + this->rate);
    ((MaterialOpacityFade *)((u8 *)this))->update_alpha();
    return *(f32 *)((s8 *)((u8 *)this) + 0x18) >= farg0;
}

s32 MaterialOpacityFade::advance_toward_max() {
    u8 *arg0 = (u8 *)this;
    this->value = (f32) ((this->value) + this->rate);
    ((MaterialOpacityFade *)arg0)->update_alpha();
    return this->value >= lbl_805DA34C;
}

s32 MaterialOpacityFade::decay_value_toward_floor() {
    u8 *arg0 = (u8 *)this;
    this->value = (f32) ((this->value) - this->rate);
    ((MaterialOpacityFade *)arg0)->update_alpha();
    return this->value <= (*(const f32 *)&lbl_805DA348);
}

void MaterialOpacityFade::update_alpha() {
    f32 temp_f2;
    temp_f2 = this->value;
    if (temp_f2 <= (*(const f32 *)&lbl_805DA348)) {
        this->color.a = (f32) (*(const f32 *)&lbl_805DA350);
        return;
    }
    if (temp_f2 < lbl_805DA34C) {
        this->color.a = (f32) (temp_f2 - lbl_805DA354);
        if ((*(const f32 *)&lbl_805DA348) == this->color.a) {
            this->color.a = (f32) lbl_805DA358;
        }
        return;
    }
    this->color.a = (f32) lbl_805DA354;
}

void TObjEneMe3SinowZoa::copy_position_vector(void* q) { *(f32*)((char*)this + 0x18) = *(f32*)((char*)q + 0x0); *(f32 *)&this->m_name = *(f32*)((char*)q + 0x0); *(f32 *)&this->m_flags = *(f32*)((char*)q + 0x4); *(f32 *)&this->m_prev = *(f32*)((char*)q + 0x8); *(f32 *)&this->m_next = *(f32*)((char*)q + 0xc); }

void MaterialOpacityFade::reset_obstruction_fade() { this->value = lbl_805DA348; this->color.a = lbl_805DA350; this->color.r = lbl_805DA348; this->color.g = lbl_805DA348; this->color.b = lbl_805DA348; }

    extern const float lbl_805DA34C;
void MaterialOpacityFade::reset_color() { this->value = lbl_805DA34C; this->color.a = lbl_805DA348; this->color.r = lbl_805DA348; this->color.g = lbl_805DA348; this->color.b = lbl_805DA348; }

void MaterialOpacityFade::set_rate(f32 v) { this->rate = v; }

}

struct B_800D7524 { f32 f0; f32 f4; f32 f8; f32 fc; f32 f10; };

struct V_800D7524 : B_800D7524 {
    virtual void m0();
    virtual void m1(s32 x);
    f32 f18;
};

extern "C" {
extern const f32 lbl_805DA360;
extern const f32 lbl_805DA350;
extern const f32 lbl_805DA348;
extern const f32 lbl_805DA35C;
void MaterialOpacityFade::set_rate_from_divisor(s32 arg1) {
    this->rate = (f32) (lbl_805DA34C / (f32) arg1);
}

#pragma push
#pragma fp_contract on
void MaterialOpacityFade::start_fade_out() {
    ((V_800D7524 *)this)->m1(10);
    ((V_800D7524 *)this)->f18 = lbl_805DA35C * ((V_800D7524 *)this)->f10 + lbl_805DA34C;
    ((V_800D7524 *)this)->f0 = lbl_805DA354;
    ((V_800D7524 *)this)->f4 = lbl_805DA348;
    ((V_800D7524 *)this)->f8 = lbl_805DA348;
    ((V_800D7524 *)this)->fc = lbl_805DA348;
}
#pragma pop

void MaterialOpacityFade::start_fade_in() {
    set_rate_from_divisor(10);
    value = -(lbl_805DA360 * rate);
    color.a = lbl_805DA350;
    color.r = lbl_805DA348;
    color.g = lbl_805DA348;
    color.b = lbl_805DA348;
}

MaterialOpacityFade::~MaterialOpacityFade() {}

MaterialOpacityFade::MaterialOpacityFade() : value(lbl_805DA348) {}

}
