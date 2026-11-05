#define TOBJECT_OUT_OF_LINE_HELPERS
#include "pso/misc/ParticleFactory.h"
#include "pso/system/SoundEffect.h"
#include "pso/TParticleCtrl.h"
#include "types.h"
#include "pso/system/vector.h"
#include "pso/player/TObjChara.h"
#include "pso/object/TObjMotion.h"
#include "pso/misc/TOMine.h"
#include "pso/misc/TOMineTrap.h"
#include "pso/TObject.h"
#include "pso/misc/TLobby.h"
#include "pso/player/TObjPlayer.h"
#include "pso/map/FloorArea.h"

struct Trap_8016F704 { u8 pad0[0x38]; f32 pos[3]; u8 pad44[0x84 - 0x44]; s32 delay; u8 pad88[0x2A8 - 0x88]; void *target; u8 pad2AC[0x34C - 0x2AC]; f32 range; u8 pad350[0x35C - 0x350]; u16 targetId; };

extern "C" {
s32 obj_testFlags30__14TObjCollidableFUl(void *, u32);
s32 get_current_floor(void);
f32 horizontal_distance_squared(void *, void *);
extern u8 lobby_rule_settings[];
u16 get_entity_id(void *);
void *get_player_by_client_id(s32 i);
void *__nw__7TObjectFUl(u32);
extern s32 enable_v2_features;
s32 create_placed_trap__10TOMineTrapFUiss(u32 arg0, s16 arg1, s16 arg2);
s32 is_split_screen();
void *TOMineDisp__ct(void *, void *, u16);
extern s32 local_client_id;
}

struct VBase_18_33b813
{
  char pad[0x18];
};

struct VObj_18_33b813 : VBase_18_33b813 {
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
    virtual s32 m20(s32, f32);
};

struct Stack_80170AC8
{
  f32 sp8;
  f32 spC;
  f32 sp10;
};

struct Node_801702C8 { u8 pad[0xC]; Node_801702C8 *next; };

struct VBase_18_1da615 { char pad[0x18]; };

struct VObj_18_1da615 : VBase_18_1da615 {
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
    virtual s32 m20(s32, f32);
    virtual f32 m21(void *, void *, s32, s32, s32);
    virtual void m22();
    virtual s32 m23(void *, f32);
};

