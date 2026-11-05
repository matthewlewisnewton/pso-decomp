#include <stdlib.h>
#include "pso/player/demo_mode.h"
#include "pso/system/CurrentTextureList.h"
#include "pso/misc/PersistentSound.h"
#include "pso/system/SoundEffect.h"
#include "pso/math/ScratchVectorStorage.h"
#include "types.h"
#include "pso/system/BmlResourceClass.h"
#include "pso/system/BmlResourceDescriptor.h"
#include "pso/misc/TKeyBoardControl_8000F764.h"
#include "pso/misc/TOTrap_801791EC.h"
#include "pso/object/TObject_80019A50.h"
#include "pso/player/TObjPlayer_800D7BFC.h"
#include "pso/object/TObjMotion.h"
#include "pso/player/TObjChara.h"
#include "pso/misc/TOTrapAncient02R.h"
#include "pso/misc/TOTrap.h"
#include "pso/misc/TOTrapAncient01.h"
#include "pso/TParticleCtrl.h"
#include "pso/misc/RenderFadeState.h"
#include "pso/misc/TMotorcycle.h"
#include "pso/misc/TRaderMapCore.h"
#include "pso/object/TObjFish.h"
#include "pso/player/TObjPlayer.h"
#include "pso/ui/TAdSinglePlyChrSelectGC.h"
#include "pso/map/FloorArea.h"
#include "pso/TObjChip.h"
#include "pso/misc/TCameraCtrl.h"
#include "pso/TMainTask.h"
#include "pso/misc/ParticleFactory.h"
#include "pso/player/TObjPlayer_801AF2F0.h"
#include "pso/render/render_util.h"
#include "pso/system/MatrixStack.h"
#include "pso/system/GinjaMaterial.h"
#include "pso/math/MatrixTransforms.h"
#include "pso/unk/text_803D8F74.h"
#include "pso/unk/text_800FD8A0.h"


