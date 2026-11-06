#include "types.h"
#include "pso/enemy/EnemyMovement.h"
#include "pso/enemy/TObjEneDD.h"
#include "pso/enemy/TObjEneRecon.h"

struct Base_8031DE2C { char pad[0x18]; };
struct VObj_8031DE2C : Base_8031DE2C {
    virtual void v0();
#define VV(n) virtual void v##n();
VV(1)VV(2)VV(3)VV(4)VV(5)VV(6)VV(7)VV(8)VV(9)VV(10)
VV(11)VV(12)VV(13)VV(14)VV(15)VV(16)VV(17)VV(18)VV(19)VV(20)
VV(21)VV(22)VV(23)VV(24)VV(25)VV(26)VV(27)VV(28)VV(29)VV(30)
VV(31)VV(32)VV(33)VV(34)VV(35)VV(36)VV(37)VV(38)VV(39)VV(40)
VV(41)VV(42)VV(43)VV(44)VV(45)VV(46)VV(47)VV(48)VV(49)VV(50)
VV(51)VV(52)VV(53)VV(54)VV(55)VV(56)VV(57)VV(58)VV(59)VV(60)
VV(61)VV(62)VV(63)VV(64)VV(65)VV(66)VV(67)VV(68)VV(69)VV(70)
VV(71)VV(72)VV(73)VV(74)VV(75)VV(76)VV(77)VV(78)VV(79)VV(80)
VV(81)VV(82)VV(83)VV(84)VV(85)VV(86)VV(87)VV(88)VV(89)VV(90)
VV(91)VV(92)VV(93)VV(94)VV(95)VV(96)VV(97)VV(98)VV(99)
#undef VV
    virtual u32 v102();
};

extern "C" {

extern f32 *TObjEneRecon__data_805D6AFC;

void TObjEneRecon::update_collide_flag() {
    void *parameters = movementParameters;
    // The current m_444 declaration is at 0x428; retain the verified flag offset.
    s32 &flags = *(s32 *)((s8 *)this + 0x444);
    if (TObjEneEpsilon__sub_800B92F8((u8 *)this, *(s32 *)((s8 *)parameters + 8), *TObjEneRecon__data_805D6AFC) != NULL) {
        flags |= 2;
        return;
    }
    flags &= ~2;
}

void TObjEneRecon::set_flag2(f32 dx, f32 dz, f32 distance) {
    s32 &flags = *(s32 *)((s8 *)this + 0x444);
    if (move_with_wall_slide_commit(dx, dz, distance) != NULL) {
        flags |= 2;
        return;
    }
    flags &= ~2;
}

void TObjEneRecon::update_flag_0x444() {
    if (((VObj_8031DE2C *)this)->v102() != 0U) {
        *(s32 *)((s8 *)this + 0x444) = (s32) (*(s32 *)((s8 *)this + 0x444) | 2);
        return;
    }
    *(s32 *)((s8 *)this + 0x444) = (s32) (*(s32 *)((s8 *)this + 0x444) & 0xFFFFFFFD);
}

void enemy_copy_target_destination__12TObjEneDD_STFv(void *);
f32 sin_table_lookup(s32);
f32 cos_table_lookup(s32);

#pragma push
#pragma fp_contract on
void TObjEneRecon::set_orbit_destination(s32 arg1) {
    enemy_copy_target_destination__12TObjEneDD_STFv(this);
    *(f32 *)((s8 *)((u8 *)this) + 0x394) = (f32) ((*(f32 *)((s8 *)((u8 *)this) + 0x468) * sin_table_lookup(arg1)) + *(f32 *)((s8 *)((u8 *)this) + 0x394));
    *(f32 *)((s8 *)((u8 *)this) + 0x398) = (f32) *(f32 *)((s8 *)((u8 *)this) + 0x460);
    *(f32 *)((s8 *)((u8 *)this) + 0x39C) = (f32) ((*(f32 *)((s8 *)((u8 *)this) + 0x468) * cos_table_lookup(arg1)) + *(f32 *)((s8 *)((u8 *)this) + 0x39C));
}
#pragma pop

void TObjEneRecon::advance_field398() {
    ((s32 (*)())enemy_copy_target_destination__12TObjEneDD_STFv)();
    *(f32 *)((s8 *)this + 0x398) = (f32) (*(f32 *)((s8 *)this + 0x398) + *(f32 *)((s8 *)this + 0x464));
}
void TObjEneRecon::sync_height() {
    ((s32 (*)())enemy_copy_target_destination__12TObjEneDD_STFv)();
    *(f32 *)((s8 *)this + 0x398) = (f32) *(f32 *)((s8 *)this + 0x460);
}
void TObjEneRecon::vfunc_61() {  }
void TObjEneRecon::vfunc_62() { if (this->mode != 6) { transition_enemy_state((s16)((void*)6)); } }

void TObjEneRecon::vfunc_63() {
    u8 *arg0 = (u8 *)this;
    s16 temp_r0;
    temp_r0 = this->mode;
    if ((temp_r0 != 7) && (temp_r0 != 8)) {
        ((TObjEneDD *)arg0)->transition_enemy_state((s16)((void*)(7)));
    }
}

void TObjEneRecon::vfunc_28() {  }

}