extern "C" {
s32 is_locally_controlled__10TObjPlayerFPv(u32 a0);
s32 get_localized_text_entry(s32 arg0, s32 arg1);
s32 get_main_phase();

extern s8 mine_trap_effect_table[];
extern s8 mine_trap_keymachine_table[];

extern f32 lbl_805DB864;
extern const f32 lbl_805DB85C;
extern const f32 TOMineTrap__data_805DB868;
void TOMineTrap__sub_80170CD4(void* p);
f32 sin_table_lookup(s32);
extern const f32 lbl_805DB884;
extern const f32 lbl_805DB888;
f32 atan2_float(f32 y, f32 x);
f32 vec3_add_to(void *, void *);
f32 vec_squared_length(u8 *arg0);
f32 subtract_vector(void *, void *);
f32 normalize_vector(void *);
extern const f64 lbl_80442200;
extern const f32 lbl_805DB870;
void queue_destruction__7TObjectFv(void *arg0);
int get_player_data__10TObjPlayerFi(int a0);
s32 check_value_equals__7TObjectFPCc(void *, s32);
extern s32 TOMineTrap__data_805D3080;
extern s32 registered_player_count;
extern s32 lbl_805D5870;
extern s32 lbl_805D5868;
extern s32 TOMineIcon01__name;
extern s32 TOMineIcon02__name;
extern s32 TOMineIcon03__name;
extern s32 TOMineIcon04__name;
u8 *get_battle_param__10TObjPlayerFi(s32);
void check_enemy_body_collisions(void *);
extern const f32 lbl_805DB874;
void *__dt__10TOMineTrapFv(void *arg0, s16 arg1);
s32 free_collision_body_parts(void *);
s32 is_locally_controlled__10TObjPlayerFPv(u32 a0 = 0);
s32 __dl__7TObjectFPv(void *);
void *__dt__6TOMineFv(void *arg0, s16 arg1);
s32 submit_cursor_candidate(void *obj, s32 slot);
void record_attack_source(void *target, u16 id);
void TOMineTrap::set_state() { this->mode = 4; }

s32 TOMineTrap::find_target_in_range() {
    Trap_8016F704 *self = (Trap_8016F704 *)this;
    u8 *p;
    s32 i;
    u16 id;

    self->targetId = 0xFFFF;
    self->target = 0;
    if (self->delay > 0) {
        self->delay--;
        return 0;
    }
    for (i = 0; i < registered_player_count + lbl_805D5870; i++) {
        p = (u8 *)get_player_data__10TObjPlayerFi(i);
        if (p == 0 || p == (u8 *)self || obj_testFlags30__14TObjCollidableFUl(p, 0x800) != 0) {
            continue;
        }
        id = get_entity_id(p);
        if (id == 0xFFFF) {
            continue;
        }
        if (id == ((TOMineTrap *)self)->get_trap_type() && TOMineTrap::get_trap_count() != 1 &&
            ((TLobby *)lobby_rule_settings)->get_rule_field_0() != 0) {
            continue;
        }
        if (id < 0x1000) {
            if (((TObjPlayer *)p)->get_floor() != get_current_floor()) {
                continue;
            }
            if (horizontal_distance_squared(self->pos, p + 0x38) < self->range * self->range) {
                self->targetId = id;
                self->target = p;
                return 1;
            }
        } else if (id < 0x4000) {
            if (horizontal_distance_squared(self->pos, p + 0x38) < self->range * self->range) {
                self->targetId = id;
                self->target = p;
                return 1;
            }
        }
    }
    return 0;
}

void TOMineTrap::set_triggered() {
    u8 *arg0 = (u8 *)this;
    this->mode = 3;
    ((TObjCollidable *)arg0)->set_indexed_flags(0, 1);
    this->actorFlags = (s32) (this->actorFlags & 0xFFFBFFFF);
}

void TOMineTrap::vfunc_86() {
    u8 *arg0 = (u8 *)this;
    this->mode = 2;
    ((TObjCollidable *)arg0)->set_indexed_flags(0, 1);
    this->actorFlags = (s32) (this->actorFlags & 0xFFFBFFFF);
}

/* Mode 4's strike against one actor. The unit is built with -inline on, so
 * these expand into run_task. The actor has to arrive as the inline argument,
 * and the player and enemy branches have to stay separate inlines, to keep the
 * original register and stack layout (docs/porting-exceptions.md). */
inline void TOMineTrap::strike_player(TObjChara *actor) {
    if (TObjPlayer::get_player_count() != 1) {
        return;
    }
    if (((TObjPlayer *)actor)->get_floor() != get_current_floor()) {
        return;
    }
    if (horizontal_distance_squared(&this->position, &actor->position) < this->m_350 * this->m_350) {
        if (actor->obj_isState2_324() == 0) {
            this->target = (u8 *)actor;
            switch (this->attack.kind) {
            case 2:
                ((TObjChara *)this->target)->apply_movement_ailment(0);
                break;
            default:
                ((TObjChara *)this->target)->receive_direct_attack(this, this->attack, 0, -1, -1);
                break;
            }
            record_attack_source(this->target, this->get_trap_type());
        }
        if (this->m_380 != 1) {
            this->m_380 = TOMineTrap::show_owner_message(this, actor);
        }
    }
}

inline void TOMineTrap::strike_enemy(TObjChara *actor, TObjPlayer *owner) {
    if (horizontal_distance_squared(&this->position, &actor->position) < this->m_350 * this->m_350) {
        this->target = (u8 *)actor;
        switch (this->attack.kind) {
        case 2:
            ((TObjChara *)this->target)->apply_movement_ailment(0);
            ((TObjChara *)this->target)->vfunc_74(0);
            break;
        default:
            ((TObjChara *)this->target)->receive_direct_attack(owner, this->attack, 0, -1, -1);
            break;
        }
        record_attack_source(this->target, this->get_trap_type());
    }
}

inline void TOMineTrap::strike_actor(TObjChara *actor, TObjPlayer *owner) {
    if (actor == 0 || actor == (TObjChara *)this) {
        return;
    }
    if (actor->obj_testFlags30(0x4000800) != 0) {
        return;
    }
    if (actor->alt_room != this->alt_room && actor->room != this->room &&
        actor->room != this->alt_room) {
        return;
    }
    u16 id = get_entity_id(actor);
    if (id == 0xFFFF) {
        return;
    }
    if (id == this->get_trap_type() && TOMineTrap::get_trap_count() != 1) {
        return;
    }
    if (id < 0x1000) {
        this->strike_player(actor);
    } else if (id < 0x4000) {
        this->strike_enemy(actor, owner);
    } else if (check_value_equals__13TUnk_804B6C24Fl(actor, TOMineTrap__data_805D3080) != 0 &&
               horizontal_distance_squared(&this->position, &actor->position) < this->m_350 * this->m_350) {
        this->target = (u8 *)actor;
        ((TObjChara *)this->target)->receive_physical_attack(this, TOMineTrap__data_805DB868);
    }
}

/* Mode 0/2 watch for a victim, mode 3 counts down to the armed state and
 * mode 4 detonates against every actor in range once, then queues its own
 * destruction. */
void TOMineTrap::run_task() {
    this->update_float_height();
    switch (this->mode) {
    case 0:
    case 2:
        if (this->find_target_in_range() == 1) {
            this->set_triggered();
        }
        VecCopy(&this->body_center_position, &this->m_334);
        VecCopy(&this->bodies->center, &this->m_334);
        return;
    case 3: {
        s32 timer = this->set_params[1];
        this->set_params[1] = timer - 1;
        if (timer < 0) {
            this->set_state();
            this->send_state_packet(2);
        }
        TOMineTrap__sub_80170CD4(this);
        submit_cursor_candidate(this, -1);
        return;
    }
    case 4: {
        TObjPlayer *owner = (TObjPlayer *)get_player_by_client_id(this->get_trap_type());
        if (owner == 0) {
            owner = (TObjPlayer *)this;
        }
        for (s32 i = 0; i < lbl_805D5868; i++) {
            this->strike_actor((TObjChara *)TObjPlayer::get_player_data(i), owner);
        }
        this->mode = 5;
        this->clear_player_status_flag(0, 1);
        this->sub_8017070C();
        this->queue_destruction();
        return;
    }
    default:
        return;
    }
}

void TOMineTrap::destroy_matching_traps() {
    void *p;
    s32 i;
    for (i = registered_player_count + lbl_805D5870; i < lbl_805D5868; i++) {
        p = (void *)get_player_data__10TObjPlayerFi(i);
        if (p != 0 && check_value_equals__7TObjectFPCc(p, TOMineTrap__data_805D3080) != 0) {
            queue_destruction__7TObjectFv(p);
        }
    }
}

s32 create_placed_trap__10TOMineTrapFUiss(u32 arg0, s16 arg1, s16 arg2) {
    u16 id;
    void *player;
    if (enable_v2_features != 1 || arg0 == 0 || (id = get_entity_id((void *)arg0)) == 0xFFFF || id >= 0x1000 ||
        (player = (void *)get_player_by_client_id(id)) == 0 || ((TObjPlayer *)player)->get_floor() != get_current_floor() ||
        arg1 < 0 || arg1 >= 4 || arg2 < 0 || arg2 > 0x14) {
        return 0;
    }
    if (is_boss_area() == 1 || is_current_area_item_enabled() == 0) {
        return 0;
    }
    return (s32)new TOMineTrap((TObjPlayer *)arg0, arg1, arg2);
}

void*TOMineTrap::get_mine_data_ptr() { return (char*)this + 0x334; }

extern s32 __vt__10TOMineTrap[];

void *__dt__10TOMineTrapFv(void *arg0, s16 arg1) {
    if (arg0 != NULL) {
        *(s32 **)((s8 *)arg0 + 0x18) = __vt__10TOMineTrap;
        ((TObjCollidable *)arg0)->unregister_object_by_id();
        free_collision_body_parts(arg0);
        __dt__6TOMineFv(arg0, 0);
        if (arg1 > 0) {
            __dl__7TObjectFPv(arg0);
        }
    }
    return arg0;
}

extern void *tl_05;
extern s32 game_difficulty_selection;
extern void *lbl_805D5A50;
extern const f32 lbl_80442138[];
extern const f32 lbl_805D307C;
extern const f32 lbl_805DB86C;
extern const f32 lbl_805DB878;
extern const f32 lbl_805DB87C;
extern const f32 lbl_805DB880;
extern void *mine_collision_body_parts[];
s32 get_bml_model(void *, s32);
s32 TObjFish__sub_8001EDB0(void *, s32);
void init_collision_body_parts(void *, void *, s32);

TOMineTrap::TOMineTrap(TObjPlayer *owner, s16 trap_index, s16 trap_id) : TOMine((TObject *)tl_05) {
    TObjPlayer *owner_player;
    s32 floor;

    m_name = (const char *)TOMineTrap__data_805D3080;
    m_380 = 0;
    if (owner != 0) {
        sub_80171348(get_entity_id(owner));
    } else {
        m_2d8 = 0xFFFF;
    }
    owner_player = 0;
    if (get_trap_type() != 0xFFFF && get_trap_type() < 0x1000) {
        owner_player = (TObjPlayer *)get_player_by_client_id(get_trap_type());
    }
    // Refreshes the cached floor area before the placement checks read it.
    get_current_floor_area();
    floor = get_current_floor();
    if (enable_v2_features == 1 && owner != 0 && owner_player != 0 && owner_player->get_floor() == floor &&
        is_current_area_item_enabled() == 1 && is_boss_area() == 0) {
        switch (trap_index) {
        default:
            trap_index = 0;
        case 0:
            attack.kind = 1;
            if (((TLobby *)lobby_rule_settings)->get_rule_field_0() == 1) {
                attack.power = lbl_805D307C;
            } else {
                f32 area_scale = lbl_80442138[get_current_floor_area()];
                attack.power = lbl_805DB86C * area_scale *
                               (lbl_805DB870 * (lbl_805DB878 * owner_player->get_actor_level_index() + lbl_805DB874));
            }
            /* lbl_805DB85C is 0.0f. Naming it makes MWCC share the load in a
             * temp created before the reload of attack.power, so the compare
             * swaps f0 and f1. The literal is not shared, and the unit's
             * .sdata2 is that one constant (0x805DB85C). */
            if (attack.power < 0.0f) {
                attack.power = 0.0f;
            }
            break;
        case 1:
            attack.kind = 2;
            attack.power = lbl_805DB85C;
            break;
        case 2:
            attack.kind = 0x11;
            attack.power = lbl_805DB85C;
            break;
        case 3:
            attack.kind = 0x12;
            attack.power = lbl_805DB85C;
            break;
        }
        s32 type = (u16)get_trap_type();
        s32 idx = (s16)trap_index;
        s32 id = (s16)trap_id;
        m_37e = type * 0x50 + (idx * 0x14 + id);
        VecCopy(&m_334, VecCopy(&home_position, VecCopy(&position, &owner->position)));
        initialize_position_copies();
        calc_attach_pos();
        spawn_disp_objects();
        m_370 = owner->rotation.yaw;
        alt_room = owner->alt_room;
        room = owner->room;
        switch (attack.kind) {
        default:
            attack.kind = 1;
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 19:
            model = (void *)get_bml_model(lbl_805D5A50, 4);
            texlist = TObjFish__sub_8001EDB0(lbl_805D5A50, 4);
            m_374 = (u32)get_bml_model(lbl_805D5A50, 1);
            m_378 = (u32)TObjFish__sub_8001EDB0(lbl_805D5A50, 1);
            break;
        case 15:
        case 16:
        case 17:
        case 18:
            model = (void *)get_bml_model(lbl_805D5A50, 5);
            texlist = TObjFish__sub_8001EDB0(lbl_805D5A50, 5);
            m_374 = (u32)get_bml_model(lbl_805D5A50, 0);
            m_378 = (u32)TObjFish__sub_8001EDB0(lbl_805D5A50, 0);
            break;
        }
        mode = 0;
        m_34c = lbl_805DB87C;
        m_350 = lbl_805DB87C;
        set_params[0] = 0x96;
        set_params[1] = 0x1E;
        if (game_difficulty_selection == 3 && ((TLobby *)lobby_rule_settings)->get_rule_field_0() == 0) {
            set_params[0] = 0x3C;
            m_350 = lbl_805DB880;
            TOMineTrap::set_trap_count(0);
            TOMineTrap::set_instance(1);
        }
        m_344 = 0;
        m_35c = 0xFFFF;
        actorFlags |= 0x60000000;
        init_collision_body_parts(this, mine_collision_body_parts, 1);
        register_object_by_id();
    } else {
        queue_destruction();
    }
}

s32 TOMine::is_target_in_list(void *obj) {
    TOMine *self = this;
    if (obj != 0) {
        u32 id = get_entity_id(obj);
        if (id < 4) {
            Node_801702C8 *n;
            for (n = *(Node_801702C8 * *)&self->m_down; n != 0; n = n->next) {
                if (((TOMineTrap *)n)->matches_id(id) != 0) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

s32 TOMine::roll_physical_accuracy(void *, s32, f32) { return 1; }
s32 TOMine::try_start_action(s32, s32) { return 1; }
void TOMine::apply_knockback_from_attacker(u8 *, f32) {  }
void TOMine::vfunc_79() {  }
s32 TOMineTrap::check_trigger(u32 arg1) {
    if (is_target_in_list((void *)arg1) == 1) {
        return 0;
    }
    if (((s32) this->m_344 == 2) && (arg1 == (u32) this->target)) {
        return 0;
    }
    if (is_locally_controlled__10TObjPlayerFPv(arg1) != 0) {
        return 1;
    }
    return 0;
}
s32 TOMineTrap::can_trigger(u32 arg1) {
    if (is_target_in_list((void *)arg1) == 1) {
        return 0;
    }
    if (((s32) this->m_344 == 2) && (arg1 == (u32) this->target)) {
        return 0;
    }
    if (is_locally_controlled__10TObjPlayerFPv(arg1) != 0) {
        return 1;
    }
    return 0;
}

void TOMine::spawn_disp_objects() {
    u8 *obj;
    u16 i;
    u8 *arg0 = (u8 *)this;
    if (is_split_screen() == 0) {
        obj = (u8 *)__nw__7TObjectFUl(0xAC);
        if (obj != NULL) {
            obj = (u8 *)TOMineDisp__ct(obj, arg0, (u16)local_client_id);
        }
        if (obj != NULL) {
            VecCopy((Vec *)(obj + 0x50), (const Vec *)(arg0 + 0x50));
            VecCopy((Vec *)(obj + 0x38), (const Vec *)(arg0 + 0x38));
        }
    } else {
        for (i = 0; i != 4; i++) {
            obj = (u8 *)__nw__7TObjectFUl(0xAC);
            if (obj != NULL) {
                obj = (u8 *)TOMineDisp__ct(obj, arg0, i);
            }
            if (obj != NULL) {
                VecCopy((Vec *)(obj + 0x50), (const Vec *)(arg0 + 0x50));
                VecCopy((Vec *)(obj + 0x38), (const Vec *)(arg0 + 0x38));
            }
        }
    }
}

void TOMine::apply_object_set_data(void *set_data) {
    u8 *arg0 = (u8 *)this;
    TObjBase::apply_object_set_data(set_data);
    this->spawn_disp_objects();
    VecCopy((Vec *)(arg0 + 0x334), (const Vec *)(arg0 + 0x38));
}
void TOMine::vfunc_85() {  }
const char *TOMine::get_name() { return (const char *)get_localized_text_entry(16, 16); }
void TOMine::update_state() {
    s32 temp_r0;
    *(s32 *)((s8 *)this + 0x348) = (s32) this->scale.z;
    temp_r0 = *(s32 *)((s8 *)this + 0x348);
    if (temp_r0 < 0) {
        *(s32 *)&this->m_344 = 0;
        return;
    }
    if (temp_r0 > 0) {
        *(s32 *)&this->m_344 = 1;
        return;
    }
    if (get_main_phase() == 0xE) {
        *(s32 *)&this->m_344 = 0;
        *(s32 *)&this->set_params[2] = 0x1E;
        return;
    }
    *(s32 *)&this->m_344 = 2;
}
void TOMineTrap::spawn_effect() {
    s32 arg0 = (s32)this;
    s32 area = get_current_floor_area();
    s32 elem = *(s32 *)(mine_trap_effect_table + area * 4);
    if (elem != -1) {
        play_sound_effect((s32)(elem), (const Vec *)(arg0 + 0x38), 0, 0);
    }
}
void TOMineTrap::attach_to_keymachine() {
    s32 arg0 = (s32)this;
    s32 area = get_current_floor_area();
    s32 elem = *(s32 *)(mine_trap_keymachine_table + area * 4);
    if (elem != -1) {
        play_sound_effect((s32)(elem), (const Vec *)(arg0 + 0x38), 0, 0);
    }
}
void TOMineTrap::detonate_if_triggered() {
    s32 arg0 = (s32)this;
    {
        TParticleCtrl *particle = spawn_particle_effect((const Vec *)((arg0 + 0x2FC)), 0x45);
        if (particle != NULL) {
            particle->set_scale(lbl_805DB864, lbl_805DB864);
        }
    }
}
void TOMine::sub_8017070C() {
    spawn_particle_effect((const Vec *)(((void *) (((u8 *)this) + 0x2FC))), 0x47);
    this->vfunc_82();
    this->vfunc_80();
}

void TOMine::vfunc_6(s16 *arg1, s32 arg2) {
    s16 temp_r0;
    temp_r0 = *(s16 *)((s8 *)arg1 + 0);
    if (temp_r0 == 5) {
        if (arg2 == 1) {
            sub_8017070C();
        }
        set_flag8();
        queue_destruction__7TObjectFv((this));
        access_object_saved_state(arg1, 0);
        return;
    }
    if (temp_r0 == 3) {
        this->mode = temp_r0;
        set_indexed_flags(0, 1);
        this->actorFlags = (s32) (this->actorFlags & 0xFFFBFFFF);
        this->calc_attach_pos();
        refresh_collision_body_centers();
        this->vfunc_81();
        access_object_saved_state(arg1, 0);
        this->queue_destruction_for_each_node();
    }
}

f32 TOMine::receive_physical_attack(void *, f32) {
    s16 sp8;
    if (((u16) this->entity_id >= 0x4000U) && ((u32) this->set_entry != 0U) && (access_object_saved_state(&sp8, 1) != 0)) {
        this->mode = 5;
        sp8 = this->mode;
        send_object_state_update(&sp8);
    }
    return lbl_805DB85C;
}
f32 TOMine::receive_weapon_special_attack(void *arg1, void *) {
    if (is_target_in_list(arg1) == 1) {
        return lbl_805DB85C;
    }
    if ((is_locally_controlled__10TObjPlayerFPv((u32)arg1) != 0) && (((TObjPlayer *)arg1)->obj_getS16_116() != 0)) {
        this->receive_physical_attack(0, TOMineTrap__data_805DB868);
    }
    return lbl_805DB85C;
}

typedef struct VBase_18_33b813 VBase_18_33b813;
typedef struct VObj_18_33b813 VObj_18_33b813;
f32 TOMine::receive_direct_attack(void *arg1, DirectAttackPayload payload, void *, s32, s32) {
  s32 temp_r0;
  s32 var_r31;
  if (arg1 == 0)
  {
    return (*(const f32 *)&lbl_805DB85C);
  }
  if (this->is_target_in_list(arg1) == 1)
  {
    return (*(const f32 *)&lbl_805DB85C);
  }
  var_r31 = 0;
  if ((get_entity_id((void *) arg1) < 4U) && (is_locally_controlled__10TObjPlayerFPv((u32)((void *) arg1)) != 0))
  {
    var_r31 = 1;
  }
  if (var_r31 != 0)
  {
    temp_r0 = payload.kind;
    if (temp_r0 != 0x13)
    {
      if ((temp_r0 < 0x13) && (temp_r0 < 5))
      {
        if (temp_r0 < 0)
        {
          if ((temp_r0 && temp_r0) && temp_r0)
          {
          }
        }
        else
        {
          goto block_13;
        }
      }
    }
    else
    {
      block_13:
      (this->receive_physical_attack(0, ((*(const f32 *)&TOMineTrap__data_805DB868))));
    }
  }
  return (*(const f32 *)&lbl_805DB85C);
}

void TOMine::update_trigger() {
    s16 sp8;
    if (((u16) this->entity_id >= 0x4000U) && ((u32) this->set_entry != 0U) && (access_object_saved_state(&sp8, 1) != 0)) {
        this->mode = 3;
        sp8 = this->mode;
        send_object_state_update(&sp8);
    }
}
void TOMine::vfunc_86() {
    u8 *arg0 = (u8 *)this;
    this->mode = 2;
    ((TObjCollidable *)arg0)->set_indexed_flags(0, 1);
    this->actorFlags = (s32) (this->actorFlags & 0xFFFBFFFF);
    ((TObjChara *)arg0)->calc_attach_pos();
    ((TObjCollidable *)arg0)->refresh_collision_body_centers();
    ((TOMine *)(arg0))->vfunc_81();
}

typedef struct Stack_80170AC8 Stack_80170AC8;
void TOMine::follow_target() {
    u8 *arg0 = (u8 *)this;
  unsigned short new_var;
  Stack_80170AC8 stack;
  f32 temp_f2;
  new_var = -1U;
  if (((this->m_35c) == new_var) || ((this->target) == 0))
  {
    this->mode = 2;
    return;
  }
  VecCopy((Vec *)(arg0 + 0x44), (const Vec *)(arg0 + 0x38));
  VecCopy((Vec *)(&stack.sp8), &this->target->position);
  stack.spC = *((f32 *) (((s8 *) arg0) + 0x3C));
  subtract_vector(&stack.sp8, (u8 *)&this->position);
  if (lbl_805DB870 < vec_squared_length((u8 *)&stack.sp8))
  {
    normalize_vector(&stack.sp8);
    stack.sp8 *= lbl_805DB870;
    stack.sp10 *= lbl_805DB870;
  }
  vec3_add_to((u8 *)&this->position, &stack.sp8);
  ((TObjPlayer *)arg0)->update_enemy_collision_flags();
  temp_f2 = *((f32 *) (((s8 *) arg0) + 0x48));
  *((f32 *) (((s8 *) arg0) + 0x3C)) = (f32) ((lbl_805DB884 * ((lbl_805DB888 + this->target->position.y) - temp_f2)) + temp_f2);
  ((TObjChara *)arg0)->calc_attach_pos();
  this->rotation.yaw = (s32) (lbl_80442200 * atan2_float((f64) stack.sp8, (f64) stack.sp10));
  ((TObjCollidable *)arg0)->refresh_collision_body_centers();
}

void TOMine::sub_80170BEC() {
    u8 *p;
    s32 i;
    switch (this->phase) {
    case 0:
        this->phase = 1;
        for (i = lbl_805D5870; i < lbl_805D5868; i++) {
            p = (u8 *)get_player_data__10TObjPlayerFi(i);
            if (p != NULL && p != ((u8 *)this) &&
                (check_value_equals__7TObjectFPCc(p, TOMineIcon01__name) != 0 ||
                 check_value_equals__7TObjectFPCc(p, TOMineIcon02__name) != 0 ||
                 check_value_equals__7TObjectFPCc(p, TOMineIcon03__name) != 0 ||
                 check_value_equals__7TObjectFPCc(p, TOMineIcon04__name) != 0) &&
                *(s32 *)(p + 0x344) == 1 && *(s32 *)(p + 0x348) == *(s32 *)(((u8 *)this) + 0x348)) {
                ((TOMine *)p)->update_trigger();
            }
        }
        break;
    }
    ((TOMineTrap *)((u8 *)this))->sync_position();
}

void TOMineTrap__sub_80170CD4(void* p) { ((TOMineTrap *)p)->sync_position(); }

void TOMine::update_float_height() {
    u8 *arg0 = (u8 *)this;
    f32 temp_f1;
    f32 temp_f4;
    if (!(this->m_340 & 2)) {
        temp_f4 = *(f32 *)((s8 *)arg0 + 0x338);
        *(f32 *)((s8 *)arg0 + 0x338) = (f32) (temp_f4 + ((lbl_805DB884 * ((lbl_805DB888 + this->home_position.y) - temp_f4)) + (*(const f32 *)&TOMineTrap__data_805DB868)));
        temp_f1 = lbl_805DB888 + this->home_position.y;
        if (temp_f1 <= *(f32 *)((s8 *)arg0 + 0x338)) {
            *(f32 *)((s8 *)arg0 + 0x338) = temp_f1;
            this->m_340 = (s32) (this->m_340 | 2);
        }
    } else {
        *(s32 *)&this->rotation.pitch = (s32) (*(s32 *)&this->rotation.pitch + 0x800);
        *(f32 *)((s8 *)arg0 + 0x338) = (f32) (*(f32 *)((s8 *)arg0 + 0x338) + sin_table_lookup(*(s32 *)&this->rotation.pitch));
    }
}

void TOMineTrap::sync_position() { VecCopy((Vec *)((char*)this + 0x38), (const Vec *)((char*)this + 0x334)); refresh_collision_body_centers(); }
void TOMine::detonate() {
    s32 i;
    u8 *obj;
    set_indexed_flags(0, 2);
    *(f32 *)(*(u8 * *)&this->bodies + 0xC) = this->m_350;
    TObjPlayer::init_all_slots();
    ((TObjPlayer *)((u8 *)this))->check_object_collisions();
    check_enemy_body_collisions(this);
    for (i = 0; i < 0x10; i++) {
        obj = get_battle_param__10TObjPlayerFi(i);
        if (TObjPlayer::is_valid_and_active((u32)obj) != 0) {
            DirectAttackPayload pair = this->attack;
            f32 r = ((VObj_18_1da615 *)obj)->m21(this, &pair, 0, -1, -1);
            if (this->attack.kind < 5) {
                ((VObj_18_1da615 *)obj)->m23(this, lbl_805DB874 * r);
            }
        }
    }
    this->mode = 6;
    this->clear_player_status_flag(0, 1);
    this->receive_physical_attack(0, TOMineTrap__data_805DB868);
}

}

