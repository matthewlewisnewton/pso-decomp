#include "types.h"
#include "pso/item/TItem.h"
#include "pso/item/TItemEquipBase.h"
#include "pso/items/TItemWeapon.h"
#include "pso/object/TObjMotion.h"
#include "pso/player/TObjPlayer.h"
#include "pso/unk/TUnk_804E1BB0.h"
#include "pso/unk/TUnk_804E1CA8.h"
#include "pso/player/TUnk_804E1F04.h"
#include "pso/player/TUnk_804E2000.h"
#include "pso/player/TUnk_804E20FC.h"
#include "pso/player/TUnk_804E21F8.h"
#include "pso/player/TUnk_804E22F4.h"
#include "pso/player/TUnk_804E23F0.h"

class TUnk_804E1E08 : public TUnk_804E23F0 {
public:
    virtual ~TUnk_804E1E08();
};

struct TItemEquipBase;

extern "C" {
void *__nw__5TItemFUl(u32);
void *setup_state__10TObjPlayerFPv(void *, s32, void *);
void *init_needle_effect__10TObjPlayerFPv(void *, s32, void *);
void *enter_state_341__13TUnk_804E2000Fv(void *, s32, void *);
void *init_mag_effect_state__10TObjPlayerFPv(void *, s32, void *);
void *init_type_447__13TUnk_804E22F4Fv(void *, s32, void *);
void *init_vtable_and_handlers_341__13TUnk_804E1F04Fv(void *, s32, void *);
void *init_vtable_and_field200__10TObjPlayerFPv(void *, s32, void *);
extern s32 tl_05;

extern "C" s8 get_attach_slot__14TItemEquipBaseFv(TItemEquipBase *arg0);
extern "C" void snap_to_owner__5TItemFv();
extern "C" void update_in_inventory__5TItemFv();
extern "C" int feed__5TItemFP9TItemData(void);
extern "C" void add_slot__5TItemFv();
extern "C" int update_object_view_visibility__5TItemFff(void *p);
extern "C" void vfunc_6__8TObjBaseFPsl();
extern "C" void vfunc_60__11TItemWeaponFv();
extern "C" void init_weapon_effect_descriptor__11TItemWeaponFP13Desc_8011E5C4();
extern "C" void vfunc_58__11TItemWeaponFv();
extern "C" void vfunc_57__11TItemWeaponFv();
extern "C" void update_weapon__11TItemWeaponFv();
extern "C" void update_idle__11TItemWeaponFv();
extern "C" void update_attack__11TItemWeaponFv();
extern "C" void activate_effect__11TItemWeaponFl();
extern "C" void update_owned__11TItemWeaponFv();
extern "C" void on_model_loaded__11TItemWeaponFv();
extern "C" void write_item_data__11TItemWeaponFP9TItemData();
extern "C" void on_unequip__11TItemWeaponFv();
extern "C" u8 get_motion_type__11TItemWeaponFv(void *p);
extern "C" void vfunc_60__13TUnk_804E23F0Fv(u8 *arg0);
extern "C" void add_equip_stats__14TItemEquipBaseFl();
extern "C" void on_equip__11TItemWeaponFv();
extern "C" void apply_object_set_data__8TObjBaseFPv();
extern "C" void apply_owner_bonuses__11TItemWeaponFv();
extern "C" void classify_actor_view_detail__8TObjBaseFfff();
extern "C" void vfunc_62__13TUnk_804E23F0FP3Vec(void *item);
extern "C" void deliver_hit__11TItemWeaponFlPUcllf();
extern "C" void perform_action__11TItemWeaponFv();
extern "C" void use__5TItemFv();
extern "C" void render__5TItemFv();
extern "C" void render_equipped_shadow__11TItemWeaponFv();
extern "C" void reserved_53__13TUnk_804E1BB0Fv(s32 arg0);
extern "C" void reserved_53__13TUnk_804E23F0Fv(u8 *arg0);
extern "C" void render_equipped__11TItemWeaponFv();
extern "C" void equip__14TItemEquipBaseFv();
extern "C" void emit_marker_effects__13TUnk_804E23F0Fv(u8 *arg0);
extern "C" void get_attack_flags__11TItemWeaponFv();
extern "C" void get_center__11TItemWeaponFv();
extern "C" void *__dt__13TUnk_804E1BB0Fv(void *arg0, s16 arg1);
extern "C" void *__dt__13TUnk_804E1CA8Fv(void *arg0, s16 arg1);
extern "C" void launch_shot__11TItemWeaponFPUclll();
extern "C" void request_equipped_model__11TItemWeaponFv();
extern "C" void get_name__5TItemFv();
extern "C" void reset_motion_fields__14TObjCollidableFv();
extern "C" void remove_equip_stats__14TItemEquipBaseFl();
extern "C" void render_shadows__5TItemFv();
extern "C" void remove_owner_bonuses__11TItemWeaponFv();
extern "C" void release_model__11TItemWeaponFv();
extern "C" int get_slot_count__5TItemFv(void);
extern "C" int add_amount__5TItemFl(void);
extern "C" int remove_amount__5TItemFl(void);
extern "C" int get_amount__5TItemFv(void);
extern "C" void run_task__5TItemFv();
extern "C" void set_attach_slot__14TItemEquipBaseFSc();
extern "C" void setup_radar_marker__10TObjPlayerFPvPv(TUnk_804E1CA8 *weapon, Desc_8011E5C4 *desc);
extern "C" void subtract_equip_stats__14TItemEquipBaseFPvPsPs();
extern "C" void subtract_item_stat_bonus__14TItemEquipBaseFllPs();
extern "C" void interact__5TItemFl();
extern "C" void unequip__14TItemEquipBaseFv();
extern "C" void update_equipped__11TItemWeaponFv();
extern "C" void destroy__14TItemEquipBaseFv();
extern "C" void refresh_special__11TItemWeaponFv();
extern "C" void is_identified__11TItemWeaponFv();
extern "C" void update_weapon__13TUnk_804E23F0Fv(void *arg0);
extern "C" void render_equipped_deferred__11TItemWeaponFv();
extern "C" void emit_marker_effects__11TItemWeaponFv();
void *lbl_804E1BB0[62] = {
    (void *)0x0, (void *)0x0, (void *)&__dt__13TUnk_804E1BB0Fv, (void *)&run_task__5TItemFv,
    (void *)&render__5TItemFv, (void *)&render_shadows__5TItemFv, (void *)&vfunc_6__8TObjBaseFPsl, (void *)&apply_object_set_data__8TObjBaseFPv,
    (void *)&reset_motion_fields__14TObjCollidableFv, (void *)&get_center__11TItemWeaponFv, (void *)&update_object_view_visibility__5TItemFff, (void *)&classify_actor_view_detail__8TObjBaseFfff,
    (void *)&get_name__5TItemFv, (void *)&interact__5TItemFl, (void *)&update_owned__11TItemWeaponFv, (void *)&update_in_inventory__5TItemFv,
    (void *)&update_equipped__11TItemWeaponFv, (void *)&activate_effect__11TItemWeaponFl, (void *)&write_item_data__11TItemWeaponFP9TItemData, (void *)&set_attach_slot__14TItemEquipBaseFSc,
    (void *)&equip__14TItemEquipBaseFv, (void *)&unequip__14TItemEquipBaseFv, (void *)&add_equip_stats__14TItemEquipBaseFl, (void *)&remove_equip_stats__14TItemEquipBaseFl,
    (void *)&subtract_item_stat_bonus__14TItemEquipBaseFllPs, (void *)&subtract_equip_stats__14TItemEquipBaseFPvPsPs, (void *)&render_equipped__11TItemWeaponFv, (void *)&render_equipped_shadow__11TItemWeaponFv,
    (void *)&render_equipped_deferred__11TItemWeaponFv, (void *)&destroy__14TItemEquipBaseFv, (void *)&perform_action__11TItemWeaponFv, (void *)&use__5TItemFv,
    (void *)&get_attack_flags__11TItemWeaponFv, (void *)&get_attach_slot__14TItemEquipBaseFv, (void *)&refresh_special__11TItemWeaponFv, (void *)&is_identified__11TItemWeaponFv,
    (void *)&get_amount__5TItemFv, (void *)&remove_amount__5TItemFl, (void *)&add_amount__5TItemFl, (void *)&get_slot_count__5TItemFv,
    (void *)&add_slot__5TItemFv, (void *)&feed__5TItemFP9TItemData, (void *)&snap_to_owner__5TItemFv, (void *)&get_motion_type__11TItemWeaponFv,
    (void *)&on_equip__11TItemWeaponFv, (void *)&on_unequip__11TItemWeaponFv, (void *)&request_equipped_model__11TItemWeaponFv, (void *)&release_model__11TItemWeaponFv,
    (void *)&apply_owner_bonuses__11TItemWeaponFv, (void *)&remove_owner_bonuses__11TItemWeaponFv, (void *)&on_model_loaded__11TItemWeaponFv, (void *)&launch_shot__11TItemWeaponFPUclll,
    (void *)&emit_marker_effects__11TItemWeaponFv, (void *)&update_attack__11TItemWeaponFv, (void *)&update_idle__11TItemWeaponFv, (void *)&reserved_53__13TUnk_804E1BB0Fv,
    (void *)&update_weapon__11TItemWeaponFv, (void *)&vfunc_57__11TItemWeaponFv, (void *)&vfunc_58__11TItemWeaponFv, (void *)&init_weapon_effect_descriptor__11TItemWeaponFP13Desc_8011E5C4,
    (void *)&vfunc_60__11TItemWeaponFv, (void *)&deliver_hit__11TItemWeaponFlPUcllf,
};
void *lbl_804E1CA8[63] = {
    (void *)0x0, (void *)0x0, (void *)&__dt__13TUnk_804E1CA8Fv, (void *)&run_task__5TItemFv,
    (void *)&render__5TItemFv, (void *)&render_shadows__5TItemFv, (void *)&vfunc_6__8TObjBaseFPsl, (void *)&apply_object_set_data__8TObjBaseFPv,
    (void *)&reset_motion_fields__14TObjCollidableFv, (void *)&get_center__11TItemWeaponFv, (void *)&update_object_view_visibility__5TItemFff, (void *)&classify_actor_view_detail__8TObjBaseFfff,
    (void *)&get_name__5TItemFv, (void *)&interact__5TItemFl, (void *)&update_owned__11TItemWeaponFv, (void *)&update_in_inventory__5TItemFv,
    (void *)&update_equipped__11TItemWeaponFv, (void *)&activate_effect__11TItemWeaponFl, (void *)&write_item_data__11TItemWeaponFP9TItemData, (void *)&set_attach_slot__14TItemEquipBaseFSc,
    (void *)&equip__14TItemEquipBaseFv, (void *)&unequip__14TItemEquipBaseFv, (void *)&add_equip_stats__14TItemEquipBaseFl, (void *)&remove_equip_stats__14TItemEquipBaseFl,
    (void *)&subtract_item_stat_bonus__14TItemEquipBaseFllPs, (void *)&subtract_equip_stats__14TItemEquipBaseFPvPsPs, (void *)&render_equipped__11TItemWeaponFv, (void *)&render_equipped_shadow__11TItemWeaponFv,
    (void *)&render_equipped_deferred__11TItemWeaponFv, (void *)&destroy__14TItemEquipBaseFv, (void *)&perform_action__11TItemWeaponFv, (void *)&use__5TItemFv,
    (void *)&get_attack_flags__11TItemWeaponFv, (void *)&get_attach_slot__14TItemEquipBaseFv, (void *)&refresh_special__11TItemWeaponFv, (void *)&is_identified__11TItemWeaponFv,
    (void *)&get_amount__5TItemFv, (void *)&remove_amount__5TItemFl, (void *)&add_amount__5TItemFl, (void *)&get_slot_count__5TItemFv,
    (void *)&add_slot__5TItemFv, (void *)&feed__5TItemFP9TItemData, (void *)&snap_to_owner__5TItemFv, (void *)&get_motion_type__11TItemWeaponFv,
    (void *)&on_equip__11TItemWeaponFv, (void *)&on_unequip__11TItemWeaponFv, (void *)&request_equipped_model__11TItemWeaponFv, (void *)&release_model__11TItemWeaponFv,
    (void *)&apply_owner_bonuses__11TItemWeaponFv, (void *)&remove_owner_bonuses__11TItemWeaponFv, (void *)&on_model_loaded__11TItemWeaponFv, (void *)&launch_shot__11TItemWeaponFPUclll,
    (void *)&emit_marker_effects__13TUnk_804E23F0Fv, (void *)&update_attack__11TItemWeaponFv, (void *)&update_idle__11TItemWeaponFv, (void *)&reserved_53__13TUnk_804E23F0Fv,
    (void *)&update_weapon__13TUnk_804E23F0Fv, (void *)&vfunc_57__11TItemWeaponFv, (void *)&vfunc_58__11TItemWeaponFv, (void *)&setup_radar_marker__10TObjPlayerFPvPv,
    (void *)&vfunc_60__13TUnk_804E23F0Fv, (void *)&deliver_hit__11TItemWeaponFlPUcllf, (void *)&vfunc_62__13TUnk_804E23F0FP3Vec,
};

void *TObjPlayer::create_object_by_type() {
    u8 *arg0 = (u8 *)this;
    void *p;
    if (arg0 != NULL) {
    switch (arg0[1]) {
    case 0x8C:
        switch (arg0[2]) {
        case 0:
            break;
        case 1:
            p = __nw__5TItemFUl(0x20C);
            if (p != NULL) {
                p = init_vtable_and_handlers_341__13TUnk_804E1F04Fv(p, tl_05, arg0);
            }
            return p;
        case 2:
            p = __nw__5TItemFUl(0x20C);
            if (p != NULL) {
                p = init_type_447__13TUnk_804E22F4Fv(p, tl_05, arg0);
            }
            return p;
        case 3:
            p = __nw__5TItemFUl(0x254);
            if (p != NULL) {
                p = init_mag_effect_state__10TObjPlayerFPv(p, tl_05, arg0);
            }
            return p;
        }
        break;
    case 0x93:
        p = __nw__5TItemFUl(0x20C);
        if (p != NULL) {
            p = enter_state_341__13TUnk_804E2000Fv(p, tl_05, arg0);
        }
        return p;
    case 0xA4:
        p = __nw__5TItemFUl(0x20C);
        if (p != NULL) {
            p = init_needle_effect__10TObjPlayerFPv(p, tl_05, arg0);
        }
        return p;
    case 0x96:
        p = __nw__5TItemFUl(0x20C);
        if (p != NULL) {
            p = setup_state__10TObjPlayerFPv(p, tl_05, arg0);
        }
        return p;
    }
    p = __nw__5TItemFUl(0x20C);
    if (p != NULL) {
        p = init_vtable_and_field200__10TObjPlayerFPv(p, tl_05, arg0);
    }
    return p;
    }
    return NULL;
}

// The factory emits its switch table first. Deferred generation preserves the
// original order of the following destructors and their virtual tables.
#pragma defer_codegen on

TUnk_804E23F0::~TUnk_804E23F0() {}

TUnk_804E22F4::~TUnk_804E22F4() {}

TUnk_804E21F8::~TUnk_804E21F8() {}

TUnk_804E20FC::~TUnk_804E20FC() {}

TUnk_804E2000::~TUnk_804E2000() {}

TUnk_804E1F04::~TUnk_804E1F04() {}

TUnk_804E1E08::~TUnk_804E1E08() {}


}
