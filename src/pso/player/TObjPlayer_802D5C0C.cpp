#include "pso/system/NinjaTypes.h"
#include "types.h"
#include "pso/item/TItem.h"
#include "pso/item/WeaponEffectDescriptor.h"
#include "pso/misc/TRaderMapCore.h"
#include "pso/player/TUnk_804E23F0.h"
#include "pso/items/TItemWeapon.h"
#include "pso/player/TObjPlayer.h"

namespace P802D5C0C {

struct VBase_18 { char pad[0x18]; };
struct VObj_18 : VBase_18 {
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual void m3();
    virtual void m4();
    virtual void m5();
    virtual void m6();
    virtual void m7();
    virtual void m8();
    virtual void m9();
    virtual void m10();
    virtual void m11();
    virtual void m12();
    virtual void m13();
    virtual void m14();
    virtual void m15();
    virtual void m16();
    virtual void m17();
    virtual void m18();
    virtual void m19();
    virtual void m20();
    virtual void m21();
    virtual void m22();
    virtual void m23();
    virtual void m24();
    virtual void m25();
    virtual void m26();
    virtual void m27();
    virtual void m28();
    virtual void m29();
    virtual void m30();
    virtual void m31();
    virtual void m32();
    virtual void m33();
    virtual void m34();
    virtual void m35();
    virtual void m36();
    virtual void m37();
    virtual void m38();
    virtual void m39();
    virtual void m40();
    virtual void m41();
    virtual void m42();
    virtual void m43();
    virtual void m44();
    virtual void m45();
    virtual void m46();
    virtual void m47();
    virtual void m48();
    virtual void m49();
    virtual void m50();
    virtual void m51();
    virtual void m52();
    virtual void m53();
    virtual void m54();
    virtual void m55();
    virtual void m56();
    virtual void m57();
    virtual void m58();
    virtual void m59();
    virtual s32 m60(s32 *);
    virtual void m61();
    virtual void m62();
    virtual s32 m63(s32, s32 *);
};

#include <stddef.h>
struct VBase_18_f1aa6a { char pad[0x18]; };

struct VObj_18_f1aa6a : VBase_18_f1aa6a {
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual void m3();
    virtual void m4();
    virtual void m5();
    virtual void m6();
    virtual void m7();
    virtual void m8();
    virtual void m9();
    virtual void m10();
    virtual void m11();
    virtual void m12();
    virtual void m13();
    virtual void m14();
    virtual void m15();
    virtual void m16();
    virtual void m17();
    virtual void m18();
    virtual void m19();
    virtual void m20();
    virtual void m21();
    virtual void m22();
    virtual void m23();
    virtual void m24();
    virtual void m25();
    virtual void m26();
    virtual void m27();
    virtual void m28();
    virtual void m29();
    virtual void m30();
    virtual void m31();
    virtual void m32();
    virtual void m33();
    virtual void m34();
    virtual void m35();
    virtual void m36();
    virtual void m37();
    virtual void m38();
    virtual void m39();
    virtual void m40();
    virtual void m41();
    virtual void m42();
    virtual void m43();
    virtual void m44();
    virtual void m45();
    virtual void m46();
    virtual void m47();
    virtual void m48();
    virtual void m49();
    virtual void m50();
    virtual void m51();
    virtual void m52();
    virtual void m53();
    virtual void m54();
    virtual void m55();
    virtual void m56();
    virtual void m57();
    virtual void m58();
    virtual void m59();
    virtual void m60();
    virtual void m61();
    virtual void m62();
    virtual s32 m63(s32, s32 *);
};

extern "C" {
s16 get_validated_attack_stage(u8 *arg0);
s32 rotate_matrix_x(int, int);
s32 push_matrix();
s32 pop_matrix();
f32 post_translate_matrix(void *);
static __declspec(section ".rodata") const Vec weapon_display_offset = {0.0f, 0.0f, 0.5f};
void* init_state_445__10TObjPlayerFPv(void* a0);
s32 get_weapon_color__11TItemWeaponFPv(NJS_ARGB *, void *);
int __ct__11TItemWeaponFP7TObjectPUc(void);

void TUnk_804E23F0::init_weapon_effect_descriptor(Desc_8011E5C4 *desc) {
    NJS_ARGB color;

    desc->scale = effect_scale;
    desc->m_58 = 0xC000;
    desc->flags |= 2;
    P802D5C0C::get_weapon_color__11TItemWeaponFPv(&color, this);
    copy_argb(&desc->color, &color);
    desc->m_74 = m_208;
    desc->m_70 = m_204;
}

void TUnk_804E23F0::update_weapon() {
    void *arg0 = this;
    if (((TItemWeapon *)arg0)->get_attack_stage() == 2) {
        *(s32 *)((s8 *)arg0 + 0x1F8) = (s32) (*(s32 *)((s8 *)arg0 + 0x1F8) | 1);
        return;
    }
    *(s32 *)((s8 *)arg0 + 0x1F8) = (s32) (*(s32 *)((s8 *)arg0 + 0x1F8) & 0xFFFFFFFE);
}

extern s32 tl_05;

void TUnk_804E23F0::vfunc_62(Vec *) {
    void *item = this;
    if (((TItemWeapon *)item)->get_attack_stage() == 0) {
        ((TObjPlayer *)P802D5C0C::tl_05)->create_item_eff_cane((TItem*)item, -1, (s32)(((TUnk_804E23F0 *)item)->m_1fc));
    }
}

    extern unsigned char TObjPlayer__sub_8032E648[];
    extern unsigned char create_network_object__10TObjPlayerFlPUll[];
    extern unsigned char __vt__13TUnk_804E23F0[];
    static const f32 lbl_805DE7A0 = 4.0f;

void TUnk_804E23F0::emit_marker_effects() {
    u8 *arg0 = reinterpret_cast<u8 *>(this);
    s32 sp8;
    ((P802D5C0C::VObj_18 *)(((TUnk_804E23F0 *)arg0)->owner))->m63(0x30, &sp8);
    if (P802D5C0C::get_validated_attack_stage((*(u8 * *)&((TUnk_804E23F0 *)arg0)->owner + 0x7CC)) == 2) {
        ((TItemWeapon *)arg0)->fire_shot_at_target((void *)(&sp8), (void *)(*(s32 *)((s8 *)arg0 + 0xF4)), 0);
        ((TItemWeapon *)arg0)->fire_shot_at_target((void *)(&sp8), (void *)(*(s32 *)((s8 *)arg0 + 0xF4)), 0x1555);
        ((TItemWeapon *)arg0)->fire_shot_at_target((void *)(&sp8), (void *)(*(s32 *)((s8 *)arg0 + 0xF4)), -0x1555);
    } else {
        ((TItemWeapon *)arg0)->fire_shot_at_target((void *)(&sp8), (void *)(*(s32 *)((s8 *)arg0 + 0xF4)), 0);
    }
    ((P802D5C0C::VObj_18 *)(arg0))->m60(&sp8);
}

void TUnk_804E23F0::vfunc_60() {
    u8 *item_weapon = reinterpret_cast<u8 *>(this);
    if (TObjPlayer::get_player_list() == 0) {
        Vec offset = P802D5C0C::weapon_display_offset;
        P802D5C0C::post_translate_matrix(&offset);
        P802D5C0C::rotate_matrix_x(0, 0x18E3);
        if (*(s32 *)((s8 *)item_weapon + 0x1f8) & 1) {
            P802D5C0C::push_matrix();
            P802D5C0C::rotate_matrix_x(0, 0x2AAA);
            ((TItem *)item_weapon)->draw_model();
            P802D5C0C::pop_matrix();
            P802D5C0C::push_matrix();
            P802D5C0C::rotate_matrix_x(0, -0x2AAA);
            ((TItem *)item_weapon)->draw_model();
            P802D5C0C::pop_matrix();
        }
    }
}

void TUnk_804E23F0::reserved_53() {
    u8 *item_weapon = reinterpret_cast<u8 *>(this);
    if (((TItemWeapon *)item_weapon)->test_weapon_flags(0x01000000U) == 0U) {
        ((TItemWeapon *)item_weapon)->draw_weapon_model();
    }
}

void* init_state_445__10TObjPlayerFPv(void* a0) { __ct__11TItemWeaponFP7TObjectPUc(); *(int*)((char*)a0 + 0x18) = (int)__vt__13TUnk_804E23F0; ((TItemWeapon *)a0)->set_weapon_flags(3); *(int*)((char*)a0 + 0x1f8) = 0; ((TUnk_804E23F0 *)a0)->m_1fc = 445; *(int*)((char*)a0 + 0x204) = (int)TObjPlayer__sub_8032E648; *(int*)((char*)a0 + 0x208) = (int)create_network_object__10TObjPlayerFlPUll; *(float*)((char*)a0 + 0x200) = lbl_805DE7A0; return a0; }

}

}