extern "C" {
u16 get_entity_id(TObjBase *);
void obj_set_flag_20000(TObjBase *);
void obj_clear_flag30_20000(TObjBase *);
// Trap callers show this receiver is not restricted to TObjEnemy.
u16 find_nearest_visible_player(void *, Vec *, f32);
s32 obj_is_hit_receivable(u8 *);

s32 check_player_flag1__6TLobbyFv();
extern s32 local_client_id;
s32 TObjFish__sub_8001EDB0(void *, s32);
s32 get_bml_model(void *, s32);
const char *bm_o_trap_ancient01_model_names[] = {
    "fe_obj_o_turigane_hahen01.gj", "fe_obj_o_turigane_hahen02.gj",
    "fe_obj_o_turigane_hahen03.gj", "fs_obj_o_turigane.gj", NULL
};
const char *bm_o_trap_ancient01_motion_names[] = {NULL};
BmlResourceDescriptor bm_o_trap_ancient01_resource_descriptor = {
    "bm_o_trap_ancient01.bml", bm_o_trap_ancient01_model_names,
    bm_o_trap_ancient01_motion_names, 4, 0
};
CollisionBody lbl_804B4844 = {
    {0.0f, 20.0f, 0.0f}, 14.0f, 0.0f, 0, 0x08011f04,
    {0.0f, 0.0f, 0.0f}, 0.0f
};
const char *TOTrapAncient01__class_name = "TOTrapAncient01";
// The original symbol reserves eight bytes; only the first word is accessed here.
struct AncientTrapResourceSlot { BmlResource *value; u8 reserved[4]; };
AncientTrapResourceSlot TOTrapAncient01__bml_resource;
f32 TObjPlayer__sub_8017A1A4(TObjCollidable *self, s32 i);
s32 free_collision_body_parts(void *);
extern s32 __vt__15TOTrapAncient01[];
s32 init_collision_body_parts(void *, void *, int);
void TOTrap__ct(void *, void *, void *);
void __construct_array(void *, void *, void *, int, int);
void __ct__15RenderFadeStateFv(void *);
s32 check_value_equals__13TUnk_804B6C24Fl(void *, s32);

extern s32 lbl_805D3530;
s32 is_split_screen();
extern s32 model_render_flags;
extern s32 saved_model_render_flags;
extern s32 saved_chunk_polygon_flags_and_mask;
extern s32 saved_chunk_polygon_flags_or_mask;
extern s32 chunk_polygon_flags_or_mask;
extern s32 chunk_polygon_flags_and_mask;
void TOTrapAncient02R__sub_80154D78(void *);


// Reverse definitions with deferred generation reproduce this unit's original
// function order and place the native vtable before the switch tables.
// This describes compiler emission, not a claim about the historical source.

void TOTrapAncient02R::vfunc_86() {
    s32 x;
    x = is_current_room(this);
    if (x == 1) {
        fn_80141CF0(&this->home_position, &scratch_vec.vector, &trap_ancient_light_color);
        TOTrapAncient02R__sub_80154D78(this);
    }
}

f32 TObjPlayer__sub_8017A1A4(TObjCollidable *self, s32 i) {
    return self->bodies[i].radius;
}

// The original exports this constructor under the C name TOTrapAncient01__ct,
// so it is not a C++ ctor the compiler can set the vtable pointer for.
TOTrapAncient01 *TOTrapAncient01__ct(TOTrapAncient01 *self, void *parent, void *creator) {
    s32 i;
    TOTrap__ct(self, parent, creator);
    *(s32 **)((s8 *)self + 0x18) = __vt__15TOTrapAncient01;
    __construct_array(self->fades, (void *)__ct__15RenderFadeStateFv, (void *)__dt__15RenderFadeStateFv, sizeof(RenderFadeState), 4);
    self->m_name = TOTrapAncient01__class_name;
    self->apply_object_set_data((void *)((s32)creator));
    self->initialize_position_copies();
    self->calc_attach_pos();
    self->model = (void *)get_bml_model(TOTrapAncient01__bml_resource.value, 3);
    self->texlist = TObjFish__sub_8001EDB0(TOTrapAncient01__bml_resource.value, 3);
    self->mode = 0;
    self->range = 0.5f * self->scale.x + 30.0f;
    if (self->scale.y < 0.0f) {
        self->scale.y = 0.0f;
    }
    if (self->scale.z < 1.0f) {
        self->scale.z = 1.0f;
    }
    self->m_34C = -self->scale.y / self->scale.z;
    self->m_350 = 30.0f + (f32)self->set_params[2];
    if (get_main_phase() == 0xE) {
        self->m_350 *= 0.33f;
    }
    if (self->m_350 < 0.0f) {
        self->m_350 = 0.0f;
    }
    self->m_354 = self->m_350;
    if (self->set_params[0] < 0) {
        self->set_params[0] = 0;
    }
    self->attack.power = self->vfunc_87((f32)self->set_params[0]);
    if (self->set_params[1] < 0) {
        self->set_params[1] = 0;
    } else if (self->set_params[1] > 5) {
        self->set_params[1] = 5;
    }
    self->attack.kind = self->set_params[1];
    self->dist = 15.0f;
    self->player = 0xFFFF;
    init_collision_body_parts(self, &lbl_804B4844, 1);
    self->refresh_collision_body_centers();
    self->actorFlags |= 0x60040000;
    self->get_or_assign_entity_id(0);
    self->register_object_by_id();
    for (i = 0; i < 4; i++) {
        self->fades[i].activate_and_dispatch();
    }
    return self;
}

TOTrapAncient01::~TOTrapAncient01() {
    unregister_object_by_id();
    free_collision_body_parts(this);
}

void TOTrapAncient01::load_resources() {
  TOTrapAncient01__bml_resource.value = new BmlResource(1, &bm_o_trap_ancient01_resource_descriptor, 0, 0, NULL);
  TMotorcycle::add_entry(0x39, get_bml_model(TOTrapAncient01__bml_resource.value, 3), TObjFish__sub_8001EDB0(TOTrapAncient01__bml_resource.value, 3), 20.0f, 0.0f);
}

void TOTrapAncient01::release_static_resource() {
    if (TOTrapAncient01__bml_resource.value != NULL) {
        delete TOTrapAncient01__bml_resource.value;
        TOTrapAncient01__bml_resource.value = NULL;
    }
}

void *TOTrapAncient01::create() {
    TOTrapAncient01 *o = (TOTrapAncient01 *)TObject::operator new(sizeof(TOTrapAncient01));
    if (o != NULL) {
        o = TOTrapAncient01__ct(o, tl_05, this);
    }
    return o;
}

void TOTrapAncient01::render() {
    RenderFadeState *fade;
    NJS_OBJECT *n;
    s32 i;
    Vec v;
    i = 0;
    if (is_split_screen() != 0) {
        i = TCameraCtrl::get_camera_mode();
    }
    fade = &fades[i];
    fade->update();
    m_340 = update_object_view_visibility(400.0f, 20.0f);
    if (m_340 == 1) {
        if (fade->updateFromCamera(&position.x) == 1) {
            saved_model_render_flags = model_render_flags;
            saved_chunk_polygon_flags_and_mask = chunk_polygon_flags_and_mask;
            saved_chunk_polygon_flags_or_mask = chunk_polygon_flags_or_mask;
            fade->set_flags_and_apply_damage_color();
        }
        push_matrix();
        post_translate_matrix(&position.x);
        rotate_matrix_y(0, rotation.yaw);
        if (check_demo_mode() != 1 && scale.y <= 0.0f) {
            v.x = 0.1f * (0.000030517578125f * (f32)rand()) - 0.05f;
            v.y = 0.0f;
            v.z = 0.1f * (0.000030517578125f * (f32)rand()) - 0.05f;
            post_translate_matrix(&v.x);
        }
        set_current_texture_list((GinjaTextureList *)texlist);
        n = (NJS_OBJECT *)model;
        push_matrix();
        translate_matrix(0, 0.0f, scale.y, 0.0f);
        post_translate_matrix(n->pos);
        draw_ginja_model((s32)((NJS_OBJECT *)model)->model);
        n = n->child;
        push_matrix();
        post_translate_matrix(n->pos);
        TParticleCtrl::begin_effect_render();
        draw_ginja_model((s32)n->model);
        TParticleCtrl::end_effect_render();
        pop_matrix();
        pop_matrix();
        pop_matrix();
        if (fade->updateFromCamera(&position.x) == 1) {
            fade->clear_flag_and_notify();
            chunk_polygon_flags_and_mask = saved_chunk_polygon_flags_and_mask;
            chunk_polygon_flags_or_mask = saved_chunk_polygon_flags_or_mask;
            model_render_flags = saved_model_render_flags;
        }
    }
}

void TOTrapAncient01::vfunc_81() {
    f32 &step = this->m_34C;
    scale.y += step;
    if (!(0.0f < scale.y)) {
        goto grounded;
    }
    switch (get_current_floor_area()) {
        case AREA_CAVE1: case AREA_CAVE2: case AREA_CAVE3:
            play_persistent_sound(0x4321a, this, &position, 0, 0);
            return;
        case AREA_MINE1: case AREA_MINE2:
            play_persistent_sound(0x4004b211, this, &position, 0, 0);
            return;
        case AREA_RUINS1: case AREA_RUINS2: case AREA_RUINS3:
            play_persistent_sound(0x4004b217, this, &position, 0, 0);
            return;
        case AREA_VR_SPACESHIP_ALPHA: case AREA_VR_SPACESHIP_BETA:
            play_persistent_sound(0x4004b212, this, &position, 0, 0);
            return;
// Keep the grounded path inside the switch's lexical extent so no-op case
// labels below bind directly to the common epilogue. Moving it outside creates
// a branch thunk and changes the compiler-generated jump-table relocations.
grounded:
    {
        this->mode = 3;
        scale.y = 0.0f;
        calc_attach_pos();
        clear_player_status_flag(0, 0x08001f04);
        set_indexed_flags(0, 0x8003);
        obj_clearFlags30(0x40000);
        spawn_particle_effect(&position, 0x8f);
        spawn_particle_effect(&position, 0x8f);
        player = find_nearest_visible_player(this, NULL, range);
        if (player != 0xffff) {
            TObjPlayer *p = (TObjPlayer *)get_player_by_client_id(player);
            target = (u8 *)p;
            if (target != NULL) {
                f32 d = horizontal_distance_squared(&((TObjPlayer *)target)->position, &position);
                dist -= TObjPlayer__sub_8017A1A4(p, 0);
                if (d < dist * dist) {
                    if (TObjPlayer::is_locally_controlled(target)) {
                        send_6x2C_impose_hold(p, &position, -1, 0, dist);
                        obj_set_flag_20000(p);
                    }
                } else {
                    player = 0xffff;
                    target = NULL;
                }
            }
        } else {
            target = NULL;
        }
    }
        case AREA_PIONEER2_EP1:
            return;
        case AREA_FOREST1:
        case AREA_FOREST2:
        case AREA_DRAGON:
        case AREA_DE_ROL_LE:
        case AREA_VOL_OPT:
        case AREA_DARK_FALZ:
        case AREA_LOBBY:
        case AREA_BATTLE1:
        case AREA_BATTLE2:
        case AREA_PIONEER2_EP2:
        case AREA_VR_TEMPLE_ALPHA:
        case AREA_VR_TEMPLE_BETA:
            return;
    }
}

void TOTrapAncient01::vfunc_82() {
    s32 i;
    TObjChara *p;
    calc_attach_pos();
    m_354 -= 1.0f;
    if (m_354 < 0.0f) {
        bodies->radius = 15.0f;
        set_indexed_flags(0, 0x100);
        TObjPlayer::init_all_slots();
        check_object_collisions();
        for (i = 0; i < 16; i++) {
            p = (TObjChara *)TObjPlayer::get_battle_param(i);
            if (p == NULL) {
                break;
            }
            if (obj_is_hit_receivable((u8 *)p) == 0) {
                break;
            }
            if (check_value_equals__13TUnk_804B6C24Fl(p, lbl_805D3530) == 0) {
                break;
            }
            p->receive_direct_attack(this, attack, NULL, -1, -1);
            if (attack.kind < 5) {
                p->apply_knockback_from_attacker((u8 *)this, 0.0f);
            }
        }
        receive_physical_attack(target, 1.0f);
    }
    submit_cursor_candidate(this, -1);
    switch (get_current_floor_area()) {
    case AREA_RUINS1:
    case AREA_RUINS2:
    case AREA_RUINS3:
        play_persistent_sound(0x4004C618, this, &position, 0, 0);
        break;
    case AREA_VR_SPACESHIP_ALPHA:
    case AREA_VR_SPACESHIP_BETA:
        play_persistent_sound(0x4004C610, this, &position, 0, 0);
        break;
    case AREA_PIONEER2_EP1:
        return;
    case AREA_FOREST1:
        break;
    case AREA_FOREST2:
        return;
    case AREA_CAVE1:
        break;
    case AREA_CAVE2:
        return;
    case AREA_CAVE3:
        break;
    case AREA_MINE1:
        return;
    case AREA_MINE2:
        break;
    case AREA_DRAGON:
        break;
    case AREA_DE_ROL_LE:
        return;
    case AREA_VOL_OPT:
        break;
    case AREA_DARK_FALZ:
        return;
    case AREA_LOBBY:
        break;
    case AREA_BATTLE1:
        return;
    case AREA_BATTLE2:
        break;
    case AREA_PIONEER2_EP2:
        return;
    case AREA_VR_TEMPLE_ALPHA:
        break;
    case AREA_VR_TEMPLE_BETA:
        return;
    }
}

void TOTrapAncient01::vfunc_84() {  }

f32 TOTrapAncient01::receive_physical_attack(void *arg1, f32 farg0) {
    this->release_trapped_player();
    return TOTrap::receive_physical_attack(arg1, farg0);
}

void TOTrapAncient01::play_sounds() {
    const TObjChipParams a = {
        {0.5f, 0.03f, 0.15f}, {position.x, position.y, position.z},
        {3.0f, 5.0f, 3.0f}, {0x800, 0x100, 0x800}, {4, 30},
        {position.y, 1.0f},
        get_bml_model(TOTrapAncient01__bml_resource.value, 0),
        TObjFish__sub_8001EDB0(TOTrapAncient01__bml_resource.value, 0), 22
    };
    const TObjChipParams b = {
        {0.5f, 0.03f, 0.15f}, {position.x, position.y, position.z},
        {3.0f, 5.0f, 3.0f}, {0x800, 0x100, 0x800}, {4, 30},
        {position.y, 1.0f},
        get_bml_model(TOTrapAncient01__bml_resource.value, 1),
        TObjFish__sub_8001EDB0(TOTrapAncient01__bml_resource.value, 1), 22
    };
    const TObjChipParams c = {
        {0.5f, 0.03f, 0.15f}, {position.x, position.y, position.z},
        {3.0f, 5.0f, 3.0f}, {0x800, 0x100, 0x800}, {4, 30},
        {position.y, 1.0f},
        get_bml_model(TOTrapAncient01__bml_resource.value, 2),
        TObjFish__sub_8001EDB0(TOTrapAncient01__bml_resource.value, 2), 22
    };
    new TObjChip(tl_06, const_cast<TObjChipParams *>(&a));
    new TObjChip(tl_06, const_cast<TObjChipParams *>(&b));
    new TObjChip(tl_06, const_cast<TObjChipParams *>(&c));
    TParticleCtrl *particle = spawn_particle_effect(&position, 0x8b);
    if (particle != NULL) particle->set_scale(1.25f, 1.25f);
    switch (get_current_floor_area()) {
    case AREA_SEABED_UPPER: case AREA_SEABED_LOWER:
        play_sound_effect(0x4004c118, &position, 0, 0); return;
    case AREA_VR_TEMPLE_ALPHA: case AREA_VR_TEMPLE_BETA:
        play_sound_effect(0x4bc07, &position, 0, 0); return;
    case AREA_VR_SPACESHIP_ALPHA: case AREA_VR_SPACESHIP_BETA:
        play_sound_effect(0x4004bc07, &position, 0, 0); return;
    case AREA_SEASIDE_NIGHT:
        play_sound_effect(0x4004bc19, &position, 0, 0); return;
    case AREA_TOWER:
        play_sound_effect(0x4004bc19, &position, 0, 0); return;
    case AREA_CENTRAL_CONTROL_AREA: case AREA_JUNGLE_NORTH:
    case AREA_JUNGLE_EAST: case AREA_MOUNTAIN: case AREA_SEASIDE:
    case AREA_GAL_GRYPHON: case AREA_OLGA_FLOW: case AREA_BARBA_RAY:
    case AREA_GOL_DRAGON:
        break;
    }
    play_sound_effect(0x4004bc12, &position, 0, 0);
}

void TOTrapAncient01::release_trapped_player() {
    s32 temp_r3;
    s32 temp_r3_2;
    if (TRaderMapCore::is_not_split_screen() == 1) {
        if (this->target != NULL) {
            temp_r3 = (s32)get_player_by_client_id((get_entity_id((TObjBase *)this->target)));
            if (temp_r3 != 0) {
                if (check_player_flag1__6TLobbyFv() != 0) {
                    TObjPlayer::send_code_45_1(temp_r3);
                }
                obj_clear_flag30_20000((TObjBase *)temp_r3);
            }
        }
    } else if ((this->target != NULL) && ((s32) local_client_id == (s32) get_entity_id((TObjBase *)this->target))) {
        temp_r3_2 = (s32)get_player_by_client_id(local_client_id);
        if (temp_r3_2 != 0) {
            if (check_player_flag1__6TLobbyFv() != 0) {
                TObjPlayer::send_code_45_1(temp_r3_2);
            }
            obj_clear_flag30_20000((TObjBase *)temp_r3_2);
        }
    }
}

void TOTrapAncient01::vfunc_6(s16 *arg1, s32 arg2) {
    if ((s16) *arg1 == 4) {
        if (arg2 == 1) {
            this->play_sounds();
        }
        this->release_trapped_player();
        set_flag8();
        queue_destruction();
    }
}

void TOTrapAncient01::vfunc_88() {  }

void TOTrapAncient01::vfunc_86() {  }

void TOTrap::apply_knockback_from_attacker(u8 *, f32) {  }

}
